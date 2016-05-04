/*
ID: ericm101
LANG: C++
TASK: namenum
*/

// READ //
/*
This program reads a number between 1 and 12 digits long from a text file named
"namenum.in" and also a dictionary text file containing viable names. The dictionary
will be named "dict.txt". The digits must be between 2 and 9. The digits are converted
to the letter that they correspond to on a numpad like those seen on flip phones, it
is important to not that the letters Q and Z are not included and each digit accounts
for three letters. The end goal is to find all valid names from the dictionary made out
of the given digits and outputting them in ascending alphabetical order. Note that the
dictionary itself is given in alphabetical order and is no more than 5000 words. 
*/


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

int main(){
	// Reading in digits from namenum.in
	ifstream in("namenum.in");
	string digits;
	in >> digits;
	int size = digits.size();

	// Setting up the dictionary
	vector<string> dictionary;
	ifstream dic("dict.txt");
	string name;
	while (dic >> name){
		if (size == name.size()){
			dictionary.push_back(name);
		} // if
	} // while

	// setting up the output file
	ofstream out("namenum.out");
	int count = 0, val;

	// Goes through each word in the dictionary letter by letter checking
	// to see if it can be converted into the given digits
	for (unsigned i = 0; i < dictionary.size(); ++i){
		for (int j = 0; j < size; ++j){
			val = dictionary[i][j] - 65;
			if (val > 16) val--;
			if ((val / 3) + 2 != (digits[j] - 48)){
				break;
			}else if (j == size - 1){
				out << dictionary[i] << endl;
				++count;
			} // if
		} // for
	} // for

	// If no words were valid, print "NONE" in text file
	if (count == 0){
		out << "NONE" << endl;
	} // if

	dic.close();
	in.close();
	out.close();

	return 0;
} // main
