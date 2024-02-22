#ifndef FAIRROLLER_H
#define FAIRROLLER_H

#include <stdint.h>
#include "orbithash.h"
#include "stormdrop.h"

uint32_t fairroller_randomize(const char *casino_input, const char *player_input);
void fairroller_shuffle(unsigned short count, unsigned char *input, uint32_t entropy);
#endif
