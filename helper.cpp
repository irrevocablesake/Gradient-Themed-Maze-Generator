#include "helper.h"
#include "time.h"

Helper::Helper()
{
	srand(time(NULL));
	state.a=rand();
	state.b=rand();
}

uint64_t Helper::xorshift128p(struct xorshift128p_state *state)
{
	uint64_t t = state->a;
	uint64_t const s = state->b;
	state->a = s;
	t ^= t << 23;		// a
	t ^= t >> 17;		// b
	t ^= s ^ (s >> 26);	// c
	state->b = t;
	return (t + s);
}