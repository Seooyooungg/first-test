#include <iostream>
#include <stdio.h>
#include "aes.h"
#define BLOCK_SIZE 16

using namespace std;

void padding(unsigned char *pmsg, unsigned char *msg, int len)
{
    int pad;
    pad = len - sizeof(msg);

    for(int i=0; i<sizeof(msg); i++)
        *(pmsg + i) = msg[i];
    for(int i=sizeof(msg); i<len; i++)
        *(pmsg + i) = pad;
}

void AES_CBC_encrypt(unsigned char *ct, unsigned char *pmsg, int len, unsigned char *iv, unsigned char *key)
{
    memcpy(ct, pmsg, len);

    for(int i=0; i<BLOCK_SIZE; i++)
        *(ct + i) ^= iv[i];
    for(int i=1; i<(len/BLOCK_SIZE); i++)
    {
        AES_encrypt(ct, key, ct);
        for(int j=0; j<BLOCK_SIZE; j++, ct++)
            *(ct + BLOCK_SIZE) ^= *ct;
    }

    AES_encrypt(ct, key, ct);
}

void AES_CEC_decrypt(unsigned char *pmsg, unsigned char *ct, int len, unsigned char *iv, unsigned char *key)
{

}

int main()
{
    unsigned char msg[] = "Single block msg";
    unsigned char aes_128_key[] = {0x06, 0xa9, 0x21, 0x40, 0x36, 0xb8, 0xa1, 0x5b,
                                    0x51, 0x2e, 0x03, 0xd5, 0x34, 0x12, 0x00, 0x06};
    unsigned char iv[] = {0x3d, 0xaf, 0xba, 0x42, 0x9d, 0x9e, 0xb4, 0x30,
                            0xb4, 0x22, 0xda, 0x80, 0x2c, 0x9f, 0xac, 0x41};

    int len = ((sizeof(msg)/BLOCK_SIZE) + 1) * BLOCK_SIZE;
    unsigned char ct[len];
    unsigned char pmsg[len];

    padding(pmsg, msg, len);
    for(int i=0; i<BLOCK_SIZE; i++)
        printf("0x%02X", pmsg[i]);

    AES_CBC_encrypt(ct, pmsg, len, iv, aes_128_key);
    for(int i=0; i<BLOCK_SIZE; i++)
        printf("0x%02X", ct[i]);
    
    return 0;
}