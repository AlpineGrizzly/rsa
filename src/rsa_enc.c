/**
 * rsa_enc.c
 * 
 * implementation file for function definitions of RSA encryption 
 * 
 * Author Dalton Kinney
 * Created Feb 4th, 20234
*/
#include <stdio.h>
#include "rsa_enc.h"

char* rsa_enc(char* data, char* pub_key) { 
    char* enc_data = NULL;

    /** Base64 decode key */

    /* Convert message into int/uint array of there asci values */

    /** Encrypt */
    printf("Encrypting following message:\n%s\nWith key\n%s\n", data, pub_key);

    return data;
}