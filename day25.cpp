#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <regex>
#include <map>
#include <math.h>

using namespace std;

char A(vector<int>::iterator* pos) {

	if (**pos == 0) {
		**pos = 1;
		++(*pos);
		return 'B';
	} else {
		**pos = 0;
		--(*pos);
		return 'B';
	}
}

char B(vector<int>::iterator* pos) {
	if (**pos == 0) {
		**pos = 0;
		++(*pos);
		return 'C';
	} else {
		**pos = 1;
		--(*pos);
		return 'B';
	}
}

char C(vector<int>::iterator* pos) {
	if (**pos == 0) {
		**pos = 1;
		++(*pos);
		return 'D';
	} else {
		**pos = 0;
		--(*pos);
		return 'A';
	}
}

char D(vector<int>::iterator* pos) {
	if (**pos == 0) {
		**pos = 1;
		--(*pos);
		return 'E';
	} else {
		**pos = 1;
		--(*pos);
		return 'F';
	}
}

char E(vector<int>::iterator* pos) {
	if (**pos == 0) {
		**pos = 1;
		--(*pos);
		return 'A';
	} else {
		**pos = 0;
		--(*pos);
		return 'D';
	}
}

char F(vector<int>::iterator* pos) {
	if (**pos == 0) {
		**pos = 1;
		++(*pos);
		return 'A';
	} else {
		**pos = 1;
		--(*pos);
		return 'E';
	}
}



int main() {

	long checksum = 12629077;
	vector<int> tape(10000, 0);
	auto pos = tape.begin()+5000;

	char state = 'A';

	for (long i=0; i < checksum; i++) {
		if (pos == tape.begin())
			cout << "warning: hit the start" << '\n';
		if (pos == tape.end())
			cout << "warning: hit the end" << '\n';
		if (state == 'A') {
			state = A(&pos);
		} else if (state == 'B') {
			state = B(&pos);
		} else if (state == 'C') {
			state = C(&pos);
		} else if (state == 'D') {
			state = D(&pos);
		} else if (state == 'E') {
			state = E(&pos);
		} else if (state == 'F') {
			state = F(&pos);
		}
	}

	int sum = 0;

	for (auto it=tape.begin(); it!=tape.end(); ++it) {
		// cout << *it << ' ';
		sum += *it;
	}

	cout << "\nchecksum = " << sum << '\n';


}
