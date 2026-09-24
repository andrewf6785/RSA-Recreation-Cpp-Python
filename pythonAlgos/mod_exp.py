def modulusExponent(a, d, n):
    result = 1
    a = a % n

    while d > 0:
        if d % 2 == 1:
            result = (result * a) % n

        a = (a * a) % n
        d //= 2

    return result