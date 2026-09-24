from pythonAlgos.pickPrime import pickPrime
from pythonAlgos.eea import gcdExtended
def Keys():


    p = pickPrime(1024)
    q = pickPrime(1024)
    #  ---HOW DOES RSA PICK PRIMES?---
    # generate a random number of 512 bits (so random number within the target range), p
    # check to see if p is prime.
    #   do this with the Miller-Rabin primality test, which uses probability to see if a number is prime and is generally faster
    #   if it is, return p
    # else:
    #   set p=p+2 and repeat

    n = p*q
    tn=((p-1)*(q-1)) #totient n
    #calculating totient n is simple, assuming efficient multiplication 


    e = 65537 

    #---HOW DOES RSA FIND COPRIMES---
    #e will be part of the public key, so it is exposed to the public anyways
    #so, you can of course pick a random prime number <tn and it will work fine
    #but, to make the exponentiation math easier on computers, it is standard to use values such as 65,537
    #which has bit value 10000000000000001
    #but in general, any prime number would work cause of course it would neccessarrily be coprime to any tn



    
    d=gcdExtended(e,tn)[1]
    while d<0:
        d+=tn
    #---HOW DOES RSA FIND D---
    #RSA finds d using the extended Euclidean algorithm
    #this let's you expand out two numbers and find the GCD 
    #I will code this separetly and implement here





    public = (n,e)
    private = (n,d)

    #print("Public Key : ",public)
    #print("Private Key : ",private)

    return public,private