/*
ID: ericm101
LANG: C++
TASK: barn1
*/

/*
This program is designed to read information from an input file including
the maximum number of boards available for a farmer in reparing stalls for
his cows, as well as the number of stalls, the number of cows, and the indexes
of the stalls containing cows. THe purpose is then to determine the fewest number
of stalls that must be covered so that all of the stalls containing cows are
covered with boards. Each of the boards can be any length. The output is simply
the fewest number of stalls that must be covered. To solve the problem, my program
finds the (stalls - 1) largest gaps between occupied stalls and subtracts those gaps
from the overall number of stalls.
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
	// creating streams
	ifstream in("barn1.in");
	ofstream out("barn1.out");
	// declaring and reading in variables
	int boards, stalls, cows, current, first, last, next;
	in >> boards >> stalls >> cows;
	// reading in occupied stalls
	vector<int> occupied(cows);
	vector<int> gaps;
	for (int i = 0; i < cows; ++i) {
		in >> occupied[i];
	}
	sort(occupied.begin(), occupied.end());

	// the next few lines, including the loop, are designed to calculate the
	// sizes of the gaps between occupied stalls
	current = occupied[0];
	first = current;
	for (int i = 1; i < cows; ++i) {
		next = occupied[i];
		last = next;
		gaps.push_back(next - current - 1);
		current = next;
	}
	sort(gaps.begin(), gaps.end());

	// this code subtracts the gaps at the beginning and the end of the
	// row of stalls from the total stalls
	int total = stalls - (stalls - last) - first + 1;
	unsigned min = boards - 1;
	if (gaps.size() < min) {
		min = gaps.size();
	}

	// subtracting the (stalls - 1) largest gaps between occupied stalls
	for (unsigned i = 0; i < min; ++i) {
		total -= gaps[gaps.size() - i - 1];
	}

	out << total << endl;


	in.close();
	out.close();

	return 0;
}