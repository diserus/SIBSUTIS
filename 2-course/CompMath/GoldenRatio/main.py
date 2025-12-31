def f(x):
    return x**2-6*x
def golden(a,b,eps):
    it = 0
    k1 = 0.382 
    k2 = 1-k1
    lambda1 = a + k1 * (b - a)
    lambda2 = a + k2 * (b - a)
    f1 = f(lambda1)
    f2 = f(lambda2)
    while abs(b-a)>eps:
        it+=1
        print(f"Текущая итерация: {it}")
        if f1 > f2:
            a = lambda1
            lambda1 = lambda2
            f1 = f2
            lambda2 = a + k2 * (b - a)
            f2 = f(lambda2)
        else:
            b = lambda2
            lambda2 = lambda1
            f2 = f1
            lambda1 = a + k1 * (b - a)
            f1 = f(lambda1)
        print(f"Текущий интервал [{a} ; {b}]")
        print(f"Значения функции: f({lambda1}) = {f1}, f({lambda2}) = {f2}\n")
    x = (a+b)/2
    print(f"\n\nМинимум функции находится в интервале [ {a} ; {b}]")
    print(f"\nПриблизительное значение минимума: x = {x}")
    print(f"\nЗначение функции f({x}) = {f(x)}")
    print(f"Количество итераций: {it}")

if __name__=="__main__":
    a=0
    b=5
    eps = 10**(-5)
    print(f"Исследуемый интервал: [{a} ; {b}]")
    print("Функция: f(x) = x^2 - 6x\n")
    golden(a,b,eps)