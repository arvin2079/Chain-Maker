#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <ctime>
#include "ChainSeq.h"

using namespace std;


//chain sequence
class ChainSeq {
public:
	int length;
	bool is_circular;

	ChainSeq();
	ChainSeq(int l, bool ic) {
		if (l < 0) {
			throw invalid_argument("chin sequence length can not be negetive or zero");
		}
		length = l;
		is_circular = ic;
	}
};

// wrapper for ChainSeq for result representation
class Result {
public:
	list<ChainSeq> chains;
	int num_of_cuts_action;
	int num_of_link_action;
	
	Result();
	Result(list<ChainSeq> ch_seq, int noca, int nola) {
		if (noca < 0) {
			throw invalid_argument("num of cuts action can not be negetive or zero");
		}

		if (nola < 0) {
			throw invalid_argument("num of link action can not be negetive or zero");
		}

		chains = ch_seq;
		num_of_cuts_action = noca;
		num_of_link_action = nola;
	}

	int total_cost() {
		return num_of_cuts_action + num_of_link_action;
	}
};


// algorithm function
Result divide_and_conquer(list<ChainSeq> entry, ChainSeq goal) {
	if (entry.size() )
	// till hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
}


// main runner
int main() {

	list<ChainSeq> entry;

	entry.push_front(ChainSeq(8 , 0));
	entry.push_front(ChainSeq(12, 0));
	entry.push_front(ChainSeq(8 , 1));
	entry.push_front(ChainSeq(3 , 0));

	ChainSeq goal(15, 0);

	Result res = divide_and_conquer(entry, goal);


	// srand(time(NULL));
	// for (int i=0 ; i < 5 ; i++) {
	// 	entry.push_front(ChainSeq(rand() % 15 + 1, rand() % 2));
	// }

	// for (auto const& i : entry) {
	// 	cout << i.length << "\t" << i.is_circular << "\n";
	// }
}