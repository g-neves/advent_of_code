#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void solve_day2_part1(char *input_name) {
  long long total = 0;

  FILE *file = fopen(input_name, "r");
  if (file == NULL) {
    printf("Error opening file: %s\n", input_name);
    return;
  }

  char *number = NULL;
  size_t cap;
  while (getdelim(&number, &cap, ',', file) != -1) {
    for (int i = 0; number[i] != '\0'; i++) {
      if (number[i] == '-') {
        long long start = atoll(number);
        long long end = atoll(number + i + 1);
        for (long long j = start; j <= end; j++) {
          char j_str[256];
          sprintf(j_str, "%lld", j);
          size_t len = strlen(j_str);
          if (len % 2 != 0) {
            continue;
          }
          if (strncmp(j_str, j_str + len / 2, len / 2) == 0) {
            total += j;
          }
        }
      }
    }
  }

  fclose(file);

  printf("Total: %lld\n", total);
}

int main() {
  // char *input_name = "input_test.txt"; // 1227775554
  char *input_name = "input.txt"; // 23039913998

  solve_day2_part1(input_name);
}
