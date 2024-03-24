import sys
import random
from sympy import sympify, poly

operations = ['+', '-', '=', '*', '!=']


def get_output(op: str, form_1: str, form_2: str) -> str:
    if op == "=":
        return "equal"
    elif op == "!=":
        return "not equal"
    elif op == "+":
        return str(sympify(form_1) + sympify(form_2))
    elif op == "-":
        return str(sympify(form_1) - sympify(form_2))
    elif op == "*":
        return str(poly(sympify(form_1) * sympify(form_2)).as_expr())


def product():
    coef = random.randint(-100, 100)
    if coef >= 0:
        res = '+' + str(coef)
    else:
        res = str(coef)
    for i in range(26):
        res += "*" + chr(random.randint(97, 122))
    return res


def sm():
    res = []
    for i in range(100):
        res.append(product())
    return ''.join(res)


def to_spf(input_string: str) -> str:
    res = input_string
    pos = res.find("**")
    while pos != -1:
        var = res[pos - 1]
        exponent = int(res[pos+2])
        res = res[:pos - 1] + f'{var}*' * (exponent - 1) + var + res[pos + 3:]
        pos = res.find("**")
    return res


if __name__ == "__main__":
    n = len(sys.argv)
    if n != 3:
        print("Incorrect number of arguments")
        sys.exit(1)
    op = sys.argv[1]
    if op not in operations:
        print("Incorrect operation")
        sys.exit(1)
    test_num = sys.argv[2]
    if not test_num.isdecimal():
        print("Incorrect test number")
        sys.exit(1)
    test_num = abs(int(test_num))
    form_1 = sm()
    if op == "=":
        form_2 = form_1
    else:
        form_2 = sm()
    with open(f"test{test_num}.txt", "w") as f:
        f.write(op + '\n')
        f.write(form_1 + '\n')
        f.write(form_2)
    form_1 = sympify(form_1)
    form_2 = sympify(form_2)
    output = get_output(op, form_1, form_2)
    with open(f"output{test_num}.txt", "w") as f:
        f.write(output + '\n')
