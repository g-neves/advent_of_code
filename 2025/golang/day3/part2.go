package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func solveDay3Part2(input string) {
	file, err := os.Open(input)
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	total := 0
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		maxDigits := findMaxDigits(line)

		var strBuilder strings.Builder
		strBuilder.Grow(12)
		for _, idx := range maxDigits {
			strBuilder.WriteByte(line[idx])
		}

		lineTotalNum, err := strconv.Atoi(strBuilder.String())
		if err != nil {
			log.Fatal(err)
		}
		total += lineTotalNum
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	fmt.Println("Total: ", total)
}

func findMaxDigits(line string) []int {
	idxs := make([]int, 12)
	lenLine := len(line)
	start := 0
	for i := 0; i < 12; i++ {
		for j := start; j < lenLine-12+i+1; j++ {
			if line[j] > line[idxs[i]] {
				idxs[i] = j
			}
		}
		start = idxs[i] + 1
		if i < 11 {
			idxs[i+1] = idxs[i] + 1
		}
	}

	return idxs
}

func main() {
	// input := "input_test.txt" // 3121910778619
	input := "input.txt" // 169408143086082
	solveDay3Part2(input)
}
