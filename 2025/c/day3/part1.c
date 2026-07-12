#include <ctype.h>
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

void solve_day3_part1(char *input_name) {
  FILE *file = fopen(input_name, "r");
  if (file == NULL) {
    printf("Error opening file: %s\n", input_name);
    return;
  }

  long long total = 0;
  char *line = malloc(256);
  while (fgets(line, 256, file)) {

    String_View line_sv = sv(line);
    strip_right(&line_sv);

    size_t max_id = 0;
    size_t sec_max_id = 1;
    if (line_sv.data[1] > line_sv.data[0]) {
      max_id = 1;
      sec_max_id = 0;
    }

    for (size_t i = 2; i < line_sv.length - 1; i++) {
      if (line_sv.data[i] > line_sv.data[max_id]) {
        sec_max_id = line_sv.length - 1;
        max_id = i;
      } else if (line_sv.data[i] > line_sv.data[sec_max_id]) {
        sec_max_id = i;
      }
    }

    if (line_sv.data[sec_max_id] < line_sv.data[line_sv.length - 1]) {
      sec_max_id = line_sv.length - 1;
    }

    total +=
        (line_sv.data[max_id] - '0') * 10 + (line_sv.data[sec_max_id] - '0');
  }

  free(line);
  fclose(file);

  printf("Total: %lld\n", total);
}

int main() {
  // char *input_name = "input_test.txt"; // 357
  char *input_name = "input.txt"; // 17085

  solve_day3_part1(input_name);

  return 0;
}
