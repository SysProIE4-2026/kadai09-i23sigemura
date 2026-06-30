/*
 *  myenv.c : env コマンドのクローン
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __linux__
#include "myputenv.h"
#endif

int main(int argc, char *argv[], char *envp[]) {
  for (int i = 1; i < argc; i++) {
    if (putenv(argv[i]) < 0) {
      execvp(argv[i], &argv[i]);
      perror(argv[i]);
      return 1;
    }
  }
  execlp("printenv", "printenv", NULL);
  perror("printenv");
  return 1;
}

/* 実行例
$ make
cc -D_GNU_SOURCE -Wall -std=c99 -o myenv myenv.c myputenv.c

$ ./myenv TEST=hello printenv TEST
hello

$ ./myenv A=1 B=2
………（省略）
A=1
B=2

$ ./myenv A=1 ls -l
total 384
-rw-r--r--  1 tsukie  staff     132  6月 30 10:31 Makefile
-rwxr-xr-x  1 tsukie  staff   33688  6月 30 12:00 myenv
-rw-r--r--  1 tsukie  staff     486  6月 30 11:57 myenv.c
-rwxr-xr-x  1 tsukie  staff     216  6月 30 10:31 myputenv.c
-rw-r--r--  1 tsukie  staff      93  6月 30 10:31 myputenv.h
-rw-r--r--  1 tsukie  staff    1268  6月 30 10:31 README.md
-rw-r--r--  1 tsukie  staff  139098  6月 30 10:31 README.pdf

$ ./myenv
__CFBundleIdentifier=com.apple.Terminal
TMPDIR=/var/folders/4x/q5xs3rz16v55lncyq6v3cxt80000gn/T/
………（省略）
_=/Users/tsukie/OneDrive - 烫?竃?胁??惴?泃?人
僻?竃?髃?筃?専郶?学惀??橃?槃?/Syspro2/kadai09-i23sigemura/./myenv

$ ./myenv ABC
ABC: No such file or directory

*/
