package main

import (
	"ACMO/common"
	"fmt"
	"strings"
	"unicode/utf8"
)

var zero = common.NewDrob(0, 1)
var one = common.NewDrob(1, 1)

func neg(d common.Drob) common.Drob {
	return common.NewDrob(-d.Chisl, d.Znam)
}

type SimplexTable struct {
	rows  int
	cols  int
	tab   [][]common.Drob // tab[i][cols] — правая часть b, остальные — коэффициенты
	basis []int           // basis[i] — индекс базисной переменной в строке i
}

func newTable(rows, cols int) *SimplexTable {
	tab := make([][]common.Drob, rows)
	for i := range tab {
		tab[i] = make([]common.Drob, cols+1) // +1 для столбца b
		for j := range tab[i] {
			tab[i][j] = zero
		}
	}
	return &SimplexTable{rows: rows, cols: cols, tab: tab, basis: make([]int, rows)}
}

// pivot выполняет один шаг метода Гаусса: вводит переменную pivCol в базис строки pivRow.
// После этого столбец pivCol становится единичным (1 в строке pivRow, 0 в остальных).
func (t *SimplexTable) pivot(pivRow, pivCol int) {
	pivElem := t.tab[pivRow][pivCol]
	// Нормируем разрешающую строку, чтобы разрешающий элемент стал 1
	for j := 0; j <= t.cols; j++ {
		t.tab[pivRow][j] = t.tab[pivRow][j].Divide(pivElem)
	}
	// Обнуляем разрешающий столбец во всех остальных строках
	for i := 0; i < t.rows; i++ {
		if i == pivRow {
			continue
		}
		factor := t.tab[i][pivCol]
		if factor.Chisl == 0 {
			continue
		}
		for j := 0; j <= t.cols; j++ {
			t.tab[i][j] = t.tab[i][j].Minus(factor.Multiply(t.tab[pivRow][j]))
		}
	}
	t.basis[pivRow] = pivCol
}

// chooseLeaving выбирает выходящую переменную по правилу минимального отношения θ = bᵢ / aᵢⱼ.
// Рассматриваются только строки с aᵢⱼ > 0 — иначе θ отрицателен или не определён,
// что привело бы к выходу за пределы допустимой области.
func chooseLeaving(t *SimplexTable, col int) int {
	minRow := -1
	var minRatio common.Drob
	for i := 0; i < t.rows; i++ {
		aij := t.tab[i][col]
		if aij.Chisl <= 0 {
			continue
		}
		ratio := t.tab[i][t.cols].Divide(aij)
		if minRow == -1 || ratio.Compare(minRatio) < 0 {
			minRow = i
			minRatio = ratio
		}
	}
	return minRow
}

func varName(j, n int) string {
	if j < n {
		return fmt.Sprintf("x%d", j+1)
	}
	return fmt.Sprintf("a%d", j-n+1)
}

func printTableau(t *SimplexTable, n int, delta []common.Drob, pivRow, pivCol int) {
	total := t.cols

	rlen := utf8.RuneCountInString
	colCount := total + 2
	widths := make([]int, colCount)

	header := make([]string, colCount)
	header[0] = "Базис"
	for j := 0; j < total; j++ {
		header[j+1] = varName(j, n)
	}
	header[colCount-1] = "b"
	for i, h := range header {
		if rlen(h) > widths[i] {
			widths[i] = rlen(h)
		}
	}

	cells := make([][]string, t.rows)
	for i := 0; i < t.rows; i++ {
		cells[i] = make([]string, colCount)
		cells[i][0] = varName(t.basis[i], n)
		for j := 0; j < total; j++ {
			cells[i][j+1] = t.tab[i][j].ToString()
		}
		cells[i][colCount-1] = t.tab[i][total].ToString()
		for k, s := range cells[i] {
			if rlen(s) > widths[k] {
				widths[k] = rlen(s)
			}
		}
	}

	deltaRow := make([]string, colCount)
	deltaRow[0] = "Δ"
	if delta != nil {
		for j := 0; j < n; j++ {
			deltaRow[j+1] = delta[j].ToString()
		}
		// Столбцы искусственных переменных в строке Δ не заполняются —
		// их оценки не используются и могут сбить с толку
		for j := n; j < total; j++ {
			deltaRow[j+1] = "—"
		}
	}
	deltaRow[colCount-1] = ""
	for k, s := range deltaRow {
		if rlen(s) > widths[k] {
			widths[k] = rlen(s)
		}
	}

	pad := func(s string, w int) string {
		return strings.Repeat(" ", w-rlen(s)) + s
	}
	hline := func() {
		parts := make([]string, colCount)
		for i, w := range widths {
			parts[i] = strings.Repeat("-", w+2)
		}
		fmt.Println(strings.Join(parts, "+"))
	}
	printRow := func(row []string, markCol int) {
		parts := make([]string, colCount)
		for i, s := range row {
			cell := " " + pad(s, widths[i]) + " "
			if markCol >= 0 && i == markCol+1 {
				cell = "[" + pad(s, widths[i]) + "]"
			}
			parts[i] = cell
		}
		fmt.Println(strings.Join(parts, "|"))
	}

	hline()
	printRow(header, -1)
	hline()
	for i, row := range cells {
		mc := -1
		if i == pivRow && pivCol >= 0 {
			mc = pivCol
		}
		printRow(row, mc)
	}
	hline()
	printRow(deltaRow, -1)
	hline()
}

