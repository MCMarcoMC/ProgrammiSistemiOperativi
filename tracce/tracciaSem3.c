/*
Sei thread, un scrittore e 5 lettori. Lo scrittore scrive su un buffer numeri dispari da 0 a 50 nelle posizioni pari 
e numeri pari da 50 a 100 nelle posizioni dispari. 
I lettori leggono coppie di numeri (paro, disparo), li somma e li stampa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define BUFFERSIZE 10

pthread_mutex_t mutex;
int buffer[BUFFERSIZE];

void *scrittore(){
    srand(time(NULL));
    pthread_mutex_lock(&mutex);
    for(int i=0; i<BUFFERSIZE;i++){
        if(i %2 == 0){
            buffer[i]=rand() % 25*2 +1;
            //printf("numero dispari in posizione pari: %d\n", buffer[i]);
        }
        else{
            buffer[i]=(rand() %25*2)+50;
            //printf("numero pari in posizione dispari: %d\n", buffer[i]);
        }
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *lettore(){
    srand(time(NULL));
    pthread_mutex_lock(&mutex);

    int indexpari = (rand() % BUFFERSIZE/2)*2;
    int indexdispari = ((rand() % (BUFFERSIZE-1)/2)*2)+1;
    printf("la coppia di numeri (pari,dispari) è: (%d,%d)\n", buffer[indexpari],buffer[indexdispari]);
    printf("la loro somma è: %d\n", buffer[indexpari]+buffer[indexdispari]);

    pthread_mutex_unlock(&mutex);
    return NULL;
} 


int main(){
    pthread_mutex_init(&mutex,NULL);

    pthread_t t[6];
    pthread_create(&t[0],NULL,scrittore,NULL);
    sleep(1);

    for(int i=1;i<6;i++){
        //printf("lettore%d: \n",i);
        pthread_create(&t[i],NULL,lettore,NULL);
        sleep(1);
    }
    
    for(int i=0;i<6;i++){
        pthread_join(t[i],NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;

}