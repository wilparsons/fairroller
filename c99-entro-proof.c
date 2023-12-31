#include <stdio.h>
#include "entro-hash.h"
#include "entro-shift.h"

void *entro_proof_hash(const char *casino_input, uint32_t *entro_proof) {
  unsigned char i = 1;

  entro_proof[0] = entro_hash(casino_input, 0);

  while (i != 32) {
    entro_proof[i] = entro_hash(casino_input, 0) + entro_proof[i - 1];
    i++;
  }

  while (i != 1) {
    i--;
    entro_proof[i] = entro_hash(casino_input, 0) + entro_proof[i - 1];
  }

  entro_proof[0] = entro_hash(casino_input, 0) + entro_proof[31];
}

uint32_t entro_proof_randomize(const char *player_input, const char *casino_input, uint32_t *entro_proof) {
  uint32_t entropy = entro_proof[31];
  unsigned long long i = 0;

  while (player_input[i] != 0) {
    entropy = entro_shift(player_input[i] + entro_proof[i & 31] + entropy);
    i++;
  }

  i = 0;

  while (casino_input[i] != 0) {
    entropy = entro_shift(casino_input[i] + entro_proof[i & 31] + entropy);
    i++;
  }

  return entropy;
}

void entro_proof_shuffle(unsigned long long count, unsigned char *input, uint32_t entropy) {
  unsigned long long position;
  unsigned char copied_input;
  unsigned long long i = 0;

  if (count > 1) {
    while (i != count) {
      position = entropy << 31;
      entropy = entro_shift((uint32_t) entropy);
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

int main(void) {
  const char *player_input = "1111111111";
  const char *casino_input = "2222222222";
  unsigned char cards[52] = {
    0xA1, 0xA2, 0xA3, 0xA4,
    0xB1, 0xB2, 0xB3, 0xB4,
    0xC1, 0xC2, 0xC3, 0xC4,
    0xD1, 0xD2, 0xD3, 0xD4,
    0x11, 0x12, 0x13, 0x14,
    0x21, 0x22, 0x23, 0x24,
    0x31, 0x32, 0x33, 0x34,
    0x41, 0x42, 0x43, 0x44,
    0x51, 0x52, 0x53, 0x54,
    0x61, 0x62, 0x63, 0x64,
    0x71, 0x72, 0x73, 0x74,
    0x81, 0x82, 0x83, 0x84,
    0x91, 0x92, 0x93, 0x94
  };
  unsigned char cards_count = 52;
  uint32_t entro_proof[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint32_t entropy = 0;
  unsigned char i = 0;

  printf("the pre-shuffled cards to show the player before the game round\n");
  i = 0;

  while (i != cards_count) {
    printf("0x%02X ", cards[i]);
    i++;

    if ((i & 3) == 0) {
      printf("\n");
    }
  }

  printf("\n");
  printf("the hashed proof from the casino input to show the player before the game round\n");
  entro_proof_hash(casino_input, entro_proof);
  i = 0;

  while (i != 32) {
    printf("0x%08X ", entro_proof[i]);
    i++;

    if ((i & 3) == 0) {
      printf("\n");
    }
  }

  printf("\n");
  printf("the player input to show the casino before the game round\n");
  printf("%s\n\n", player_input);
  entropy = entro_proof_randomize(player_input, casino_input, entro_proof);
  printf("the generated number from both the casino input and the player input to show the player after the game round\n");
  printf("%u\n\n", entropy);
  entro_proof_shuffle(cards_count, cards, entropy);
  i = 0;
  printf("the shuffled cards from the generated number to show the player after the game round\n");

  while (i != cards_count) {
    printf("0x%02X ", cards[i]);
    i++;

    if ((i & 3) == 0) {
      printf("\n");
    }
  }

  printf("\n");
  printf("the casino input to show the player after the game round for verification\n");
  printf("%s\n", casino_input);
  return 0;
}
