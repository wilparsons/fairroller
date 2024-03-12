# FairRoller
![FairRoller Logo](https://repository-images.githubusercontent.com/737368018/80f7aa96-1277-4f80-b939-29dc4066de5e)

## Description
FairRoller is a casino-to-player provable fairness algorithm.

Read [this article](https://medium.com/@wilparsons/fairroller-is-a-new-casino-shuffling-algorithm-with-provable-and-explainable-fairness-94964478b11f) for an in-depth explanation.

## Usage
``` c
#include <stdio.h>
#include "fairroller.h"

int main(void) {
  const char *casino_input = "1111111111";
  const char *player_input = "2222222222";
  unsigned char items[12] = {
    0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x01, 0x02,
    0x03, 0x04, 0x05, 0x06
  };
  unsigned char items_count = 12;
  uint32_t proof[8];
  uint32_t entropy = 0;
  unsigned char i = 0;

  i = 0;

  while (i != items_count) {
    printf("0x%02X", items[i]);
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
  fairroller_shuffle(items_count, items, entropy);
  i = 0;

  while (i != items_count) {
    printf("0x%02X", items[i]);
    i++;

    if ((i & 3) == 0) {
      printf("\n");
    } else {
      printf(" ");
    }
  }

  return 0;
}
```

## Reference
#### `fairroller_randomize()`
This is the randomization function that accepts the 2 following arguments.

`casino_input` is the null-terminated `char` string from the casino to seed randomization.

`player_input` is the null-terminated `char` string from the player to seed randomization.

The return value data type is `uint32_t`.

It returns the 32-bit unsigned integer pseudo-random number result.

#### `fairroller_shuffle()`
This is the item shuffling function that accepts the 3 following arguments.

`items_count` is the count of elements in the `items` array.

`items` is an unshuffled array with `unsigned char` integers to shuffle.

`entropy` is the 32-bit unsigned integer result from `fairroller_randomize()`.

The return value data type is `void`.
