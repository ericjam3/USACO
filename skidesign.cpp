/*
ID: ericm101
LANG: C++
TASK: skidesign
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Ski {
public:
	Ski();

	void run_this_sucker();

private:
	vector<int> hills;
	int num_hills;
	int min_cost;
};


int main() {
	Ski obj;
	obj.run_this_sucker();

	return 0;
}

Ski::Ski() {
	ifstream in("skidesign.in");
	int height;
	in >> num_hills;
	for (int i = 0; i < num_hills; ++i) {
		in >> height;
		hills.push_back(height);
	}
	sort(hills.begin(), hills.end());
	in.close();
	min_cost = 0;
	for (int i = 0; i < num_hills; ++i) {
		if (hills[i] < 42) {
			min_cost += pow(42 - hills[i], 2);
		}
		else if (hills[i] > 59) {
			min_cost += pow(hills[i] - 59, 2);
		}
	}
	
}

void Ski::run_this_sucker() {
	for (int i = 0; i <= 100; ++i) {
		int j = i + 17;
		int temp_cost = 0;
		for (int k = 0; k < num_hills; ++k) {
			if (hills[k] < i) {
				temp_cost += pow(i - hills[k], 2);
			}
			else if (hills[k] > j) {
				temp_cost += pow(hills[k] - j, 2);
			}
			if (temp_cost > min_cost) {
				break;
			}
		}
		if (temp_cost < min_cost) {
			min_cost = temp_cost;
		}
	}
	ofstream out("skidesign.out");
	out << min_cost << endl;
	out.close();
}