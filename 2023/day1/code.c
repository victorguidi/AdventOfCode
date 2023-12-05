#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
  no_match = 0,
  one = 1,
  two = 2,
  three = 3,
  four = 4,
  five = 5,
  six = 6,
  seven = 7,
  eight = 8,
  nine = 9
} Numbers;

Numbers isStringNumber(char *line)
{
  // TODO: Check if there is this value in the string
  char numbers[10][6] = {"one", "two", "three", "four", "five", "six", "seven","eight", "nine"};
  for(int i = 0; i <= 9; i++) 
  {
    char *substring = strstr(line, numbers[i]);
    // FIX: This is not working
    while(substring != NULL)
    {
      if (substring == line || !isalpha(*(substring - 1)))
      {
        size_t length = strlen(numbers[i]);
        if (substring[length] == strlen(numbers[i]))
        {
          printf("%d -> substring, %d -> numbers", substring[length], strlen(numbers[i]));
          return (Numbers)(i + 1);
        }
      }
      substring = strstr(substring + 1, numbers[i]);
    }
  }
  return no_match;
}

int SumValuesForLine(char line[1024]) {
  int total = 0;
  char values[2];
  int counter = 0;

  for (int i = 0; i < strlen(line); i++) {
    Numbers result = isStringNumber(&line[i]);
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

      // printf("%c%c\n", values[0], values[1]);
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

  fp = fopen("test.txt", "r");
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
