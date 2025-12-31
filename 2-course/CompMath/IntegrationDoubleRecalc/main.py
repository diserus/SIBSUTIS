import numpy as np
def f(x): 
    return 1/x

def trapezoid(a,b,h):
    n = int((b - a) / h)+1
    x = [a + i * h for i in range(n)]
    y = [f(i) for i in x]
    result = 0
    for i in range(n-1):
        result += h * ((y[i] + y[i+1])/2)
    return result,x,y
def simpson(a,b,h):
    n = int((b - a) / h)+1
    if (n-1)%2!=0:
        print("Для Симпсона требуется четное число отрезков")
        return
    x = [a + i * h for i in range(n)]
    y = [f(i) for i in x]
    result = 0
    for i in range(0,n-2,2):
        result+=(2*h)*((1/6)*y[i] + (2/3)*y[i+1] + (1/6)*y[i+2])
    return result,x,y


if __name__ == "__main__":
    h_start =0.1
    a=1
    b=2
    eps = 10**(-8)
    h = h_start
    exact = np.log(b) - np.log(a) 
    iterations = 0
    print(f"\nТочное значение ln({b/a}) = {exact}")  
    print(f"\nИнтеграл от {a} до {b} функции f(x) = 1/x\n")
    print(f"Точность: {eps}\n")
    print("h = ", h, '\n')

    print("=" * 10, "Формула Трапеций ", "=" * 10, "\n")

    while True:
        iterations += 1
        first,_,_ = trapezoid(a,b,h)
        second,_,_ = trapezoid(a, b,h/2)
        print(f"h = {h}, I(h) = {first}, I(h/2) = {second}")
        print("Количество отрезков: ", int((b - a) / h))
        abs_err = abs(second-exact)
        print(f"Абсолютная погрешность: |I(h/2)-I_exact| = {abs_err}\n")
        if abs(first - second) < eps * 3:
            h/=2
            break
        h /= 2

    solution,x,y = trapezoid(a,b,h)
    print("\n","=" * 10, "РЕЗУЛЬТАТЫ ФОРМУЛЫ ТРАПЕЦИЙ", "=" * 10)
    print(f"Количество итераций: {iterations}")
    print(f"Итоговый шаг: {h}")
    print(f"Значение интеграла I = {solution}\n")
    print(f"\nТаблица значений (шаг = {h:.6f}):")    
    print("  x\t\tF(x)")
    k = 10
    for x_val, y_val in zip(x[:k], y[:k]):
        print(f"{x_val:.6f}\t{y_val:.6f}")
    print("...")
    for x_val, y_val in zip(x[-k:], y[-k:]):
        print(f"{x_val:.6f}\t{y_val:.6f}")
    iterations = 0
    h = h_start
    print("\n","=" * 10, "Формула Симпсона ", "=" * 10, "\n")

    while True:
        iterations += 1
        first,_,_ = simpson(a,b,h)
        second,_,_ = simpson(a,b,h/2)
        print(f"h = {h}, I(h) = {first}, I(h/2) = {second}")
        print("Количество отрезков: ", int((b - a) / h))
        abs_err = abs(second-exact)
        print(f"Абсолютная погрешность: |I(h/2)-I_exact| = {abs_err}\n")
        if abs(first - second) < eps * 15:
            break
        h /= 2
        
    solution,x,y = simpson(a,b,h)
    print("\n","=" * 10, "РЕЗУЛЬТАТЫ ФОРМУЛЫ СИМПСОНА", "=" * 10)
    print(f"Количество итераций: {iterations}")
    print(f"Итоговый шаг: {h}")
    print(f"Значение интеграла I = {solution}\n")
    print(f"\nТаблица значений (шаг = {h:.6f}):")    
    print("  x\t\tF(x)")
    k = 10
    for x_val, y_val in zip(x[:k], y[:k]):
        print(f"{x_val:.6f}\t{y_val:.6f}")
    print("...")
    for x_val, y_val in zip(x[-k:], y[-k:]):
        print(f"{x_val:.6f}\t{y_val:.6f}")

