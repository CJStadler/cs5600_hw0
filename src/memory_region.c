#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory_region.h"

memory_region memory_region_from_line(char line[]) {
  uintptr_t starting_address;
  uintptr_t ending_address;
  char permissions[4];

  // Extract the addresses and permissions from the line.
  sscanf(line, "%lx-%lx %s * \n", &starting_address, &ending_address,
         permissions);

  struct MemoryRegion region;

  // Construct pointers to the locations at the addresses.
  region.start = (void *)starting_address;
  region.end = (void *)ending_address;

  region.isReadable = permissions[0] == 'r';
  region.isWriteable = permissions[1] == 'w';
  region.isExecutable = permissions[2] == 'x';

  return (region);
}

int region_is_read_only(memory_region *region) {
  return (region->isReadable && !region->isWriteable && !region->isExecutable);
}

int region_is_read_write(memory_region *region) {
  return (region->isReadable && region->isWriteable && !region->isExecutable);
}

int region_size(memory_region *region) { return (region->end - region->start); }

void write_region_to_file(memory_region *region, FILE *file) {
  char readable;
  char writeable;
  char executable;

  if (region->isReadable) {
    readable = 'r';
  } else {
    readable = '-';
  }

  if (region->isWriteable) {
    writeable = 'w';
  } else {
    writeable = '-';
  }

  if (region->isExecutable) {
    executable = 'x';
  } else {
    executable = '-';
  }

  fprintf(file, "%lx-%lx ", (uintptr_t)region->start, (uintptr_t)region->end);

  fputc(readable, file);
  fputc(writeable, file);
  fputc(executable, file);
  fputc('\n', file);
}
