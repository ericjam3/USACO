/*
ID: ericm101
LANG: C++
TASK: wormhole
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

/*
This program is written to solve the wormholes USACO online training problem.
Farmer John has between 2 and 12 (must be even amount) wormholes in his cow
pasture, each of which is paired with one other wormhole. Given the positions
of each of the wormholes, he wants to know how many different pairings could
result in one of his cows being trapped in an infinite cycle if the cow only
travels in the +x direction. The first line it takes in from an input file is
the number of wormholes. Each line after that contains an x and y coordinate
of a wormhole. This program generates all the possible pairings of wormholes
and for each pairing traverses the pasture full of wormholes starting at each
one until it finds an infinite cycle or has exhausted all of the starting points
without doing so. It adds up the total amount of pairings that would result in
the cow getting stuck in an infinite cycle and writes it to the output file. 
*/

// Used to store coordinates of points on the grid
struct Coords {
	long long x;
	long long y;
};

// This function is used to sort the ordered pairs such that
// points in the lower left are first and points in the upper
// right are last
bool comparator(Coords a, Coords b) {
	if (a.y < b.y || (a.y == b.y && a.x < b.x)) {
		return true;
	}
	return false;
}

// Runs the program
class Worm {
public:
	// Driver function
	void run();

private:
	int num_holes;
	int count;
	int current_ind;
	vector<Coords> wormholes;
	vector<bool> used;
	vector<int> pairings;

	// Sets up variables and vectors
	void set_up();

	// Creates all the possible pairings of wormholes
	void pair_up(int num);

	// Checks for loops based on all possible starting points
	// Adds up total amount of pairings that result in a loop
	void traverse_paths();
};

int main() {
	Worm obj;
	obj.run();

	return 0;
}

void Worm::set_up() {
	count = 0;
	ifstream in("wormhole.in");
	in >> num_holes;
	wormholes.resize(num_holes);
	used.resize(num_holes);
	pairings.resize(num_holes);

	// Reading in and setting up wormhole coordinates
	for (int i = 0; i < num_holes; ++i) {
		in >> wormholes[i].x >> wormholes[i].y;
		used[i] = false;
	}
	in.close();
	sort(wormholes.begin(), wormholes.end(), comparator);
}

void Worm::run() {
	set_up();
	used[0] = true;
	current_ind = 0;
	pair_up(0);
	ofstream out("wormhole.out");
	out << count << endl;
	out.close();
}

void Worm::pair_up(int num) {
	// Evaluates to true unless we are onto the final pairing
	if (num < (num_holes / 2) - 1) {
		int old_ind = current_ind, temp_ind;
		for (int i = old_ind + 1; i < num_holes; ++i) {
			if (!used[i]) {
				pairings[i] = old_ind;
				pairings[old_ind] = i;
				used[i] = true;
				// Finding the next unpaired wormhole to use for the next iteration
				for (int j = old_ind + 1; j < num_holes; ++j) {
					if (!used[j]) {
						current_ind = j;
						temp_ind = j;
						used[current_ind] = true;
						break;
					}
				}

				// Pairs up the next two wormholes
				pair_up(num + 1);
				
				// Backtracking
				used[i] = false;
				used[temp_ind] = false;
			}
		}
	}
	// Used for putting together the final pairing and running the traverse_paths
	// function to check for loops
	else {
		for (int i = current_ind + 1; i < num_holes; ++i) {
			if (!used[i]) {
				pairings[i] = current_ind;
				pairings[current_ind] = i;
				used[i] = true;
				traverse_paths();
				used[i] = false;
				break;
			}
		}
	}
}

void Worm::traverse_paths() {
	for (int i = 0; i < num_holes; ++i) {
		int current = i;
		int counter = 0;
		while (1) {
			current = pairings[current];
			// If we have traversed enough points to guarantee a loop,
			// add on to the overall count
			if (counter > num_holes) {
				count++;
				return;
			}

			// Break out of the while loop if the cow would run into no more wormholes
			// on this route
			if ((current + 1 >= num_holes) || wormholes[current + 1].y != wormholes[current].y) {
				break;
			}
			else {
				current = current + 1;
				// If we have traversed enough points to guarantee a loop,
				// add on to the overall count
				if (counter > num_holes) {
					count++;
					return;
				}
			}
			counter++;
		}
	}
}