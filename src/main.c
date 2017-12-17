#include <stdio.h>

#include "memory_region.h"

int main() {
  FILE *file = fopen("test.txt", "r");
  if (file == NULL) {
    printf("no such file.");
    return (1);
  };

  char line[1000];
  int read_only_total = 0;
  int read_write_total = 0;

  while (fgets(line, 1000, file) != NULL) {
    memory_region region = memory_region_from_line(&line);

    // if (region_is_read_only(region)) {
    //   read_only_total += region_size(region);
    // } else if (region_is_read_write(region)) {
    //   read_write_total += region_size(region);
    // }
  };

  printf("Total read-only: %i\n", read_only_total);
  printf("Total read-write: %i\n", read_write_total);

  fclose(file);
  return (0);
}
