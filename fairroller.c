#include "fairroller.h"

uint32_t fairroller_randomize(const char *casino_input, const char *player_input) {
  uint32_t state[4] = {0, 0, 0, 0};
  uint32_t entropy = 0;
  unsigned short i = 0;

  while (casino_input[i] != 0) {
    entropy = stormdrop(state) + casino_input[i];
    i++;
  }

  i = 0;

  while (player_input[i] != 0) {
    entropy = stormdrop(state) + player_input[i];
    i++;
  }

  return entropy;
}

void fairroller_shuffle(unsigned short count, unsigned char *input, uint32_t entropy) {
  uint32_t state[4] = {0, 0, 0, entropy};
  unsigned short position;
  unsigned char copied_input;
  unsigned short i = 0;

  if (count > 1) {
    while (i != count) {
      entropy = stormdrop(state);
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
