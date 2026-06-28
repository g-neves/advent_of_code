package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func solve(input string) {
	file, err := os.ReadFile(input)
	if err != nil {
		panic(err)
	}
	total := 0
	str := string(file)
	str = strings.Replace(str, "\n", "", -1)
	parts := strings.Split(str, ",")
	for _, part := range parts {
		split := strings.Index(part, "-")
		startStr := part[:split]
		start, startErr := strconv.Atoi(startStr)
		if startErr != nil {
			panic(startErr)
		}
		endStr := part[split+1:]
		end, endErr := strconv.Atoi(endStr)
		if endErr != nil {
			panic(endErr)
		}
		for i := start; i <= end; i++ {
			iStr := strconv.Itoa(i)
			if len(iStr)%2 != 0 {
				continue
			}
			if iStr[:len(iStr)/2] == iStr[len(iStr)/2:] {
				total += i
			}
		}

	}

	fmt.Println("Total: ", total)
}

func main() {
	// input := "input_test.txt" // Expected output: 1227775554
	input := "input.txt" // 23039913998
	solve(input)
}
