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

sem_t semA, semB, semC, semD, semE, semF, semH, semG, semI;
pthread_t tidA, tidB, tidC, tidD, tidE, tidF, tidG, tidH, tidI;

int main(int argc, char **argv){

  sem_init(&semA, 0, 0);
  sem_init(&semB, 0, 0);
  sem_init(&semC, 0, 0);
  sem_init(&semD, 0, 0);
  sem_init(&semE, 0, 0);
  sem_init(&semF, 0, 0);
  sem_init(&semG, 0, 0);
  sem_init(&semH, 0, 0);
  sem_init(&semI, 0, 1);

  while(1){
    
    pthread_create(&tidA, NULL, process_A, NULL);
    pthread_create(&tidB, NULL, process_B, NULL);
    pthread_create(&tidC, NULL, process_C, NULL);
    pthread_create(&tidD, NULL, process_D, NULL);
    pthread_create(&tidE, NULL, process_E, NULL);
    pthread_create(&tidF, NULL, process_F, NULL);
    pthread_create(&tidG, NULL, process_G, NULL);
    pthread_create(&tidH, NULL, process_H, NULL);
    
    process_I(NULL);
  }
  
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
  printf("A - waiting\n");
  sem_wait(&semI);
  printf("A - awake\n");
  printf("A - start\n");
  sleep(2);
  printf("A - finish\n");
  for(i=0; i<3; i++) sem_post(&semA);
  return NULL;
}

void* process_B(void* arg){
  printf("B - waiting\n");
  sem_wait(&semA);
  printf("B - awake\n");
  printf("B - start\n");
  sleep(2);
  printf("B - finish\n");
  sem_post(&semB);
  return NULL;
}

void* process_C(void* arg){
  int i;
  printf("C - waiting\n");
  sem_wait(&semA);
  printf("C - awake\n");
  printf("C - start\n");
  sleep(2);
  printf("C - finish\n");
  for(i=0; i<2; i++) sem_post(&semC);
  return NULL;
}

void* process_D(void* arg){
  printf("D - waiting\n");
  sem_wait(&semA);
  printf("D - awake\n");
  printf("D - start\n");
  sleep(2);
  printf("D - finish\n");
  sem_post(&semD);
  return NULL;
}

void* process_E(void* arg){
  printf("E - waiting\n");
  sem_wait(&semC);
  printf("E - awake\n");
  printf("E - start\n");
  sleep(2);
  printf("E - finish\n");
  sem_post(&semE);
  return NULL;
}

void* process_F(void* arg){
  printf("F - waiting\n");
  sem_wait(&semC);
  printf("F - awake\n");
  printf("F - start\n");
  sleep(2);
  printf("F - finish\n");
  sem_post(&semF);
  return NULL;
}

void* process_G(void* arg){
  printf("G - waiting\n");
  sem_wait(&semE);
  sem_wait(&semF);
  printf("G - awake\n");
  printf("G - start\n");
  sleep(2);
  printf("G - finish\n");
  sem_post(&semG);
  return NULL;
}

void* process_H(void* arg){
  printf("H - waiting\n");
  sem_wait(&semD);
  printf("H - awake\n");
  printf("H - start\n");
  sleep(2);
  printf("H - finish\n");
  sem_post(&semH);
  return NULL;
}

void* process_I(void* arg){
  printf("I - waiting\n");
  sem_wait(&semB);
  sem_wait(&semG);
  sem_wait(&semH);
  printf("I - awake\n");
  printf("I - start\n");
  sleep(2);
  printf("I - finish\n");
  sem_post(&semI);
  return NULL;
}



