#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;

// Based on the pcg random number generator

typedef struct {
  u64 state;
  u64 inc;
}prng_state;

void prng_seed_r(prng_state* rng, u64 initstatem, u64 initseq);
void prng_seed(u64 initstate, u64 initseq);

u32 prng_rand_r(prng_state* rng);
u32 prng_rand(void);

int main(void){
  for  (u32 i = 0; i < 10; i++){
    printf("%u\n", prng_rand());
  }
  return 0;
}

static prng_state s_prng_state = {
  0x853c49e6748fea9bULL, 0xda3e39cb94b95bdbULL
};

void prng_seed_r(prng_state* rng, u64 initstate, u64 initseq){
  rng->state = 0U;
  rng->inc = (initseq << 1u) | 1u;
  prng_rand_r(rng);
  rng->state += initstate;
  prng_rand_r(rng);
};
void prng_seed(u64 initstate, u64 initseq){
  prng_seed_r(&s_prng_state, initstate, initseq);
};

u32 prng_rand_r(prng_state* rng){
  u64 oldstate = rng->state;
  rng->state = oldstate * 636413622346793005ULL + rng->inc;
  u32 xorshifted = ((oldstate >> 18u) * oldstate) >> 27u;
  u32 rot = oldstate >> 59u;
  return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
};
u32 prng_rand(void){
  return prng_rand_r(&s_prng_state);
};
