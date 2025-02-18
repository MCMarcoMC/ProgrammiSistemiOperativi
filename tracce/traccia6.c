/*
Generare due processi figli che cmunicano con il padre:
    - uno dei processi genera numeri casuali [0-50] ed invia al padre solo i numeri multipli di 3
    - l'altro processo genera numeri casuali [51-100] ed invia al padre solo i multipli di 2
    - il padre stampa i numeri ricevuti ed esegue la loro somma quando la somma > 130
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main() {
    pid_t pid1, pid2;
    int pipe1[2];
    int pipe2[2];
    int num = 0;

    if(pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Errore nella creazione delle pipe");
        exit(0);
    }

    pid1 = fork();
    if(pid1 < 0){  //errore figlio1
        perror("errore nella creazione del primo processo");
    }
    if(pid1 == 0){ //figlio1
        close(pipe1[0]);
        srand(getpid());
        for(int i=0; i<=10; i++){
            num = rand() % 51;
            if (num % 3 == 0)
                write(pipe1[1], &num, sizeof(num));
        }
        close(pipe1[1]);
        exit(0);
            
    }
   
    if(pid1 >= 0){ //padre
        int sum1 = 0, sum2 = 0;

        close(pipe1[1]);
        while(read(pipe1[0],&num, sizeof(num)) > 0){
            printf("Ricevuto dal 1 figlio: %d\n", num);
            sum1 += num;
        }
        close(pipe1[0]);

        pid2 = fork();
        if(pid2 < 0){ //errore figlio2
            perror("errore nella creazione del secondo processo");
        }

        else if(pid2 == 0){ //figlio2
            close(pipe2[0]);
            srand(getpid());
            for(int i=0; i<=10; i++){
                num = rand() % 50 + 51;
                if (num % 2 == 0)
                    write(pipe2[1], &num, sizeof(num));
            }
            close(pipe2[1]);
            exit(0);
            
            
        }
        close(pipe2[1]);
        while(read(pipe2[0],&num, sizeof(num)) > 0){
            printf("Ricevuto dal 2 figlio: %d\n", num);
            sum2 += num;
        }
        close(pipe2[0]);

        if((sum1+sum2)>500){
            printf("la somma dei nueri è: %d\n", sum1+sum2);
        }
        else
            printf("la somma dei numeri non supera 500\n");

    }
    return 0;
}