#include "crypto.h"
#include "stdio.h"
/**
 * Bring normal buffer into bitsliced form
 * @param pt Input: state_bs in normal form
 * @param state_bs Output: Bitsliced state
 */
static void enslice(const uint8_t pt[CRYPTO_IN_SIZE * BITSLICE_WIDTH], bs_reg_t state_bs[CRYPTO_IN_SIZE_BIT])
{
    uint8_t i ;
    for (i = 0 ; i < CRYPTO_IN_SIZE_BIT; ++i) {
        uint8_t by = i >> 3; // find the number of lines (8 per line)
        uint8_t b = (uint8_t)(i % 8); // find the number of columns
        state_bs[i] =  (pt[by +   0] >> b & 0x1) <<  0 | (pt[by +   8] >> b & 0x1) <<  1 |
                       (pt[by +  16] >> b & 0x1) <<  2 | (pt[by +  24] >> b & 0x1) <<  3 |
                       (pt[by +  32] >> b & 0x1) <<  4 | (pt[by +  40] >> b & 0x1) <<  5 |
                       (pt[by +  48] >> b & 0x1) <<  6 | (pt[by +  56] >> b & 0x1) <<  7 |
                       (pt[by +  64] >> b & 0x1) <<  8 | (pt[by +  72] >> b & 0x1) <<  9 |
                       (pt[by +  80] >> b & 0x1) << 10 | (pt[by +  88] >> b & 0x1) << 11 |
                       (pt[by +  96] >> b & 0x1) << 12 | (pt[by + 104] >> b & 0x1) << 13 |
                       (pt[by + 112] >> b & 0x1) << 14 | (pt[by + 120] >> b & 0x1) << 15 |
                       (pt[by + 128] >> b & 0x1) << 16 | (pt[by + 136] >> b & 0x1) << 17 |
                       (pt[by + 144] >> b & 0x1) << 18 | (pt[by + 152] >> b & 0x1) << 19 |
                       (pt[by + 160] >> b & 0x1) << 20 | (pt[by + 168] >> b & 0x1) << 21 |
                       (pt[by + 176] >> b & 0x1) << 22 | (pt[by + 184] >> b & 0x1) << 23 |
                       (pt[by + 192] >> b & 0x1) << 24 | (pt[by + 200] >> b & 0x1) << 25 |
                       (pt[by + 208] >> b & 0x1) << 26 | (pt[by + 216] >> b & 0x1) << 27 |
                       (pt[by + 224] >> b & 0x1) << 28 | (pt[by + 232] >> b & 0x1) << 29 |
                       (pt[by + 240] >> b & 0x1) << 30 | (pt[by + 248] >> b & 0x1) << 31;
    }


}

/*
static void ensliceKey(const uint8_t key[CRYPTO_KEY_SIZE], uint8_t state_bs[CRYPTO_IN_SIZE])
{
    uint32_t i ;
    for (i = 0 ; i < 32; ++i) {
        uint32_t by = i >> 3; // find the number of lines (8 per line)
        uint32_t b = (uint32_t)(i % 8); // find the number of columns
        state_bs[i] =  (pt[by +   0] >> b & 0x1) <<  0 | (pt[by +   8] >> b & 0x1) <<  1 |
                       (pt[by +  16] >> b & 0x1) <<  2 | (pt[by +  24] >> b & 0x1) <<  3 |
                       (pt[by +  32] >> b & 0x1) <<  4 | (pt[by +  40] >> b & 0x1) <<  5 |
                       (pt[by +  48] >> b & 0x1) <<  6 | (pt[by +  56] >> b & 0x1) <<  7 |
                       (pt[by +  64] >> b & 0x1) <<  8 | (pt[by +  72] >> b & 0x1) <<  9 |
                       (pt[by +  80] >> b & 0x1) << 10 | (pt[by +  88] >> b & 0x1) << 11 |
                       (pt[by +  96] >> b & 0x1) << 12 | (pt[by + 104] >> b & 0x1) << 13 |
                       (pt[by + 112] >> b & 0x1) << 14 | (pt[by + 120] >> b & 0x1) << 15 |
                       (pt[by + 128] >> b & 0x1) << 16 | (pt[by + 136] >> b & 0x1) << 17 |
                       (pt[by + 144] >> b & 0x1) << 18 | (pt[by + 152] >> b & 0x1) << 19 |
                       (pt[by + 160] >> b & 0x1) << 20 | (pt[by + 168] >> b & 0x1) << 21 |
                       (pt[by + 176] >> b & 0x1) << 22 | (pt[by + 184] >> b & 0x1) << 23 |
                       (pt[by + 192] >> b & 0x1) << 24 | (pt[by + 200] >> b & 0x1) << 25 |
                       (pt[by + 208] >> b & 0x1) << 26 | (pt[by + 216] >> b & 0x1) << 27 |
                       (pt[by + 224] >> b & 0x1) << 28 | (pt[by + 232] >> b & 0x1) << 29 |
                       (pt[by + 240] >> b & 0x1) << 30 | (pt[by + 248] >> b & 0x1) << 31;
    }


}

*/

