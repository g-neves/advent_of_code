package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func solve(input string) {
	file, err := os.Open(input)
	if err != nil {
		panic(err)
	}

	defer file.Close()

	zeroCount := 0
	position := 50
	scanner := bufio.NewScanner(file)
	direction := 1
	for scanner.Scan() {
		line := scanner.Text()
		if first := line[0]; first == 'L' {
			direction = -1
		} else {
			direction = 1
		}

		steps, err := strconv.Atoi(line[1:])
		if err != nil {
			panic(err)
		}

		position = rotate(position, direction, steps)
		if position == 0 {
			zeroCount++
		}
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	fmt.Println("Total:", zeroCount)
}

func rotate(position int, direction int, steps int) int {
	position = (position + direction*steps) % 100
	if position < 0 {
		position = 100 + position
	}

	return position
}

func main() {
	// input := "input_test.txt" // Expected: 3
	input := "input.txt" // 1055
	solve(input)
}
