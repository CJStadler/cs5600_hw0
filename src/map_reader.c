#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#include "memory_region.h"

char *boolean_str(int flag) {
  if (flag) {
    return ("true");
  } else {
    return ("false");
  }
};

void display_region(memory_region *region) {
  printf("Start address: %p\n", region->start);
  printf("End address %p\n", region->end);

  printf("Is readable?: %s\n", boolean_str(region->isReadable));
  printf("Is writeable?: %s\n", boolean_str(region->isWriteable));
  printf("Is executable?: %s\n", boolean_str(region->isExecutable));
};

int main(int argc, char **argv) {
  char *in_filename;

  if (argc < 2) {
    printf("Missing required argument for in filename.\n");
    return (0);
  } else {
    in_filename = argv[1];
  }

  FILE *map_file = fopen(in_filename, "r");
  if (map_file == NULL) {
    printf("No such map file %s.\n", in_filename);
    return (1);
  };

  char line[1000];
  int read_only_total = 0;
  int read_write_total = 0;

  while (fgets(line, 1000, map_file) != NULL) {
    memory_region region = memory_region_from_line(line);

    if (region_is_read_only(&region)) {
      read_only_total += region_size(&region);
    } else if (region_is_read_write(&region)) {
      read_write_total += region_size(&region);
    }

    display_region(&region);
  };

  printf("Total read-only: %i\n", read_only_total);
  printf("Total read-write: %i\n", read_write_total);

  fclose(map_file);

  return (1);
}
