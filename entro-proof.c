#include "entro-hash.h"
#include "entro-proof.h"
#include "entro-shift.h"

void entro_proof_hash(const char *casino_input, uint32_t *entropy) {
  entropy[0] = entro_hash(casino_input, 0);
  entropy[1] = entro_hash(casino_input, entropy[0]) ^ entropy[0];
  entropy[2] = entro_hash(casino_input, entropy[1]) ^ entropy[1];
  entropy[3] = entro_hash(casino_input, entropy[2]) ^ entropy[2];
  entropy[4] = entro_hash(casino_input, entropy[3]) ^ entropy[3];
  entropy[5] = entro_hash(casino_input, entropy[4]) ^ entropy[4];
  entropy[6] = entro_hash(casino_input, entropy[5]) ^ entropy[5];
  entropy[7] = entro_hash(casino_input, entropy[6]) ^ entropy[6];
  entropy[8] = entro_hash(casino_input, entropy[7]) ^ entropy[7];
  entropy[9] = entro_hash(casino_input, entropy[8]) ^ entropy[8];
  entropy[10] = entro_hash(casino_input, entropy[9]) ^ entropy[9];
  entropy[11] = entro_hash(casino_input, entropy[10]) ^ entropy[10];
  entropy[12] = entro_hash(casino_input, entropy[11]) ^ entropy[11];
  entropy[13] = entro_hash(casino_input, entropy[12]) ^ entropy[12];
  entropy[14] = entro_hash(casino_input, entropy[13]) ^ entropy[13];
  entropy[15] = entro_hash(casino_input, entropy[14]) ^ entropy[14];
  entropy[16] = entro_hash(casino_input, entropy[15]) ^ entropy[15];
  entropy[17] = entro_hash(casino_input, entropy[16]) ^ entropy[16];
  entropy[18] = entro_hash(casino_input, entropy[17]) ^ entropy[17];
  entropy[19] = entro_hash(casino_input, entropy[18]) ^ entropy[18];
  entropy[20] = entro_hash(casino_input, entropy[19]) ^ entropy[19];
  entropy[21] = entro_hash(casino_input, entropy[20]) ^ entropy[20];
  entropy[22] = entro_hash(casino_input, entropy[21]) ^ entropy[21];
  entropy[23] = entro_hash(casino_input, entropy[22]) ^ entropy[22];
  entropy[24] = entro_hash(casino_input, entropy[23]) ^ entropy[23];
  entropy[25] = entro_hash(casino_input, entropy[24]) ^ entropy[24];
  entropy[26] = entro_hash(casino_input, entropy[25]) ^ entropy[25];
  entropy[27] = entro_hash(casino_input, entropy[26]) ^ entropy[26];
  entropy[28] = entro_hash(casino_input, entropy[27]) ^ entropy[27];
  entropy[29] = entro_hash(casino_input, entropy[28]) ^ entropy[28];
  entropy[30] = entro_hash(casino_input, entropy[29]) ^ entropy[29];
  entropy[31] = entro_hash(casino_input, entropy[30]) ^ entropy[30];
  entropy[0] ^= entropy[31];
  entropy[1] ^= entropy[0];
  entropy[2] ^= entropy[1];
  entropy[3] ^= entropy[2];
  entropy[4] ^= entropy[3];
  entropy[5] ^= entropy[4];
  entropy[6] ^= entropy[5];
  entropy[7] ^= entropy[6];
  entropy[8] ^= entropy[7];
  entropy[9] ^= entropy[8];
  entropy[10] ^= entropy[9];
  entropy[11] ^= entropy[10];
  entropy[12] ^= entropy[11];
  entropy[13] ^= entropy[12];
  entropy[14] ^= entropy[13];
  entropy[15] ^= entropy[14];
  entropy[16] ^= entropy[15];
  entropy[17] ^= entropy[16];
  entropy[18] ^= entropy[17];
  entropy[19] ^= entropy[18];
  entropy[20] ^= entropy[19];
  entropy[21] ^= entropy[20];
  entropy[22] ^= entropy[21];
  entropy[23] ^= entropy[22];
  entropy[24] ^= entropy[23];
  entropy[25] ^= entropy[24];
  entropy[26] ^= entropy[25];
  entropy[27] ^= entropy[26];
  entropy[28] ^= entropy[27];
  entropy[29] ^= entropy[28];
  entropy[30] ^= entropy[29];
}

uint32_t entro_proof_randomize(const char *casino_input, const char *player_input) {
  uint32_t entropy = 0;
  unsigned short i = 0;

  while (casino_input[i] != 0) {
    entropy = entro_shift(casino_input[i] + entropy);
    i++;
  }

  i = 0;

  while (player_input[i] != 0) {
    entropy = entro_shift(player_input[i] + entropy);
    i++;
  }

  return entropy;
}

void entro_proof_shuffle(unsigned short count, unsigned char *input, uint32_t entropy) {
  unsigned short position;
  unsigned char copied_input;
  unsigned short i = 0;

  if (count > 1) {
    while (i != count) {
      entropy = entro_shift(entropy);
      position = entropy % count;

      if (position != i) {
        copied_input = input[i];
        input[i] = input[position];
        input[position] = copied_input;
      }

      i++;
    }
  }
}
