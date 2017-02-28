#include<stdio.h>
#include<unistd.h>
#include<assert.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


typedef int* pipe_sem_t;

pipe_sem_t pipe_sem_create(int n);
void pipe_sem_destroy(pipe_sem_t sem);
void pipe_sem_wait(pipe_sem_t sem);
void pipe_sem_signal(pipe_sem_t sem);
void spawn(void (*f)(void));
void process_A();
void process_B();
void process_C();
void process_D();
void process_E();
void process_F();
void process_G();
void process_H();
void process_I();

pipe_sem_t semA, semB, semC, semD, semE, semF, semH, semG, semI;

pipe_sem_t pipe_sem_create(int n){
  int *fds;
  int i;
  fds = malloc(2*sizeof(int));
  pipe(fds);
  
  for(i=0; i<n; i++) pipe_sem_signal((pipe_sem_t) fds);
  return (pipe_sem_t) fds;
}

void pipe_sem_destroy(pipe_sem_t sem){
  close(sem[0]);
  close(sem[1]);
  free(sem);
}

void pipe_sem_wait(pipe_sem_t sem){
  char token;
  read(sem[0], (void*) &token, 1);
}

void pipe_sem_signal(pipe_sem_t sem){
  char token = '*';
  write(sem[1], (void*) &token, 1);
}

void spawn(void (*f)(void)){
  pid_t pid;
  pid = fork();
  if(pid == 0){
    f();
    exit(0);
  }
}

int main(int argc, char **argv){

  semA = pipe_sem_create(0);
  semB = pipe_sem_create(0);
  semC = pipe_sem_create(0);
  semD = pipe_sem_create(0);
  semE = pipe_sem_create(0);
  semF = pipe_sem_create(0);
  semG = pipe_sem_create(0);
  semH = pipe_sem_create(0);
  semI = pipe_sem_create(1);

  while(1){
    
    spawn(process_A);
    spawn(process_B);
    spawn(process_C);
    spawn(process_D);
    spawn(process_E);
    spawn(process_F);
    spawn(process_G);
    spawn(process_H);
    
    process_I();
  }
  
  pipe_sem_destroy(semA);
  pipe_sem_destroy(semB);
  pipe_sem_destroy(semC);
  pipe_sem_destroy(semD);
  pipe_sem_destroy(semE);
  pipe_sem_destroy(semF);
  pipe_sem_destroy(semG);
  pipe_sem_destroy(semH);
  pipe_sem_destroy(semI);
  
  return 0;
}

void process_A(){
  int i;
  printf("A - waiting\n");
  pipe_sem_wait(semI);
  printf("A - awake\n");
  printf("A - start\n");
  sleep(2);
  printf("A - finish\n");
  for(i=0; i<3; i++) pipe_sem_signal(semA);
}

void process_B(){
  printf("B - waiting\n");
  pipe_sem_wait(semA);
  printf("B - awake\n");
  printf("B - start\n");
  sleep(2);
  printf("B - finish\n");
  pipe_sem_signal(semB);
}

void process_C(){
  int i;
  printf("C - waiting\n");
  pipe_sem_wait(semA);
  printf("C - awake\n");
  printf("C - start\n");
  sleep(2);
  printf("C - finish\n");
  for(i=0; i<2; i++) pipe_sem_signal(semC);
}

void process_D(){
  printf("D - waiting\n");
  pipe_sem_wait(semA);
  printf("D - awake\n");
  printf("D - start\n");
  sleep(2);
  printf("D - finish\n");
  pipe_sem_signal(semD);
}

void process_E(){
  printf("E - waiting\n");
  pipe_sem_wait(semC);
  printf("E - awake\n");
  printf("E - start\n");
  sleep(2);
  printf("E - finish\n");
  pipe_sem_signal(semE);
}

void process_F(){
  printf("F - waiting\n");
  pipe_sem_wait(semC);
  printf("F - awake\n");
  printf("F - start\n");
  sleep(2);
  printf("F - finish\n");
  pipe_sem_signal(semF);
}

void process_G(){
  printf("G - waiting\n");
  pipe_sem_wait(semE);
  pipe_sem_wait(semF);
  printf("G - awake\n");
  printf("G - start\n");
  sleep(2);
  printf("G - finish\n");
  pipe_sem_signal(semG);
}

void process_H(){
  printf("H - waiting\n");
  pipe_sem_wait(semD);
  printf("H - awake\n");
  printf("H - start\n");
  sleep(2);
  printf("H - finish\n");
  pipe_sem_signal(semH);
}

void process_I(){
  printf("I - waiting\n");
  pipe_sem_wait(semB);
  pipe_sem_wait(semG);
  pipe_sem_wait(semH);
  printf("I - awake\n");
  printf("I - start\n");
  sleep(2);
  printf("I - finish\n");
  pipe_sem_signal(semI);
}



