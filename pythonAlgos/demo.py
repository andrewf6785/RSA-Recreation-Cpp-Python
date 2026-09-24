from pythonAlgos.keys import Keys
from pythonAlgos.encrypt import encrypt
from pythonAlgos.decrypt import decrypt











pub,priv = Keys()
n=pub[0]
e=pub[1]
d=priv[1]

print("Public Key : ",(e,n))
print("Private Key : ",(d,n),"\n")


m=1042

print("Encrypting message ",m)
c=encrypt(m,e,n)
print("Encrypted message is ",c,"\n")

print("Decrpyting message ",c)
decrpytedCiphertext = decrypt(c,d,n)
print("Decrypted message is ",decrpytedCiphertext)
