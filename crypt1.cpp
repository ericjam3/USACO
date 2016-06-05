/*
ID: ericm101
LANG: C++
TASK: crypt1
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
This program reads from a text file named "crypt1.in". It first reads a single integer
which represents the number of digits that will appear on the line below, separated
by spaces. Those digits, ranging between 1 and 9 inclusive, will then be read in. The
purpose of the program is to find all the solutions of a cryptarithm involving the
multiplication of the given digits and must result in the use of only the given digits.
To make it more clear, here is an example:
Given:
5
2 3 4 6 8

The only solution that will work is:
 222
 *22
____
 444
444
____
4884
 */


class Crypt1 {
public:
	// constructor for the class
	// Initializes both candidates and digits vectors
	Crypt1(vector<int> & vec, vector<bool> & cand);

	void run_this_bad_boy();

	void first_digit();

	void second_digit();

	void third_digit();

	void fourth_digit();

	void fifth_digit();

private:
	vector<int> digits;
	vector<bool> candidates;
	vector<int> first_sums;
	vector<int> current;
	int total;
	int carry_over;
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

	obj.run_this_bad_boy();

	in.close();

	//system("Pause");
	return 0;
}

Crypt1::Crypt1(vector<int> & vec, vector<bool> & cand) {
	digits = vec;
	candidates = cand;
}

void Crypt1::run_this_bad_boy() {
	first_sums.resize(4);
	total = 0;
	first_digit();
	ofstream out("crypt1.out");
	out << total << "\n";
	out.close();
}

void Crypt1::first_digit() {
	for (unsigned i = 0; i < digits.size(); ++i) {
		current.push_back(digits[i]);
		second_digit();
		current.pop_back();
	}
}

void Crypt1::second_digit() {
	for (unsigned i = 0; i < digits.size(); ++i) {
		if (candidates[(digits[i] * current.front()) % 10]) {
			carry_over = (digits[i] * current.front()) / 10;
			current.push_back(digits[i]);
			third_digit();
			current.pop_back();
		}else{
			continue;
		}
	}
}

void Crypt1::third_digit() {
	const int temp = carry_over;
	for (unsigned i = 0; i < digits.size(); ++i) {
		carry_over = temp;
		int num = (digits[i] * current.front()) + carry_over;
		if (candidates[num % 10]) {
			carry_over = num / 10;
			current.push_back(digits[i]);
			first_sums[1] = num % 10;
			fourth_digit();
			current.pop_back();
		}else{
			continue;
		}
	}
}

void Crypt1::fourth_digit() {
	const int temp = carry_over;
	for (unsigned i = 0; i < digits.size(); ++i) {
		carry_over = temp;
		int num = (digits[i] * current.front()) + carry_over;
		if (num < 10 && candidates[num]) {
			carry_over = num / 10;
			current.push_back(digits[i]);
			first_sums[2] = num % 10;
			fifth_digit();
			current.pop_back();
		}else {
			continue;
		}
	}
}

void Crypt1::fifth_digit() {
	for (unsigned i = 0; i < digits.size(); ++i) {
		int num1 = digits[i] * current[1];
		int num2 = digits[i] * current[2] + (num1 / 10);
		int num3 = digits[i] * current[3] + (num2 / 10);
		int sum1 = (num1 % 10) + first_sums[1];
		int sum2 = (num2 % 10) + first_sums[2] + (sum1 / 10);
		int sum3 = (num3 % 10) + (sum2 / 10);

		if (candidates[num1 % 10] && candidates[num2 % 10] && candidates[num3 % 10]
		    && candidates[sum1 % 10] && candidates[sum2 % 10]
			&& num3 < 10 && candidates[sum3]) {
			++total;
		}else{
			continue;
		}
	}
}