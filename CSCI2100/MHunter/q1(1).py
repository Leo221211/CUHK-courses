import math

alpha = 1.5 * math.pi / 180
D = 70
theta = 120 * math.pi / 180
d = 200

def return_h(n):
    s = n * d
    return D - s * math.tan(alpha)

# left
def cal_x1(h):
    return h / (math.tan(alpha) - math.tan(math.pi/2 - theta/2))

# right
def cal_x2(h):
    return h / (math.tan(alpha) + math.tan(math.pi/2 - theta/2))

def return_W(h):
    return cal_x2(h) - cal_x1(h)

def return_eta(n, h, W):
    h_prime = return_h(n - 1)
    x1 = cal_x1(h)
    x2_prime = cal_x2(h_prime) - d
    return (x2_prime - x1) / W

if __name__ == '__main__':
    n = float(input("Enter a value for n: "))

    # calculate h
    h = return_h(n)
    print("h =", h)

    print("x1 =",cal_x1(h))
    print("x2 =",cal_x2(h))
    # calculate W
    W = return_W(h)
    print("W =", W)

    # calculate eta
    eta = return_eta(n, h, W)
    print("eta =", eta * 100, "%")