const (
	Optimal    = 0
	Infeasible = 1
	Unbounded  = 2
	MultiSol   = 3
)

type LPResult struct {
	Code      int
	Solutions [][]common.Drob
	ObjVal    common.Drob
}

func SolveLP(A [][]common.Drob, b []common.Drob, c []common.Drob) LPResult {
	m := len(A)
	n := len(c)
	total := n + m // n исходных + m искусственных переменных

	t := newTable(m, total)

	// Строим начальную таблицу фазы 1.
	// Искусственная переменная aᵢ (индекс n+i) становится базисной для строки i.
	// Если bᵢ < 0, умножаем строку на -1, чтобы значение базисной переменной было ≥ 0 —
	// это необходимое условие допустимости начального базиса.
	for i := 0; i < m; i++ {
		sign := one
		if b[i].Chisl < 0 {
			sign = neg(one)
		}
		for j := 0; j < n; j++ {
			t.tab[i][j] = A[i][j].Multiply(sign)
		}
		t.tab[i][n+i] = one
		t.tab[i][total] = b[i].Multiply(sign)
		t.basis[i] = n + i
	}

	// Оценки Δⱼ для фазы 1: минимизируем W = Σaᵢ.
	// Δⱼ = −∑{ строки с искусственной в базисе } aᵢⱼ
	// Знак минус потому что задача — минимизация, а симплекс-метод ищет Δⱼ < 0.
	phase1Delta := func() []common.Drob {
		delta := make([]common.Drob, n)
		for j := 0; j < n; j++ {
			s := zero
			for i := 0; i < m; i++ {
				if t.basis[i] >= n { // строка с искусственной переменной в базисе
					s = s.Sum(t.tab[i][j])
				}
			}
			delta[j] = neg(s)
		}
		return delta
	}

	fmt.Println("╔══════════════════════════════════════╗")
	fmt.Println("║        ФАЗА 1: Поиск базиса          ║")
	fmt.Println("╚══════════════════════════════════════╝")
	fmt.Println("\nНачальная таблица:")
	printTableau(t, n, phase1Delta(), -1, -1)

	step := 1
	for {
		delta := phase1Delta()
		entering := -1
		for j := 0; j < n; j++ {
			if delta[j].Chisl < 0 {
				entering = j // первая переменная с Δⱼ < 0 — правило Блэнда для избежания зацикливания
				break
			}
		}
		if entering == -1 {
			break // все Δⱼ ≥ 0 — вспомогательная задача решена
		}
		leaving := chooseLeaving(t, entering)
		if leaving == -1 {
			break // не должно произойти при W = Σaᵢ (функция ограничена снизу нулём)
		}
		fmt.Printf("\nШаг %d: вводим %s, выводим %s  (элемент = %s)\n",
			step, varName(entering, n), varName(t.basis[leaving], n),
			t.tab[leaving][entering].ToString())
		t.pivot(leaving, entering)
		step++
		printTableau(t, n, phase1Delta(), -1, -1)
	}

	// Проверяем несовместность: если хоть одна искусственная переменная осталась
	// в базисе с ненулевым значением — W > 0, допустимой точки не существует.
	for i := 0; i < m; i++ {
		if t.basis[i] >= n && t.tab[i][total].Chisl != 0 {
			fmt.Println("\n→ Искусственные переменные ненулевые — система несовместна.")
			return LPResult{Code: Infeasible}
		}
	}
	fmt.Println("\n→ Допустимый базис найден.")

	// Оценки Δⱼ для фазы 2: стандартная формула симплекс-метода.
	// Δⱼ = ∑ᵢ cᵦᵢ·aᵢⱼ − cⱼ, где cᵦᵢ — коэффициент целевой функции базисной переменной.
	// Искусственные переменные имеют cᵦᵢ = 0, чтобы не влиять на исходную задачу.
	phase2Delta := func() []common.Drob {
		delta := make([]common.Drob, n)
		for j := 0; j < n; j++ {
			s := zero
			for i := 0; i < m; i++ {
				bv := t.basis[i]
				var cb common.Drob
				if bv < n {
					cb = c[bv]
				} else {
					cb = zero // искусственная переменная не входит в исходную целевую функцию
				}
				s = s.Sum(cb.Multiply(t.tab[i][j]))
			}
			delta[j] = s.Minus(c[j])
		}
		return delta
	}

	fmt.Println("\n╔══════════════════════════════════════╗")
	fmt.Println("║      ФАЗА 2: Оптимизация             ║")
	fmt.Println("╚══════════════════════════════════════╝")
	fmt.Println("\nТаблица после фазы 1:")
	printTableau(t, n, phase2Delta(), -1, -1)

	step = 1
	for {
		delta := phase2Delta()
		entering := -1
		for j := 0; j < n; j++ {
			if delta[j].Chisl < 0 {
				entering = j
				break
			}
		}
		if entering == -1 {
			break // все Δⱼ ≥ 0 — достигнут оптимум
		}
		leaving := chooseLeaving(t, entering)
		if leaving == -1 {
			// Нет строк с aᵢⱼ > 0 — целевая функция неограниченно растёт вдоль направления xⱼ
			fmt.Println("\n→ Целевая функция не ограничена.")
			return LPResult{Code: Unbounded}
		}
		fmt.Printf("\nШаг %d: вводим %s, выводим %s  (элемент = %s)\n",
			step, varName(entering, n), varName(t.basis[leaving], n),
			t.tab[leaving][entering].ToString())
		t.pivot(leaving, entering)
		step++
		printTableau(t, n, phase2Delta(), -1, -1)
	}
	fmt.Println("\n→ Все Δ ≥ 0 — оптимум достигнут.")

	// Считываем решение: небазисные переменные равны 0, базисные — значению b в их строке
	extractSol := func() []common.Drob {
		x := make([]common.Drob, n)
		for j := range x {
			x[j] = zero
		}
		for i := 0; i < m; i++ {
			if t.basis[i] < n {
				x[t.basis[i]] = t.tab[i][total]
			}
		}
		return x
	}

	sol1 := extractSol()
	objVal := zero
	for j := 0; j < n; j++ {
		objVal = objVal.Sum(c[j].Multiply(sol1[j]))
	}

	delta := phase2Delta()
	altSols := [][]common.Drob{sol1}

	// Поиск второго оптимального решения.
	// Если небазисная переменная имеет Δⱼ = 0, она может войти в базис без изменения Z —
	// это означает, что оптимум достигается на целом ребре (бесконечно много решений).
	for j := 0; j < n; j++ {
		if delta[j].Chisl != 0 {
			continue
		}
		isBasic := false
		for i := 0; i < m; i++ {
			if t.basis[i] == j {
				isBasic = true
				break
			}
		}
		if isBasic {
			continue
		}
		leaving := chooseLeaving(t, j)
		if leaving == -1 {
			continue
		}
		fmt.Printf("\n→ %s небазисная с Δ=0 — ищем второе решение (вводим %s).\n",
			varName(j, n), varName(j, n))
		t.pivot(leaving, j)
		sol2 := extractSol()
		obj2 := zero
		for k := 0; k < n; k++ {
			obj2 = obj2.Sum(c[k].Multiply(sol2[k]))
		}
		if obj2.Compare(objVal) == 0 {
			altSols = append(altSols, sol2)
		}
		break // достаточно одного дополнительного решения по условию задания
	}

	code := Optimal
	if len(altSols) > 1 {
		code = MultiSol
	}
	return LPResult{Code: code, Solutions: altSols, ObjVal: objVal}
}

func printResult(r LPResult, n int) {
	fmt.Println("\n════════════════════════════════════════")
	switch r.Code {
	case Infeasible:
		fmt.Println("РЕЗУЛЬТАТ: Решение отсутствует (система несовместна).")
	case Unbounded:
		fmt.Println("РЕЗУЛЬТАТ: Целевая функция не ограничена.")
	case Optimal:
		fmt.Println("РЕЗУЛЬТАТ: Оптимальное решение:")
		printSol(r.Solutions[0], n)
		fmt.Printf("Z = %s\n", r.ObjVal.ToString())
	case MultiSol:
		fmt.Println("РЕЗУЛЬТАТ: Бесконечно много решений. Два из них:")
		fmt.Println("\nРешение 1:")
		printSol(r.Solutions[0], n)
		fmt.Println("\nРешение 2:")
		printSol(r.Solutions[1], n)
		fmt.Printf("\nZ = %s\n", r.ObjVal.ToString())
	}
	fmt.Println("════════════════════════════════════════")
}

func printSol(x []common.Drob, n int) {
	for j := 0; j < n; j++ {
		fmt.Printf("  x%d = %s\n", j+1, x[j].ToString())
	}
}
