package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func performOperation(numbers []int, operation string) int {
	result := 0
	if operation == "+" {
		for _, num := range numbers {
			result += num
		}
	} else if operation == "*" {
		result = 1
		for _, num := range numbers {
			result *= num
		}
	}
	return result
}

func populateArr(arr [][]int, firstRow []string) [][]int {
	for i := 0; i < len(firstRow); i++ {
		if len(strings.ReplaceAll(firstRow[i], " ", "")) > 0 {
			arr = append(arr, []int{})
		}
	}

	return arr
}

func solveDay6Part1(input string) {
	file, err := os.Open(input)
	if err != nil {
		panic(err)
	}

	total := 0
	scanner := bufio.NewScanner(file)
	arr := [][]int{}
	isLastLine := false
	isPopulated := false
	ops := []string{}

	// Get data
	for scanner.Scan() {
		line := scanner.Text()

		numbers := strings.Split(line, " ")

		if !isPopulated {
			arr = populateArr(arr, numbers)
			isPopulated = true
		}

		if numbers[0] == "*" || numbers[0] == "+" {
			isLastLine = true
		}

		j := 0
		for i := 0; i < len(numbers); i++ {
			numTrimmed := strings.ReplaceAll(numbers[i], " ", "")
			if len(numTrimmed) == 0 {
				continue
			}
			if !isLastLine {
				n, err := strconv.Atoi(numTrimmed)
				if err != nil {
					panic(err)
				}
				arr[j] = append(arr[j], n)
			} else {
				if numTrimmed == "+" || numTrimmed == "*" {
					ops = append(ops, numTrimmed)
				}
			}

			j++
		}
	}

	for i, num := range arr {
		total += performOperation(num, ops[i])
	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}

	fmt.Println("Total: ", total)
}

func main() {
	// input := "input_test.txt" // Expected output: 4277556
	input := "input.txt" // 7326876294741
	solveDay6Part1(input)
}
