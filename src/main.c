#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory_region.h"

int main(int argc, char **argv) {
  char *pid;
  char *out_filename;

  if (argc < 2) {
    printf("Missing required argument for out filename.\n");
    return (0);
  } else {
    out_filename = argv[1];

    if (argc < 3) {
      pid = "self";
    } else {
      pid = argv[2];
    }
  }

  char *map_filename = malloc(strlen(pid) + 12);
  if (map_filename == NULL) {
    printf("Failed to allocate memory for map_filename.\n");
    return (1);
  }

  strcat(map_filename, "/proc/");
  strcat(map_filename, pid);
  strcat(map_filename, "/maps");

  printf("map_file: %s\n", map_filename);

  FILE *map_file = fopen(map_filename, "r");
  if (map_file == NULL) {
    printf("No such map_file %s.\n", map_filename);
    return (1);
  };

  free(map_filename);

  FILE *out_file = fopen(out_filename, "w");

  char line[1000];
  int read_only_total = 0;
  int read_write_total = 0;

  while (fgets(line, 1000, map_file) != NULL) {
    memory_region region = memory_region_from_line(&line);

    if (region_is_read_only(&region)) {
      read_only_total += region_size(&region);
    } else if (region_is_read_write(&region)) {
      read_write_total += region_size(&region);
    }

    write_region_to_file(&region, out_file);
  };

  printf("Total read-only: %i\n", read_only_total);
  printf("Total read-write: %i\n", read_write_total);

  fclose(map_file);
  fclose(out_file);
  return (0);
}
