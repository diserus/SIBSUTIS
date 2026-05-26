package main

import (
	"ACMO/common"
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintln(os.Stderr, "Использование: rgz <файл_входных_данных>")
		os.Exit(1)
	}

	A, b, c, err := readInput(os.Args[1])
	if err != nil {
		fmt.Fprintf(os.Stderr, "Ошибка чтения файла: %v\n", err)
		os.Exit(1)
	}

	n := len(c)
	result := SolveLP(A, b, c)
	printResult(result, n)
}

func readInput(path string) (A [][]common.Drob, b []common.Drob, c []common.Drob, err error) {
	f, err := os.Open(path)
	if err != nil {
		return
	}
	defer f.Close()

	var rows [][]common.Drob
	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" || strings.HasPrefix(line, "#") {
			continue
		}
		parts := strings.Fields(line)
		row := make([]common.Drob, len(parts))
		for i, p := range parts {
			row[i], err = parseDrob(p)
			if err != nil {
				return
			}
		}
		rows = append(rows, row)
	}
	if scanner.Err() != nil {
		err = scanner.Err()
		return
	}
	if len(rows) < 2 {
		err = fmt.Errorf("недостаточно строк в файле")
		return
	}

	m := len(rows) - 1
	n := len(rows[0]) - 1

	A = make([][]common.Drob, m)
	b = make([]common.Drob, m)
	for i := 0; i < m; i++ {
		if len(rows[i]) != n+1 {
			err = fmt.Errorf("несовместимая длина строки %d", i+1)
			return
		}
		A[i] = rows[i][:n]
		b[i] = rows[i][n]
	}

	if len(rows[m]) < n {
		err = fmt.Errorf("строка целевой функции слишком короткая")
		return
	}
	c = rows[m][:n]
	return
}

func parseDrob(s string) (common.Drob, error) {
	parts := strings.SplitN(s, "/", 2)
	chisl, err := strconv.Atoi(parts[0])
	if err != nil {
		return common.Drob{}, fmt.Errorf("неверное число: %s", s)
	}
	if len(parts) == 1 {
		return common.NewDrob(chisl, 1), nil
	}
	znam, err := strconv.Atoi(parts[1])
	if err != nil {
		return common.Drob{}, fmt.Errorf("неверное число: %s", s)
	}
	return common.NewDrob(chisl, znam), nil
}
