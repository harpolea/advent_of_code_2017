#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <cmath>

using namespace std;

auto steps(int input) {
    if (input == 1) return 0;

    int p = int(sqrt(input));
    if (p % 2 == 0) p -= 1;
    int q = (int)(input - p*p) / (p+1);
    int r = (input - p*p) % (p+1);

    return (p+1) / 2 + abs((p+1)/2 - r);
}

void square(vector<int>* snail) {
    if (snail->size() == 0) {
        snail->push_back(1);
        return;
    }

    int size = snail->size() + 1;
    int p,q,r;
    p = int(sqrt(size));
    if (p % 2 == 0) p -= 1;
    if (size == p*p) {
        p -= 2;
        q = 3;
        r = p + 1;
    } else {
        q = (int)(size - p*p) / (p+1);
        r = (size - p*p) % (p+1);
    }

    int sum = snail->back();

    if (p == 1) {
        if (r == 1 && q == 0) {
        } else if (r == 1 && q > 0) {
            sum += (*snail)[size-3] + 1;
        } else {
            sum += 1;
        }

        if (q == 3 && r > 0) {
            sum += 1;
        }
    } else {
        if (r == 1 && q == 0) {
            sum += (*snail)[(p-2)*(p-2)];
        } else if (r == 0) {
            sum +=  (*snail)[size - (4*p-3) - q*2];
        } else if (r == 1) {
            sum += (*snail)[size-3] + (*snail)[size-1 - (4*p-3) - q*2] + (*snail)[size - (4*p-3) - q*2];
        } else if (r == 2 && q == 0) {
            sum += (*snail)[size-3] + (*snail)[(p-2)*(p-2)] + (*snail)[(p-2)*(p-2) + 1];
        } else if (r == p) {
            sum += (*snail)[size - (4*p-3) - q*2 - 1] + (*snail)[size - (4*p-3) - q*2 - 2];
        } else if (r == p+1) {
            sum += (*snail)[p*p - 1] + (*snail)[p*p];
        } else {
            sum += (*snail)[size - (4*p-3) - q*2 - 2] + (*snail)[size - (4*p-3) - q*2 - 1] + (*snail)[size - (4*p-3) - q*2];
        }

        if (r == p && q == 3) {
            sum += (*snail)[p*p];
        }

    }
    snail->push_back(sum);
}

int main() {

    // check test distances
    if (steps(1) != 0 || steps(12) != 3 || steps(23) != 2 || steps(1024) != 31) {
        cout << "steps(1) = " << steps(1) << '\n';
        cout << "steps(12) = " << steps(12) << '\n';
        cout << "steps(23) = " << steps(23) << '\n';
        cout << "steps(1024) = " << steps(1024) << '\n';

        cerr << "Test cases failed\n";
    }

    int puzzle_input = 325489;

    cout << "Number of steps = " << steps(puzzle_input) << '\n';

    vector <int> snake;
    square(&snake);

    while(snake.back() < puzzle_input) {
        square(&snake);
    }
    cout << "last snake " << snake.back() << '\n';

}
