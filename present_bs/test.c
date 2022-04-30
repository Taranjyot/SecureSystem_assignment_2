/**
 * Based on https://gist.github.com/nezza/27835ad5e5d5482e2b81445c5ab8df9c by Thomas Roth <code@stacksmashing.net>
 * Modified by David Oswald <d.f.oswald@bham.ac.uk>
 **/
#include "crypto.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

int main()
{
    int temp = 256;
    uint8_t by = temp >> 3;
//    printf("%hhx",  by);


    //uint8_t pt[CRYPTO_IN_SIZE * BITSLICE_WIDTH] = {0};
    //uint32_t i ;

    /*
    for (i = 0 ; i <= 255; ++i) {

        int counter = 0;
        uint8_t b = i >> 3;; // find the number of columns

        pt[i] =  (state_bs[counter +   0] >> b & 0x1) <<  0 | (state_bs[counter +   1] >> b & 0x1) <<  1 |
                 (state_bs[counter +  2] >> b & 0x1) <<  2 | (state_bs[counter +  3] >> b & 0x1) <<  3 |
                 (state_bs[counter +  4] >> b & 0x1) <<  4 | (state_bs[counter +  5] >> b & 0x1) <<  5 |
                 (state_bs[counter +  6] >> b & 0x1) <<  6 | (state_bs[counter +  7] >> b & 0x1) <<  7;

        counter+=8;
        if(counter>=64) {
            counter = 0;
        }
    }
    printf("hellow wowld");

     */

    uint32_t i;
    for (i = 0 ; i <= 255; i++) {

    }


    bs_reg_t state_bs[CRYPTO_IN_SIZE_BIT] ={1};

    uint32_t i;
    int count =0;
    printf("%hhx", state_bs[count+0]);
    uint8_t pt[CRYPTO_IN_SIZE * BITSLICE_WIDTH] = {1};
    //printf("%hhx", pt[1]);
    uint8_t temp1 =0;
    for (i = 0 ; i <=255; i++) {
        count+=8;

       // printf("/n \n %d", count);
    }

   // printf("%hhx",count);
    //printf("\n %d", count);

   /*
    count =0;
    for(bs_reg_t i=0;i<64;i++) {

        count++;
    }
    printf("/n \n %d", count);
*/
    return 0;
}

