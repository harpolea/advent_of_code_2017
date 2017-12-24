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

void run_instruction(string instruction, int * pos, map <string, long> *rs, long * counter) {
    smatch sm;
    regex re("([a-z]+)\\s(-?\\w+)\\s?(-?\\w*)");

    regex_match(instruction, sm, re);
    string ins = sm[1].str();

    if (ins == "set") {
        string X = sm[2].str();
        try {
            int Y = stoi(sm[3].str());
            (*rs)[X] = Y;
        } catch(exception& e) {
            string Y = sm[3].str();
            (*rs)[X] = (*rs)[Y];
        }
    } else if (ins == "add") {
        string X = sm[2].str();
        try {
            int Y = stoi(sm[3].str());
            (*rs)[X] += Y;
        } catch(exception& e) {
            string Y = sm[3].str();
            (*rs)[X] += (*rs)[Y];
        }
    }else if (ins == "sub") {
        string X = sm[2].str();
        try {
            int Y = stoi(sm[3].str());
            (*rs)[X] -= Y;
        } catch(exception& e) {
            string Y = sm[3].str();
            (*rs)[X] -= (*rs)[Y];
        }
    } else if (ins == "mul") {
        (*counter)++;
        string X = sm[2].str();
        try {
            int Y = stoi(sm[3].str());
            (*rs)[X] *= Y;
        } catch(exception& e) {
            string Y = sm[3].str();
            (*rs)[X] *= (*rs)[Y];
        }
    } else if (ins == "jnz") {
        int iX, iY;
        try {
            iX = stoi(sm[2].str());
        } catch(exception& e) {
            string X = sm[2].str();
            rs->insert(pair<string, int>(X, 0));
            iX = (*rs)[X];
        }
        try {
            iY = stoi(sm[3].str());
        } catch(exception& e) {
            string Y = sm[3].str();
            rs->insert(pair<string, int>(Y, 0));
            iY = (*rs)[Y];
        }
        if (iX != 0) {
            (*pos) += iY-1;
        }
    }
    if (*pos == 12) counter+= (*rs)["b"];
}

bool not_prime(int n) {
    for (int i = 2; i <= sqrt(n)+1; i++) {
        if (n % i == 0) {
            return true;
        }
    }
    return false;
}

int part2(int b0, int c0) {
    int h = 0;
    for (int b = b0; b < c0+1; b+=17) {
        if (not_prime(b)) h++;
    }
    return h;
}

int main() {

    string filename = "day23.txt";
    ifstream sstream(filename);
    vector <string> instructions;
    regex re("([a-z]+)\\s(-?\\w+)\\s?(-?\\w*)");

    for (string line; getline(sstream, line); )
    instructions.push_back(line);

    int pos = 0;
    map <string, long> registers;

    for (int i = 0; i < 8; i++) {
        registers.insert(pair<string, int>(string(1,'a'+char(i)), 0));
    }

    long counter = 0;

    while (pos >= 0 && pos < instructions.size()){
        run_instruction(instructions[pos], &pos, &registers, &counter);
        pos++;
    }

    cout << "Mul operation is invoked " << counter << " times.\n";

    int b0 = 93 * 100 + 100000;
    int c0 = b0 + 17000;

    cout << "h in part 2 = " << part2(b0, c0) << '\n';

}
