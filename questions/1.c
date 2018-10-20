// filename: 1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char secret[8] = "secret!";

void you_win() { puts("you win!"); exit(0); }
void you_lose() { puts("you lose"); exit(1); }

int test(char *param) {
    char solution[8];
    if (param == NULL) return 0;
    strcpy(solution, param);
    return !strcmp(solution, secret);
}

void main(int argc, char *argv[])
{
  if (test(argv[1])) you_win();
  else you_lose();
}
