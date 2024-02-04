'''
gen_keypair.py 

Python script for generating dynamic key pair pem encoded files to be used for RSA encryption

Logic for using cryptography library used from here: https://dev.to/aaronktberry/generating-encrypted-key-pairs-in-python-69b

Author Dalton Kinney
Created Feb 4th, 2024
'''
import sys
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import serialization

def main():
    priv_fn = "private_key.pem"
    pub_fn = "public_key.pem"
    private_key_pass = b"password" # No password for now
    keysize = 0 # Size of keys to be generated

    if len(sys.argv) == 2:
        try: 
            keysize = int(sys.argv[1])
        except:
            print("Must provide integer key value!")
            exit(0)        
        print(f"Generating keys of size {keysize}")
    else:
        print("Invalid keysize")

    # Generate keysized rsa pair
    # Generate the private key  
    private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=keysize
    )

    encrypted_pem_private_key = private_key.private_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PrivateFormat.PKCS8,
        encryption_algorithm=serialization.BestAvailableEncryption(private_key_pass)
    )

    # Generate the public 
    pem_public_key = private_key.public_key().public_bytes(
      encoding=serialization.Encoding.PEM,
      format=serialization.PublicFormat.SubjectPublicKeyInfo
    ) 

    # Encode and write to pem files
    private_key_file = open(priv_fn, "w")
    private_key_file.write(encrypted_pem_private_key.decode())
    private_key_file.close()

    public_key_file = open(pub_fn, "w")
    public_key_file.write(pem_public_key.decode())
    public_key_file.close()

    print(f"Keys written to {priv_fn} and {pub_fn}")

if __name__ == "__main__":
    main()