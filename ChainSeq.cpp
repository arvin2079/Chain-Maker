#include "ChainSeq.h"

// constructor
ChainSeq::ChainSeq(int l, bool ic) {
    if (length < 0) {
        throw invalid_argument("chin sequence length can not be negetive or zero");
    }
    length = l;
    is_circular = ic;
}
