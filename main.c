#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv) {
  char dirname[128];
  if (argc > 1) {
    strcpy(dirname, argv[1]);
  } else {
    printf("Please enter a directory to scan:\n");
    scanf("%s", dirname);
  }
  printf("\nDirectory: %s\n\n\n", dirname);
  char cur_file[256];


  DIR* directory = opendir(dirname);
  //struct _dirdesc directory;

  if (errno != 0) {
    printf("Error %d: %s\n", errno, strerror(errno));
    return errno;
  }

  int dir_size = 0;

  struct dirent* entry;
  struct stat cur_stat;

  entry = readdir(directory);
  printf("Directories:\n");

  while (entry) {
    if (entry->d_type == DT_DIR) {
      printf("\t%s\n", entry->d_name);
    }
    entry = readdir(directory);
  }
  closedir(directory);

  opendir(dirname);
  entry = readdir(directory);
  printf("\nFiles\n");

  while (entry) {
    if (entry->d_type == DT_REG) {
      printf("\t%s\n", entry->d_name);
      strcpy(cur_file, dirname);
      strcat(cur_file, "/");
      strcat(cur_file, entry->d_name);
      stat(cur_file, &cur_stat);
      dir_size += cur_stat.st_size;
    }
    entry = readdir(directory);
  }

  printf("\n\nTotal directory size: %d\n", dir_size);
}
