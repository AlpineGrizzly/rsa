/**
 * main.c
 * 
 * Simplified DES encryption/decryption tool
 * 
 * Author Dalton Kinney
 * Created January 28th, 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include "rsa_enc.h"
#include "rsa_dec.h"

#define DEBUG 1
#define BUF_SIZE 2048

/**
 * usage
 * 
 * Prints the usage of the program
*/
void usage() { 
	char* usage_string = "Usage: rsa [-d] -f filename -k public_key.pem | private_key.pem\n" 
						 "RSA encryption/decryption implementation. \n\n" 
                         "-h      Show this information\n"
                         "-f      File to be encrypted/decrypted\n"
                         "-k      Pem file containing public key | private key if `-d` flag is in use\n"
                         "-d      Flag to perform decryption on data file (If omitted, will assume file is to be encrypted\n";
	printf("%s", usage_string);
}

/**
 * get_data
 * 
 * Reads data from a file and stores it into a buffer
 * 
 * @param filename Name of file to read data from 
 * @param buf buffer for data to be read into 
 * 
 * @return 1 if successful, 0 otherwise
*/
int get_data(char* filename, char buf[BUF_SIZE]) { 
    FILE *pdata = fopen(filename, "r");

    if (pdata == NULL) { 
        return 0;
    }

    // Begin reading data into bu`ffer 
    int count = fread(buf, sizeof(char), BUF_SIZE, pdata);
    fclose(pdata);

    return 1;
}

int get_key(char *keyfile, char buf[BUF_SIZE]) { 
    int count;
    char temp[BUF_SIZE] = {0};
    FILE *pkeys = fopen(keyfile, "r");

    if (pkeys == NULL) { 
        return 0;
    }

    /** Get key from pem file */
    while(fgets(temp, BUF_SIZE, pkeys))
    {
        temp[strcspn(temp, "\n")] = '\0';    // Strip \n character if present
        if (strcmp(temp, "-----BEGIN PUBLIC KEY-----") == 0) continue;   // Stop reading
        if (strcmp(temp, "-----BEGIN ENCRYPTED PRIVATE KEY-----") == 0) continue;   // Stop reading
        if (strcmp(temp, "-----END PUBLIC KEY-----") == 0) break;   // Stop reading
        if (strcmp(temp, "-----END ENCRYPTED PRIVATE KEY-----") == 0) break;   // Stop reading
        strcat(buf, temp);
        // use sscanf on buffer to find the individual fields in the line
    }

    fclose(pkeys);

    return 1;
}

int main(int argc, char* argv[]) { 
    int   opt;                 // Used to hold args as we parse
    int   mode = 0;            // Holds mode for enc/dec (0 = Enc; 1 = Dec)  
    
    char* datafile = NULL;     // Filename of data to be enc/decr 
    char* keyfile = NULL;
    char* post_data = NULL;           // Post enc | dec data
	
    /* Parse arguments */ 
	while ((opt = getopt(argc, argv, "hf:k:d")) != -1) {
        switch (opt) {
        	case 'h': usage(); break;
        	case 'f': datafile = optarg; break;
            case 'k': keyfile = optarg; break;
            case 'd': mode = 1; break; // Enable decryption mode
        default:
            usage();
        }
    }

    /** Verfiy arguments */
	if (datafile == NULL || keyfile == NULL) { 
        usage();
        return 0;
    }

    /** Read data from file */
    char data[BUF_SIZE] = {0};

    if (!get_data(datafile, data)) {
        printf("Unable to read %s!\n", datafile);
        return 0;
    }

    char key[BUF_SIZE] = {0};
    if (!get_key(keyfile, key)) {
        printf("Unable to read %s!\n", keyfile);
        return 0;
    }
     
    /** Perform enc/dec */
    post_data = mode ? rsa_dec(data, key) : rsa_enc(data, key);

    /** Write data to out file */
    printf("write post data to file:\n%s\n", post_data);

    return 0;
}
