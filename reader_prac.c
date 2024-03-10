#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

int rc=0;
sem_t wrt,mutex;

void *writer(){
sem_wait(&wrt);
printf("i am writing\n");
sem_post(&wrt);
}

void *reader(){
sem_wait(&mutex);
rc++;
if(rc==1)
sem_wait(&wrt);
sem_post(&mutex);
printf("reading file\n");
sem_wait(&mutex);
rc--;
if(rc==0)
sem_post(&wrt);
sem_post(&mutex);
}

int main(){
pthread_t rid[5],wid[5];
sem_init(&wrt,0,1);
sem_init(&mutex,0,1);
int i,m,n;
printf("enter  num of writer");
scanf("%d",&m);
printf("enter  num of reader");
scanf("%d",&n);
for(i=0;i<m;i++)
pthread_create(&wid[i],NULL,writer,NULL);
for(i=0;i<n;i++)
pthread_create(&rid[i],NULL,reader,NULL);
for(i=0;i<m;i++)
pthread_join(wid[i],NULL);
for(i=0;i<n;i++)
pthread_join(rid[i],NULL);

}
