#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <regex>
#include <set>
#include <deque>
#include <math.h>

using namespace std;

class Ant {
public:
    vector <vector<bool>> grid;
    int dir;
    pair <int, int> pos;
    int bursts;

    Ant(string filename) {
        ifstream sstream(filename);

        for (string ss; getline(sstream, ss); ) {
            vector <bool> temp;
            temp.reserve(ss.size());
            for (auto it=ss.begin(); it!=ss.end(); ++it) {
                if (*it == '.') {
                    temp.push_back(false);
                } else {
                    temp.push_back(true);
                }
            }
            grid.push_back(temp);
        }
        dir = 2;
        pos.first = grid.size() / 2;
        pos.second = grid[0].size() / 2;
        bursts = 0;
    }

    void move() {
        if (grid[pos.first][pos.second]) {
            if (dir == 0) {
                dir = 3;
            } else {
                dir = (dir-1) % 4;
            }
        } else {
            dir = (dir + 1) % 4;
            bursts++;
        }

        grid[pos.first][pos.second] = !grid[pos.first][pos.second];

        pos.first += int(cos(M_PI/2 * dir));
        pos.second += int(sin(M_PI/2 * dir));
        // cout << int(cos(M_PI/2 * dir)) << ',' << sin(M_PI/2 * dir) << '\n';

        resize_grid();
    }

    void resize_grid() {
        if (pos.first >=0 && pos.first < grid.size() && pos.second >= 0 && pos.second < grid[0].size()) return;
        int npad = 5;
        vector <vector<bool>> new_grid;
        if (pos.first < 0) {
            vector <bool> temp;
            temp.reserve(grid[0].size());
            for (auto i=0; i < grid[0].size(); i++) {
                temp.push_back(false);
            }
            for (int i = 0; i < npad; i++) {
                new_grid.push_back(temp);
            }
            for (auto it=grid.begin(); it!=grid.end(); ++it) {
                temp.clear();
                copy(it->begin(), it->end(), back_inserter(temp));
                new_grid.push_back(temp);
            }

            pos.first += npad;
        } else if (pos.first >= grid.size()) {
            vector <bool> temp;
            temp.reserve(grid[0].size());
            for (auto it=grid.begin(); it!=grid.end(); ++it) {
                temp.clear();
                copy(it->begin(), it->end(), back_inserter(temp));
                new_grid.push_back(temp);
            }
            temp.clear();
            for (auto i=0; i < grid[0].size(); i++) {
                temp.push_back(false);
            }
            for (int i = 0; i < npad; i++) {
                new_grid.push_back(temp);
            }

        }

        if (pos.second < 0) {
            for (auto it=grid.begin(); it!=grid.end(); ++it) {
                vector <bool> temp;
                temp.reserve(grid[0].size()+npad);
                for (auto i=0; i < npad; i++) {
                    temp.push_back(false);
                }
                copy(it->begin(), it->end(), back_inserter(temp));
                new_grid.push_back(temp);
            }

            pos.second += npad;

        } else if (pos.second >= grid[0].size()) {
            for (auto it=grid.begin(); it!=grid.end(); ++it) {
                vector <bool> temp;
                temp.reserve(grid[0].size()+npad);
                copy(it->begin(), it->end(), back_inserter(temp));
                for (auto i=0; i < npad; i++) {
                    temp.push_back(false);
                }
                new_grid.push_back(temp);
            }

        }
        grid = new_grid;
    }

    void print_grid() {
        for (auto i = 0; i < grid.size(); i++){
            for (auto j = 0; j < grid[0].size(); j++) {
                char point = grid[i][j] ? '#' : '.';
                if (i == pos.first && j == pos.second) {
                    cout << '[' << point << ']';
                } else {
                    cout << ' ' << point << ' ';
                }
            }
            cout << '\n';
        }
        cout << '\n';
    }
};

class EvolvedAnt {
public:
    vector <vector<char>> grid;
    int dir;
    pair <int, int> pos;
    int bursts;

