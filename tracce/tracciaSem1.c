/*
Due thread, il produttore inserisce numeri pari da 0 a 100 in posizioni pari, 
e numeri dispari da 100 a 200 in posizioni dispari all’interno di un buffer di N elementi, 
iniziliazzato a -1, il consumatore legge dal buffer un numero pari e un numero dispari, 
li somma e stampa la loro somma.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10

sem_t mutex;
sem_t empty;
sem_t full;

int buffer[N] = {-1};


void insert_num(){
    srand(getpid());
    for(int i =0;i<N;i++)
        if(i%2 == 0){
            int num = rand() %51 *2;
            buffer[i]=num;   
            }   
        
        else{
            int num = rand() % 101 + 100;
            if(num %2 ==0){
                buffer[i]=num+1;
            }
            else{
                buffer[i]=num;
            }
        }
}


void *producer(void *arg){
    sem_wait(&empty); 
    sem_wait(&mutex);

    insert_num();
        
    sem_post(&mutex);
    sem_post(&full);
    
}


void print_buffer() {
    printf("Contenuto del buffer: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
    int indexPari = (rand()% 5) *2;
    int indexDispari = ((rand() %5)+1)*2 -1;
    printf("numero dispari: %d\n",buffer[indexDispari]);
    printf("numero pari: %d\n",buffer[indexPari]);
    printf("la loro somma è: %d\n",buffer[indexPari]+buffer[indexDispari]);
}


void *consumer(void *arg){
    
    sem_wait(&full);
    sem_wait(&mutex);

    print_buffer();

    sem_post(&mutex);
    sem_post(&empty);

    
}


int main(){
    
    pthread_t prod, cons;

    sem_init(&mutex,0,1);
    sem_init(&empty,0, N);
    sem_init(&full,0,0);
    
    pthread_create(&prod,NULL, producer,NULL);
    pthread_create(&cons,NULL, consumer,NULL);
    

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    

    return 0;
}


