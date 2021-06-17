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
	bool result_complete;

	bool operator == (const Result& s) const { 
		return num_of_cuts_action + num_of_link_action == s.num_of_cuts_action + s.num_of_link_action; 
	}

	bool operator != (const Result& s) const { return !operator==(s); }

	bool operator < (const Result& s) const { 
		double noc = (num_of_cuts_action == numeric_limits<double>::infinity()) ? 0 : num_of_cuts_action;
		double nol = (num_of_link_action == numeric_limits<double>::infinity()) ? 0 : num_of_link_action;
		double snoc = (s.num_of_cuts_action == numeric_limits<double>::infinity()) ? 0 : s.num_of_cuts_action;
		double snol = (s.num_of_link_action == numeric_limits<double>::infinity()) ? 0 : s.num_of_link_action;
		return noc + nol < snoc + snol; 
	}

	bool operator > (const Result& s) const { 
		double noc = (num_of_cuts_action == numeric_limits<double>::infinity()) ? 0 : num_of_cuts_action;
		double nol = (num_of_link_action == numeric_limits<double>::infinity()) ? 0 : num_of_link_action;
		double snoc = (s.num_of_cuts_action == numeric_limits<double>::infinity()) ? 0 : s.num_of_cuts_action;
		double snol = (s.num_of_link_action == numeric_limits<double>::infinity()) ? 0 : s.num_of_link_action;
		return noc + nol > snoc + snol;
	}
	
	Result() {
		num_of_cuts_action = numeric_limits<double>::infinity();
		num_of_link_action = numeric_limits<double>::infinity();
		result_complete = false;
	};
	Result(list<ChainSeq> ch_seq, int noca, int nola, bool rc) {
		chains = ch_seq;
		num_of_cuts_action = noca;
		num_of_link_action = nola;
		result_complete = rc;
	}

	int total_cost() {
		double noc=0, nol=0;
		if (num_of_cuts_action != numeric_limits<double>::infinity()) { noc = num_of_cuts_action; }
		if (num_of_link_action != numeric_limits<double>::infinity()) { nol = num_of_link_action; }
		return noc + nol;
	}

	Result merge_results(Result res1, Result res2) {
		res1.chains.splice(res1.chains.end(), res2.chains);

		res1.num_of_cuts_action = (res1.num_of_cuts_action == numeric_limits<double>::infinity()) ? 0 : res1.num_of_cuts_action;
		res1.num_of_link_action = (res1.num_of_link_action == numeric_limits<double>::infinity()) ? 0 : res1.num_of_link_action;
		res2.num_of_cuts_action = (res2.num_of_cuts_action == numeric_limits<double>::infinity()) ? 0 : res2.num_of_cuts_action;
		res2.num_of_link_action = (res2.num_of_link_action == numeric_limits<double>::infinity()) ? 0 : res2.num_of_link_action;

		res1.num_of_cuts_action += res2.num_of_cuts_action;
		res1.num_of_link_action += res2.num_of_link_action;

		res1.result_complete = res2.result_complete;

		return res1;
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

	while (!entries.empty()) {
		ChainSeq selected_goal = goal;
		ChainSeq selected_entry = entries.back();
		entries.pop_back();

		cout << "goal___________length: " << goal.length << "\n";
		cout << "selected_entry_length: " << selected_entry.length << ", " << selected_entry.is_circular << "\n";
		cout << "final_____________res: [cuts= " << final_res.num_of_cuts_action << ", links= " << final_res.num_of_link_action << "]\n\n";

		if (selected_goal.length == selected_entry.length) {
			
			Result temp_res;
			temp_res.chains.push_back(selected_entry);

			if (selected_entry.is_circular && temp_res.num_of_cuts_action == numeric_limits<double>::infinity()) { 
				temp_res.num_of_cuts_action = 1; 
			} else if (selected_entry.is_circular) {
				temp_res.num_of_cuts_action ++;
			}

			temp_res.result_complete = true;

			if (final_res > temp_res || final_res.chains.empty()) { final_res = temp_res; }
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

			temp_res = temp_res.merge_results(temp_res, divide_and_conquer(entries, next_goal, _first_round));

			if (temp_res.result_complete && (final_res > temp_res || final_res.chains.empty())) { final_res = temp_res; }
		} 
		
		else {
			Result temp_res;
			temp_res.chains.push_back(selected_entry);

			if (temp_res.num_of_cuts_action == numeric_limits<double>::infinity()) {
				temp_res.num_of_cuts_action = 1;
			} else {
				temp_res.num_of_cuts_action ++;
			} 

			if (selected_entry.is_circular && temp_res.num_of_cuts_action == numeric_limits<double>::infinity()) { 
				temp_res.num_of_cuts_action = 1; 
			} else if (selected_entry.is_circular) {
				temp_res.num_of_cuts_action ++;
			}

			temp_res.result_complete = true;

			if (final_res > temp_res || final_res.chains.empty()) { final_res = temp_res; }
		}
		
	}

	return final_res;
}

Result DACwrapper(list<ChainSeq> entries, ChainSeq goal) {
	Result result = divide_and_conquer(entries, goal);

	result.num_of_cuts_action = (result.num_of_cuts_action == numeric_limits<double>::infinity()) ? 0 : result.num_of_cuts_action;
	result.num_of_link_action = (result.num_of_link_action == numeric_limits<double>::infinity()) ? 0 : result.num_of_link_action;

	if (goal.is_circular && result.num_of_cuts_action != 0 && result.num_of_link_action != 0) { result.num_of_link_action ++; }

	return result;
}


// Driver code
int main() {

	list<ChainSeq> entries;

	// entries initialization
	ChainSeq ch1 = ChainSeq(8 , 1);
	ChainSeq ch2 = ChainSeq(38 , 0);
	ChainSeq ch3 = ChainSeq(18 , 1);
	ChainSeq ch4 = ChainSeq(9, 1);
	ChainSeq ch5 = ChainSeq(14, 0);
	ChainSeq ch6 = ChainSeq(2, 0);
	ChainSeq ch7 = ChainSeq(3, 1);

	entries.push_back(ch1);
	entries.push_back(ch2);
	entries.push_back(ch3);
	entries.push_back(ch4);
	entries.push_back(ch5);
	entries.push_back(ch6);
	entries.push_back(ch7);

	// goal initialization
	ChainSeq goal(69, 1);

	// running algorithm
	Result result = DACwrapper(entries, goal);

	// representing output
	if (!result.chains.empty()) {
		cout << "USED CHAINS NO: " << result.chains.size() << " | CUTS NO: " << result.num_of_cuts_action << " | LINKS NO: " << result.num_of_link_action;
		cout << " | TOTAL COST: " << result.total_cost() << "\n\n";
		cout << "using chains below:\n";
		for (auto const& i : result.chains) {
			cout << "(" << i.length << ", " << i.is_circular << ")\n";
		}
	} else {
		cout << "ERROR : the chain you are looking for can not be made by these entry chains!!";
	}
	
	return 0;
}