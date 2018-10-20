// filename: producer.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int i,n = argc > 1 ? atoi(argv[1]) : 10;
  for (i=0; i<n; i++) { 
    printf("%d\n", rand() % 100); fflush(stdout);
  }
  sleep(3);
  return n/2;
}
