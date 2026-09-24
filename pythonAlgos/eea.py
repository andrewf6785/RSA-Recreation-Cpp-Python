#EXTENDED EUCLIDEAN ALGORITHM IN PYTHON

def gcdExtended(a, b):
    if a == 0:
        return b, 0, 1
    gcd, x1, y1 = gcdExtended(b % a, a)
    x = y1 - (b // a) * x1
    y = x1
    return gcd, x, y


#print("GCD is", g)
#print("x =", x, ", y =", y)
#x is always the modular inverse of a modulo b







    

