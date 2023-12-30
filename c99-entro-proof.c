#include <stdio.h>
#include "entro-hash.h"
#include "entro-shift.h"

void *entro_proof_hash(const char *server_input, uint32_t *entro_proof) {
  const char finalization_input[2] = {111, 0};
  unsigned char i = 1;

  entro_proof[0] = entro_hash(server_input, 0);

  while (i != 32) {
    entro_proof[i] = entro_hash(server_input, entro_proof[i - 1]);
    i++;
  }

  while (i != 1) {
    i--;
    entro_proof[i] = entro_hash(finalization_input, entro_proof[i - 1]);
  }

  entro_proof[0] = entro_hash(finalization_input, entro_proof[31]);
}

uint32_t entro_proof_randomize(const char *client_input, const char *server_input, uint32_t *entro_proof) {
  uint32_t entropy = entro_proof[0];
  unsigned long long i = 0;

  while (client_input[i] != 0) {
    entropy = entro_shift(client_input[i] + entro_proof[~i & 31] + ~entropy);
    i++;
  }

  i = 0;

  while (server_input[i] != 0) {
    entropy = entro_shift(server_input[i] + entro_proof[~i & 31] + ~entropy);
    i++;
  }

  return entropy;
}

int main(void) {
  const char *client_input = "1111111111";
  const char *server_input = "2222222222";
  uint32_t entro_proof[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint32_t entropy = 0;
  unsigned char i = 0;

  entro_proof_hash(server_input, entro_proof);

  while (i != 32) {
    printf("0x%08X ", entro_proof[i]);
    i++;

    if ((i & 3) == 0) {
      printf("\n");
    }
  }

  printf("\n");
  entropy = entro_proof_randomize(client_input, server_input, entro_proof);
  printf("%u\n", entropy);
  return 0;
}
