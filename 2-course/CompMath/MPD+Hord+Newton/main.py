def f(x):

    return x*x-3
def df(x):
    return 2*x

def MPD(a,b,eps):
    if f(a)*f(b)>=0:
        raise ValueError("Нет корня уравнения") 
    while (abs(b-a)/2) > eps:
        c= (a+b)/2
        if (f(c)==0):
            return c
        elif (f(a)*f(c)<0):
            b= c
        elif (f(c)*f(b)<0):
            a=c
    return (a+b)/2

def hord(a,b,eps):
    if f(a)*f(b)>=0:
        raise ValueError("Нет корня уравнения")
    c_old = a
    while True:
        c = (a * f(b) - b * f(a)) / (f(b) - f(a))  
        if abs(c - c_old) < eps:
            break
        if f(a) * f(c) < 0:
            b = c
        else:
            a = c
        c_old = c 
    return c

def newton(eps):
    x_old = 2
    while True:
        x = x_old - (f(x_old)/df(x_old))
        if abs(x_old-x)<eps:
            break
        x_old = x
    return x

if __name__ == "__main__":
    a = 1
    b=2
    eps = 10**(-6)
    print(f"Метод половинного деления: {MPD(a,b,eps)}")
    print(f"Метод хорд: {hord(a,b,eps)}")
    print(f"Метод Ньютона: {newton(eps)}")