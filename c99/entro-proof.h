#ifndef ENTRO_PROOF_H
#define ENTRO_PROOF_H

#include <stdint.h>

void entro_proof_hash(const char *casino_input, uint32_t *entro_proof);
uint32_t entro_proof_randomize(const char *casino_input, const char *player_input, uint32_t *entro_proof);
void entro_proof_shuffle(unsigned short count, unsigned char *input, uint32_t entropy);
#endif
