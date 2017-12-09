#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <map>

using namespace std;

auto score(string instring) {
    int score = 0;
    int n_open_groups = 0;
    bool garbage = false;
    bool negate = false;
    int garbage_count = 0;
    for (auto it=instring.begin(); it!=instring.end(); ++it) {
        if (!garbage && *it == '{') {
            n_open_groups++;
        } else if (!garbage && n_open_groups > 0 && *it == '}') {
            // assume all groups eventually close
            score += n_open_groups;
            n_open_groups--;
        } else if (!garbage && !negate && *it == '<') {
            garbage = true;
        } else if (garbage && !negate && *it == '>') {
            garbage = false;
        } else if (garbage && !negate && *it != '!') {
            garbage_count++;
        }

        if (!negate && garbage && *it == '!') {
            negate = true;
        } else if (negate) {
            negate = false;
        }
    }

    return pair<int, int> (score, garbage_count);
}

int main() {
    vector<string> tests = {"{}", "{{{}}}", "{{},{}}", "{{{},{},{{}}}}",
        "{<a>,<a>,<a>,<a>}", "{{<ab>},{<ab>},{<ab>},{<ab>}}",
        "{{<!!>},{<!!>},{<!!>},{<!!>}}", "{{<a!>},{<a!>},{<a!>},{<ab>}}"};
    vector<int> test_scores = {1, 6, 5, 16, 1, 9, 9, 3};

    for (unsigned i = 0; i < tests.size(); ++i) {
        auto s = score(tests[i]);
        cout << "Score of " << tests[i] << " = " << s.first <<
            ". Should be " << test_scores[i] << '\n';
    }

    ifstream in("day9.txt");
    ostringstream contents;
    if (in) {
        contents << in.rdbuf();
        in.close();
    }

    vector<string> tests2 = {"<>", "<random characters>", "<<<<>", "<{!>}>",
        "<!!>", "<!!!>>", "<{o\"i!a,<{i<a>"};
    vector<int> test_scores2 = {0, 17, 3, 2, 0, 0, 10};
    for (unsigned i = 0; i < tests2.size(); ++i) {
        auto s = score(tests2[i]);
        cout << "N garbage characters in " << tests2[i] << " = " << s.second << ". Should be " << test_scores2[i] << '\n';
    }

    auto s = score(contents.str());
    cout << "Puzzle score = " << s.first << '\n';
    cout << "Puzzle garbage characters = " << s.second << '\n';
}
