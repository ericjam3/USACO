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

class Milk {
public:

	void run();

private:
	vector<bool> results;
	vector<int> pails;
	vector<int> caps;
	vector<vector<bool> > checked;

	void set_up();

	void algo();

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
	if (checked[pails[0]][pails[1]]) {
		return;
	}
	checked[pails[0]][pails[1]] = true;
	if (!pails[0]) {
		results[pails[2]] = true;
	}

	for (int i = 0; i < 3; ++i) {
		if (pails[i]) {
			for (int j = 0; j < 3; ++j) {
				if (j != i && pails[j] != caps[j]) {
					if (pails[i] >= caps[j] - pails[j]) {
						int change = caps[j] - pails[j];
						pails[i] -= change;
						pails[j] += change;
						algo();
						pails[i] += change;
						pails[j] -= change;
					}
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