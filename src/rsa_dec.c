/**
 * rsa_dec.h
 * 
 * Header for RSA decryption function declarations 
 * 
 * Author Dalton Kinney
 * Created Feb 4th, 2024
*/
#include <stdio.h>
#include "rsa_dec.h"

char* rsa_dec(char* data, char* priv_key) { 
    char* dec_data = NULL;

    printf("Decrypting following message:\n%s\nWith key\n%s\n", data, priv_key);

    return data;
}