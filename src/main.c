#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory_region.h"

int main(int argc, char **argv) {
  char *pid;

  if (argc < 2) {
    pid = "self";
  } else {
    pid = argv[1];
  }

  char *filename = malloc(strlen(pid) + 12);
  if (filename == NULL) {
    printf("Failed to allocate memory for filename.\n");
    return (1);
  }

  strcat(filename, "/proc/");
  strcat(filename, pid);
  strcat(filename, "/maps");

  printf("file: %s\n", filename);

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("No such file %s.\n", filename);
    return (1);
  };

  free(filename);

  char line[1000];
  int read_only_total = 0;
  int read_write_total = 0;

  while (fgets(line, 1000, file) != NULL) {
    memory_region region = memory_region_from_line(&line);

    if (region_is_read_only(&region)) {
      read_only_total += region_size(&region);
    } else if (region_is_read_write(&region)) {
      read_write_total += region_size(&region);
    }
  };

  printf("Total read-only: %i\n", read_only_total);
  printf("Total read-write: %i\n", read_write_total);

  fclose(file);
  return (0);
}
