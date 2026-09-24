#Miller rabin test for primality
#pick n > 2
# see black notebook for slightly more detailed pseudocode 
# k, in my limited research, should be ~40 which will reduce the probability of miscomputation
# to about 2^-80 and works out to ~10% of the total computation time for finding a prime 
    # as you will need to roughly check ~300 numbers in the target range to find a prime number





import random
from pythonAlgos.mod_exp import modulusExponent
    

def miller_rabin(n,k):
    if n==2 or n==3:
        return True
    if n<2 or n%2==0:
        return False
    d = n-1
    s =0
    while d%2==0: # while d is even
        d = d//2
        s = s+1
    for i in range(k):
        a = random.randint(2,n-2)
        x=modulusExponent(a,d,n)
        if x ==1 or x==n-1:
            continue
        for r in range(1,s):
            x=modulusExponent(x,2,n)
            if x==n-1:
                break 
            elif x==1:
                return False
        return False
    return True
