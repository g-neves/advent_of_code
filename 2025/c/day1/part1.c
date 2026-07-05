#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int position;
  int count;
} State;

int rotate(int position, int direction, int steps) {
  position = (position + direction * steps) % 100;
  if (position < 0) {
    position += 100;
  }

  return position;
}

int getSteps(char *line) { return (int)strtol(line + 1, NULL, 10); }

int main() {
  // char *input_name = "input_test.txt"; // Expected output: 3
  char *input_name = "input.txt"; // Expected output: 1055
  FILE *input = fopen(input_name, "r");

  int zero_count = 0;
  int position = 50;
  int direction;
  int steps;

  char *line = NULL;
  size_t cap = 0;
  while (1) {
    ssize_t n = getline(&line, &cap, input);
    if (n == -1) { // EOF or error
      break;
    }
    if (line[0] == 'L') {
      direction = -1;
    } else {
      direction = 1;
    }

    steps = getSteps(line);

    position = rotate(position, direction, steps);
    if (position == 0) {
      zero_count++;
    }
  }

  printf("Total: %d\n", zero_count);

  free(line);
  fclose(input);
  return 0;
}
