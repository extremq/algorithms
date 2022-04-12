#include <iostream>
#include <string>

// Popular prime choice for modulo computations
#define Q 1'000'000'007

typedef long long LL;

// Modular logarithmic exponentiation (just added % q for each multiplication)
// Also, pretty overkill if you ask me.
LL mod_exp(LL x, LL y, LL q)
{
    LL res = 1;

    x = x % q;

    if (x == 0) return 0;

    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % q;

        y = y >> 1;
        x = (x * x) % q;
    }
    return res;
}

// Simple comparison between two strings
void compare_pattern(const std::string pattern, const std::string text, int i, bool& found) {
    int stop = i + pattern.length();

    if (stop > text.length()) {
        return;
    }

    int counter = 0;

    for (; i < stop; ++i, ++counter) {
        if (text[i] != pattern[counter]) {
            return;
        }
    }

    std::cout << "Found pattern at index " << i - counter << '\n';

    found = true;
}

void search_string(const std::string pattern, const std::string text) {
    // Supporting the whole ascii and extended ascii set
    const LL b = 256; 
    const LL pat_len = pattern.length(), text_len = text.length();

    if (text_len < pat_len) {
        std::cout << "Pattern is longer than text. What did you expect?\n";
        return;
    }

    // Compute the pattern hash
    /*
    * Some notes:
    * (a * b) mod c = (a mod c * b mod c) mod c - same for subtraction and addition
    * However, the base is always smaller than Q, so base % Q == base
    * Also, there is no need to module pattern_hash in the multiplication since
    * it is already modulo'd by the sum.
    */
    LL pattern_hash = 0;
    for (int i = 0; i < pat_len; ++i) {
        pattern_hash = (pattern_hash * b) % Q;
        pattern_hash = (pattern_hash % Q + pattern[i]) % Q;
    }

    // Now, let's start hashing the text. We first hash the first len(pattern) characters.

    LL current_hash = 0;
    for (int i = 0; i < pat_len; ++i) {
        current_hash = (current_hash * b) % Q;
        current_hash = (current_hash % Q + text[i]) % Q;
    }

    // It's always the same exponent, so no need to compute it again and again.
    LL exponent = mod_exp(b, pat_len - 1, Q);

    // And now we start hashing character by character
    bool found = false;
    for (int i = 0; i < text_len - pat_len + 1; ++i) {

        if (current_hash == pattern_hash)
            compare_pattern(pattern, text, i, found);

        if (i < text_len - pat_len) {
            // The only legitimate time we would want to modulo is for big alphabets.
            // In our case, we aren't to fear: text[i] and b < 256 (ascii), exponent < Q,
            // Q * 256 * 256 = Q * 65536 = 6.5536e+13. Long long supports numbers magnitudes higher.
            current_hash = b * (current_hash - exponent * text[i]) + text[i + pat_len];
            current_hash %= Q;

            // REMINDER: don't use unsigned integers for this. I've wasted so much time figuring why 
            // it wouldn't work.
            if (current_hash < 0)
                current_hash += Q;
        }
    }

    if (!found) {
        std::cout << "Couldn't find any match.\n";
    }
}

int main()
{
    std::string text, pattern;

    std::getline(std::cin, text);
    std::getline(std::cin, pattern);
    
    search_string(pattern, text);
}
