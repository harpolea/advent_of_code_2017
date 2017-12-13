#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <map>
#include <regex>
#include <set>

using namespace std;
auto traverse(int node, set <int> zerogroup, map<int, vector<int>> nodes);

auto traverse(int node, set <int> zerogroup, map<int, set<int>> nodes) {
    // node is in set
    if (zerogroup.find(node) != zerogroup.end()) {
        return zerogroup;
    } else {
        //cout << node << ' ';
        zerogroup.insert(node);
        for (auto it=nodes[node].begin(); it!=nodes[node].end(); ++it) {
            zerogroup = traverse(*it, zerogroup, nodes);
        }
        //cout << "size = " << zerogroup.size() << '\n';
    }
    return zerogroup;
}

auto get_group(map <int, set<int>> nodes, int zero) {
    set <int> group = {zero};

    for (auto it = nodes[zero].begin(); it!=nodes[zero].end(); ++it) {
        group = traverse(*it, group, nodes);
    }

    return group;
}

auto groupsize(string filename, bool part1) {
    ifstream sstream(filename);
    string ss;
    map <int, set<int>> nodes;
    regex re("(\\d+)");
    set <int> blank = {0};

    while (getline(sstream, ss)) {
        //cout << ss << '\n';
        vector <string> svec;
        copy(sregex_token_iterator(ss.begin(), ss.end(), re, 1), sregex_token_iterator(),
          back_inserter(svec));
        if (svec.size() > 1) {
            int key = stoi(svec[0]);
            set <int> keyset = {key};
            nodes.insert(pair<int, set<int>>(key, blank));
            for (auto it=svec.begin()+1; it!=svec.end(); ++it) {
                int i = stoi(*it);
                nodes[key].insert(i);
                if (!nodes.insert(pair<int, set<int>>(i, keyset)).second) nodes[i].insert(key);
            }
        }
    }

    if (part1) {
        set <int> zerogroup = get_group(nodes, 0);
        cout << "zerogroup size = " << zerogroup.size() << '\n';
    } else {
        int n_groups = 0;
        cout << nodes.begin()->first << '\n';
        while (!nodes.empty()) {
            cout << nodes.begin()->first << '\n';
            set <int> group = get_group(nodes, nodes.begin()->first);
            // remove all elements of group from map
            for (auto it=group.begin(); it!=group.end(); ++it) {
                auto iter = nodes.find(*it);
                if (iter != nodes.end()) nodes.erase(iter);
            }
            n_groups++;
            cout << "Nodes size = " << nodes.size() << " group size = " << group.size() << '\n';
        cout << nodes.begin()->first << '\n';
        }
        cout << "There are " << n_groups << " groups.\n";
    }

}

int main() {
    groupsize("day12.txt", false);
}
