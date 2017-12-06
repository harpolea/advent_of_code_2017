#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

using namespace std;

auto read_input(string filename) {
    vector <int> jumps;
    ifstream file(filename);
    copy(istream_iterator<int>(file), istream_iterator<int>(), back_inserter(jumps));
    return jumps;
}

auto jump(vector<int> jumps, bool part2) {
    int count = 0;
    int position = 0;
    while (position < jumps.size()) {
        int j = jumps[position];

        // if part2 this variable will be set
        if (part2 && j >= 3) {
            jumps[position]--;
        } else {
            jumps[position]++;
        }
        position += j;
        count++;
    }

    return count;
}

int main() {
    string filename = "day5.txt";

    vector <int> jumps = read_input("day5.txt");

    cout << "number of jumps = " << jump(jumps, true) << '\n';
}
