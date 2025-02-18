/*
Scrivere un programma in C con tre thread che operano su due array di dimensione N inizialmente a 0.
• Il primo thread scrive in un array A numeri casuali tra 1 e 150, scrivendo un numero per volta in posizioni randomiche.
• Il secondo thread scrive in un array B numeri cassuali tra 150 e 300, scrivendo un numero per volta in posizioni randomiche.
• Il terzo thread controlla se entrambi gli array sono stati inizializzati, in caso affermativo calcola il massimo in A e in B,
• calcola il minimo in A e in B. Infine determina il max{max(A), max(B)} e il min{min(A), min(B)}.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 10
int A[N] = {0};
int B[N] = {0};
pthread_mutex_t mutex;


void *thread1(void *arg){
    srand(time(NULL));
    printf("Array A: ");
    for(int i = 0; i < N; i++){
        pthread_mutex_lock(&mutex);
        int num = rand() % 150+1;
        int pos = rand() % N;
        A[pos] = num;
        printf("%d, ", num);
        pthread_mutex_unlock(&mutex);
    }
    printf("\n");
    int sleeptime = rand() % 5;
    sleep(sleeptime);
}

void *thread2(void *arg){
    srand(time(NULL));
    printf("Array B: ");
    for(int i = 0; i < N; i++){
        pthread_mutex_lock(&mutex);
        int num = rand() % 151+150;
        int pos = rand() % N;
        B[pos] = num;
        printf("%d, ", num);
        pthread_mutex_unlock(&mutex);
    }
    printf("\n");
    int sleeptime = rand() % 5;
    sleep(sleeptime);
}

void *thread3(void *arg){
    int count1 = 0;
    int count2 = 0;
    int maxA=0, maxB=0, minA=0,minB=0, MAX=0,MIN=0;
    for(int i = 0; i<N;i++){
        pthread_mutex_lock(&mutex);
        
        if(A[i] != 0){
            count1++;
        }
        
        if(B[i] != 0){
            count2++;
        }
        pthread_mutex_unlock(&mutex);
    }
    
    if(count1 == N && count2 == N){

        for(int i=0;i < N; i++){
            pthread_mutex_lock(&mutex);
            if(A[i] > maxA){
                maxA = A[i];
            }
            if(B[i] > maxB){
                maxB = B[i];
            }
            if(A[i] < minA){
                minA = A[i];
            }
            if(A[i] < minA){
                minB = A[i];
            }
            if(maxA>maxB){
                MAX = maxA;
            }
            else{
                MAX = maxB;
            }
            if(minA>minB){
                MIN = minA;
            }
            else{
                MIN = minB;
            }            
            pthread_mutex_unlock(&mutex);
            printf("Massimo di A: %i\n", maxA);
        }
        
    
    }
    
        printf("Massimo di A: %i\n", maxA);
        printf("Masssimo di B: %i\n", maxB);
        printf("Minimo di A: %i\n", minA);
        printf("Minimo di B: %i\n", minB);
        printf("Massimo tra A e B: %i\n", MAX);
        printf("Minimo tra A e B: %i\n", MIN);
    
    
    int sleeptime = rand() % 5;
    sleep(sleeptime);
}
    


int main() {
    pthread_t threads[3];
    pthread_mutex_init(&mutex, NULL);
    

    pthread_create(&threads[0], NULL, thread1, NULL);
    pthread_create(&threads[1], NULL, thread2, NULL);
    pthread_create(&threads[2], NULL, thread3, NULL);
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
        printf("Thread %i terminato.\n", i);
        
    }


    pthread_mutex_destroy(&mutex);

    return 0;
}

//scrivi una funzione 



