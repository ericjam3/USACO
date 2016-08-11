/*
ID: ericm101
LANG: C++
TASK: milk3
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/*
This program solves the Mother's Milk USACO training problem. In this problem,
there are 3 pails; A, B, and C. We are given the capacity of each of the pails
which will be between 1 and 20 inclusive. Note that the pails can all have
different capacities. To start out, pail C is full to capacity with milk while
pails A and B are empty. The problem statement says that milk can be poured from
one pail into another for any amount of time in such a way that you don't stop
a pour until either the source pail is empty or the recipient pail is full. The
purpose of this program is to output all of the possible amounts of milk in pail C
at any point when pail A is empty. This program uses a branch and bound algorithm
to go through all possible combinations of amounts of milk in each pail, bounding
when a combination is reached that was previously dealt with.
*/

// This class runs the program, containing all of the member functions and
// member variables as private types
class Milk {
public:
	// Driver function to run the program
	void run();

private:
	// Indexes corresponding to amounts of milk that can end up in pail C when
	// pail A is empty are marked true
	vector<bool> results;
	// This vector contains the amounts of milk in each pail during the running
	// of the algorithm
	vector<int> pails;
	// This vector contains the capacites of each pail
	vector<int> caps;
	// This vector of vectors marks which combinations of amounts in each pail
	// have already been dealt with. Only amounts in pail A and pail C are used
	// because if you know those two values then pail C can only contain one value
	vector<vector<bool> > checked;

	// This function sets up member variables so that the algorithm can be ran
	void set_up();

	// This function runs the branch and bound algorithm
	void algo();

	// This function outputs the necessary information
	void output();
};

int main() {
	Milk obj;
	obj.run();
	return 0;
}

void Milk::run() {
	set_up();
	algo();
	output();
}

void Milk::set_up() {
	ifstream in("milk3.in");
	int cap_A, cap_B, cap_C;
	in >> cap_A >> cap_B >> cap_C;
	caps.push_back(cap_A);
	caps.push_back(cap_B);
	caps.push_back(cap_C);
	in.close();
	vector<bool> temp(cap_C + 1, false);
	results = temp;
	vector<int> pails_in(3, 0);
	pails = pails_in;
	pails[2] = cap_C;
	vector<bool> row(cap_B + 1, false);
	vector<vector<bool> > table(cap_A + 1, row);
	checked = table;
}

void Milk::algo() {
	// If already dealt with, return
	if (checked[pails[0]][pails[1]]) {
		return;
	}
	checked[pails[0]][pails[1]] = true;
	// If pail A is empty, add the amount in pail C to results
	if (!pails[0]) {
		results[pails[2]] = true;
	}

	// Outer loop controls the pail that is being poured from
	for (int i = 0; i < 3; ++i) {
		if (pails[i]) {
			// Inner loop controls pail being poured into
			for (int j = 0; j < 3; ++j) {
				if (j != i && pails[j] != caps[j]) {
					// If there is at least as much milk in the
					// source pail as room left in the recipient pail
					if (pails[i] >= caps[j] - pails[j]) {
						int change = caps[j] - pails[j];
						pails[i] -= change;
						pails[j] += change;
						algo();
						pails[i] += change;
						pails[j] -= change;
					}
					// If there is more room left in the recipient pail than
					// room left in the source pail
					else {
						int change = pails[i];
						pails[i] -= change;
						pails[j] += change;
						algo();
						pails[i] += change;
						pails[j] -= change;
					}
				}
			}
		}
	}
}

void Milk::output() {
	ofstream out("milk3.out");
	for (unsigned i = 0; i < results.size() - 1; ++i) {
		if (results[i]) {
			out << i << " ";
		}
	}
	if (results.back()) {
		out << results.size() - 1;
	}
	out << endl;
	out.close();
}