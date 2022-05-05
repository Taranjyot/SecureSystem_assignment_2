/**
 * Based on https://gist.github.com/nezza/27835ad5e5d5482e2b81445c5ab8df9c by Thomas Roth <code@stacksmashing.net>
 * Modified by David Oswald <d.f.oswald@bham.ac.uk>
 **/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "crypto.h"






static uint8_t pt[CRYPTO_IN_SIZE * BITSLICE_WIDTH] = {0x45, 0x84, 0x22, 0x7B, 0x38, 0xC1, 0x79, 0x55};
static uint8_t pt2[CRYPTO_IN_SIZE * BITSLICE_WIDTH] = {  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static uint8_t key[CRYPTO_KEY_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,};


        static uint8_t cpyBit(uint8_t out,uint8_t pos, uint8_t v) {
    //uint8_t mask = ~(1<<pos);
    //out = (out & mask);
    //return (out | (v << pos));


    out &= ~(1 << pos);
    // printf("\n outBit = ");
    out |= (v << pos);
    //printf("%hhx",out);

    //printf("\n");
    return out;

}
//  45 84 22 7B 38 C1 79 55
int main()
{
    uint8_t b = 0;
    uint64_t begin = 0, end = 0, duration;
    int c = -1;

    printf("\n\n Hello worl");
  //  WriteByteArray( arrayOne, "arrayOne" );
    //crypto_func(pt, key);

    /*
    printf("\n\n");
    for(uint8_t i=0;i<CRYPTO_IN_SIZE ;i++) {
        printf("%hhx", pt[i]);
        printf(", ");
    }
     */
    // pt[0] = &pt2;
    memcpy (pt, pt2, 256 * sizeof(uint8_t));
    int i;
    for (i = 0; i < 8; i++)
    {
        if (i > 0) printf(":");
        printf("0x%02X", pt[i]);
    }
    printf("\n");


}

