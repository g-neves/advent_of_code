package main

import (
	"bufio"
	"fmt"
	"os"
)

func solveDay7Part1(input string) {
	file, err := os.Open(input)

	if err != nil {
		panic(err)
	}

	scanner := bufio.NewScanner(file)
	lines := []string{}

	for scanner.Scan() {
		line := scanner.Text()
		lines = append(lines, line)
	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}

	defer file.Close()

	startingPoint := getStartingPoint(lines[0])
	if startingPoint == -1 {
		panic("No starting point found")
	}

	lines[1] = lines[1][:startingPoint] + "|" + lines[1][startingPoint+1:len(lines[1])]

	for i := 2; i < len(lines); i++ {
		split(&lines, i)
	}

	printDiagram(lines)

	total := countSplits(lines)
	fmt.Println("Total: ", total)
}

// TODO: implement this function to count the number of splits in the diagram
// NOTE: I need to figure out a way to count the splits
// It looks like when three pipes are placed side by side, they are counted as
// 1.5 splits IN PAIR. This is what I could figure out while trying to
// understand the counting...
func countSplits(lines []string) int {
	total := 0
	for _, line := range lines {
		fmt.Println(line)
		total += 0
	}
	return total
}

func split(lines *[]string, idx int) {
	for i := 0; i < len((*lines)[0]); i++ {
		if string((*lines)[idx-1][i]) != "|" {
			continue
		}
		if string((*lines)[idx][i]) == "." {
			(*lines)[idx] = (*lines)[idx][:i] + "|" + (*lines)[idx][i+1:len((*lines)[idx])]
		} else if string((*lines)[idx][i]) == "^" {
			(*lines)[idx] = (*lines)[idx][:i-1] + "|^|" + (*lines)[idx][i+2:len((*lines)[idx])]
		}
	}
}

func printDiagram(lines []string) {
	for _, line := range lines {
		fmt.Println(line)
	}
}

func getStartingPoint(line string) int {
	for i := 0; i < len(line); i++ {
		if line[i] == 'S' {
			return i
		}
	}

	return -1
}

func main() {
	input := "input_test.txt" // Expected output: 21
	// input := "input.txt"
	solveDay7Part1(input)
}
