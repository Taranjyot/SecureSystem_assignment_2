#include "crypto.h"
#include "stdio.h"
/**
 * Bring normal buffer into bitsliced form
 * @param pt Input: state_bs in normal form
 * @param state_bs Output: Bitsliced state
 */
static void enslice(const uint8_t pt[CRYPTO_IN_SIZE * BITSLICE_WIDTH], bs_reg_t state_bs[CRYPTO_IN_SIZE_BIT])
{
	// 8 * 32

    uint8_t temp = 0;
    uint8_t bitCalc = 0;
    int length = CRYPTO_IN_SIZE * BITSLICE_WIDTH;
    uint8_t j = 0, k =0;
    for(uint8_t i =0;i < length; i++) {

        state_bs[j + k] = pt[i];
        bitCalc += (CRYPTO_IN_SIZE);
        k+=8;
        if(k == 248) {
            k=0;
        }
        if(i%8 ==0) {
            j++;
        }
    }


}

/**
 * Bring bitsliced buffer into normal form
 * @param state_bs Input: Bitsliced state
 * @param pt Output: state_bs in normal form
 */
static void unslice(const bs_reg_t state_bs[CRYPTO_IN_SIZE_BIT], uint8_t pt[CRYPTO_IN_SIZE * BITSLICE_WIDTH])
{
	// INSERT YOUR CODE HERE AND DELETE THIS COMMENT
    uint8_t j = 0, k =0;
    int length = CRYPTO_IN_SIZE * BITSLICE_WIDTH;
    for(uint8_t i =0;i < length; i++) {

        pt[j + k] = state_bs[i];
        bitCalc += (CRYPTO_IN_SIZE);
        k+=BITSLICE_WIDTH;
        if(k == 224) {
            k=0;
        }
        if(i% BITSLICE_WIDTH ==0) {
            j++;
        }
    }

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

static void add_round_key(uint8_t pt[CRYPTO_IN_SIZE], uint8_t roundkey[CRYPTO_IN_SIZE])
{
    for(uint8_t i=0;i< 8;i++) {
        pt[i] = pt[i] ^ roundkey[i];
    }
}

static void sbox_layer(uint8_t s[CRYPTO_IN_SIZE])
{

    // INSERT YOUR CODE HERE AND DELETE THIS COMMENT
    for(uint8_t i=0;i<8;i++) {
        uint8_t ln = s[i] & 0xf;
        uint8_t un = (s[i] >> 4) & 0xf;
        s[i] = sbox[ln] | (sbox[un] << 4);
    }

}

void crypto_func(uint8_t pt[CRYPTO_IN_SIZE * BITSLICE_WIDTH], uint8_t key[CRYPTO_KEY_SIZE])
{
    for(int i=0;i < 256;i++) {
        printf("%hhx", pt[i]);
        printf(", ");
        if(i %BITSLICE_WIDTH ==0) {
            printf("\n");
        }
    }

    printf("\n Hello");
	// State buffer and additional backbuffer of same size (you can remove the backbuffer if you do not need it)
	bs_reg_t state[CRYPTO_IN_SIZE_BIT];
	bs_reg_t bb[CRYPTO_IN_SIZE_BIT];
	
	uint8_t round;
	uint8_t i;
	
	// Bring into bitslicing form
	enslice(pt, state);
	
	// INSERT PRESENT MAIN CODE HERE AND DELETE THIS COMMENT //

    for(i = 1; i <= 31; i++)
    {
        add_round_key(pt, key + 2);
        sbox_layer(pt);
        pbox_layer(pt);
        update_round_key(key, i);
    }

    // Add Round Key
    for(uint8_t b=0;b<64;b++) {
        state_exp[i]
    }


    // permutation
    bs_reg_t state_out[64] = {0};
    for(uint8_t b=0; b<64;b++) {
        uint8_t  out = b/4 +(b%4) *16;
        state_out[out] = state_exp[i];
    }
	// Convert back to normal form
	unslice(state, pt);
}