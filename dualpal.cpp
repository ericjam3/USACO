/*
ID: ericm101
LANG: C++
TASK: dualpal
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
	ifstream in("dualpal.in");
	int N, S, count = 0;
	in >> N >> S;
	S++;
	ofstream out("dualpal.out");
	while (count < N){
		int totalPals = 0;
		for (int i = 2; i <= 10; ++i){
			bool first = false;
			vector<int> palind;
			int num = S, temp;
			for (int k = 18 - i; k >= 0; --k){
				if (pow(i, k) <= num){
					temp = num / pow(i, k);
					palind.push_back(temp);
					num -= temp * pow(i, k);
					first = true;
				}else if (first){
					palind.push_back(0);
				} // if
			} // for
			totalPals++;
			for (unsigned d = 0; d <= palind.size() / 2; ++d){
				if (palind[d] != palind[palind.size() - d - 1]){
					totalPals--;
					break;
				} // if
			} // for
		} // for

		if (totalPals >= 2){
			out << S << "\n";
			++count;
		} // if

		S++;
	} // while


	out.close();
	in.close();
	return 0;
} // main