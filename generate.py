import math
from typing import List

ITERS = 16
FRAC_BITS = 24


def get_k(iters: int) -> float:
    k = 1.0
    for i in range(iters):
        k *= 1 / math.sqrt(1 + 2 ** (-2 * i))
    return k


def get_table(iters: int) -> List[float]:
    return [math.atan(2 ** (-i)) for i in range(iters)]


def to_fixed(x: float) -> int:
    assert x >= 0
    return int(x * 2**FRAC_BITS) & 0xFFFFFFFF


def to_fixed_str(x: float) -> str:
    return hex(to_fixed(x))


print(f"K = {to_fixed_str(get_k(ITERS))}")
print(f"{{ {', '.join(str(to_fixed_str(x)) for x in get_table(ITERS))} }}")
