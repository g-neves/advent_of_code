def main(file: str) -> None:
    zero_count = 0
    position = 50
    with open(file, "r") as f:
        for line in f.readlines():
            direction = -1 if line[0] == "L" else 1
            steps = int(line[1:])

            position, n_zeroes = rotate(position, direction, steps)
            zero_count += n_zeroes

    print(zero_count)


def rotate(position: int, direction: int, steps: int) -> tuple[int, int]:
    n_zeroes, new_position = divmod((position + direction * steps), 100)
    if n_zeroes < 0:
        n_zeroes = abs(n_zeroes)

    # When it starts at zero and goes to left, floor will set it to -1
    if position == 0 and direction < 0:
        n_zeroes -= 1

    # if new position is zero, n_zeroes will be zero, but it got to zero
    if new_position == 0 and direction < 0:
        n_zeroes += 1

    return new_position, n_zeroes


if __name__ == "__main__":
    # input_test_str = "input_test.txt"  # Expected output: 6
    # main(input_test_str)
    input_str = "input.txt"  # 6386
    main(input_str)
