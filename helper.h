#ifndef _HELPER_H_
#define _HELPER_H_

#pragma once

#include "time.h"
#include "stdint.h"
#include<stdlib.h>

class Helper
{
    struct xorshift128p_state
    {
        uint64_t a, b;
    };
    
    public :
        xorshift128p_state state;
        Helper();
        uint64_t xorshift128p(struct xorshift128p_state *state);
};

#endif