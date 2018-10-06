def pay(hours, rate):
    return round(hours * rate, 2);


def console_pay():
    print("Enter hours:")
    hours = float(input())  # row_input in Python3
    print("Enter rate:")
    rate = float(input())
    print("Pay:" + str(pay(hours, rate)))