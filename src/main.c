#include <stdio.h>

// #include "memory_region.h"

typedef struct MemoryRegion {
  void *start; // Renamed from "startAddr" because the "address" is be an
               // int, whereas this is a pointer to the location at the address.
  void *end;   // Renamed from "endAddr".
  int isReadable;
  int isWriteable;
  int isExecutable;
} memory_region;

memory_region memory_region_from_line(char *line) {
  unsigned int starting_address;
  unsigned int ending_address;
  char permissions[4];

  // Extract the addresses and permissions from the line.
  sscanf(line, "%x-%x %s * \n", &starting_address, &ending_address,
         permissions);

  struct MemoryRegion r;

  // Construct pointers to the locations at the addresses.
  r.start = (void *)&starting_address;
  r.end = (void *)&ending_address;

  r.isReadable = permissions[0] == 'r';
  r.isWriteable = permissions[1] == 'w';
  r.isExecutable = permissions[2] == 'x';

  return (r);
}

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
