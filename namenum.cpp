/*
ID: ericm101
LANG: C++
TASK: namenum
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <ctime>

using namespace std;




int main(){
	ifstream in("namenum.in");
	string digits;
	in >> digits;
	int size = digits.size();
	vector<string> dictionary;
	ifstream dic("dict.txt");
	string name;
	ofstream out("namenum.out");
	while (dic >> name){
		if (size == name.size()){
			dictionary.push_back(name);
		}
	}
	int count = 0, val;
	for (unsigned i = 0; i < dictionary.size(); ++i){
		for (int j = 0; j < size; ++j){
			val = dictionary[i][j] - 65;
			if (val > 16) val--;
			if ((val / 3) + 2 != (digits[j] - 48)){
				break;
			}else if (j == size - 1){
				out << dictionary[i] << endl;
				++count;
			}
		}
	}
	if (count == 0){
		out << "NONE" << endl;
	}

	dic.close();
	in.close();
	out.close();

	return 0;
}