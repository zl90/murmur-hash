#include <string>
#include <iostream>
#include "murmur.h"

const uint32_t c1 = 0xcc9e2d51;
const uint32_t c2 = 0x1b873593;
const int8_t r1 = 15;
const int8_t r2 = 13;
const int8_t m = 5;
const uint32_t n = 0xe6546b64;

uint32_t leftRotate(uint32_t num, uint32_t shift)
{
    return (num << shift) | (num >> (32 - shift));
}

uint32_t multiply(uint32_t num, uint32_t shift)
{
    return ((num & 0xffff) * shift) + ((((num >> 16) * shift) & 0xffff) << 16);
}

uint32_t murmur3_32(std::string key = "", uint32_t seed = 0)
{
    uint32_t hash = seed;
    uint32_t len = key.length();
    uint32_t i = 0;

    // Add to the hash for each four byte chunk of the key
    while (len - i >= 4)
    {
        i += 4;

        uint32_t a = static_cast<uint32_t>(key[i - 4]);
        uint32_t b = static_cast<uint32_t>(key[i - 3]);
        uint32_t c = static_cast<uint32_t>(key[i - 2]);
        uint32_t d = static_cast<uint32_t>(key[i - 1]);

        uint32_t k = (a << 24) + (b << 16) + (c << 8) + d;

        k = multiply(k, c1);
        k = leftRotate(k, r1);
        k = multiply(k, c2);

        hash = hash ^ k;
        hash = leftRotate(hash, r2);
        hash = multiply(hash, m) + n;
    }

    // Handle the remaining bytes:
    int8_t remaining = len - i;
    if (remaining > 0 && remaining < 4)
    {
        uint32_t remainingBytes = 0;
        uint32_t byte1 = static_cast<uint32_t>(key[len - 3]);
        uint32_t byte2 = static_cast<uint32_t>(key[len - 2]);
        uint32_t byte3 = static_cast<uint32_t>(key[len - 1]);

        switch (remaining)
        {
        case 3:
            remainingBytes ^= byte1 << 16;
        case 2:
            remainingBytes ^= byte2 << 8;
        case 1:
            remainingBytes ^= byte3;
        default:
            break;
        }

        remainingBytes = multiply(remainingBytes, c1);
        remainingBytes = leftRotate(remainingBytes, r1);
        remainingBytes = multiply(remainingBytes, c2);

        hash = hash ^ remainingBytes;
    }

    hash = hash ^ len;

    hash = hash ^ (hash >> 16);
    hash = multiply(hash, 0x85ebca6b);
    hash = hash ^ (hash >> 13);
    hash = multiply(hash, 0xc2b2ae35);
    hash = hash ^ (hash >> 16);

    return hash;
}