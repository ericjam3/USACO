/*
ID: ericm101
LANG: C++
TASK: numtri
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class Tri {
public:

	void run();

private:
	vector<vector<int> > triangle;
	vector<int> highest_nums;
	int rows;
	int max;

	void set_up();

	void BB(int sum, int row, int col);

	void find_bound();

	bool promising(int row, int sum);
};

int main() {
	Tri obj;
	obj.run();
	return 0;
}

void Tri::run() {
	set_up();
	find_bound();
	BB(0, 0, rows - 1);
	ofstream out("numtri.out");
	out << max << endl;
	out.close();
}

void Tri::set_up() {
	ifstream in("numtri.in");
	in >> rows;
	vector<int> highest_temp(rows, 0);
	highest_nums = highest_temp;
	vector<int> row(rows * 2 - 1);
	vector<vector<int> > table(rows, row);
	triangle = table;
	int num, mid = rows - 1, offset_beg = 0;
	for (int i = 0; i < rows; ++i) {
		int offset = offset_beg;
		for (int j = 0; j <= i; ++j) {
			in >> num;
			if (num > highest_nums[i]) highest_nums[i] = num;
			triangle[i][mid + offset] = num;
			offset += 2;
		}
		offset_beg -= 1;
	}
	in.close();
}

void Tri::BB(int sum, int row, int col) {
	sum += triangle[row][col];
	if (row == rows - 1) {
		if (sum > max) {
			max = sum;
		}
		return;
	}
	if (!promising(row, sum)) return;
	BB(sum, row + 1, col + 1);
	BB(sum, row + 1, col - 1);
}

void Tri::find_bound() {
	int col = rows - 1;
	int sum = triangle[0][col];
	for (int i = 1; i < rows; ++i) {
		if (triangle[i][col - 1] > triangle[i][col + 1]) {
			sum += triangle[i][col - 1];
			col--;
		}
		else {
			sum += triangle[i][col + 1];
			col++;
		}
	}
	max = sum;
}

bool Tri::promising(int row, int sum) {
	for (int i = row + 1; i < rows; ++i) {
		sum += highest_nums[i];
	}
	if (sum < max) return false;
	return true;
}