#include <random>
#include "rengine.hpp"

thread_local std::random_device r;
thread_local std::default_random_engine engine(r());