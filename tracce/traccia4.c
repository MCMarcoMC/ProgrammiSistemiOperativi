
/*Due processi leggono dallo stesso file che si trova all’interno di una directory, (es. /data/file.txt).
Controllare che il file sia in modalità lettura, altrimenti restituire errore.
• Il primo processo legge dall’inizio del file fino a metà,
• Il secondo legge dalla metà in poi. I figli mandano il contenuto al padre
• Il padre lo stampa nel seguente formato: [PID_FIGLIO] -> TESTO*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#define size 600 //se supero il numero 1016 mi aggiunge cose a caso hahahah

int main(int argc,char *argv[]){

    if(argc!=2) printf("inserisci: %s namefile.ext", argv[0]);
    int fd=open(argv[1],O_RDONLY);
    struct stat st;

    if (stat(argv[1], &st) == -1) {
        perror("stat");
        return 1; 
    }
    if ((st.st_mode & S_IRUSR)) {
        printf("Il proprietario ha il permesso di lettura\n");
    }
    else {
        perror("non hai il pemesso in lettura");
    }    
    char buffer[size];
    int pipe1[2];
    pipe(pipe1);
    
    pid_t p1,p2;
    p1=fork();

    if (p1==0){//figlio 1

        read(fd,&buffer,st.st_size/2);
        printf("la prima metà in p1 è :%s\n",buffer);
        //printf("la dimensione della prima metà è: %ld\n",st.st_size/2);
        close(pipe1[0]);
        write(pipe1[1],&buffer,sizeof(buffer));
        close(pipe1[1]);
        exit(0);
    }
    if(p1>0){ //padre
    
    int pipe2[2];
    pipe(pipe2);

        p2=fork();
        if (p2==0){//figlio 2
            
            lseek(fd, st.st_size/2, SEEK_SET);
            read(fd,&buffer,st.st_size/2);
            close(pipe2[0]);
            write(pipe2[1],&buffer, sizeof(buffer));
            close(pipe2[1]);
            printf("la seconda metà in p2 è: %s\n",buffer);
            //printf("la dimensione della prima metà è: %ld\n",st.st_size/2);
            exit(0);
        }
        else{//padre
            int status1, status2;
            waitpid(p1,&status1,0); 
            close(pipe1[1]);
            read(pipe1[0],&buffer, sizeof(buffer));
            close(pipe1[0]);
            printf("la prima metà ricevuta è:%s\n\n",buffer);

            waitpid(p2,&status2,0);
            close(pipe2[1]);
            read(pipe2[0],&buffer, sizeof(buffer));
            close(pipe2[0]);
            printf("la seconda metà ricevuta è:%s\n",buffer);
            //exit(0);
        }
    }
    return 0;
    }
