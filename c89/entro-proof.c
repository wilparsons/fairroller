#include "entro-hash.h"
#include "entro-proof.h"
#include "entro-shift.h"

void entro_proof_hash(const char *casino_input, uint32 *entro_proof) {
  unsigned char i = 1;

  entro_proof[0] = entro_hash(casino_input, 0);

  while (i != 32) {
    entro_proof[i] = entro_hash(casino_input, entro_proof[i - 1]) ^ entro_proof[i - 1];
    i++;
  }

  while (i != 1) {
    i--;
    entro_proof[i] = entro_hash(casino_input, entro_proof[i - 1]) ^ entro_proof[i - 1];
  }

  entro_proof[0] = entro_hash(casino_input, entro_proof[31]) ^ entro_proof[31];
}

uint32 entro_proof_randomize(const char *casino_input, const char *player_input, uint32 *entro_proof) {
  uint32 entropy = entro_proof[31];
  unsigned short i = 0;

  while (casino_input[i] != 0) {
    entropy = entro_shift(casino_input[i] + entro_proof[i & 31] + entropy);
    i++;
  }

  i = 0;

  while (player_input[i] != 0) {
    entropy = entro_shift(player_input[i] + entro_proof[i & 31] + entropy);
    i++;
  }

  return entropy;
}

void entro_proof_shuffle(unsigned short count, unsigned char *input, uint32 entropy) {
  unsigned short position;
  unsigned char copied_input;
  unsigned short i = 0;

  if (count > 1) {
    while (i != count) {
      position = entropy << 31;
      entropy = entro_shift((uint32) entropy);
      position += entropy;

      if (position >= count) {
        position %= count;
      }

      if (position != i) {
        copied_input = input[i];
        input[i] = input[position];
        input[position] = copied_input;
      }

      i++;
    }
  }
}
