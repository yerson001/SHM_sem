#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

int main()
{
    int sem_id;
    int shm_id;
    int rc;
    key_t key;
    key = ftok(".",'A');

    if(key == -1)
    {
        perror("ftok");
        exit(1);
    }

    initsem(key,1);
    int i = 0;
    for(;i<15;++i)
    {
        sem_p();
        printf(" [B] ");
        fflush(stdout);

        int n = rand()%3; sleep(n);

        //printf("B");
        //fflush(stdout);
        sem_v();

        n = rand()%3; sleep(n);
    }
    //sleep(3);
    sem_destroy();
}
