package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
	"strconv"
)


// Perform the desired operation
func performOperationStr(numbers []string, operation string) int {
	result := 0
	if operation == "*" {
		result = 1 
	} else if operation == "+" {
		result = 0
	}
	nums := []string{}
	numsInt := []int{}
	for i := 0; i < len(numbers[0]); i++ {
		nums = append(nums, "")
	}

	for i := 0; i < len(numbers[0]); i++ {
		for j := range numbers {
			nums[i] = nums[i] + string(numbers[j][i])
		}
	}

	for _, num := range nums {
		int, err := strconv.Atoi(strings.ReplaceAll(num, " ", ""))
		if err != nil {
			panic(err)
		}
		numsInt = append(numsInt, int)
	}

	for _, num := range numsInt {
		if operation == "+" {
			result += num
		} else if operation == "*" {
			result *= num
		}
	}

	return result
}

// Get indexes of spaces in each line, and count how many times each index has a space
func getSpacesIndexes(lines []string) map[int]int {
	spaces := make(map[int]int)
	for _, line := range lines {
		for i := 0; i < len(line); i++ {
			if string(line[i]) == " " {
			spaces[i]++
			}
		}
	}

	return spaces
}

// Get indexes of spaces that are common to all lines, and also include -1 and the last index of the line
func getCommonSpaces(spaces *map[int]int, maxSeparator, maxIdx int) []int {
	commonSpaces := []int{}
	for key, val := range *spaces {
		if val == maxSeparator {
			commonSpaces = append(commonSpaces, key)
		}
	}

	commonSpaces = append(commonSpaces, -1)
	commonSpaces = append(commonSpaces, maxIdx)
	sort.Ints(commonSpaces)
	return commonSpaces
}

// Find the maximum value in the map of spaces
// This is used so that we can find the common spaces
// NOTE: This should be the same as the number of lines in the input, 
// because the common spaces are the spaces that are present in all lines
func findMaxSeparator(spaces *map[int]int) int {
	maxSeparator := 0
	for _, val := range *spaces {
		if val > maxSeparator {
			maxSeparator = val
		}
	}
	return maxSeparator
}

// Get operations from last line
func getOperations(lines []string) []string {
	ops := []string{}
	for i := 0; i < len(lines[len(lines)-1]); i++ {
		if lines[len(lines)-1][i] != ' ' {
			ops = append(ops, string(lines[len(lines)-1][i]))
		}
	}
	return ops
}

// Just construct the matrix of numbers based on the common spaces found in the lines
// aligned in columns
func constructMatrix(lines []string, commonSpaces []int) [][]string {
	matrix := [][]string{}
	for i := 0; i < len(commonSpaces)-1; i++ {
		row := []string{}
		for _, line := range lines {
			row = append(row, string(line[commonSpaces[i]+1:commonSpaces[i+1]]))

		}
		matrix = append(matrix, row)
	}
	return matrix
}

// find the longest line in the input to make sure we 
// include trailing spaces in each line to make them all the same length
func findLongestLine(lines []string) int {
	longestLine := 0
	for _, line := range lines {
		if len(line) > longestLine {
			longestLine = len(line)
		}
	}
	return longestLine
}

// Include trailing spaces in each line to make them all the same length
// because sometimes the last number would be x in one line and yy in another line, 
// and we need to make sure they are all the same length because the digits in the 
// operations are aligned by their position in the line.
func includeTrailingSpaces(lines *[]string, longestLine int) {
	for i := 0; i < len(*lines); i++ {
		if len((*lines)[i]) < longestLine {
			(*lines)[i] = (*lines)[i] + strings.Repeat(" ", longestLine-len((*lines)[i]))
		}
	}
}

func solveDay6Part2(input string) {
	file, err := os.Open(input)
	if err != nil {
		panic(err)
	}

	total := 0
	scanner := bufio.NewScanner(file)
	lines := []string{}

	for scanner.Scan() {
		line := scanner.Text()
		lines = append(lines, line)
	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}

	ops := getOperations(lines)
	lines = lines[:len(lines)-1] // exclude operations
	longestLine := findLongestLine(lines)
	includeTrailingSpaces(&lines, longestLine)
	spaces := getSpacesIndexes(lines)
	maxSeparator := findMaxSeparator(&spaces)
	commonSpaces := getCommonSpaces(&spaces, maxSeparator, len(lines[0]))
	matrix := constructMatrix(lines, commonSpaces)

	for i := 0; i < len(matrix); i++ {
		total += performOperationStr(matrix[i], ops[i])
	}

	fmt.Println("Total: ", total)
}

func main() {
	// input := "input_test.txt" // Expected output: 3263827
	input := "input.txt" // 10756006415204
	solveDay6Part2(input)
}
