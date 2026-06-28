def main(input: str) -> None:
    total = 0
    with open(input, "r") as f:
        ids_list = f.read().split(",")

    print(ids_list)
    for ids in ids_list:
        start, end = ids.split("-")
        for num in range(int(start), int(end) + 1):
            str_num = str(num)
            if len(str_num) % 2 == 1:
                continue

            if str_num[: len(str_num) // 2] == str_num[len(str_num) // 2 :]:
                total += num

    print(total)


if __name__ == "__main__":
    # input_str = "input_test.txt"  # Expected output: 1227775554
    input_str = "input.txt"  # 23039913998
    main(input_str)
