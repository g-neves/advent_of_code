def main(file: str) -> None:
    zero_count = 0
    position = 50
    with open(file, "r") as f:
        for line in f.readlines():
            direction = -1 if line[0] == "L" else 1
            steps = int(line[1:])

            position = rotate(position, direction, steps)
            if position == 0:
                zero_count += 1

    print(zero_count)


def rotate(position: int, direction: int, steps: int) -> int:
    new_position = (position + direction * steps) % 100
    if new_position < 0:
        new_position = 100 - new_position

    return new_position


if __name__ == "__main__":
    input_test_str = "input_test.txt"  # Expected output: 3
    input_str = "input.txt"  # 1055
    main(input_str)
