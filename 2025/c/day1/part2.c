#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int position;
  int zero_count;
} State;

int floor_div(int a, int b) {
  int q = a / b;
  int r = a % b;
  if (r != 0 && (a ^ b) < 0) {
    q--;
  }

  return q;
}

void rotate(State *state, int direction, int steps) {
  int discount = 0;
  if (state->position == 0 && direction < 0 && steps > 0) {
    discount = 1;
  }

  int new_position = state->position + direction * steps;
  int zero_count = floor_div(new_position, 100);
  new_position = new_position % 100;

  if (new_position < 0) {
    new_position = 100 + new_position;
  }

  if (zero_count < 0) {
    zero_count *= -1;
  }
  zero_count -= discount;

  if (new_position == 0 && direction < 0) {
    zero_count++;
  }

  state->position = new_position;
  state->zero_count += zero_count;
}

int get_steps(char *line) { return (int)strtol(line + 1, NULL, 10); }

int main() {
  // char *input_name = "input_test.txt"; // Expected output: 6
  char *input_name = "input.txt"; // Expected output: 6386
  FILE *input = fopen(input_name, "r");

  int zero_count = 0;
  int position = 50;
  State state = {position, zero_count};
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

    steps = get_steps(line);

    rotate(&state, direction, steps);
    if (position == 0) {
      zero_count++;
    }
  }

  printf("Total: %d\n", state.zero_count);

  free(line);
  fclose(input);
  return 0;
}
