//Scrivere un programma che esegue la moltiplicazione tra matrici 3x3 usando la programmazione parallela.
//Il primo processo figlio computa la prima colonna.
//Il secondo processo figlio computa la seconda colonna.
//Il processo padre computa la terza colonna e riceve dai figli i due vettori colonna computati e compone la matrice finale e la stampa.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){
    int matrice[3][3];
    pid_t p1, p2;
    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);
    
    
    p1 = fork();
    if(p1<0){
        perror("errore nella creazione della prima pipe\n");
        exit(1);
    }
    if (p1==0){   //creazione figlio1
        srand(getpid());
        int array1[3];
        close(pipe1[0]);
        for(int i=0;i<3;i++){    
            int num = rand() % 50;
            array1[i]= num; 
        }
        write(pipe1[1], array1, (sizeof(int))*3);
        close(pipe1[1]);
        exit(0);
    }
    if(p1>0){  //padre
        p2 = fork();
        if (p2<0)
        {
            perror("errore nella creazione del 2 figlio");
            exit(1);
        }
        
        if(p2==0){//figlio2
            srand(getpid());
            int array2[3];
            close(pipe2[0]);
            for(int i=0;i<3;i++){
                int num = rand() % 50;
                array2[i]= num; 
            }

            write(pipe2[1], array2, (sizeof(int))*3);
            close(pipe2[1]);
            exit(0);
        }
        else if(p2>0){//padre
            close(pipe1[1]);
            close(pipe2[1]);
            int array1ricevuto[3], array2ricevuto[3];

            srand(getpid());
            for(int i = 0;i<3;i++){
                matrice[i][2] = rand() % 50;
            }

            read(pipe1[0], array1ricevuto, (sizeof(int))*3 );
            read(pipe2[0], array2ricevuto, (sizeof(int))*3 );

            for(int i = 0;i<3;i++){
                matrice[i][0] = array1ricevuto[i];
            }

            for(int i = 0;i<3;i++){
                matrice[i][1] = array2ricevuto[i];
            }

            for(int i = 0;i<3;i++){
                for(int j=0;j<3;j++){
                    printf("%d ",matrice[i][j]);
                }
                printf("\n");
            }
            close(pipe1[0]);
            close(pipe2[0]);
            exit(0);


        }
    
    
}
}