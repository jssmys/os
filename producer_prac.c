#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

int c=0;
sem_t full,mutex,empty;

void *producer(){
sem_wait(&empty);
sem_wait(&mutex);
printf("producer has produced item %d\n",++c);
sem_post(&mutex);
sem_post(&full);
}

void *consumer(){
sem_wait(&full);
sem_wait(&mutex);
printf("consumer has consumed item %d\n",c--);
sem_post(&mutex);
sem_post(&empty);
}

int main(){
pthread_t pid[5] , cid[5];
sem_init(&empty,0,5);
sem_init(&full,0,0);
sem_init(&mutex,0,1);
int i,m,n;
printf("enter numberof producer");
scanf("%d",&m);
printf("enter numberof consumer");
scanf("%d",&n);
for(i=0;i<m;i++)
pthread_create(&pid[i],NULL,producer,NULL);
for(i=0;i<n;i++)
pthread_create(&cid[i],NULL,consumer,NULL);
for(i=0;i<m;i++)
pthread_join(pid[i],NULL);
for(i=0;i<n;i++)
pthread_join(cid[i],NULL);

exit(0);
}



