#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int get_dir_size(char* path);

int main(int argc, char** argv) {
  char dirname[128];
  if (argc > 1) {
    strcpy(dirname, argv[1]);
  } else {
    printf("Please enter a directory to scan:\n");
    scanf("%s", dirname);
  }
  printf("\nSelected directory: %s\n\n\n", dirname);
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
      strcpy(cur_file, dirname);
      strcat(cur_file, "/");
      strcat(cur_file, entry->d_name);
      if (strcmp(entry->d_name, "..") && strcmp(entry->d_name, ".")) {
        dir_size += get_dir_size(cur_file);
      }
    }
    entry = readdir(directory);
  }
  closedir(directory);

  if (errno != 0) {
    printf("Error %d: %s\n", errno, strerror(errno));
    return errno;
  }

  opendir(dirname);
  entry = readdir(directory);
  printf("\nFiles:\n");

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

  if (errno != 0) {
    printf("Error %d: %s\n", errno, strerror(errno));
    return errno;
  }
  return errno;
}

int get_dir_size(char* path) {
  DIR* directory = opendir(path);
  if (errno != 0) {
    printf("Error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  int dir_size = 0;

  char cur_file[256];
  struct dirent* entry;
  struct stat cur_stat;

  entry = readdir(directory);

  while (entry) {
    strcpy(cur_file, path);
    strcat(cur_file, "/");
    strcat(cur_file, entry->d_name);

    if (errno != 0) {
      printf("Error %d: %s\n", errno, strerror(errno));
    }

    if (strcmp(entry->d_name, "..") && strcmp(entry->d_name, ".") && entry->d_type == DT_DIR) {
      dir_size += get_dir_size(cur_file);
    } else {
      stat(cur_file, &cur_stat);
      dir_size += cur_stat.st_size;
    }
    entry = readdir(directory);
  }
  return dir_size;
}
