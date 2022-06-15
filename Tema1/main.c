#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
typedef struct
{
    int pthreadId;
    int numero;

} hilo;

unsigned long factorial(int n)
{
    unsigned long fact = 1;

    for (int i = 1; i <= n; i++) {
        fact = fact * i;
    }

    return fact;
}

void *buildProcess(void* arg) {
    int processId = ((hilo *)arg)->pthreadId;
    int numero = ((hilo *)arg)->numero;
    printf("Factorial de %d : %lu\n",numero,factorial(numero));
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    pthread_t threads[argc];

    for (int i = 1; i < argc; ++i) {

        hilo *arg = (hilo *)malloc(sizeof(hilo));

        arg->pthreadId = i;
        arg->numero = atoi(argv[i]);

        pthread_create(&threads[i], NULL, buildProcess, (void *) arg);
        pthread_join(threads[i],NULL);
    }

    return 0;
}
