#include <stdio.h>

#include "memory_region.h"

memory_region memory_region_from_line(char *line) {
  unsigned int starting_address;
  unsigned int ending_address;
  char permissions[4];

  // Extract the addresses and permissions from the line.
  sscanf(line, "%x-%x %s * \n", &starting_address, &ending_address,
         permissions);

  struct MemoryRegion region;

  // Construct pointers to the locations at the addresses.
  region.start = (void *)&starting_address;
  region.end = (void *)&ending_address;

  region.isReadable = permissions[0] == 'r';
  region.isWriteable = permissions[1] == 'w';
  region.isExecutable = permissions[2] == 'x';

  return (region);
}
