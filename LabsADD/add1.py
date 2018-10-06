import pay as pay

def hello_user():
    print("Enter name")
    name = input()
    print("Hello " + name)


def celsium_to_farengeit(celsium):
    return round(celsium - 32 * 5 / 9, 2);


def console_ctf():
    print("Температура по шкале Цельсия:")
    degree = float(input())
    print("Температура по шкале Фаренгейта:" + str(celsium_to_farengeit(degree)))


hello_user()
pay.console_pay()
console_ctf()
