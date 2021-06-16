#pragma once
#include <stdexcept>

using namespace std;

class ChainSeq{
public:
    int length;
    bool is_circular;

    ChainSeq();
    ChainSeq(int l, bool ic);
};