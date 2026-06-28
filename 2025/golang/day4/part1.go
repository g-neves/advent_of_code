package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

func canLift(lines []string, row, col int) bool {
	hasUp := row > 0
	hasDown := row < len(lines)-2
	hasLeft := col > 0
	hasRight := col < len(lines[row])-1

	if lines[row][col] == '.' {
		return false
	}

	var strBuilder strings.Builder
	strBuilder.Grow(8)

	// Up-Down
	if hasUp {
		strBuilder.WriteByte(lines[row-1][col])
	} else {
		strBuilder.WriteByte('.')
	}
	if hasDown {
		strBuilder.WriteByte(lines[row+1][col])
	} else {
		strBuilder.WriteByte('.')
	}

	// Left-Right
	if hasLeft {
		strBuilder.WriteByte(lines[row][col-1])
	} else {
		strBuilder.WriteByte('.')
	}
	if hasRight {
		strBuilder.WriteByte(lines[row][col+1])
	} else {
		strBuilder.WriteByte('.')
	}

	// Diagonals
	if hasUp && hasLeft {
		strBuilder.WriteByte(lines[row-1][col-1])
	} else {
		strBuilder.WriteByte('.')
	}
	if hasUp && hasRight {
		strBuilder.WriteByte(lines[row-1][col+1])
	} else {
		strBuilder.WriteByte('.')
	}
	if hasDown && hasLeft {
		strBuilder.WriteByte(lines[row+1][col-1])
	} else {
		strBuilder.WriteByte('.')
	}
	if hasDown && hasRight {
		strBuilder.WriteByte(lines[row+1][col+1])
	} else {
		strBuilder.WriteByte('.')
	}

	return strings.Count(strBuilder.String(), "@") < 4
}

func solveDay4Part1(input string) {
	data, err := os.ReadFile(input)
	if err != nil {
		panic(err)
	}

	lines := strings.Split(string(data), "\n")
	total := 0
	for row, line := range lines[:len(lines)-1] {
		if len(line) == 0 {
			continue
		}
		for col, _ := range line {
			if canLift(lines, row, col) {
				fmt.Println("Can lift: ", line, row, col)
				total++
			}
		}
	}

	log.Println("Total: ", total)
}

func main() {
	// input := "input_test.txt" // Expected output: 13
	input := "input.txt" // 1376
	solveDay4Part1(input)
}
