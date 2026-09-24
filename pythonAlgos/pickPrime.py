import secrets
from pythonAlgos.miller_rabin import miller_rabin
def pickPrime(bits):
    possiblePrime = secrets.randbits(bits)
    while(not miller_rabin(possiblePrime,40)): 
        
        possiblePrime = secrets.randbits(bits)#just pick another number lol
    return possiblePrime