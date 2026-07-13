#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  const char *data;
  size_t length;
} String_View;

String_View sv(const char *data) { return (String_View){data, strlen(data)}; }

void strip_right(String_View *sv) {
  while (sv->length > 0 && isspace(sv->data[sv->length - 1])) {
    sv->length--;
  }
}

int *find_max_digits(String_View *sv) {
  int *max_digits = calloc(12, sizeof(int));
  size_t len_line = sv->length;
  size_t start = 0;
  for (size_t i = 0; i < 12; i++) {
    for (size_t j = start; j < len_line - 12 + i + 1; j++) {
      if (sv->data[j] > sv->data[max_digits[i]]) {
        max_digits[i] = j;
      }
    }
    start = max_digits[i] + 1;
    if (i < 11) {
      max_digits[i + 1] = max_digits[i] + 1;
      ;
    }
  }

  return max_digits;
}

void solve_day3_part2(char *input_name) {
  FILE *file = fopen(input_name, "r");
  if (file == NULL) {
    printf("Error opening file: %s\n", input_name);
    return;
  }

  long long total = 0;
  char *line = malloc(256);
  while (fgets(line, 256, file)) {

    String_View line_sv = sv(line);
    strip_right(&line_sv); // fgets returns the \n character

    int *max_digits = find_max_digits(&line_sv);

    long long num = 0;
    for (size_t i = 0; i < 12; i++) {
      num += (line_sv.data[max_digits[i]] - '0') * (long long)pow(10, 11 - i);
    }

    total += num;
    free(max_digits);
  }

  free(line);
  fclose(file);

  printf("Total: %lld\n", total);
}

int main() {
  // char *input_name = "input_test.txt"; // 3121910778619
  char *input_name = "input.txt"; // 169408143086082

  solve_day3_part2(input_name);

  return 0;
}
