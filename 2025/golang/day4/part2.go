package main

import (
	"log"
	"os"
	"strings"
)

func canLiftAndRemove(lines *[]string, row, col int) bool {
	hasUp := row > 0
	hasDown := row < len(*lines)-2
	hasLeft := col > 0
	hasRight := col < len((*lines)[row])-1

	if (*lines)[row][col] == '.' {
		return false
	}

	var strBuilder strings.Builder
	strBuilder.Grow(8)

	// TODO: This is ugly, could be moved to an auxiliary method
	// Up-Down
	if hasUp {
		strBuilder.WriteByte((*lines)[row-1][col])
	} else {
		strBuilder.WriteByte('.')
	}
	if hasDown {
		strBuilder.WriteByte((*lines)[row+1][col])
	} else {
		strBuilder.WriteByte('.')
	}

	// Left-Right
	if hasLeft {
		strBuilder.WriteByte((*lines)[row][col-1])
	} else {
		strBuilder.WriteByte('.')
	}
	if hasRight {
		strBuilder.WriteByte((*lines)[row][col+1])
	} else {
		strBuilder.WriteByte('.')
	}

	// Diagonals
	if hasUp && hasLeft {
		strBuilder.WriteByte((*lines)[row-1][col-1])
	} else {
		strBuilder.WriteByte('.')
	}
	if hasUp && hasRight {
		strBuilder.WriteByte((*lines)[row-1][col+1])
	} else {
		strBuilder.WriteByte('.')
	}
	if hasDown && hasLeft {
		strBuilder.WriteByte((*lines)[row+1][col-1])
	} else {
		strBuilder.WriteByte('.')
	}
	if hasDown && hasRight {
		strBuilder.WriteByte((*lines)[row+1][col+1])
	} else {
		strBuilder.WriteByte('.')
	}

	canLift := strings.Count(strBuilder.String(), "@") < 4
	if canLift {
		(*lines)[row] = (*lines)[row][:col] + "." + (*lines)[row][col+1:]
	}

	return canLift
}

func solveDay4Part2(input string) {
	data, err := os.ReadFile(input)
	if err != nil {
		panic(err)
	}

	total := 0
	iterateAgain := true
	lines := strings.Split(string(data), "\n")

	for iterateAgain {
		iterateAgain = false
		for row, line := range lines[:len(lines)-1] {
			if len(line) == 0 {
				continue
			}
			for col, _ := range line {
				if canLiftAndRemove(&lines, row, col) {
					iterateAgain = true
					total++
				}
			}
		}
	}

	log.Println("Total: ", total)
}

func main() {
	// input := "input_test.txt" // Expected output: 43
	input := "input.txt"  // 1376
	solveDay4Part2(input) // 8587
}
