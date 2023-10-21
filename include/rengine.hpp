#pragma once

#include <random>

/**
 * Random number generator boilerplate.
 * @see https://en.cppreference.com/w/cpp/numeric/random
 */
extern thread_local std::random_device r;
extern thread_local std::default_random_engine engine;