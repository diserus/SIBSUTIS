package common

import (
	"fmt"
)

type Drob struct {
	Chisl int
	Znam  int
}

func NewDrob(Chisl, Znam int) Drob {
	if Znam == 0 {
		panic("знаменатель не должен быть 0")
	}
	if Znam < 0 {
		Znam = -Znam
		Chisl = -Chisl
	}
	divisor := gcd(Chisl, Znam)

	return Drob{Chisl: Chisl / divisor, Znam: Znam / divisor}
}
func gcd(a, b int) int {
	a = abs(a)
	b = abs(b)
	for b != 0 {
		a, b = b, a%b
	}
	return a
}
func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

func (d Drob) Multiply(other Drob) Drob {
	return NewDrob(
		d.Chisl*other.Chisl,
		d.Znam*other.Znam)

}
func (d Drob) Divide(other Drob) Drob {
	return NewDrob(
		d.Chisl*other.Znam,
		d.Znam*other.Chisl)
}
func (d Drob) Sum(other Drob) Drob {
	newChisl := d.Chisl*other.Znam + other.Chisl*d.Znam
	newZnam := d.Znam * other.Znam
	return NewDrob(newChisl, newZnam)
}
func (d Drob) Minus(other Drob) Drob {
	newChisl := d.Chisl*other.Znam - other.Chisl*d.Znam
	newZnam := d.Znam * other.Znam
	return NewDrob(newChisl, newZnam)
}

func (d Drob) Abs() Drob {
	if d.Chisl < 0 {
		d.Chisl = -d.Chisl
	}
	return d

}
func (d Drob) Compare(other Drob) int {
	diff := d.Minus(other)
	if diff.Chisl > 0 {
		return 1
	} else if diff.Chisl < 0 {
		return -1
	}
	return 0
}
func (d Drob) ToString() string {
	if d.Znam == 1 || d.Chisl == 0 {
		return fmt.Sprintf("%d", d.Chisl)
	}
	return fmt.Sprintf("%d/%d", d.Chisl, d.Znam)
}
