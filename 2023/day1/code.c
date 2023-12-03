#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int SumValuesForLine(char line[1024]) {
  int total = 0;
  char values[2];
  int counter = 0;

  for (int i = 0; i < strlen(line); i++) {
    if (isdigit(line[i])) {
      if (counter == 0) values[0] = line[i];
      else values[1] = line[i];
      counter++;

      if (counter < 2) {
        values[1] = values[0];
      }
    } else if (line[i] == '\n') {

      char *v = (char *)malloc(3);  //memory for two digits and null terminator (since we know is the first and last digit)
      if (v == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
      }

      printf("%c%c\n", values[0], values[1]);
      sprintf(v, "%c%c", values[0], values[1]);

      total += strtol(v, NULL, 10);
      free(v);
      counter = 0;
    }
  }

  return total;
}

int main() {
  FILE *fp;
  char buffer[1024];

  int result;

  fp = fopen("file.txt", "r");
  if (fp == NULL) {
      printf("Error opening file\n");
      return 1;
  }

  // FGETS WILL loop in the file until the last line
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
      result += SumValuesForLine(buffer);
  }

  fclose(fp);

  printf("Final Result -> %d\n", result);
  return 0;
}
