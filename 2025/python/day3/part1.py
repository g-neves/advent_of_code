def main(input: str) -> None:
    total = 0
    with open(input, "r") as f:
        for line in f.readlines():
            line = line.strip()
            if int(line[0]) > int(line[1]):
                max_idx, sec_max_idx = 0, 1
            else:
                max_idx, sec_max_idx = 1, 0

            for idx, digit in enumerate(line[2:-1]):  # We suppose that len(line) > 2
                if int(digit) > int(line[max_idx]):
                    sec_max_idx = len(line) - 1
                    max_idx = idx
                elif int(digit) > int(line[sec_max_idx]):
                    sec_max_idx = idx

            if int(line[-1]) > int(line[sec_max_idx]):
                sec_max_idx = len(line) - 1

            total += int(f"{line[max_idx]}{line[sec_max_idx]}")
            print(line)
            print(max_idx)
            print(sec_max_idx)
            print(int(f"{line[max_idx]}{line[sec_max_idx]}"))

    print("total:", total)


if __name__ == "__main__":
    input_str = "input_test.txt"
    # input_str = "input.txt"
    main(input_str)
