/*
Si scriva un programma con tre thread che risolvono il seguente problema: Un buffer di n elementi inizializzato con a -1 viene riempito nel seguente modo:
• Il primo thread aggiunge nelle posizioni pari del buffer un numero casuale da 0 a 100.
• Il secondo thread aggiunge nelle posizioni dispari del buffer un casuale da 100 a 200.
• Il terzo thread somma gli elementi e modifica il buffer nel seguente modo:
buff[0] = buff[0]; buff[1] = buff[1] + buff[0]; buff[2] = buff[1] + buff[2]. Si proponga una soluzione di mutua esclusione.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //serve per sys call
#include <time.h>

#define N 10

int buffer[N] = {0};
pthread_mutex_t mutex;

void *add_pari(void *arg){
    srand(time(NULL));
    while(1){
        pthread_mutex_lock(&mutex);
        int index = rand() % N;
        if(index % 2 == 0){
            buffer[index] = rand() % 101;
        }
        pthread_mutex_unlock(&mutex);
        int sleeptime = rand() % 5;
        sleep(sleeptime);
        
    }
}

void *add_dispari(void *arg){
    srand(time(NULL));
    while(1){
        pthread_mutex_lock(&mutex);
        int index = rand() % N;
        if(index % 2 != 0){
            buffer[index] = rand() % 101 + 100;
        }
        pthread_mutex_unlock(&mutex);
        int sleeptime = rand() % 5;
        sleep(sleeptime);
    }
}

void *sum_num(void *arg){
    while(1){
        pthread_mutex_lock(&mutex);
        printf("buffer: ");
        for(int i=0; i < N; i++){
            printf("%d ", buffer[i]);
        }
        printf("\n");

        for(int i=0; i < 3; i++){
          if (i == 0){
            buffer[i] = buffer[i];
          }  
          else
            buffer[i] = buffer[i] + buffer[i-1];
        }

         printf("buffer modificato: ");
        for(int i=0; i < N; i++){
            printf("%d ", buffer[i]);
        }
        printf("\n");

        pthread_mutex_unlock(&mutex);
        int sleeptime = rand() % 5;
        sleep(sleeptime);
    }
}

int main() {
    pthread_t threads[3];
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&threads[0], NULL, add_pari, NULL);
    pthread_create(&threads[1], NULL, add_dispari, NULL);
    pthread_create(&threads[2], NULL, sum_num, NULL);

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
        printf("Thread %i terminated.\n", i);
    }


    pthread_mutex_destroy(&mutex);
    return 0;
}
