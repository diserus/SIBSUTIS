from math import sqrt,factorial
def lagrange(x,y,point):
    n = len(x)
    result = 0
    for i in range(n):
        term = y[i]
        for j in range(n):
            if j!=i:
                term*=(point-x[j])/(x[i]-x[j]) 
        result+=term
    return result
def pogreshnost(point):
    m4 = 15/16
    koef = abs((point-1)*(point-2)*(point-3)*(point-4))
    eps_usech = (m4/factorial(4))*koef
    eps_okr = 10**(-5)
    eps_real = eps_okr + eps_usech
    return eps_real
def f(x):
    return sqrt(x)
if __name__=='__main__':
    x = [1, 2, 3, 4]
    y = [1, 1.4142, 1.7321, 2]
    point = 2.56
    interpolated = lagrange(x, y, point)
    print(f"\nИнтерполяция по формуле Лагранжа для x = {point}")
    print ("\nФункция y = sqrt(x)")
    print(f"\nPn({point}) = {interpolated}")
    print(f"\nТочное значение по функции y = {f(point)}")
    print(f"\nРазница составила: {interpolated - f(point)}")
    print(f"\nРеальная погрешность = {pogreshnost(point)}")