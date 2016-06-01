#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


class Crypt1 {
public:
	// constructor for the class
	// Initializes both candidates and digits vectors
	Crypt1(vector<int> & vec, vector<bool> & cand);



private:
	vector<int> digits;
	vector<bool> candidates;
};

int main() {
	ifstream in("crypt1.in");
	int num_digits, digit;
	in >> num_digits;
	vector<bool> candidates(10, false);
	vector<int> digits;
	while (in >> digit) {
		candidates[digit] = true;
		digits.push_back(digit);
	}

	Crypt1 obj(digits, candidates);

	
	in.close();
	
	system("Pause");
	return 0;
}

Crypt1::Crypt1(vector<int> & vec, vector<bool> & cand) {
	digits = vec;
	candidates = cand;
}