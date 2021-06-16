#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <ctime>
#include "ChainSeq.h"

using namespace std;

void divide_and_conquer(list<ChainSeq> entry, ChainSeq goal) {
	cout << "in divide and conq..";
}

int main() {
	list<ChainSeq> entry;
	srand(time(NULL));
	for (int i=0 ; i < 5 ; i++) {
		entry.push_front(ChainSeq(rand() % 10 + 1, rand() % 2));
	}

	// for (auto const& i : entry) {
    // 	cout << i.length << "\n";
	// }
}