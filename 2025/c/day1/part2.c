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

int get_steps(char *line) {
  int steps = 0;
  sscanf(line + 1, "%d", &steps);
  return steps;
}

void solve_day1_part2(char *input_name) {
  FILE *file = fopen(input_name, "r");
  if (file == NULL) {
    printf("Error opening file: %s\n", input_name);
    return;
  }

  int zero_count = 0;
  char line[256];
  int direction;
  int position = 50;
  int steps;
  State state = {position, zero_count};
  while (fgets(line, sizeof(line), file)) {
    if (line[0] == 'L') {
      direction = -1;
    } else {
      direction = 1;
    }

    steps = get_steps(line);
    rotate(&state, direction, steps);
  }

  fclose(file);

  printf("Total: %d\n", state.zero_count);
}

int main() {
  // char *input_name = "input_test.txt"; // 6
  char *input_name = "input.txt"; // 6386

  solve_day1_part2(input_name);

  return 0;
}
