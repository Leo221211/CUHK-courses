import math

mu = 0.95
N = 20
nu_max = 0.1

epsilon = mu - nu_max

upper_bound = 2 * math.exp(-2 * epsilon ** 2 * N)

print(f'upper bound is {upper_bound}')