package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

type State struct {
	position  int
	zeroCount int
}

func (s *State) rotate(direction int, steps int) {
	// Avoid counting twice zero if starting at zero
	discount := 0
	if (s.position == 0) && (direction < 0) && (steps > 0) {
		discount = 1
	}

	newPosition := (s.position + direction*steps)
	zeroCount := floorDiv(newPosition, 100)
	newPosition = newPosition % 100
	// Adjust for when we crossed zero rotating left
	if newPosition < 0 {
		newPosition = 100 + newPosition
	}
	// Adjust sign of zeroCount
	if zeroCount < 0 {
		zeroCount *= -1
	}
	zeroCount -= discount
	// Adjst for when we cross zero rotating left and end up at zero
	if newPosition == 0 && direction < 0 {
		zeroCount++
	}

	s.position = newPosition
	s.zeroCount += zeroCount
}

func solve(input string) {
	file, err := os.Open(input)
	if err != nil {
		panic(err)
	}

	defer file.Close()

	s := State{position: 50}
	direction := 1

	scanner := bufio.NewScanner(file)
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

		s.rotate(direction, steps)
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	fmt.Println("Total:", s.zeroCount)
}

func floorDiv(a, b int) int {
	q := a / b
	r := a % b
	if r != 0 && (a^b) < 0 {
		q--
	}
	return q
}

func main() {
	// input := "input_test.txt" // Expected: 6
	input := "input.txt" // 6386
	solve(input)
}
