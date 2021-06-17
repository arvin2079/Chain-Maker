#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <ctime>
#include <limits>

using namespace std;


//chain sequence
class ChainSeq {
public:
	int length;
	bool is_circular;

	bool operator == (const ChainSeq& s) const { return length == s.length && is_circular == s.is_circular; }
    bool operator != (const ChainSeq& s) const { return !operator==(s); }
	bool operator <  (const ChainSeq& s) const { return length < s.length; }
	bool operator >  (const ChainSeq& s) const { return length > s.length; }

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
	double num_of_cuts_action;
	double num_of_link_action;

	bool operator == (const Result& s) const { 
		return num_of_cuts_action + num_of_link_action == s.num_of_cuts_action + s.num_of_link_action; 
	}

	bool operator != (const Result& s) const { return !operator==(s); }

	bool operator < (const Result& s) const { 
		return num_of_cuts_action + num_of_link_action < s.num_of_cuts_action + s.num_of_link_action; 
	}

	bool operator > (const Result& s) const { 
		return num_of_cuts_action + num_of_link_action > s.num_of_cuts_action + s.num_of_link_action; 
	}
	
	Result() {
		num_of_cuts_action = numeric_limits<double>::infinity();
		num_of_link_action = numeric_limits<double>::infinity();
	};
	Result(list<ChainSeq> ch_seq, int noca, int nola) {
		chains = ch_seq;
		num_of_cuts_action = noca;
		num_of_link_action = nola;
	}

	int total_cost() {
		double noc=0, nol=0;
		if (num_of_cuts_action != numeric_limits<double>::infinity()) { noc = num_of_cuts_action; }
		if (num_of_link_action != numeric_limits<double>::infinity()) { nol = num_of_link_action; }
		return noc + nol;
	}

	Result merge_results(Result res1, Result res2) {
		res1.chains.splice(res1.chains.end(), res2.chains);
		res1.num_of_cuts_action += res2.num_of_cuts_action;
		res1.num_of_link_action += res2.num_of_link_action;
	}
};


// algorithm function
Result divide_and_conquer(list<ChainSeq> entries, ChainSeq goal, bool _first_round = true) {
	
	if (_first_round) {
		Result r;
		for (auto const& entry : entries) {
			if (goal == entry) {
				r.chains.push_back(entry);
				return r;
			}
		}
	}
	
	Result final_res;
	
	goal.is_circular = false;

	_first_round = false;

	for (auto const& entry : entries) {
		cout << entry.is_circular << "\n";
		ChainSeq selected_goal = goal;
		ChainSeq selected_entry = entry;

		entries.remove(entry);

		if (selected_goal.length == selected_entry.length) {
			Result temp_res;
			temp_res.chains.push_back(selected_entry);

			if (temp_res.num_of_link_action == numeric_limits<double>::infinity()) {
				temp_res.num_of_link_action = 1;
			} else {
				temp_res.num_of_link_action ++;
			} 
			if (selected_entry.is_circular && temp_res.num_of_cuts_action == numeric_limits<double>::infinity()) { 
				temp_res.num_of_cuts_action = 1; 
			} else if (selected_entry.is_circular) {
				temp_res.num_of_cuts_action ++;
			}

			if (final_res < temp_res) { final_res = temp_res; }
		}

		else if (selected_goal.length > selected_entry.length) {
			Result temp_res;
			temp_res.chains.push_back(selected_entry);

			ChainSeq next_goal = selected_goal;
			next_goal.length -= selected_entry.length;

			if (temp_res.num_of_link_action == numeric_limits<double>::infinity()) {
				temp_res.num_of_link_action = 1;
			} else {
				temp_res.num_of_link_action ++;
			} 
			if (selected_entry.is_circular && temp_res.num_of_cuts_action == numeric_limits<double>::infinity()) { 
				temp_res.num_of_cuts_action = 1; 
			} else if (selected_entry.is_circular) {
				temp_res.num_of_cuts_action ++;
			}

			temp_res.merge_results(temp_res, divide_and_conquer(entries, next_goal, _first_round));
		} 
		
		else {
			Result temp_res;
			temp_res.chains.push_back(selected_entry);

			if (temp_res.num_of_link_action == numeric_limits<double>::infinity()) {
				temp_res.num_of_link_action = 1;
			} else {
				temp_res.num_of_link_action ++;
			} 
			if (selected_entry.is_circular && temp_res.num_of_cuts_action == numeric_limits<double>::infinity()) { 
				temp_res.num_of_cuts_action = 1; 
			} else if (selected_entry.is_circular) {
				temp_res.num_of_cuts_action ++;
			}

			if (selected_entry.is_circular) { temp_res.num_of_cuts_action ++; }
			if (final_res < temp_res) { final_res = temp_res; }
		}

	}

	return final_res;
}


// Driver code
int main() {

	list<ChainSeq> entries;

	ChainSeq ch1 = ChainSeq(8 , 0);
	ChainSeq ch2 = ChainSeq(12, 0);
	ChainSeq ch3 = ChainSeq(8 , 1);
	ChainSeq ch4 = ChainSeq(15 , 0);

	entries.push_back(ch1);
	entries.push_back(ch2);
	entries.push_back(ch3);
	entries.push_back(ch4);

	ChainSeq goal(15, 0);

	Result result = divide_and_conquer(entries, goal);

	cout << "result chains length : " << result.chains.size() << " | result cost : " << result.total_cost();
	
	return 0;

	// srand(time(NULL));
	// for (int i=0 ; i < 5 ; i++) {
	// 	entries.push_front(ChainSeq(rand() % 15 + 1, rand() % 2));
	// }

	// entries.remove(ch2);

	// for (auto const& i : entries) {
	// 	cout << i.length << "\t" << i.is_circular << "\n";
	// }
}