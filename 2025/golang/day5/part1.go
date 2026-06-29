package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type IDWindow struct {
	start int
	end   int
}

func isFresh(availableIds []IDWindow, line int) bool {
	for _, id := range availableIds {
		if line >= id.start && line <= id.end {
			return true
		}
	}
	return false
}

func addAvailableIds(availableIds []IDWindow, line string) []IDWindow {
	windows := strings.Split(line, "-")
	start, err := strconv.Atoi(windows[0])
	if err != nil {
		panic(err)
	}
	end, err := strconv.Atoi(windows[1])
	if err != nil {
		panic(err)
	}
	return append(availableIds, IDWindow{start: start, end: end})
}

func solveDay5Part1(input string) {
	file, err := os.Open(input)
	if err != nil {
		panic(err)
	}

	total := 0
	scanner := bufio.NewScanner(file)
	availableIds := []IDWindow{}
	isSplitted := false
	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			isSplitted = true
			continue
		}

		if isSplitted {
			id, err := strconv.Atoi(line)
			if err != nil {
				panic(err)
			}
			if isFresh(availableIds, id) {
				total++
			}
			continue
		}

		availableIds = addAvailableIds(availableIds, line)

	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}

	fmt.Println("Total: ", total)
}

func main() {
	// input := "input_test.txt" // Expected output: 3
	input := "input.txt" // 737
	solveDay5Part1(input)
}
