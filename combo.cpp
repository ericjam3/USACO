/*
ID: ericm101
LANG: C++
TASK: combo
*/

/*
This program will read in an integer representing the number of ticks on
a lock, followed by two sets of three integers between 1 and the number of
ticks. These will represent two combinations that are valid for unlocking 
the lock. These locks offer some leeway so if any given entry is off by 2
or fewer, the lock will accept it. The goal is to determine the amount of
distinct combinations that will work to open the lock. Given the following
as input:

50
1 2 3
5 6 7

There are 249 possible combinations that will work. In general, there will
be 250 combinations minus the amount that overlap. In the example above for
instance, 3 4 5 will work for both of the combinations so it can be subtracted
from the 250 total.
*/

#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// This class will store necessary variables and data structures and run the program
class Combo {
public:
	// Constructor
	Combo(int ticks_in, int f1_in, int f2_in, int f3_in, int m1_in, int m2_in, int m3_in);
	// Runs the algorithm to solve the problem
	void run_algorithm();

private:
	int ticks;
	vector<int> farmer;
	vector<int> master;

	// This is a helper function used to find any overlaps in combinations
	int big_lock();
};

int main() {
	// reading things in from input file
	ifstream in("combo.in");
	int ticks, f1, f2, f3, m1, m2, m3;
	in >> ticks >> f1 >> f2 >> f3 >> m1 >> m2 >> m3;

	// initializing class and running algorithm
	Combo obj(ticks, f1, f2, f3, m1, m2, m3);
	obj.run_algorithm();

	in.close();
	return 0;
}

// Setting up the variables
Combo::Combo(int ticks_in, int f1_in, int f2_in, int f3_in, int m1_in, int m2_in, int m3_in) {
	ticks = ticks_in;
	farmer.push_back(f1_in);
	farmer.push_back(f2_in);
	farmer.push_back(f3_in);
	master.push_back(m1_in);
	master.push_back(m2_in);
	master.push_back(m3_in);
}

void Combo::run_algorithm() {
	ofstream out("combo.out");

	// These if statements are for cases in which the lock has very few ticks
	if (ticks == 1) {
		out << 1 << "\n";
	}
	else if (ticks == 2) {
		out << 8 << "\n";
	}
	else if (ticks == 3) {
		out << 27 << "\n";
	}
	else if (ticks == 4) {
		out << 64 << "\n";
	}
	else if (ticks == 5) {
		out << 125 << "\n";
	}
	else {
		// runs the big_lock function because the lock is sufficiently large to produce 250 combs
		out << 250 - big_lock() << "\n";
	}

	out.close();
}

int Combo::big_lock() {
	int factor = 1;
	bool overlap = false;

	// loop for each of the three number in the combination
	for (int i = 0; i < 3; ++i) {
		int fmin, fmax, mmin, mmax, fact, mact;
		fact = farmer[i];
		mact = master[i];
		fmin = farmer[i] - 2;

		// number doesn't get under 1, instead wraps around the lock
		if (fmin < 1) {
			fmin = fmin + ticks;
		}
		fmax = farmer[i] + 2;
		mmin = master[i] - 2;

		// number doesn't get under 1, instead wraps around the lock
		if (mmin < 1) {
			mmin = mmin + ticks;
		}
		mmax = master[i] + 2;

		// checks to see if combinations are within 4 of each other, signaling overlap
		if (abs(fact - mact) <= 4) {
			overlap = true;
			factor *= 5 - abs(fact - mact);
		}
		// checks for overlap around 1 and max
		else if (fmax > ticks && fmax % 10 >= mmin) {
			if (fmax % 10 > mmin) {
				factor *= 2;
			}
			overlap = true;
		}
		// checks for overlap around 1 and max
		else if (mmax > ticks && mmax % 10 >= fmin) {
			if (mmax % 10 > fmin) {
				factor *= 2;
			}
			overlap = true;
		}
		// checks for overlap around 1 and max
		else if (ticks - fact + mact <= 4) {
			factor *= 5 - (ticks - fact + mact);
			overlap = true;
		}
		// checks for overlap around 1 and max
		else if (ticks - mact + fact <= 4) {
			factor *= 5 - (ticks - mact + fact);
			overlap = true;
		}
	}
	if (overlap) return factor;
	// If there is no overlap even for one number, then there is no overall overlap
	return 0;
}