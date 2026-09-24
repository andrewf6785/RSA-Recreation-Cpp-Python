// This is a demo of RSA Key creation using a cpp implementation
// Some print statements are commented out to avoid flooding the terminal with numbers
// but can be uncommented if one wishes to see the keys and check the math

#include <iostream>
#include "keys.h"
#include "encrypt.h"
#include "decrypt.h"

int main(){
    std::cout<<"Generating public and private keys."<<std::endl;
    auto [n,e,d]= keys();

    //std::cout<<"n: "<<n<<std::endl;

    //std::cout<<"Public key e\n"<<e<<std::endl;

    //std::cout<<"Private key d\n"<<d<<std::endl;

    largeInt m = 123456789;

    std::cout<<"Encrypting message "<<m<<std::endl;
    largeInt ciphertext = encrypt(m,e,n);
    //std::cout<<"Ciphertext is\n"<<ciphertext<<std::endl;

    std::cout<<"Decrypting ciphertext"<<std::endl;
    largeInt plaintext = decrypt(ciphertext,d,n);

    std::cout<<"Decrypted message is "<<plaintext<<std::endl;
}