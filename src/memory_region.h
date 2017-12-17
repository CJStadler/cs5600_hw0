typedef struct MemoryRegion {
  void *startAddr;
  void *endAddr;
  int isReadable;
  int isWriteable;
  int isExecutable;
} memory_region;

extern memory_region memory_region_from_line(char *line);
