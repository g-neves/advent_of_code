package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

type IDWindow struct {
	start int
	end   int
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

func countAvailableIds(availableIds []IDWindow) int {
	total := 0
	return total
}

func mergeIntervals(availableIds []IDWindow) []IDWindow {
	for i := 0; i < len(availableIds)-1; i++ {
		if availableIds[i].end >= availableIds[i+1].start-1 {
			availableIds[i].end = max(availableIds[i].end, availableIds[i+1].end)
			availableIds = append(availableIds[:i+1], availableIds[i+2:]...)
			i--
		}
	}
	return availableIds
}

func solveDay5Part2(input string) {
	file, err := os.Open(input)
	if err != nil {
		panic(err)
	}

	total := 0
	scanner := bufio.NewScanner(file)
	availableIds := []IDWindow{}
	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			break
		}
		availableIds = addAvailableIds(availableIds, line)
	}
	sort.Slice(availableIds, func(i, j int) bool {
		return availableIds[i].start < availableIds[j].start
	})

	availableIds = mergeIntervals(availableIds)
	for _, id := range availableIds {
		total += id.end - id.start + 1
	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}

	fmt.Println("Total: ", total)
}

func main() {
	// input := "input_test.txt" // Expected output: 14
	input := "input.txt" // 357485433193284
	solveDay5Part2(input)
}
