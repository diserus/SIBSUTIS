from math import sqrt,factorial


def matrixPrint(matrix):
    max_len = max(len(f"{col:.4g}") for row in matrix for col in row)

    for row in matrix:
        for col in row:
            val = f"{col:.4g}"  
            print(f"{val:>{max_len+2}}", end="")
        print()
    print()

def lagrange(x,y,point):
    n = len(x)
    result = 0
    for i in range(n):
        chisl = 1
        znam = 1
        for j in range(n):
            if j!=i:
                chisl *= point - x[j]
                znam *=x[i]-x[j] 
        result+=y[i] *(chisl/znam)
    return result

def eitken(x, y, point):
    n = len(x)
    P = [[0] * n for _ in range(n)]
    
    for i in range(n):
        P[i][0] = y[i]
    
    for j in range(1,n):
        for i in range(j,n):
             P[i][j] = ((point - x[i-j]) * P[i][j-1] - (point - x[i]) * P[i-1][j-1]) / (x[i] - x[i-j])
    return P[n-1][-1],P

def pogreshnost(point):
    m4 = 15/16
    koef = abs((point-1)*(point-2)*(point-3)*(point-4))
    eps_usech = (m4/factorial(4))*koef
    eps_okr = 10**(-5)
    eps_real = eps_okr + eps_usech
    return eps_real

if __name__=='__main__':
    x = [1,2, 3, 4]
    y = [1, 1.4142, 1.7321, 2]
    point = 2.56
    interpol_lagrange = lagrange(x, y, point)
    print ("\nФункция y = sqrt(x)\n")
    print(f"Точное значение функции для x = {point} | y = {sqrt(point)}\n\n")
    print(f"\nИнтерполяция по формуле Лагранжа для x = {point}")
    print(f"Pn({point}) = {interpol_lagrange}")

    interpol_eitken,P = eitken(x,y,point)
    print(f"\nИнтерполяция по формуле Эйткена для x = {point}")
    print(f"Pn({point}) = {interpol_eitken}")
    matrixPrint(P)
    print(f"\nСравнение в точке x = {point}\n")
    print(f"Лагранж: {interpol_lagrange} (Разница: {abs(interpol_lagrange)-sqrt(point)})")
    print(f"Эйткен: {interpol_eitken} (Разница: {abs(interpol_eitken)-sqrt(point)})")

    print(f"\nРеальная погрешность = {pogreshnost(point)}")
