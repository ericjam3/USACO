/*
ID: ericm101
LANG: C++
TASK: sprime
*/

#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class Sprime {
public:

	void run();

private:
	vector<long> results;
	int num_digs;

	void set_up();

	void gen_primes(long num, int dig);

	bool is_prime(long num);

	void output();
};

int main() {
	Sprime obj;
	obj.run();
	return 0;
}

void Sprime::run() {
	set_up();
	vector<int> vec;
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(5);
	vec.push_back(7);
	for (unsigned i = 0; i < vec.size(); ++i) {
		gen_primes(vec[i], 1);
	}
	output();
}

void Sprime::set_up() {
	ifstream in("sprime.in");
	in >> num_digs;
	in.close();
}

void Sprime::gen_primes(long num, int dig) {
	long temp = num;
	for (long i = 1; i <= 9; i += 2) {
		num *= 10;
		num += i;
		if (is_prime(num)) {
			if (dig == num_digs - 1) {
				results.push_back(num);
			}
			else {
				gen_primes(num, dig + 1);
			}
		}
		num = temp;
	}
}

bool Sprime::is_prime(long num) {
	int bound = sqrt(num);
	for (long i = 3; i <= bound; ++i) {
		if (num % i == 0) return false;
	}
	return true;
}

void Sprime::output() {
	ofstream out("sprime.out");
	for (unsigned i = 0; i < results.size(); ++i) {
		out << results[i] << endl;
	}
	out.close();
}