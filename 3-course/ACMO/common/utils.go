package common

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func ReadMatrix(filename string) [][]Drob {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	var matrix [][]Drob
	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Fields(line)
		row := make([]Drob, len(parts))
		for i, p := range parts {
			val, _ := strconv.Atoi(p)
			row[i] = NewDrob(val, 1)
		}
		matrix = append(matrix, row)
	}
	return matrix
}
func PrintMatrix(matrix [][]Drob) {
	for i := range matrix {
		for _, val := range matrix[i] {

			fmt.Print(val.ToString())
			fmt.Print(" ")
		}
		fmt.Print("\n")
	}

}

func СopyMatrix(matrix [][]Drob) [][]Drob {
	mat := make([][]Drob, len(matrix))
	for i := range mat {
		mat[i] = make([]Drob, len(matrix[i]))
		copy(mat[i], matrix[i])
	}
	return mat
}
