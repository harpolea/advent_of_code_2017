#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>    // std::reverse
#include <iterator>

using namespace std;

auto sparse_hash(vector<int> lengths, int list_size, int nrounds) {
    int pos = 0;
    int skip = 0;
    vector <int> l;
    l.reserve(list_size);
    for (int i = 0; i < list_size; i++) {
        l.push_back(i);
    }

    for (int i = 0; i < nrounds; i++) {
        for (auto it=lengths.begin(); it!=lengths.end(); ++it) {

            if (*it > list_size) {
                continue;
            }
            // rotate so pos is at start
            // this helps deal with list circularity
            rotate(l.begin(), l.begin()+pos, l.end());
            reverse(l.begin(), l.begin()+*it);
            // rotate back
            rotate(l.begin(), l.begin()+(list_size-pos), l.end());
            pos = (pos + *it + skip) % list_size;
            skip++;
        }
    }
    return l;
}

auto dense_hash(vector <int> l) {
    if (l.size() != 256)
        cerr << "List size is not 256!!\n";

    vector <int> dense_hash;
    dense_hash.reserve(16);
    // do the bitwise xor of segments of length 16
    for (int j = 0; j < 16; j++) {
        int bitxor = l[j*16];
        for (int i = 1; i < 16; i++) {
            bitxor ^= l[j*16 + i];
        }
        dense_hash.push_back(bitxor);
    }

    string hexstring = "";
    for (auto it = dense_hash.begin(); it!=dense_hash.end(); ++it) {
        stringstream sstream;
        sstream << hex << *it;
        if (sstream.str().size() < 2) {
            hexstring += '0' + sstream.str(); // pad with leading 0
        } else {
            hexstring += sstream.str();
        }
    }
    return hexstring;
}

auto ascii(string s) {
    vector <int> codes;
    codes.reserve(s.size()+5);
    for (auto it = s.begin(); it!=s.end(); ++it) {
        codes.push_back( (int) *it);
    }

    vector <int> extras = {17, 31, 73, 47, 23};
    copy(extras.begin(), extras.end(), back_inserter(codes));
    return codes;
}

auto knot_hash(string s) {
    vector <int> codes = ascii(s);
    return dense_hash(sparse_hash(codes, 256, 64));
}

int main() {
    vector <int> test_lengths = {3, 4, 1, 5};

    auto l = sparse_hash(test_lengths, 5, 1);
    if (l[0] * l[1] != 12) {
        "Test case for part 1 did not work :(\n";
    }

    vector <int> puzzle_lengths = {197,97,204,108,1,29,5,71,0,50,2,255,248,78,254,63};

    l = sparse_hash(puzzle_lengths, 256, 1);
    cout << "Product of first 2 elements in puzzle = " << l[0] * l[1] << '\n';

    string puzzle_str = "197,97,204,108,1,29,5,71,0,50,2,255,248,78,254,63";

    if (!(knot_hash("") == "a2582a3a0e66e6e86e3812dcb672a272" &&
    knot_hash("AoC 2017") == "33efeb34ea91902bb2f59c9920caa6cd" &&
    knot_hash("1,2,3") == "3efbe78a8d82f29979031a4aa0b16a9d" &&
    knot_hash("1,2,4") == "63960835bcdc130f0b66d7ff4f6a5a8e"))
        cout << "Test cases don't work :(\n";

    auto h = knot_hash(puzzle_str);
    cout << "puzzle hash = " << h << '\n';

}
