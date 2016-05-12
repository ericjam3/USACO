/*
ID: ericm101
LANG: C++
TASK: barn1
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


int main(){
	ifstream in("barn1.in");
	ofstream out("barn1.out");
	int boards, stalls, cows, current, first, last, next;
	in >> boards >> stalls >> cows >> current;
	first = current;
	vector<int> gaps;

	for (int i = 1; i < cows; ++i){
		in >> next;
		last = next;
		gaps.push_back(next - current - 1);
		current = next;
	}

	sort(gaps.begin(), gaps.end());

	int total = stalls - (stalls - last) - first + 1;
	unsigned min = boards - 1;
	if (gaps.size() < min){
		min = gaps.size();
	}

	for (unsigned i = 0; i < min; ++i){
		total -= gaps[gaps.size() - i - 1];
	}
	
	out << total << endl;


	in.close();
	out.close();
	return 0;
}