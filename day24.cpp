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

void process_ports(string line, vector<pair<int, int> >* ports) {
	smatch sm;
	regex re("([0-9]+)\\/([0-9]+)");

	regex_match(line, sm, re);

	ports->push_back(pair<int,int>(stoi(sm[1].str()), stoi(sm[2].str())));
}

int make_bridges(vector<pair<int, int> >* remaining_ports,
                 vector<int>* bridge, int strongest) {

	if (remaining_ports->empty()) {
		int sum_of_elems = 0;
		for (auto it = bridge->begin(); it!=bridge->end(); ++it) {
			sum_of_elems += 2 * *it;
		};
        sum_of_elems -= bridge->back();
		return max(sum_of_elems, strongest);
	} else {
		int last_port = bridge->back();

		for (auto it=remaining_ports->begin(); it!=remaining_ports->end(); ++it) {
			vector<pair<int, int> > copy_remaining_ports;
			vector<int> copy_bridge(*bridge);

			if (it->first == last_port) {
				copy_bridge.push_back(it->second);

				for (auto jit=remaining_ports->begin(); jit!=remaining_ports->end(); ++jit) {
					if (it != jit) copy_remaining_ports.push_back(*jit);
				}

				strongest = max(strongest, make_bridges(&copy_remaining_ports, &copy_bridge, strongest));
			} else if(it->second == last_port) {
				copy_bridge.push_back(it->first);

				for (auto jit=remaining_ports->begin(); jit!=remaining_ports->end(); ++jit) {
					if (it != jit) copy_remaining_ports.push_back(*jit);
				}

				strongest = max(strongest, make_bridges(&copy_remaining_ports, &copy_bridge, strongest));
			}
		}
	}

	vector<pair<int, int> > empty;
	return max(strongest, make_bridges(&empty, bridge, strongest));

}

void make_long_bridges(vector<pair<int, int> >* remaining_ports,
                 vector<int>* bridge, vector<pair<int, int> >* length_and_strength) {

	if (remaining_ports->empty()) {
		int sum_of_elems = 0;
		for (auto it = bridge->begin(); it!=bridge->end(); ++it) {
			sum_of_elems += 2 * *it;
		};
        sum_of_elems -= bridge->back();
		length_and_strength->push_back(pair<int,int>(bridge->size()-1, sum_of_elems));
        return;
	} else {
		int last_port = bridge->back();

		for (auto it=remaining_ports->begin(); it!=remaining_ports->end(); ++it) {
			vector<pair<int, int> > copy_remaining_ports;
			vector<int> copy_bridge(*bridge);

			if (it->first == last_port) {
				copy_bridge.push_back(it->second);

				for (auto jit=remaining_ports->begin(); jit!=remaining_ports->end(); ++jit) {
					if (it != jit) copy_remaining_ports.push_back(*jit);
				}

				make_long_bridges(&copy_remaining_ports, &copy_bridge, length_and_strength);
			} else if(it->second == last_port) {
				copy_bridge.push_back(it->first);

				for (auto jit=remaining_ports->begin(); jit!=remaining_ports->end(); ++jit) {
					if (it != jit) copy_remaining_ports.push_back(*jit);
				}

				make_long_bridges(&copy_remaining_ports, &copy_bridge, length_and_strength);;
			}
		}
	}

	vector<pair<int, int> > empty;
    make_long_bridges(&empty, bridge, length_and_strength);
	return;

}


int main() {

	string filename = "day24.txt";
	ifstream sstream(filename);
	vector <pair<int, int> > ports;

	for (string line; getline(sstream, line); )
		process_ports(line, &ports);

	vector<int> bridge{0};

	// int strongest = make_bridges(&ports, &bridge, 0);

	// cout << "The strongest is " << strongest << '\n';

    vector<int> long_bridge{0};

    vector<pair<int, int> > length_and_strength;

    make_long_bridges(&ports, &bridge, &length_and_strength);

    int longest = 0;
    int strongest = 0;

    for (auto it=length_and_strength.begin(); it!=length_and_strength.end(); ++it) {
        if (it->first > longest) {
            longest = it->first;
            strongest = it->second;
        } else if (it->first == longest) {
            strongest = max(strongest, it->second);
        }
    }

    cout << "The longest has length " << longest << " and has strength " << strongest << '\n';


}
