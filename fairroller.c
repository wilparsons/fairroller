#include "fairroller.h"

uint32_t fairroller_randomize(const char *casino_input, const char *player_input) {
  uint32_t entropy = 0;
  unsigned short i = 0;

  while (casino_input[i] != 0) {
    entropy = stormdrop(casino_input[i] + entropy);
    i++;
  }

  i = 0;

  while (player_input[i] != 0) {
    entropy = stormdrop(player_input[i] + entropy);
    i++;
  }

  return entropy;
}

void fairroller_shuffle(unsigned short count, unsigned char *input, uint32_t entropy) {
  unsigned short position;
  unsigned char copied_input;
  unsigned short i = 0;

  if (count > 1) {
    while (i != count) {
      entropy = stormdrop(entropy);
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
