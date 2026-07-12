#include <stdio.h>
#include <stdlib.h>

int rotate(int position, int direction, int steps) {
  position = (position + direction * steps) % 100;
  if (position < 0) {
    position += 100;
  }

  return position;
}

int get_steps(char *line) {
  int steps = 0;
  sscanf(line + 1, "%d", &steps);
  return steps;
}

void solve_day1_part1(char *input_name) {
  FILE *file = fopen(input_name, "r");
  if (file == NULL) {
    printf("Error opening file: %s\n", input_name);
    return;
  }

  int zero_count = 0;
  char line[256];
  int direction;
  int position = 50;
  while (fgets(line, sizeof(line), file)) {
    if (line[0] == 'L') {
      direction = -1;
    } else {
      direction = 1;
    }

    int steps = get_steps(line);
    position = rotate(position, direction, steps);
    if (position == 0) {
      zero_count++;
    }
  }

  fclose(file);

  printf("Total: %d\n", zero_count);
}

int main() {
  // char *input_name = "input_test.txt"; // 3
  char *input_name = "input.txt"; // 1055

  solve_day1_part1(input_name);

  return 0;
}
