// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "types.h"
#include "stat.h"
#include "user.h"

#define N  10

void
waitpidtest(void)
{
  int pid, wpid;
  int status;

  printf(1, "waitpid test\n");

  while ((pid = fork()) <= 0) {
    if (pid < 0)
      continue;
    exit(-1);
  }
  printf(1, "for existing pid: ");
  wpid = waitpid(pid, &status, 0);
  if (wpid == pid) {
    printf(1, "OK\n");
  } else {
    printf(1, "failed\n");
  }

  printf(1, "for not existing pid: ");
  wpid = waitpid(-1, &status, 0);
  if (wpid == -1) {
    printf(1, "OK\n");
  } else {
    printf(1, "failed\n");
  }
}

int
main(void)
{
  waitpidtest();
  exit(-1);
}
