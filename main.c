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

  DIR* directory = opendir(dirname);
  //struct _dirdesc directory;

  if (errno != 0) {
    printf("Error %d: %s\n", errno, strerror(errno));
    return errno;
  }

  struct dirent* entry;
  entry = readdir(directory);

  while (entry) {
    printf("\t%s\n", entry->d_name);
    entry = readdir(directory);
  }
}
