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
			for j := 1; j < len(iStr)/2+1; j++ {
				pattern := iStr[:j]
				if strings.Repeat(pattern, len(iStr)/j) == iStr {
					total += i
					break
				}
			}
		}
	}

	fmt.Println("Total: ", total)
}

func main() {
	// input := "input_test.txt" // Expected output: 4174379265
	input := "input.txt" // 35950619148
	solve(input)
}
