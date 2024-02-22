#include <stdio.h>
#include "fairroller.h"

int main(void) {
  const char *casino_input = "1111111111";
  const char *player_input = "2222222222";
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
  uint32_t proof[8];
  uint32_t entropy = 0;
  unsigned char i = 0;

  i = 0;

  while (i != cards_count) {
    printf("0x%02X", cards[i]);
    i++;

    if ((i & 3) == 0) {
      printf("\n");
    } else {
      printf(" ");
    }
  }

  printf("\n%s\n\n", casino_input);
  orbithash(casino_input, proof);
  i = 0;

  while (i != 8) {
    printf("0x%08X", proof[i]);
    i++;

    if ((i & 3) == 0) {
      printf("\n");
    } else {
      printf(" ");
    }
  }

  entropy = fairroller_randomize(casino_input, player_input);
  printf("\n%s\n\n", player_input);
  printf("0x%08X\n\n", entropy);
  fairroller_shuffle(cards_count, cards, entropy);
  i = 0;

  while (i != cards_count) {
    printf("0x%02X", cards[i]);
    i++;

    if ((i & 3) == 0) {
      printf("\n");
    } else {
      printf(" ");
    }
  }

  return 0;
}
