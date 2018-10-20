// filename: 4.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  // read number from argv[1] using atoi.
  // If no or an invalid number is provided, use the default value 5
  int n = argc > 1 ? atoi(argv[1]) : 5;

  // multiply by 2 and convert to string
  char str[16];
  snprintf(str, sizeof(str), "%d", 2*n);

  // open pipe
  ...;
  if (pipe(...) == -1) {
    perror("Cannot open pipe");
    return 1;
  }

  // fork
  pid_t pid = fork();
  if (pid == 0) {
    // child
    char *child_argv[] = {
      ..., // prepare arguments
      NULL
    };

    // redirect write end of pipe to STDOUT,
    // close unused read end
    ...;

    ...; // execute program
    perror("Cannot execute child.");
  } else if (pid > 0) {
    // parent
    int i, res;
    FILE *pipe_read;

    // convert file descriptor into file stream
    // and close unused write end
    ...;

    // read numbers and print as hex until pipe closed 
    do {
      ...; // read number from pipe file stream
      ...; // print in hex format
    } while (...};
  }

  return 0;
}
