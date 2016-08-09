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

struct AriInfo {
	int first;
	int n;
};

class Ariprog {
public:
	void run();

private:
	vector<bool> hashtable;
	vector<AriInfo> progression;
	int length;
	int max;
	int highest_num;

	void set_up();

	void find_possible();

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
	vector<bool> temp(max * max * 2 + 1, false);
	hashtable = temp;
}

void Ariprog::run() {
	set_up();
	find_possible();
	for (int j = 1; highest_num >= j * (length - 1); ++j) {
		int diff = j;
		for (int i = 0; highest_num - i >= j * (length - 1); ++i) {
			int first = i;
			for (int n = 0; n < length; ++n) {
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