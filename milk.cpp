/*
ID: ericm101
LANG: C++
TASK: milk
*/

/*
The purpose of this program is to find the way for a company to
purchase a specified amount of milk at the cheapest cost. The company
has a list of farmers that it will buy from and for each of those farmers,
we have information on how much milk they have and how much it costs per
unit. The input is formatted as follows: The first line contains two integers,
N and M. N is the amount of milk needed and M is the number of farmers to buy
it from. The next M lines contain two integers each, the first is the cost per
unit and the second is the amount of milk available. With this information, 
the program will determine the cheapest way to get the needed amount of milk.
Note that you can buy a portion of a farmer's available milk, there is no need
to buy them out! Outputted is the minimum cost for the milk
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// organizes information for each farmer
struct farmer_info{
	int cost;
	int amount;
};

// Used for sorting buying options in terms of cost per unit
bool comp(const farmer_info i, const farmer_info j){
	return i.cost < j.cost;
}


int main(){
	ifstream in("milk.in");
	ofstream out("milk.out");
	int milk_needed, num_farmers, total_milk = 0, total_cost = 0;
	unsigned ind = 0;
	in >> milk_needed >> num_farmers;
	vector<farmer_info> data(num_farmers);

	// Reading information on different buying options and saving
	// it in a vector of structs
	for (int i = 0; i < num_farmers; ++i){
		in >> data[i].cost >> data[i].amount;
	}
	
	// sorting the vector of buying options in terms of unit cost
	sort(data.begin(), data.end(), comp);
	
	// loop through the vector of buying options starting with the cheapest
	// milk per unit, adding to the total minimum cost. Stop once we no longer
	// have to buy the full amount of milk from the next farmer and buy the
	// fraction that we need, adding the cost of the milk we have bought
	while (total_milk < milk_needed){
		if (data[ind].amount + total_milk <= milk_needed){
			total_cost += data[ind].amount * data[ind].cost;
			total_milk += data[ind].amount;
		}else{
			total_cost += (milk_needed - total_milk) * data[ind].cost;
			total_milk = milk_needed;
		}
		ind++;
	}
	out << total_cost << endl;
	in.close();
	out.close();
	return 0;	
}