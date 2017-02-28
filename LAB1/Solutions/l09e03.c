#include<stdio.h>
#include<unistd.h>
#include<assert.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

void* process_A(void *arg);
void* process_B(void *arg);
void* process_C(void *arg);
void* process_D(void *arg);
void* process_E(void *arg);
void* process_F(void *arg);
void* process_G(void *arg);
void* process_H(void *arg);
void* process_I(void *arg);

sem_t semA, semB, semC, semD, semE, semF, semG, semH, semI;
pthread_t tidA, tidB, tidC, tidD, tidE, tidF, tidG, tidH, tidI;

int main(int argc, char **argv){

  sem_init(&semA, 0, 1);
  sem_init(&semB, 0, 0);
  sem_init(&semC, 0, 0);
  sem_init(&semD, 0, 0);
  sem_init(&semE, 0, 0);
  sem_init(&semF, 0, 0);
  sem_init(&semG, 0, 0);
  sem_init(&semH, 0, 0);
  sem_init(&semI, 0, 0);

  pthread_create(&tidA, NULL, process_A, NULL);
  pthread_create(&tidB, NULL, process_B, NULL);
  pthread_create(&tidC, NULL, process_C, NULL);
  pthread_create(&tidD, NULL, process_D, NULL);
  pthread_create(&tidE, NULL, process_E, NULL);
  pthread_create(&tidF, NULL, process_F, NULL);
  pthread_create(&tidG, NULL, process_G, NULL);
  pthread_create(&tidH, NULL, process_H, NULL);
  
  process_I(NULL);
  
  sem_destroy(&semA);
  sem_destroy(&semB);
  sem_destroy(&semC);
  sem_destroy(&semD);
  sem_destroy(&semE);
  sem_destroy(&semF);
  sem_destroy(&semG);
  sem_destroy(&semH);
  sem_destroy(&semI);
  
  return 0;
}

void* process_A(void* arg){
  int i;
  while(1){
    printf("A - waiting\n");
    sem_wait(&semA);
    printf("A - awake\n");
    printf("A - start\n");
    sleep(2);
    printf("A - finish\n");
    
    sem_post(&semB);
    sem_post(&semC);
				sem_post(&semD);
  }
}

void* process_B(void* arg){
  while(1){
    printf("B - waiting\n");
    sem_wait(&semB);
    printf("B - awake\n");
    printf("B - start\n");
    sleep(2);
    printf("B - finish\n");
    sem_post(&semI);
  }
}

void* process_C(void* arg){
  int i;
  while(1){
    printf("C - waiting\n");
    sem_wait(&semC);
    printf("C - awake\n");
    printf("C - start\n");
    sleep(2);
    printf("C - finish\n");
    sem_post(&semE);
	   sem_post(&semF);
  }
}

void* process_D(void* arg){
  while(1){
    printf("D - waiting\n");
    sem_wait(&semD);
    printf("D - awake\n");
    printf("D - start\n");
    sleep(2);
    printf("D - finish\n");
    sem_post(&semH);
  }
}

void* process_E(void* arg){
  while(1){
    printf("E - waiting\n");
    sem_wait(&semE);
    printf("E - awake\n");
    printf("E - start\n");
    sleep(2);
    printf("E - finish\n");
    sem_post(&semG);
  }
}

void* process_F(void* arg){
  while(1){
    printf("F - waiting\n");
    sem_wait(&semF);
    printf("F - awake\n");
    printf("F - start\n");
    sleep(2);
    printf("F - finish\n");
    sem_post(&semG);
  }
}

void* process_G(void* arg){
  while(1){
    printf("G - waiting\n");
    sem_wait(&semG);
    sem_wait(&semG);
    printf("G - awake\n");
    printf("G - start\n");
    sleep(2);
    printf("G - finish\n");
    sem_post(&semI);
  }
}

void* process_H(void* arg){
  while(1){
    printf("H - waiting\n");
    sem_wait(&semH);
    printf("H - awake\n");
    printf("H - start\n");
    sleep(2);
    printf("H - finish\n");
    sem_post(&semI);
  }
}

void* process_I(void* arg){
  while(1){
    printf("I - waiting\n");
    sem_wait(&semI);
    sem_wait(&semI);
    sem_wait(&semI);
    printf("I - awake\n");
    printf("I - start\n");
    sleep(2);
    printf("I - finish\n");
    sem_post(&semA);
  }
}



