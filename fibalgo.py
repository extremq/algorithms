from functools import lru_cache


def fib(n):
    if n <= 1:
        return n
    else:
        return fib(n - 1) + fib(n - 2)


cache = {}  # cache using dictionaries


def fib2(n):
    if n not in cache.keys():
        if n <= 1:
            return n
        else:
            cache[n] = fib2(n - 1) + fib2(n - 2)
            return cache[n]
    else:  # term was already computed
        return cache[n]


@lru_cache(maxsize=None)  # cache using lru_cache
def fib3(n):
    if n <= 1:
        return n
    else:
        return fib3(n - 1) + fib3(n - 2)


@lru_cache(maxsize=None)
def fib4(n):
    if n <= 2:
        if n < 2:  # F(2) = F(1)^2 + F(2)^2
            return n
        return 1
    else:
        if n % 2 == 0:
            f_n = fib4(n // 2)
            f_np1 = fib4(n // 2 + 1)
            return f_n * (2 * f_np1 - f_n)
        else:
            f_n = fib4((n - 1) // 2)
            f_np1 = fib4((n + 1) // 2)
            return f_n * f_n + f_np1 * f_np1
