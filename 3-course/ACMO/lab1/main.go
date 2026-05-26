package main

import (
	"ACMO/common"
	"fmt"
)

func ZhordanGauss(matrix [][]common.Drob) ([]common.Drob, string) {
	n := len(matrix)
	if n == 0 {
		return nil, "Пустая матрица"
	}
	m := len(matrix[0])
	numVars := m - 1

	pivotCol := make([]int, n)
	for i := range pivotCol {
		pivotCol[i] = -1
	}

	row, col := 0, 0
	for row < n && col < numVars {
		bestRow := -1
		for j := row; j < n; j++ {
			if matrix[j][col].Chisl != 0 {
				if bestRow == -1 || matrix[j][col].Abs().Compare(matrix[bestRow][col].Abs()) > 0 {
					bestRow = j
				}
			}
		}
		if bestRow == -1 {
			col++
			continue
		}

		fmt.Printf("Меняем %d строку на %d\n", row, bestRow)
		matrix[row], matrix[bestRow] = matrix[bestRow], matrix[row]

		vedusch := matrix[row][col]
		fmt.Printf("Ведущий элемент: %s\n", vedusch.ToString())

		for j := 0; j < m; j++ {
			matrix[row][j] = matrix[row][j].Divide(vedusch)
		}

		fmt.Println("После нормализации:")
		common.PrintMatrix(matrix)
		fmt.Println()

		for j := 0; j < n; j++ {
			if j != row {
				factor := matrix[j][col]
				if factor.Chisl != 0 {
					for k := 0; k < m; k++ {
						matrix[j][k] = matrix[j][k].Minus(factor.Multiply(matrix[row][k]))
					}
				}
			}
		}

		fmt.Printf("После обнуления столбца %d:\n", col)
		common.PrintMatrix(matrix)
		fmt.Println()

		pivotCol[row] = col
		row++
		col++
	}

	for i := 0; i < n; i++ {
		allZero := true
		for j := 0; j < numVars; j++ {
			if matrix[i][j].Chisl != 0 {
				allZero = false
				break
			}
		}
		if allZero && matrix[i][numVars].Chisl != 0 {
			return nil, "Система не имеет решений (несовместна)"
		}
	}

	rank := 0
	for _, pc := range pivotCol {
		if pc != -1 {
			rank++
		}
	}

	if rank < numVars {
		return nil, "Система имеет бесконечно много решений"
	}

	fmt.Println("Единственное решение системы:")
	solution := make([]common.Drob, numVars)
	for i := 0; i < n; i++ {
		if pivotCol[i] != -1 {
			solution[pivotCol[i]] = matrix[i][numVars]
		}
	}
	return solution, ""
}

func main() {
	matrix := common.ReadMatrix("matrix.txt")
	fmt.Println("Исходная матрица:")
	common.PrintMatrix(matrix)

	solution, str := ZhordanGauss(matrix)
	if solution == nil {
		fmt.Print(str)
		return
	}
	fmt.Println("\nРешение:")
	for i, val := range solution {
		if val.Znam == 1 {
			fmt.Printf("x%d = %d\n", i+1, val.Chisl)
		} else {
			fmt.Printf("x%d = %s\n", i+1, val.ToString())
		}
	}
}
