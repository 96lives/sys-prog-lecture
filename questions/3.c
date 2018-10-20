// filename: 3.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  // read number from argv[1] using atoi.
  // If no or an invalid number is provided, 
  // use the default value 5
  int n = ...;

  // multiply by 2 and convert to string
  char str[16];
  snprintf(str, sizeof(str), "%d", 2*n);

  // fork
  ...;
  if (...) {
    // child
    char *child_argv[] = {
      ..., // prepare arguments
      NULL
    };

    ...; // execute program
    perror("Cannot execute child.");
  } else if (pid > 0) {
    // parent
    int status, exitcode;
    if (...) { // wait for child
      exitcode = ...; // extract exit code
      printf("Child terminated with exit code %d.\n", exitcode);
    } else {
      perror("Cannot wait for child.");
    }
  }

  return 0;
}
