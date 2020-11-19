#ifndef SEM_H
#define SEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <unistd.h>

struct semun
{
    int val;
    struct semid_ds *buf;
    ushort *array;
};

static int semid = 0;

void initsem(key_t key,int nsems)
{
    semid = semget(key,nsems,IPC_CREAT | IPC_EXCL| 0600);
    if(semid == -1)
    {
        semid = semget(key,nsems,IPC_CREAT | 0600);
        if(semid == -1)
        {
            printf("semget error");
        }
    }
    else
    {
        struct semun a;//a pass value
        a.val = 1;
        if(semctl(semid,0,SETVAL,a)==-1)//0 represents the semaphore table
        {
            perror("semctl init error");
        }
    }
}

void sem_p()
{
    struct sembuf buf;
    buf.sem_num = 0;//Semaphore subscript
    buf.sem_op = -1;//p operation
    buf.sem_flg = SEM_UNDO;
    if(semop(semid,&buf,1)==-1)
    {
        perror("p error");
    }
}

void sem_v()
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;//Set the semaphore value to automatically recover when the process has an error to prevent a process from occupying the semaphore
    if(semop(semid,&buf,1)==-1)//1 represents the operand, the number of sembuf
    {
        perror("v error");
    }
}

void sem_destroy()
{
    if(semctl(semid,0,IPC_RMID)==-1)//0 represents the semaphore set
    {
        perror("semctl destroy error");
    }
    printf("\n End process press to continue ...");
}   

#endif
