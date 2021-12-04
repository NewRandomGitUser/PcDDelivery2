#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#define TRUE 1
#define NUM_THREADS 4

int SOMA = 0; 
int request, respond = 0;
int currentThreadNumber;

void serverProcess() {
  while (TRUE) {
    while (request == 0){}
    respond = request;
    while (respond != 0){}
    request = 0;
  }
}

void clientProcess(int currentThreadNumber) {
  while (TRUE) {
    while (respond != currentThreadNumber)
      request = currentThreadNumber;
    //Entra na Região Crítica
    int local = SOMA;
    sleep(rand()%2);
    SOMA = local + 1;
    printf("Local:[%d], SOMA:[%d], Thread:[%d]\n", local,SOMA,currentThreadNumber);
    respond = 0;
    //Libera a região Crítica
  }
}


int main(int argc, char *argv[]) {
  #pragma omp parallel \
  num_threads(NUM_THREADS) \
  private(currentThreadNumber) \
  shared(SOMA, request, respond)
  {
    currentThreadNumber = omp_get_thread_num();
    if (currentThreadNumber == 0){
      serverProcess();
    } else {
      clientProcess(currentThreadNumber);
    }
  }
  return 0;
}