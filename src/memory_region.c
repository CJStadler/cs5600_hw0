#include <stdio.h>

typedef struct MemoryRegion {
  void *startAddr;
  void *endAddr;
  int isReadable;
  int isWriteable;
  int isExecutable;
} memory_region;

extern memory_region memory_region_from_line(char *line) {
  unsigned int starting_address;
  unsigned int ending_address;
  char permissions[4];

  sscanf(line, "%x-%x %s * \n", &starting_address, &ending_address,
         permissions);
  printf("%x\n", starting_address);
  printf("%x\n", ending_address);
  printf("%s\n", permissions);

  struct MemoryRegion r;

  r.startAddr = &starting_address;
  r.endAddr = &ending_address;

  return (r);
}
