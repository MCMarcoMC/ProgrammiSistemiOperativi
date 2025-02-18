/*
Scrivere un programma in C che data una stringa di N caratteri crea N/2 threads 
che stampano ciascuno un carattere della stringa in maiuscolo. (Semafori binari o mutex)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

#define N 3
pthread_mutex_t mutex;

char parola[] = "parola";

void *thread1(){
    srand(getpid());
    pthread_mutex_lock(&mutex);
    int index = rand() % strlen(parola);
    printf("trhead1: %c\n", toupper(parola[index]));
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *thread2(){
    srand(getpid());
    pthread_mutex_lock(&mutex);
    int index = rand() % strlen(parola);
    printf("trhead2: %c\n", toupper(parola[index]));
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *thread3(){
    srand(getpid());
    pthread_mutex_lock(&mutex);
    int index = rand() % strlen(parola);
    printf("trhead3: %c\n", toupper(parola[index]));
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){
    pthread_mutex_init(&mutex, NULL);
    pthread_t t[N];

    pthread_create(&t[0],NULL, thread1,NULL);
    pthread_create(&t[1],NULL, thread2,NULL);
    pthread_create(&t[2],NULL, thread3,NULL);

    for(int i = 0; i<N;i++){
        pthread_join(t[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

}