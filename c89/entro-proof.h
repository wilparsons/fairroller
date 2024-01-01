#ifndef ENTRO_PROOF_H
#define ENTRO_PROOF_H

#include <limits.h>

#ifndef UINT32
#define UINT32
#if INT_MAX == 2147483647
typedef unsigned int uint32;
#else
typedef unsigned long uint32;
#endif
#endif

void entro_proof_hash(const char *casino_input, uint32 *entro_proof);
uint32 entro_proof_randomize(const char *casino_input, const char *player_input, uint32 *entro_proof);
void entro_proof_shuffle(unsigned short count, unsigned char *input, uint32 entropy);
#endif
