package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func solve(input string) {
	file, err := os.Open(input)
	if err != nil {
		panic(err)
	}

	total := 0
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		lenLine := len(line)
		maxIdx := 0
		secMaxIdx := 1
		if line[1] > line[0] {
			maxIdx = 1
			secMaxIdx = 0
		}
		for i := 2; i < lenLine-1; i++ {
			if line[i] > line[maxIdx] {
				secMaxIdx = lenLine - 1
				maxIdx = i
			} else if line[i] > line[secMaxIdx] {
				secMaxIdx = i
			}
		}

		if line[secMaxIdx] < line[lenLine-1] {
			secMaxIdx = lenLine - 1
		}

		num, err := strconv.Atoi(string(line[maxIdx]) + string(line[secMaxIdx]))
		if err != nil {
			panic(err)
		}
		total += num

	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}

	fmt.Println("Total: ", total)

}

func main() {
	// input := "input_test.txt" // 357
	input := "input.txt" // 17085
	solve(input)
}
