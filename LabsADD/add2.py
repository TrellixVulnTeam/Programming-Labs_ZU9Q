import pay as pay


def score(number):
    number = round(number)
    if number > 3:
        return "Good score"
    else:
        return "Bad score"


def console_score():
    print("Enter score:")
    try:
        n = float(input())
        print(score(n))
    except ValueError:
        print("Incorrect arg")


def file_row_sum():
    try:
        sum = 0
        with open("test.in", 'r') as file:
            for line in file:
                try:
                    sum += int(line)
                except ValueError:
                    continue
        print("Sum = " + str(sum))
    except FileNotFoundError:
        print("File do not found")


if __name__ == "__main__":
    pay.console_pay()
    file_row_sum()

