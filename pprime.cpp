/*
ID: ericm101
LANG: C++
TASK: pprime
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Pprime {
public:

	void run();

private:
	vector<long long> pals;
	vector<long long> results;
	int min;
	int max;

	void set_up();

	void find_pals();

	void find_primes();

	void output();
};

int main() {
	Pprime obj;
	obj.run();
	return 0;
}

void Pprime::run() {
	set_up();
	find_pals();
	find_primes();
	output();
}

void Pprime::set_up() {
	ifstream in("pprime.in");
	in >> min >> max;
	in.close();
}

void Pprime::find_pals() {
	for (int i = min; i <= max; ++i) {
		int temp = i;
		bool isPal = true;
		vector<int> digits;
		while (temp) {
			digits.push_back(temp % 10);
			temp /= 10;
		}
		for (unsigned j = 0; j < digits.size() / 2; ++j) {
			if (digits[j] != digits[digits.size() - 1 - j]) {
				isPal = false;
				break;
			}
		}
		if (isPal) {
			pals.push_back(i);
		}
	}
}

void Pprime::find_primes() {
	for (unsigned i = 0; i < pals.size(); ++i) {
		bool prime = true;
		for (long long j = 2; j < pals[i] / 2; ++j) {
			if (pals[i] % j == 0) {
				prime = false;
				break;
			}
		}
		if (prime) {
			results.push_back(pals[i]);
		}
	}
}

void Pprime::output() {
	ofstream out("pprime.out");
	for (unsigned i = 0; i < results.size(); ++i) {
		out << results[i] << endl;
	}
	out.close();
}