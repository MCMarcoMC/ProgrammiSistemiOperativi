/*
Un processo padre genera 2 processi figli
    -il primo processo figlio invia al padre  numero casuale 0 a 100
    -il padre legge questo numero, lo moltiplica per un k casuale e lo manda al secondo figlio.
    -il decondo figlio legge il numero inviato dal padre e lo stampa a video
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main(){
    pid_t pid1,pid2;
    int pipe1[2], pipe2[2];
    int num = 0, k = rand() % 6;
    srand(getpid()); 

    if(pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Errore nella creazione delle pipe");
        exit(0);
    }
    
    pid1 = fork();
    if(pid1<0){     //figlio1 fallito
        perror("errore nella creazione del primo processo");
        exit(0);
    }
    else if(pid1==0){     //figlio1 creato
        close(pipe1[0]);
        num = rand() % 101;
        write(pipe1[1], &num,sizeof(num));
        close(pipe1[1]);
        exit(0);
    }
    else{ //padre
        close(pipe1[1]);
        read(pipe1[0], &num , sizeof(num));
        int n = num * k;
        close(pipe1[0]);

        write(pipe2[1], &n, sizeof(n));
        close(pipe2[1]);

        pid2 = fork(); //errore figlio2
        if(pid2 < 0){
            perror("errore nella creazione del secondo processo");
            exit(0);
        }
        else if(pid2 == 0){//figlio2 creato
            close(pipe2[1]);
            read(pipe2[0], &n, sizeof(n));
            printf("il valore inviato dal padre è: %d\n",n);
            close(pipe2[0]);
            exit(0);
        }
    }
}