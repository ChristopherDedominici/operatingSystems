#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

typedef int * Semaphore;

Semaphore semA,semB,semC,semD,semE,semF,semG,semH,semI;

Semaphore make_sem() {
  int *sem;
  sem = calloc(2,sizeof(int));
  pipe(sem);
  return sem;
}

void WAIT(Semaphore s) {
  int junk;
  if (read(s[0], &junk, 1) <=0) {   // it blocks if pipe is empty
    fprintf(stderr, "ERROR : wait\n");
    exit(1);
  }
}

void SIGNAL(Semaphore s) {
  if (write(s[1], "x", 1) <=0) {
    fprintf(stderr, "ERROR : signal\n");
    exit(1);
  }
}

void pA(){  
WAIT(semI);
sleep(1);
printf("   A\n");
SIGNAL(semA);        
SIGNAL(semA);        
SIGNAL(semA);        
exit(0);
}

void pB(){  
WAIT(semA);        
sleep(2);
printf("B  ");
SIGNAL(semB);            
exit(0);
}

void pC(){  
WAIT(semA);        
sleep(3);
printf("C  ");
SIGNAL(semC);        
SIGNAL(semC);        
exit(0);
}

void pD(){  
WAIT(semA);        
sleep(4);
printf("D\n");
SIGNAL(semD);        
exit(0);
}

void pE(){  
WAIT(semC);        
sleep(1);
printf(" E ");
SIGNAL(semE);                
exit(0);
}

void pF(){  
WAIT(semC);        
sleep(2);
printf("  F\n");
SIGNAL(semF);        
exit(0);     
}


void pG(){  
WAIT(semF);        
WAIT(semE);        
sleep(1);
printf("   G");   
SIGNAL(semG);        
exit(0);
}

void pH(){  
WAIT(semD);
sleep(5);
printf("  H\n");
SIGNAL(semH);
exit(0);       
}

void pI(){  
WAIT(semG); 
WAIT(semH); 
WAIT(semB); 
sleep(1);
printf("   I\n");
SIGNAL(semI);
//exit(0);
}

int main (int argc, char **argv) {
  int pIDA,pIDB,pIDC,pIDD, pIDE,pIDF,pIDG,pIDH;
                       
  semA=make_sem();
  semB=make_sem();
  semC=make_sem();
  semD=make_sem();
  semE=make_sem();
  semF=make_sem();
  semG=make_sem();
  semH=make_sem();
  semI=make_sem();

  SIGNAL(semI);

  // Soluzione "inefficiente" ricreo i processi ad ogni ciclo
  // Vedere soluzione con i Thread per l'alternativa !!!
  while(1) {
    pIDA=fork();
    if (pIDA!=0) {
       pIDB=fork();
       if (pIDB!=0) {
         pIDC=fork(); 
         if (pIDC!=0) {
              pIDD=fork();
              if (pIDD!=0) {
                  pIDH=fork();
                  if (pIDH!=0) {
                      pI();
                    } else
                      pH();    
               } else
                pD();   
           }else {
                pIDE=fork();
                if (pIDE!=0)
                   pC();
                else {
                      pIDF=fork();
                      if (pIDF!=0) {
                         pE();  
                       } else {
                            pIDG=fork();
                            if (pIDG!=0)  
                                pF();
                            else pG(); 
                          }     
                   }   
            }   
          }else
            pB();                        
    }else pA();
  }  
                              
  return (0);
}

