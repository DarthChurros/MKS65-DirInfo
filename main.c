#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc, char** argv) {
  char dirname[128];
  if (argc > 1) {
    strcpy(dirname, argv[1]);
  } else {
    printf("Please enter a directory to scan:\n");
    scanf("%s", dirname);
  }
  printf("\nDirectory: %s\n", dirname);
  return 0;
}
