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

	// This function runs the whole process of finding the total
	// amount of acceptable ways for the cryptarithm to work
	void run_this_bad_boy();

	// Runs through all possibilites for the bottom right number
	// in the cryptarithm
	//  abc
	// x de
	// letter e in the above example
	void first_digit();

	// Runs through all possibilites for the top right number
	// in the cryptarithm and checks to see if they result in 
	// a possible solution, if not, the algorithm goes no further
	// with that digit in this location
	//  abc
	// x de
	// letter c in the above example
	void second_digit();

	// Runs through all possibilites for the top middle number
	// in the cryptarithm and checks to see if they result in 
	// a possible solution, if not, the algorithm goes no further
	// with that digit in this location
	//  abc
	// x de
	// letter b in the above example
	void third_digit();

	// Runs through all possibilites for the top left number
	// in the cryptarithm and checks to see if they result in 
	// a possible solution, if not, the algorithm goes no further
	// with that digit in this location
	//  abc
	// x de
	// letter a in the above example
	void fourth_digit();

	// Runs through all possibilites for the bottom left number
	// in the cryptarithm and checks to see if they result in 
	// a possible solution, if not, the algorithm goes no further
	// with that digit in this location. If the digit does work,
	// the total amount of solutions is incremented by 1
	//  abc
	// x de
	// letter d in the above example
	void fifth_digit();

private:
	vector<int> digits;				 // vector of allowed digits
	vector<bool> candidates;		 // vector that is true for allowed digits
	vector<int> first_sums;		     // partial sums from the first pass
	vector<int> current;			 // contains digits currently included
	int total;						 // total amount of solutions
	int carry_over;					 // used when there is a carry over during multiplication
};

int main() {
	// reading in digits, setting up problem
	ifstream in("crypt1.in");
	int num_digits, digit;
	in >> num_digits;
	vector<bool> candidates(10, false);
	vector<int> digits;
	while (in >> digit) {
		candidates[digit] = true;
		digits.push_back(digit);
	}

	// creating object
	Crypt1 obj(digits, candidates);

	// runs the algorithm
	obj.run_this_bad_boy();

	in.close();

	return 0;
}

// constructor
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