#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>

using namespace std;

auto read_input(string in_string) {
    vector <int> banks;
    istringstream in(in_string);
    copy(istream_iterator<int>( in ), istream_iterator<int>(),
        back_inserter(banks) );
    return banks;
}

auto banks(string instring, bool part2) {
    vector<int> banks = read_input(instring); // vector holding banks
    map <vector <int>, int> previous_states; // dictionary to hold previous states and cycle number first seen

    while (previous_states.find(banks) == previous_states.end()) { // iterate while current state not in dict
        previous_states.insert(pair <vector <int>, int> (banks, previous_states.size())); // record current state
        auto max_el = max_element(banks.begin(), banks.end()); // find max element in banks
        int max_el_index = distance(banks.begin(), max_el); // its position
        int max_val = *max_el; // its value
        *max_el = 0; // set max bank to 0
        
        for (int i = max_el_index+1; i < max_el_index+1+max_val; i++) {
            banks[i%banks.size()]++;
        }
    }
    return part2 ? previous_states.size() - previous_states.find(banks)->second : previous_states.size(); // if part 2 return current counter - cycle number saw banks originally, otherwise just number of cycles
}

int main() {
    cout << "Test case passes part 1? " << (banks("0 2 7 0", false)==5)  << '\n';

    string puzzle_input = "2	8	8	5	4	2	3	1	5	5	1	2	15	13	5	14";

    cout << "Test output: " << banks(puzzle_input, false) << '\n';

    cout << "Test case passes part 2? " << (banks("0 2 7 0", true)==4) << '\n';

    cout << "Test output: " << banks(puzzle_input, true) << '\n';
}