    EvolvedAnt(string filename) {
        ifstream sstream(filename);

        for (string ss; getline(sstream, ss); ) {
            vector <char> temp;
            temp.reserve(ss.size());
            copy(ss.begin(), ss.end(), back_inserter(temp));
            grid.push_back(temp);
        }
        dir = 2;
        pos.first = grid.size() / 2;
        pos.second = grid[0].size() / 2;
        bursts = 0;
    }

    void move() {
        if (grid[pos.first][pos.second] == '#') {
            if (dir == 0) {
                dir = 3;
            } else {
                dir = (dir-1) % 4;
            }
            grid[pos.first][pos.second] = 'F';
        } else if (grid[pos.first][pos.second] == '.') {
            dir = (dir + 1) % 4;
            grid[pos.first][pos.second] = 'W';
        } else if (grid[pos.first][pos.second] == 'W') {
            grid[pos.first][pos.second] = '#';
            bursts++;
        } else { //flagged
            dir = (dir + 2) % 4;
            grid[pos.first][pos.second] = '.';
        }

        pos.first += int(cos(M_PI/2 * dir));
        pos.second += int(sin(M_PI/2 * dir));

        resize_grid();
    }

    void resize_grid() {
        if (pos.first >=0 && pos.first < grid.size() && pos.second >= 0 && pos.second < grid[0].size()) return;
        int npad = 5;
        vector <vector<char>> new_grid;
        if (pos.first < 0) {
            vector <char> temp;
            temp.reserve(grid[0].size());
            for (auto i=0; i < grid[0].size(); i++) {
                temp.push_back('.');
            }
            for (int i = 0; i < npad; i++) {
                new_grid.push_back(temp);
            }
            for (auto it=grid.begin(); it!=grid.end(); ++it) {
                temp.clear();
                copy(it->begin(), it->end(), back_inserter(temp));
                new_grid.push_back(temp);
            }

            pos.first += npad;
        } else if (pos.first >= grid.size()) {
            vector <char> temp;
            temp.reserve(grid[0].size());
            for (auto it=grid.begin(); it!=grid.end(); ++it) {
                temp.clear();
                copy(it->begin(), it->end(), back_inserter(temp));
                new_grid.push_back(temp);
            }
            temp.clear();
            for (auto i=0; i < grid[0].size(); i++) {
                temp.push_back('.');
            }
            for (int i = 0; i < npad; i++) {
                new_grid.push_back(temp);
            }

        }

        if (pos.second < 0) {
            for (auto it=grid.begin(); it!=grid.end(); ++it) {
                vector <char> temp;
                temp.reserve(grid[0].size()+npad);
                for (auto i=0; i < npad; i++) {
                    temp.push_back('.');
                }
                copy(it->begin(), it->end(), back_inserter(temp));
                new_grid.push_back(temp);
            }

            pos.second += npad;

        } else if (pos.second >= grid[0].size()) {
            for (auto it=grid.begin(); it!=grid.end(); ++it) {
                vector <char> temp;
                temp.reserve(grid[0].size()+npad);
                copy(it->begin(), it->end(), back_inserter(temp));
                for (auto i=0; i < npad; i++) {
                    temp.push_back('.');
                }
                new_grid.push_back(temp);
            }

        }
        grid = new_grid;
    }

    void print_grid() {
        for (auto i = 0; i < grid.size(); i++){
            for (auto j = 0; j < grid[0].size(); j++) {
                if (i == pos.first && j == pos.second) {
                    cout << '[' << grid[i][j] << ']';
                } else {
                    cout << ' ' << grid[i][j] << ' ';
                }
            }
            cout << '\n';
        }
        cout << '\n';
    }
};

int main() {

    string filename = "day22.txt";

    Ant a(filename);
    a.print_grid();
    int nmoves = 10000;
    for (int i = 0; i < nmoves; i++) {
        a.move();
        // a.print_grid();
    }
    // a.print_grid();
    cout << "After " << nmoves << " moves there were " << a.bursts << " infection-causing bursts.\n";

    EvolvedAnt e(filename);
    nmoves = 10000000;
    for (int i = 0; i < nmoves; i++) {
        e.move();
        // e.print_grid();
    }
    // e.print_grid();
    cout << "After " << nmoves << " moves there were " << e.bursts << " infection-causing bursts.\n";

}
