#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#define MAX 20

int array[MAX];

typedef struct
{
    int pthreadId;
    int numero;
    int salto;

} hilo;

sem_t sem;

void *buildProcess(void* arg) {

    int processId = ((hilo *)arg)->pthreadId;
    int numero = ((hilo *)arg)->numero;
    int salto = ((hilo *)arg)->salto;
    int sem_status;

    sem_getvalue(&sem,&sem_status);

//    printf("Proceso %d, desde %d hasta %d\n",processId,processId * salto,(processId + 1) * salto);

    for (int i = processId * salto; i < (processId + 1) * salto; ++i) {

        if( sem_status == 1){
            if(array[i] == numero){
                printf("Se encontro el numero %d en la posicion %d\n",numero,i);
                sem_post(&sem);
                pthread_exit(NULL);

            }
        }else{
            printf("Cerrando el proceso %d\n",processId);
            pthread_exit(NULL);
        }

    }


    printf("No se encontro el numero %d\n",numero);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    sem_init(&sem, 0, 1);
    srand(time(0));
    for (int i = 0; i < 20; ++i) {
        array[i] = rand() % 10;
        printf("%d ",array[i]);
    }
    puts("\n");

    int numberToFind = atoi(argv[1]);
    int numberThreads = atoi(argv[2]);


    hilo *arg = (hilo *)malloc(sizeof(hilo));

    pthread_t threads[numberThreads];


    for (int i = 0; i < numberThreads; ++i) {
        arg->pthreadId = i;
        arg->numero = numberToFind;
        arg->salto = numberThreads;

        pthread_create(&threads[i], NULL, buildProcess,(void *) arg);
        pthread_join(threads[i],NULL);
    }

    sem_destroy(&sem);
    return 0;
}
