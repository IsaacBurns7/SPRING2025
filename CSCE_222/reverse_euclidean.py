import math

def reverse_euclidean(num1, num2):
    history = []

    history.append([num1, num2, 0, 0])
    remainder = 1000

    j = 0
    while remainder != 0:
        quotient = math.floor(history[j][0] / history[j][1])
        remainder = history[j][0] % history[j][1]

        history[j][2] = quotient
        history[j][3] = remainder

        history.append([history[j][1], remainder, 0, 0])

        print(f"{j} {history[j]}")
        j += 1
    return history

def find_linear_combinations(history, num1, num2, gcd):
    n = len(history) - 1
    quotient_dict = {}

    while n > 0:
        #remainder = big_num - quotient * small_num
        history[n][3] = history[n][0] - history[n][2] * history[n][1]
        if history[n][0] in quotient_dict:
            history[n][0] += 1
        else: 
            history[n][0] = 1

        if history[n][1] in quotient_dict:
            history[n][1] -= history[n][2]
        else: 
            history[n][1] = history[n][2] * -1

        n -= 1
    

history = reverse_euclidean(252, 198)
find_linear_combinations(history, 252, 198, 18)
# history = reverse_euclidean(21, 55)