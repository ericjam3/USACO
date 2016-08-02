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

struct Coords {
	int x;
	int y;
};

bool comparator(Coords a, Coords b) {
	if (a.y < b.y || (a.y == b.y && a.x < b.x)) {
		return true;
	}
	return false;
}

class Worm {
public:
	void run();

private:
	int num_holes;
	int count;
	int current_ind;
	vector<Coords> wormholes;
	vector<bool> used;
	vector<int> pairings;

	void set_up();

	void pair_up(int num);

	void traverse_paths();
};

int main() {
	Worm obj;
	obj.run();

	system("Pause");
	return 0;
}

void Worm::set_up() {
	count = 0;
	ifstream in("wormhole.in");
	in >> num_holes;
	wormholes.resize(num_holes);
	used.resize(num_holes);
	pairings.resize(num_holes);
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
	if (num < (num_holes / 2) - 1) {
		int old_ind = current_ind, temp_ind;
		for (int i = old_ind + 1; i < num_holes; ++i) {
			if (!used[i]) {
				pairings[i] = old_ind;
				pairings[old_ind] = i;
				used[i] = true;
				for (int j = old_ind + 1; j < num_holes; ++j) {
					if (!used[j]) {
						current_ind = j;
						temp_ind = j;
						used[current_ind] = true;
						break;
					}
				}
				pair_up(num + 1);
				used[i] = false;
				used[temp_ind] = false;
			}
		}
	}
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
		vector<bool> visited(num_holes, false);
		visited[i] = true;
		while (1) {
			current = pairings[current];
			if (visited[current]) {
				count++;
				return;
			}
			visited[current] = true;
			if ((current + 1 >= num_holes) || wormholes[current + 1].y != wormholes[current].y) {
				break;
			}else{
				current = current + 1;
				if (visited[current]) {
					count++;
					return;
				}
				visited[current] = true;
			}
		}
	}
}