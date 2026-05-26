package main

import (
	"ACMO/common"
	"fmt"
)

// Метод Жордана-Гаусса с выводом шагов.
// Возвращает ранг, базисные столбцы и признак совместности.
func jordanGaussWithPrint(matrix [][]common.Drob) (int, []int, bool) {
	n := len(matrix)
	m := len(matrix[0])
	numVars := m - 1

	var pivotCols []int
	step := 0
	row, col := 0, 0

	for row < n && col < numVars {
		// Выбор ведущего элемента (с частичным выбором)
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

		if bestRow != row {
			fmt.Printf("  Перестановка строк %d и %d\n", row, bestRow)
			matrix[row], matrix[bestRow] = matrix[bestRow], matrix[row]
		}

		vedusch := matrix[row][col]
		fmt.Printf("  Ведущий элемент: a[%d][%d] = %s\n", row, col, vedusch.ToString())

		// Нормировка ведущей строки
		for j := 0; j < m; j++ {
			matrix[row][j] = matrix[row][j].Divide(vedusch)
		}

		// Обнуление остальных строк в ведущем столбце
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

		step++
		fmt.Printf("\nМатрица после шага %d (обнуление столбца %d):\n", step, col+1)
		common.PrintMatrix(matrix)
		fmt.Println()

		pivotCols = append(pivotCols, col)
		row++
		col++
	}

	// Проверка совместности
	for i := 0; i < n; i++ {
		allZero := true
		for j := 0; j < numVars; j++ {
			if matrix[i][j].Chisl != 0 {
				allZero = false
				break
			}
		}
		if allZero && matrix[i][numVars].Chisl != 0 {
			return len(pivotCols), pivotCols, false
		}
	}

	return len(pivotCols), pivotCols, true
}

// Попытка построить базисное решение для заданного набора базисных столбцов.
// Небазисным переменным присваивается 0.
func tryBasis(origMatrix [][]common.Drob, basisCols []int, numVars int) ([]common.Drob, bool) {
	n := len(origMatrix)
	r := len(basisCols)

	// Формируем подматрицу из базисных столбцов + правая часть
	submat := make([][]common.Drob, n)
	for i := range submat {
		submat[i] = make([]common.Drob, r+1)
		for j, bc := range basisCols {
			submat[i][j] = origMatrix[i][bc]
		}
		submat[i][r] = origMatrix[i][numVars]
	}

	// Жордан-Гаусс на подматрице (без вывода)
	rowPtr := 0
	pivotRowForCol := make([]int, r)
	for i := range pivotRowForCol {
		pivotRowForCol[i] = -1
	}

	for c := 0; c < r; c++ {
		bestRow := -1
		for j := rowPtr; j < n; j++ {
			if submat[j][c].Chisl != 0 {
				bestRow = j
				break
			}
		}
		if bestRow == -1 {
			return nil, false // столбец нулевой — базис вырожден
		}

		submat[rowPtr], submat[bestRow] = submat[bestRow], submat[rowPtr]
		vedusch := submat[rowPtr][c]

		for j := 0; j <= r; j++ {
			submat[rowPtr][j] = submat[rowPtr][j].Divide(vedusch)
		}
		for j := 0; j < n; j++ {
			if j != rowPtr {
				factor := submat[j][c]
				if factor.Chisl != 0 {
					for k := 0; k <= r; k++ {
						submat[j][k] = submat[j][k].Minus(factor.Multiply(submat[rowPtr][k]))
					}
				}
			}
		}

		pivotRowForCol[c] = rowPtr
		rowPtr++
	}

	// Проверка ранга и совместности подсистемы
	if rowPtr < r {
		return nil, false
	}
	for i := 0; i < n; i++ {
		allZero := true
		for j := 0; j < r; j++ {
			if submat[i][j].Chisl != 0 {
				allZero = false
				break
			}
		}
		if allZero && submat[i][r].Chisl != 0 {
			return nil, false
		}
	}

	// Формируем вектор решения (небазисные переменные = 0)
	solution := make([]common.Drob, numVars)
	for i := range solution {
		solution[i] = common.Drob{Chisl: 0, Znam: 1}
	}
	for c, pr := range pivotRowForCol {
		if pr != -1 {
			solution[basisCols[c]] = submat[pr][r]
		}
	}
	return solution, true
}

// Генерация всех комбинаций C(n, r)
func combinations(n, r int) [][]int {
	var result [][]int
	combo := make([]int, r)
	var helper func(start, depth int)
	helper = func(start, depth int) {
		if depth == r {
			c := make([]int, r)
			copy(c, combo)
			result = append(result, c)
			return
		}
		for i := start; i <= n-r+depth; i++ {
			combo[depth] = i
			helper(i+1, depth+1)
		}
	}
	helper(0, 0)
	return result
}

func main() {
	origMatrix := common.ReadMatrix("matrix.txt")

	fmt.Println("Исходная матрица:")
	common.PrintMatrix(origMatrix)
	fmt.Println()

	if len(origMatrix) == 0 {
		fmt.Println("Пустая матрица")
		return
	}

	numVars := len(origMatrix[0]) - 1

	// Жордан-Гаусс с выводом шагов (работаем на копии)
	workMatrix := common.СopyMatrix(origMatrix)
	fmt.Println("=== Шаги метода Жордана-Гаусса ===")
	rank, _, consistent := jordanGaussWithPrint(workMatrix)

	if !consistent {
		fmt.Println("Система не имеет решений (несовместна)")
		return
	}

	fmt.Printf("Ранг системы: %d, количество переменных: %d\n\n", rank, numVars)

	if rank == 0 {
		fmt.Println("Нулевая матрица — тривиальное решение (все переменные свободны)")
		return
	}

	// Поиск всех базисных решений перебором C(numVars, rank) комбинаций
	fmt.Println("=== Поиск всех базисных решений ===")
	fmt.Printf("Перебираем C(%d,%d) = %d комбинаций базисных переменных...\n\n",
		numVars, rank, len(combinations(numVars, rank)))

	combos := combinations(numVars, rank)
	var basicSolutions [][]common.Drob
	var basisSets [][]int

	for _, basisCols := range combos {
		sol, ok := tryBasis(origMatrix, basisCols, numVars)
		if ok {
			basicSolutions = append(basicSolutions, sol)
			basisSets = append(basisSets, basisCols)
		}
	}

	if len(basicSolutions) == 0 {
		fmt.Println("Базисных решений не найдено")
		return
	}

	fmt.Printf("Найдено базисных решений: %d\n\n", len(basicSolutions))

	for i, sol := range basicSolutions {
		basis := basisSets[i]
		basisNames := make([]string, len(basis))
		for j, b := range basis {
			basisNames[j] = fmt.Sprintf("x%d", b+1)
		}
		fmt.Printf("Базисное решение %d  (базис: %v):\n", i+1, basisNames)
		for j, val := range sol {
			fmt.Printf("  x%d = %s\n", j+1, val.ToString())
		}
		fmt.Println()
	}
}
