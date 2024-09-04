import math

delta = 0.05

error = float(input('input error:'))

N_min = math.log(2 / delta) / (2 * error ** 2)

N_min = math.ceil(N_min)

print(f'N_min is {N_min}')