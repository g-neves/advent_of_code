def main(input: str) -> None:
    total = 0
    with open(input, "r") as f:
        ids_list = f.read().strip().split(",")

    for ids in ids_list:
        start, end = ids.split("-")
        for num in range(int(start), int(end) + 1):
            str_num = str(num)

            for i in range(1, len(str_num) // 2 + 1):
                if len(str_num) % i != 0:
                    continue

                if str_num[:i] * (len(str_num) // i) == str_num:
                    total += num
                    break

    print("total:", total)


if __name__ == "__main__":
    # input_str = "input_test.txt"  # Expected output: 4174379265
    input_str = "input.txt"  # 35950619148
    main(input_str)
