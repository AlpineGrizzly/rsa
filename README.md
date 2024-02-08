# rsa
Implementation of RSA encryption/decryption for Computer Architecture and Design

# Requirements
```sh
sudo apt install libcurl4-openssl-dev
pip install cryptography==3.4.8
```

# Generate public private key pair 
Creates a `private._key.pem` and a `public_key.pem` keypair to be used as input to the RSA encryption program. Minimum size of key is 512 bits.
but can be changed in the code to support larger.
```sh
python3 gen_keys.py KEYSIZE
``` 


# Building encrypter/decrypter
```sh
cd rsa/src
make
```
## Encryption with RSA
Passing the flags -f with a file to encrypt and the public key to use, the result will be a `.enc` file encrypted using rsa in the 
same directory. 
```sh
./rsa -f file2enc.txt -k public_key.pem 
```

# Decrypting with RSA
Similar to encryption command except we will use a `-d` flag to denote decryption
and the key passed with the `-k` flag will be the private key
```sh
./rsa -d -f file2dec.enc -k private_key.pem 
```