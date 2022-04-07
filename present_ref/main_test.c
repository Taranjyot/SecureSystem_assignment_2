/**
 * Based on https://gist.github.com/nezza/27835ad5e5d5482e2b81445c5ab8df9c by Thomas Roth <code@stacksmashing.net>
 * Modified by David Oswald <d.f.oswald@bham.ac.uk>
 **/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "crypto.h"






static uint8_t pt[CRYPTO_IN_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static uint8_t key[CRYPTO_KEY_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ;

int main()
{
    uint8_t b = 0;
    uint64_t begin = 0, end = 0, duration;
    int c = -1;

    printf("%c", pt[0]);
    crypto_func(pt, key);
    printf("Hello world \n");
    printf("%p", (void*) pt);
    printf("\n");
}

