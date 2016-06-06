/*
ID: ericm101
LANG: C++
TASK: combo
*/

#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class Combo {
public:
	Combo(int ticks_in, int f1_in, int f2_in, int f3_in, int m1_in, int m2_in, int m3_in);

	void run_algorithm();

private:
	int ticks;
	vector<int> farmer;
	vector<int> master;

	int big_lock();
};

int main() {
	// reading things in from input file
	ifstream in("combo.in");
	int ticks, f1, f2, f3, m1, m2, m3;
	in >> ticks >> f1 >> f2 >> f3 >> m1 >> m2 >> m3;
	Combo obj(ticks, f1, f2, f3, m1, m2, m3);
	obj.run_algorithm();

	in.close();
	return 0;
}

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
		out << 250 - big_lock() << "\n";
	}
	
	out.close();
}

int Combo::big_lock() {
	int factor = 1;
	bool overlap = false;
	for (int i = 0; i < 3; ++i) {
		int fmin, fmax, mmin, mmax;
		fmin = farmer[i] - 2;
		if (fmin < 1) {
			fmin = fmin + ticks;
		}
		fmax = farmer[i] + 2;
		mmin = master[i] - 2;
		if (mmin < 1) {
			mmin = mmin + ticks;
		}
		mmax = master[i] + 2;
		
		if (fmax >= mmin) {
			overlap = true;
			factor *= fmax - mmin + 1;
		}
		else if (mmax >= fmin) {
			overlap = true;
			factor *= mmax - fmin + 1;
		}
	}
	if (overlap) return factor;
	return 0;
}
