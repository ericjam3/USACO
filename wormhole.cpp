/*
ID: ericm101
LANG: C++
TASK: wormhole
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct coords {
	int x;
	int y;
};

class Worm {
public:
	void run();

private:
	int num_holes;
	int count;
	vector<coords> wormholes;

	void set_up();
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
	for (int i = 0; i < num_holes; ++i) {
		in >> wormholes[i].x >> wormholes[i].y;
	}
	in.close();
}

void Worm::run() {
	set_up();
	for (int i = 0; i < num_holes; ++i) {
		for (int j = 0; j < num_holes; ++j) {
			if (wormholes[i].y == wormholes[j].y && wormholes[i].x < wormholes[j].x) {
				++count;
				break;
			}
		}
	}
	ofstream out("wormhole.out");
	out << count << "\n";
	out.close();
}