typedef struct MemoryRegion {
  void *start; // Renamed from "startAddr" because the "address" is be an
               // int, whereas this is a pointer to the location at the address.
  void *end;   // Renamed from "endAddr".
  int isReadable;
  int isWriteable;
  int isExecutable;
} memory_region;

memory_region memory_region_from_line(char *line);