/**
 * Bring bitsliced buffer into normal form
 * @param state_bs Input: Bitsliced state
 * @param pt Output: state_bs in normal form
 */
static void unslice(const bs_reg_t state_bs[CRYPTO_IN_SIZE_BIT], uint8_t pt[CRYPTO_IN_SIZE * BITSLICE_WIDTH])
{
    uint32_t i;
    uint32_t counter = 0;
    for (i = 0 ; i <= 255; i++) {

        uint8_t b = i >> 3;; // find the number of columns

        pt[i] =  (state_bs[counter +  0] >> b & 0x1) <<  0 | (state_bs[counter +  1] >> b & 0x1) <<  1 |
                 (state_bs[counter +  2] >> b & 0x1) <<  2 | (state_bs[counter +  3] >> b & 0x1) <<  3 |
                 (state_bs[counter +  4] >> b & 0x1) <<  4 | (state_bs[counter +  5] >> b & 0x1) <<  5 |
                 (state_bs[counter +  6] >> b & 0x1) <<  6 | (state_bs[counter +  7] >> b & 0x1) <<  7;

        counter+=8;
        if(counter>=64) {
            counter = 0;
        }
    }
}


static uint8_t getBit(uint8_t v, uint8_t bit) {
    return (v >> bit) & 0x1;
}

/**
 * Perform next key schedule step
 * @param key Key register to be updated
 * @param r Round counter
 * @warning For correct function, has to be called with incremented r each time
 * @note You are free to change or optimize this function
 */
static void update_round_key(uint8_t key[CRYPTO_KEY_SIZE], const uint8_t r)
{
	//
	// There is no need to edit this code - but you can do so if you want to
	// optimise further
	//

	const uint8_t sbox[16] = {
		0xC, 0x5, 0x6, 0xB, 0x9, 0x0, 0xA, 0xD, 0x3, 0xE, 0xF, 0x8, 0x4, 0x7, 0x1, 0x2,
	};

	uint8_t tmp = 0;
	const uint8_t tmp2 = key[2];
	const uint8_t tmp1 = key[1];
	const uint8_t tmp0 = key[0];
	
	// rotate right by 19 bit
	key[0] = key[2] >> 3 | key[3] << 5;
	key[1] = key[3] >> 3 | key[4] << 5;
	key[2] = key[4] >> 3 | key[5] << 5;
	key[3] = key[5] >> 3 | key[6] << 5;
	key[4] = key[6] >> 3 | key[7] << 5;
	key[5] = key[7] >> 3 | key[8] << 5;
	key[6] = key[8] >> 3 | key[9] << 5;
	key[7] = key[9] >> 3 | tmp0 << 5;
	key[8] = tmp0 >> 3   | tmp1 << 5;
	key[9] = tmp1 >> 3   | tmp2 << 5;
	
	// perform sbox lookup on MSbits
	tmp = sbox[key[9] >> 4];
	key[9] &= 0x0F;
	key[9] |= tmp << 4;
	
	// XOR round counter k19 ... k15
	key[1] ^= r << 7;
	key[2] ^= r >> 1;
}

