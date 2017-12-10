#include <stdio.h>

// #include "memory_region.h"

int main() {
  FILE *file = fopen("test.txt", "r");
  if (file == NULL) {
    printf("no such file.");
    return (1);
  };

  char line[1000];
  unsigned int starting_address;
  unsigned int ending_address;
  char permissions[4];

  printf("start\n");

  while (fgets(line, 1000, file) != NULL) {
    sscanf(line, "%x-%x %s * \n", &starting_address, &ending_address,
           permissions);
    printf("%x\n", starting_address);
    printf("%x\n", ending_address);
    printf("%s\n", permissions);
  };

  printf("done\n");
  fclose(file);

  return (0);
}
