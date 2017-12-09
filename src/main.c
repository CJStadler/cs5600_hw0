#include <stdio.h>

// #include "memory_region.h"

int main() {
  FILE *file = fopen("test.txt", "r");
  if (file == NULL) {
    printf("no such file.");
    return (1);
  };

  char line[1000];
  char addresses[100];
  char permissions[100];

  printf("start\n");

  while (fgets(line, 1000, file) != NULL) {
    sscanf(line, "%s %s * \n", addresses, permissions);
    printf("%s\n", addresses);
    printf("%s\n", permissions);
  };

  printf("done\n");
  fclose(file);

  return (0);
}
