/*
ID: ericm101
LANG: C++
TASK: ariprog
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

/*
This program deals with arithmetic progressions which are sequences in the
following form: a, a + b, a + 2b, ... , a + nb where n = 0, 1, 2, 3, ...
It also deals with bisquares which are numbers that can be represented by the
sum of the squares of two other numbers (Ex. 13 = 2^2 + 3^2).
The purpose of this program is to find all the arithmetic progressions of a
given length over a given set of bisquares. The input is simply two numbers,
the first is the length of the arithmetic progressions you are looking for
and the second is the maximum value to be used to compute the set of bisquares.
For example if the input is "4 8" then the program finds all arithmetic
progressions of length 4 and the progressions can go at most to 128 = 8^2 + 8^2.
Outputted are all the arithmetic progressions represented on their own line by
the first number in the sequence followed by the distance between successive
numbers in the sequence.
*/


// This struct holds the info for the first number and the distance between
// numbers in the arithmetic progressions
struct AriInfo {
	int first;
	int n;
};

// This class helps organize the program and all the variables used
class Ariprog {
public:
	// Driver function to run the program
	void run();

private:
	// Indexes of this vector are marked as true if they are in
	// the set of bisquares
	vector<bool> hashtable;
	// This vector holds all of the necessary information for the
	// arithmetic progressions that are found
	vector<AriInfo> progression;
	int length;
	int max;
	int highest_num;

	// Reading in input and setting up variables
	void set_up();

	// Find all of the possible numbers represented as bisquares
	void find_possible();

	// This function simply outputs the necessary information to
	// a file called "ariprog.out"
	void output();
};

int main() {
	Ariprog obj;
	obj.run();
	return 0;
}

void Ariprog::set_up() {
	ifstream in("ariprog.in");
	in >> length >> max;
	in.close();
	highest_num = 0;
	// Set the hashtable vector elements all to false
	vector<bool> temp(max * max * 2 + 1, false);
	hashtable = temp;
}

void Ariprog::run() {
	set_up();
	find_possible();

	// Outer loop controls the distance between successive elements in
	// the arithmetic progressions
	for (int j = 1; highest_num >= j * (length - 1); ++j) {
		// This variable holds the distance between elements in the
		// arithmetic progressions so that if one is found, it can
		// be saved for the output later
		int diff = j;
		// The inner loop iterates over different starting values for the
		// arithmetic sequence
		for (int i = 0; highest_num - i >= j * (length - 1); ++i) {
			int first = i;
			// This loop simply goes through an aritmetic progression
			// based on the starting value and difference between each
			// element which are given by the first two loops
			for (int n = 0; n < length; ++n) {
				// This evaluates to true if the next number in the progression
				// cannot be represented among the pool of bisquares. It then
				// breaks out of the innermost loop to try a different sequence
				if (!hashtable[i + (n * j)]) {
					break;
				}
				else if (n == length - 1) {
						AriInfo temp;
						temp.first = first;
						temp.n = diff;
						progression.push_back(temp);
				}
			}
		}
	}
	output();
}

void Ariprog::find_possible() {
	for (int i = 0; i <= max; ++i) {
		for (int j = 0; j <= max; ++j) {
			int sum = (i * i) + (j * j);
			hashtable[sum] = true;
			highest_num = sum;
		}
	}
}

void Ariprog::output() {
	ofstream out("ariprog.out");
	if (progression.size() > 0) {
		for (unsigned i = 0; i < progression.size(); ++i) {
			out << progression[i].first << " " << progression[i].n << "\n";
		}
	}
	else {
		out << "NONE" << endl;
	}

	out.close();
}