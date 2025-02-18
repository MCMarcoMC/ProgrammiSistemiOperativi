#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_size 1024
#define READ 0
#define WRITE 1

int main(void) {
    int pipe1[2];
    pipe(pipe1);
    pid_t pid1 = fork();

    char messaggio[BUFFER_size];

    if (pid1 == 0) { // Processo figlio 1
        char messaggio[] = "Ciao";
        write(pipe1[1],messaggio, sizeof(messaggio));
        close(pipe1[1]);




    }else { // Processo padre
        pid_t pid2 = fork();
        if (pid2==0){
            read(pipe1[0],messaggio, sizeof(messaggio));
            close(pipe1[0]);
            printf("Ho ricevuto il messaggio: %s\n",messaggio);

        }




    else { // Processo padre
        close(pipe1[0]);
        close(pipe1[1]);

    }

    }return 0;
}