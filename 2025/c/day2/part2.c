#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  const char *data;
  size_t length;
} String_View;

String_View sv(const char *data) { return (String_View){data, strlen(data)}; }

int is_symmetric(String_View sv, size_t k) {
  if (sv.length % k != 0) {
    return 0;
  }
  for (size_t i = 0; i < sv.length; i++) {
    if (sv.data[i] != sv.data[i % k]) {
      return 0;
    }
  }
  return 1;
}

void solve_day2_part2(char *input_name) {
  long long total = 0;

  FILE *file = fopen(input_name, "r");
  if (file == NULL) {
    printf("Error opening file: %s\n", input_name);
    return;
  }

  char *number = NULL;
  size_t cap = 0;
  while (getdelim(&number, &cap, ',', file) != -1) {
    for (int i = 0; number[i] != '\0'; i++) {
      if (number[i] == '-') {
        long long start = atoll(number);
        long long end = atoll(number + i + 1);
        for (long long j = start; j <= end; j++) {
          char *j_str = malloc(21);
          sprintf(j_str, "%lld", j);
          String_View j_sv = sv(j_str);
          int matched = 0;
          for (int k = 1; k < j_sv.length / 2 + 1; k++) {
            if (is_symmetric(j_sv, k)) {
              matched = 1;
              break;
            }
          }

          if (matched) {
            total += j;
          }
          free(j_str);
        }
      }
    }
  }
  free(number);
  fclose(file);

  printf("Total: %lld\n", total);
}

int main() {
  // char *input_name = "input_test.txt"; // 4174379265
  char *input_name = "input.txt"; // 35950619148

  solve_day2_part2(input_name);
}
