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

struct Dale {
	int height;
	int change;

	Dale() { change = 0; }
};

bool comparator(Dale a, Dale b) {
	return a.height < b.height;
}

class Ski {
public:
	Ski();

	void run_this_sucker();

	void add_her_up();

private:
	vector<Dale> hills;
	int num_hills;
};


int main() {
	Ski obj;
	obj.run_this_sucker();

	return 0;
}

Ski::Ski() {
	ifstream in("skidesign.in");
	int height;
	Dale hill;
	in >> num_hills;
	for (int i = 0; i < num_hills; ++i) {
		in >> hill.height;
		hills.push_back(hill);
	}
	sort(hills.begin(), hills.end(), comparator);
	in.close();
}

void Ski::run_this_sucker() {
	for (unsigned i = 0; i < num_hills / 2; ++i) {
		if (num_hills % 2) {
			double diff = hills[(num_hills / 2) + i + 1].height - hills[(num_hills / 2) - i - 1].height;
			if (diff > 17) {
				diff -= 17;
				diff /= 2;
				hills[(num_hills / 2) + i + 1].height -= ceil(diff);
				hills[(num_hills / 2) + i + 1].change += ceil(diff);
				hills[(num_hills / 2) - i - 1].height += floor(diff);
				hills[(num_hills / 2) - i - 1].change += floor(diff);

				sort(hills.begin(), hills.end(), comparator);
			}
		}
		else {
			double diff = hills[(num_hills / 2) + i].height - hills[(num_hills / 2) - i - 1].height;
			if (diff > 17) {
				diff -= 17;
				diff /= 2;
				hills[(num_hills / 2) + i].height -= ceil(diff);
				hills[(num_hills / 2) + i].change += ceil(diff);
				hills[(num_hills / 2) - i - 1].height += floor(diff);
				hills[(num_hills / 2) - i - 1].change += floor(diff);

				sort(hills.begin(), hills.end(), comparator);
			}
		}
	}
	add_her_up();
}

void Ski::add_her_up() {
	int cost = 0;
	for (int i = 0; i < num_hills; ++i) {
		cost += pow(hills[i].change, 2);
	}
	ofstream out("skidesign.out");
	out << cost << endl;
	out.close();
}

