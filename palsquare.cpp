/*
ID: ericm101
LANG: C++
TASK: palsquare
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

int main(){
	ifstream in("palsquare.in");
	int base, start, begin;
	in >> base;
	switch (base){
		case 2: 
			start = 16;
			begin = 7;
			break;
		case 3:
			start = 10;
			begin = 4;
			break;
		case 4: 
			start = 8;
			begin = 3;
			break;
		case 5:
			start = 7;
			begin = 3;
			break;
		case 6: 
			start = 6;
			begin = 2;
			break;
		case 7:
			start = 5;
			begin = 2;
			break;
		default:
			start = 4;
			begin = 2;
			break;	
	} // switch

	int num;
	
	ofstream out("palsquare.out");
	for (int i = 1; i <= 300; ++i){
		bool first = false, ispal = true;
		vector<int> palind;
		num = pow(i, 2);
		for (int k = start; k >= 0; --k){
			if (pow(base, k) <= num){
				palind.push_back(num / pow(base, k));
				num -= palind.back() * pow(base, k);
				first = true;
			}else if (first){
				palind.push_back(0);
			}
		}
		for (unsigned d = 0; d <= palind.size() / 2; ++d){
			if (palind[d] != palind[palind.size() - d - 1]){
				ispal = false;
				break;
			}
		}

		if (ispal){
			int num2 = i;
			bool f = false;
			vector<int> pal;
			for (int k = begin; k >= 0; --k){
				if (pow(base, k) <= num2){
					pal.push_back(num2 / pow(base, k));
					num2 -= pal.back() * pow(base, k);
					f = true;
				}else if (f){
					pal.push_back(0);
				}
			}
			
			for (unsigned d = 0; d < pal.size(); ++d){
				out << pal[d];
			}
			out << " ";
			
			for (unsigned d = 0; d < palind.size(); ++d){
				out << palind[d];
			}
			out << endl;
			
		}
	}
	return 0;
} // main