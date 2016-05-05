/*
ID: ericm101
LANG: C++
TASK: milk
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct farmer_info{
	int cost;
	int amount;
};

int main(){
	ifstream in("milk.in");
	ofstream out("milk.out");
	int milk_needed, num_farmers;
	in >> milk_needed >> num_farmers;
	vector<farmer_info> data(num_farmers);
	for (int i = 0; i < num_farmers; ++i){
		in >> data[i].cost >> data[i].amount;
	}
	in.close();
	out.close();
	return 0;	
}