def f(x, y):
    return 2 * x - y
def euler(x0, y0, target, h):
    n = int(round((target - x0) / h))
    xs = [x0 + i*h for i in range(n+1)]
    ys = [y0]
    x, y = x0, y0
    for _ in range(n):
        y = y + h * f(x, y)
        x = x + h
        ys.append(y)
    return xs, ys
def runge_kutta2_time(x0, y0, target, h):
    n = int(round((target - x0) / h))
    xs = [x0 + i*h for i in range(n+1)]
    ys = [y0]
    x, y = x0, y0
    for _ in range(n):
        y_sr = y + (h/2) * f(x, y)
        y = y + h * f(x+h/2, y_sr)
        x = x + h
        ys.append(y)
    return xs, ys
def runge_kutta2_diff(x0, y0, target, h):
    n = int(round((target - x0) / h))
    xs = [x0 + i*h for i in range(n+1)]
    ys = [y0]
    x, y = x0, y0
    for _ in range(n):
        y_sr = y + (h/2) * f(x, y)
        y = y + h * f(x+h/2, y_sr)
        x = x + h
        ys.append(y)
    return xs, ys
def runge_kutta4(x0, y0, target, h):
    n = int(round((target - x0) / h))
    xs = [x0 + i*h for i in range(n+1)]
    ys = [y0]
    x, y = x0, y0
    for _ in range(n):
        k1 = f(x, y)
        k2 = f(x + h/2, y + (h/2) * k1)
        k3 = f(x + h/2, y + (h/2) * k2)
        k4 = f(x + h, y + h * k3)
        y = y + (h/6) * (k1 + 2*k2 + 2*k3 + k4)
        x = x + h
        ys.append(y)
    return xs, ys
def print_table(x, y, h):
    print(f"\nТаблица значений (шаг = {h:.6f}):")    
    print("\nx\t\ty")
    k = 10
    for x_val, y_val in zip(x[:k], y[:k]):
        print(f"{x_val:.6f}\t{y_val:.6f}")
    print("...")
    for x_val, y_val in zip(x[-k:], y[-k:]):
        print(f"{x_val:.6f}\t{y_val:.6f}")
if __name__ == "__main__":
    x0 = 1
    y0 = 3
    h = 0.2
    target = 2  
    eps = 10**-6 
    iterations = 0
    print("\nРешение дифференциального уравнения y' = 2x - y")
    print(f"Начальные условия: y({x0}) = {y0}")
    print(f"Начальный шаг: {h}")
    print(f"Целевая точка: x = {target}")
    print(f"Требуемая точность: {eps}\n")
    print("=" * 10, "Метод Эйлера ", "=" * 10, "\n")


    while True:
        iterations += 1
        x_h, y_h = euler(x0, y0, target, h)
        x_h2, y_h2 = euler(x0, y0, target, h / 2)

        diffs = [abs(y_h2[2*i] - y_h[i]) for i in range(len(y_h))]
        err = max(diffs)

        print(f"Шаг h={h:.6f}, max|y_h2 - y_h|={err:.6f}")
        if err < eps:
            h /= 2
            break
        h /= 2

    x_sol, y_sol = euler(x0, y0, target, h)
    print("\n","=" * 10, "РЕЗУЛЬТАТЫ МЕТОДА ЭЙЛЕРА", "=" * 10)
    print(f"\nКоличество итераций: {iterations}")
    print(f"Итоговый шаг: {h:.6f}")
    print(f"Значение y({x_sol[-1]}) = {y_sol[-1]:.6f}")
    print_table(x_sol, y_sol, h)


    h = 0.2  
    iterations = 0
    print("\n","=" * 10, "Метод Рунге-Кутта 2 порядка: с усреднением по времени ", "=" * 10, "\n")


    while True:
        iterations += 1
        x_h, y_h = runge_kutta2_time(x0, y0, target, h)
        x_h2, y_h2 = runge_kutta2_time(x0, y0, target, h / 2)

        diffs = [abs(y_h2[2*i] - y_h[i]) for i in range(len(y_h))]
        err = max(diffs)

        print(f"Шаг h={h:.6f}, max|y_h2 - y_h|={err:.6f}")
        if err < eps*3:
            h /= 2
            break
        h /= 2

    x_sol, y_sol = runge_kutta2_time(x0, y0, target, h)
    print("\n","=" * 10, "РЕЗУЛЬТАТЫ МЕТОДА РУНГЕ-КУТТА 2 ПОРЯДКА С УСРЕДНЕНИЕМ ПО ВРЕМЕНИ", "=" * 10)
    print(f"\nКоличество итераций: {iterations}")
    print(f"Итоговый шаг: {h:.6f}")
    print(f"Значение y({x_sol[-1]}) = {y_sol[-1]:.6f}")
    print_table(x_sol, y_sol, h)
    

    h = 0.2  
    iterations = 0
    print("\n","=" * 10, "Метод Рунге-Кутта 2 порядка: с усреднением по производной ", "=" * 10, "\n")


    while True:
        iterations += 1
        x_h, y_h = runge_kutta2_diff(x0, y0, target, h)
        x_h2, y_h2 = runge_kutta2_diff(x0, y0, target, h / 2)

        diffs = [abs(y_h2[2*i] - y_h[i]) for i in range(len(y_h))]
        err = max(diffs)

        print(f"Шаг h={h:.6f}, max|y_h2 - y_h|={err:.6f}")
        if err < eps*3:
            h /= 2
            break
        h /= 2

    x_sol, y_sol = runge_kutta2_diff(x0, y0, target, h)
    print("\n","=" * 10, "РЕЗУЛЬТАТЫ МЕТОДА РУНГЕ-КУТТА 2 ПОРЯДКА С УСРЕДНЕНИЕМ ПО ПРОИЗВОДНОЙ", "=" * 10)
    print(f"\nКоличество итераций: {iterations}")
    print(f"Итоговый шаг: {h:.6f}")
    print(f"Значение y({x_sol[-1]}) = {y_sol[-1]:.6f}")
    print_table(x_sol, y_sol, h)

    h = 0.2  
    iterations = 0
    print("\n","=" * 10, "Метод Рунге-Кутта 4 порядка ", "=" * 10, "\n")


    while True:
        iterations += 1
        x_h, y_h = runge_kutta4(x0, y0, target, h)
        x_h2, y_h2 = runge_kutta4(x0, y0, target, h / 2)

        diffs = [abs(y_h2[2*i] - y_h[i]) for i in range(len(y_h))]
        err = max(diffs)

        print(f"Шаг h={h:.6f}, max|y_h2 - y_h|={err:.6f}")
        if err < eps*15:
            h /= 2
            break
        h /= 2

    x_sol, y_sol = runge_kutta4(x0, y0, target, h)
    print("\n","=" * 10, "РЕЗУЛЬТАТЫ МЕТОДА РУНГЕ-КУТТА 4 ПОРЯДКА", "=" * 10)
    print(f"\nКоличество итераций: {iterations}")
    print(f"Итоговый шаг: {h:.6f}")
    print(f"Значение y({x_sol[-1]}) = {y_sol[-1]:.6f}")
    print_table(x_sol, y_sol, h)