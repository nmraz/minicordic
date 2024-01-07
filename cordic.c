#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define FRAC_BITS 24
#define ITERS 16

// Constants from `generate.py`
#define K 0x9b74ed

int32_t atan_table[ITERS] = {
    0xc90fda, 0x76b19c, 0x3eb6eb, 0x1fd5ba, 0xffaad, 0x7ff55, 0x3ffea, 0x1fffd,
    0xffff,   0x7fff,   0x3fff,   0x1fff,   0xfff,   0x7ff,   0x3ff,   0x1ff,
};

int32_t int_to_fixed(int32_t val) {
    return val << FRAC_BITS;
}

int32_t fixed_mul(int32_t a, int32_t b) {
    return (int32_t) (((int64_t) a * b) >> FRAC_BITS);
}

int32_t cordic_sin(int32_t angle) {
    int32_t x = int_to_fixed(1);
    int32_t y = int_to_fixed(0);
    for (size_t i = 0; i < ITERS; i++) {
        int32_t sign = angle > 0 ? 1 : -1;
        int32_t theta = atan_table[i];
        int32_t new_x = x - sign * (y >> i);
        int32_t new_y = sign * (x >> i) + y;
        x = new_x;
        y = new_y;
        angle -= sign * theta;
    }
    return fixed_mul(y, K);
}

int32_t double_to_fixed(double x) {
    return x * (double) (1 << FRAC_BITS);
}

double fixed_to_double(int32_t x) {
    return x / (double) (1 << FRAC_BITS);
}

void test_sins(double x) {
    printf("sin(%f): std=%f, cordic=%f\n", x, sin(x),
           fixed_to_double(cordic_sin(double_to_fixed(x))));
}

int main(void) {
    test_sins(1);
    test_sins(M_PI_2);
    test_sins(M_PI_4);
}
