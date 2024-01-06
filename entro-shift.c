#include "entro-shift.h"

uint32_t entro_shift(uint32_t entropy) {
  entropy ^= (entropy << 14) ^ (entropy >> 13);
  entropy = ~(entropy ^ 1111111111) - (~entropy << 5);
  entropy = (entropy << 31) + (entropy >> 1);
  entropy += entropy << 3;
  entropy ^= 1111111111;
  entropy = ~(entropy - (entropy << 5));
  return (entropy >> 1) ^ entropy;
}
