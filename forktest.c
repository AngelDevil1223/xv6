// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "types.h"
#include "stat.h"
#include "user.h"

#define N  10

void
printf(int fd, const char *s, ...)
{
  write(fd, s, strlen(s));
}

void
forktest(void)
{
  int n, pid;
  int status;

  printf(1, "fork test\n");

  for(n=0; n<N; n++){
    pid = fork();
    if(pid < 0)
      break;
    if(pid == 0)
      exit(n);
  }

  if(n == N){
    printf(1, "fork claimed to work N times!\n", N);
    exit(1001);
  }

  for(; n > 0; n--){
    if(wait(&status) < 0){
      printf(1, "wait stopped early\n");
      printf(1, "wait result: %d\n\n", status);
      exit(1002);
    }
    printf(1, "wait result in loop: %d\n\n", status);
  }

  if(wait(&status) != -1){
    printf(1, "wait got too many\n");
    printf(1, "wait result: %d\n\n", status);
    exit(1003);
  }
  printf(1, "wait result: %d\n\n", status);

  printf(1, "fork test OK\n");
}

int
main(void)
{
  forktest();
  exit(-1);
}