static void add_round_key(bs_reg_t state_bs[CRYPTO_IN_SIZE_BIT], uint8_t roundKey[CRYPTO_IN_SIZE])
{
    for(uint8_t i=0;i< 64;i++) {
        uint8_t val = getBit(roundKey[i/8], i%8);
        if(val == 1) {
            state_bs[i] ^= 0xffffffff;
        } else {
            state_bs[i] ^= 0;
        }
    }
}
static void add_round_key1(bs_reg_t state_bs[CRYPTO_IN_SIZE_BIT], uint8_t roundKey[CRYPTO_IN_SIZE_BIT])
{
    for(uint8_t i=0;i< 64;i++) {
        state_bs[i] = state_bs[i] ^ roundKey[i];
    }

}

uint32_t sbox0(uint32_t in_0,uint32_t in_1, uint32_t in_2, uint32_t in_3) {
    return (in_0 ^ in_1 & in_2 ^ in_2 ^ in_3);
}

uint32_t sbox1(uint32_t in_0, uint32_t in_1, uint32_t in_2, uint32_t in_3) {
    return (in_0 & in_2 & in_1 ^ in_0 & in_3 & in_1 ^ in_3 &in_1 ^ in_1 ^ in_0 & in_2 & in_3 ^in_2 & in_3 ^ in_3);
}

uint32_t sbox2(uint32_t in_0, uint32_t in_1, uint32_t in_2, uint32_t in_3) {
    return ~(in_0 & in_1 ^ in_0 & in_3 & in_1 ^ in_3 & in_1 ^ in_2 ^ in_0 & in_3 ^ in_0 & in_2 & in_3 ^ in_3);
}

uint32_t sbox3(uint32_t in_0, uint32_t in_1, uint32_t in_2, uint32_t in_3) {
    return ~(in_1 & in_2 & in_0 ^ in_1 & in_3 & in_0 ^ in_2 & in_3 & in_0 ^ in_0 ^ in_1 ^ in_1 & in_2 ^ in_3);
}


static void sbox_layer(bs_reg_t state_bs[CRYPTO_IN_SIZE_BIT])
{
    bs_reg_t state_out[64] = { 0 };
    for(uint8_t s = 0; s < 16; s++) {
        uint32_t in_0 = state_bs[s*4 + 0]; // Get input bits
        uint32_t in_1 = state_bs[s*4 + 1]; // to s’th SBox
        uint32_t in_2 = state_bs[s*4 + 2];
        uint32_t in_3 = state_bs[s*4 + 3];
        state_out[s*4 + 0] = sbox0(in_0, in_1, in_2, in_3);
        state_out[s*4 + 1] = sbox1(in_0, in_1, in_2, in_3);
        state_out[s*4 + 2] = sbox2(in_0, in_1, in_2, in_3);
        state_out[s*4 + 3] = sbox3(in_0, in_1, in_2, in_3);
    }
    for(uint8_t i=0;i<64;i++) {
        state_bs[i] = state_out[i];
    }

}

static void pbox_layer(bs_reg_t state[CRYPTO_IN_SIZE_BIT]) {
    bs_reg_t state_out[64] = {0};
    for (uint8_t b = 0; b < 64; b++) {
        uint8_t out = b/4 + (b % 4) * 16;
        state_out[out] = state[b];
    }
    for(uint8_t i=0;i<64;i++) {
        state[i] = state_out[i];
    }

}
void crypto_func(uint8_t pt[CRYPTO_IN_SIZE * BITSLICE_WIDTH], uint8_t key[CRYPTO_KEY_SIZE])
{

	// State buffer and additional backbuffer of same size (you can remove the backbuffer if you do not need it)
	bs_reg_t state[CRYPTO_IN_SIZE_BIT];
    //uint8_t key_enslice[CRYPTO_IN_SIZE_BIT];

	uint8_t round;
	uint8_t i = 0;

	// Bring into bitslicing form
    //ensliceKey(key+2,key_enslice);
	enslice(pt, state);
	
	// INSERT PRESENT MAIN CODE HERE AND DELETE THIS COMMENT //

    for(i = 1; i <= 31; i++)
    {
        add_round_key(state, key +2)
        sbox_layer(state);
        pbox_layer(state);
        update_round_key(key, i);
    }
    add_round_key(state, key +2);

    // Convert back to normal form
	unslice(state, pt);

}