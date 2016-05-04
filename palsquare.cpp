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
#include <ctime>

using namespace std;

int main(){
	ifstream in("palsquare.in");
	int base, start;
	in >> base;
	switch (base){
		case 2: 
			start = 16;
			break;
		case 3:
			start = 10;
			break;
		case 4: 
			start = 8;
			break;
		case 5:
			start = 7;
			break;
		case 6: 
			start = 6;
			break;
		case 7:
			start = 5;
			break;
		default:
			start = 4;
			break;	
	}
	int num;
	vector<int> palind;
	ofstream out("palsquare.out");
	for (int i = 1; i <= 300; ++i){
		num = pow(i, 2);
		for (int k = start; k >= 0; --k){
			if (pow(base, k) <= num){
				palind.push_back(num / pow(base, k));
				num -= palind.back() * pow(base, k));
			}
		}
	}
	return 0;
}