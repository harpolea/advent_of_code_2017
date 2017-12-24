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

class Particle {
    public:
        vector <long> pos, vel, acc;

        Particle(vector <int> values) {
            copy(values.begin(), values.begin()+3, back_inserter(pos));
            copy(values.begin()+3, values.begin()+6, back_inserter(vel));
            copy(values.begin()+6, values.end(), back_inserter(acc));
        }

        void update_vel () {
            for (auto i = 0; i < 3; i++) {
                vel[i] += acc[i];
            }
        }

        void update_pos() {
            for (auto i = 0; i < 3; i++) {
                pos[i] += vel[i];
            }
        }

        long dist() {
            long d = 0;
            for (auto i = 0; i < 3; i++) {
                d += abs(pos[i]);
            }
            return d;
        }

        bool collide(Particle p, int * dead_time) {
            int tp = -1;
            int tm = -1;
            bool anyt = false;
            for (auto i = 0; i < 3; i++) {
                float a = 0.5 * (acc[i] - p.acc[i]);
                float b = vel[i]-p.vel[i];
                float c = pos[i] - p.pos[i];
                bool anyt = false;
                // cout << pos[i] << ' ' << p.pos[i] << '\n';
                if (b*b >= 4 * a * c) {
                    float t1, t2;
                    if (a == 0) {
                        if (b == 0) {
                            anyt = true;
                            t1 = -1;
                            t2 = -1;
                        } else {
                            t1 = -c/b;
                            t2 = -c/b;
                        }
                    } else {
                        t1 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
                        t2 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
                    }
                    // cout << t1 << ' ' << t2 << ' ' << a << ' ' << b << ' ' << c << '\n';
                    if (a == 0 && b == 0) {

                    } else {
                            if ((abs(t1 - int(t1)) > 0.000001 ||  t1 < 0 ) && (abs(t2 - int(t2)) > 0.000001 || t2 < 0)) {
                            // cout << t1 << ' ' << t2 << '\n';
                            return false;
                        } else if (i == 0) {
                            if (abs(t1 - int(t1)) < 0.000001 ||  t1 >= 0 ) tp = t1;
                            if (abs(t2 - int(t2)) < 0.000001 || t2 >= 0) tm = t2;
                        } else {
                            // cout << abs(t1 - int(t1))  << ' ' << abs(t2 - int(t2)) << ' ' << tp << ' ' << tm << '\n';
                        }

                        if (!anyt && (t1 == tp || t1 == tm || t2 == tp || t2 == tm)) {

                            // if (i > 0) cout << i << ' ' << t1 << ' ' << t2 << ' ' << tp << ' ' << tm << '\n';
                        } else { return false;}
                    }

                } else {
                    return false;
                }
            }
            if (tm > 0) {
                *dead_time = tm;
            } else {
                *dead_time = tp;
            }
            cout << "COLLISION\n";
            return true;
        }
};

int main() {

    string filename = "day20.txt";
    ifstream sstream(filename);

    regex re("p=<(-?\\d+),(-?\\d+),(-?\\d+)>,\\sv=<(-?\\d+),(-?\\d+),(-?\\d+)>,\\sa=<(-?\\d+),(-?\\d+),(-?\\d+)>");

    vector <Particle> particles;
    deque<Particle> collider;

    for (string ss; getline(sstream, ss); ) {
        vector<int> values;
        smatch sm;
        regex_search(ss, sm, re);
        for (auto i = 1; i < sm.size(); i++) {
            values.push_back(stoi(sm[i].str()));
            // cout << values[i-1] << ' ';
        }
        // cout << '\n';
        // particles.push_back(Particle(values));
        collider.push_back(Particle(values));
    }

    //evolve particles
    // for (int t = 0; t < 2000; t++) {
    //     for (auto it = particles.begin(); it!=particles.end(); ++it) {
    //         it->update_pos();
    //         it->update_vel();
    //     }
    // }
    //
    // vector<long> distances;
    // distances.reserve(particles.size());
    // for (auto it = particles.begin(); it!=particles.end(); ++it) {
    //     distances.push_back(abs(it->dist()));
    //     // cout << it->dist() << '\n';
    // }
    //
    // auto min_res = min_element(distances.begin(), distances.end());
    // cout << "Distance is " << *min_res << ' ' << "at position " << distance(distances.begin(), min_res) << '\n';

    //evolve particles
    int ndead = 0;
    int dead_time = 0;

    // collide particles
    while (!collider.empty()) {
        bool collision = false;
        for (auto i = 1; i < collider.size(); i++) {
            int deadt = 0;
            if (collider[0].collide(collider[i], &deadt)) {
                if (!collision) {
                    ndead+=2;
                    collider.erase(collider.begin()+i);
                    dead_time = deadt;
                    collision = true;
                } else {
                    if (deadt == dead_time) {
                        collider.erase(collider.begin()+i);
                        ndead++;
                    }
                }
                i--;
            }
        }
        collider.pop_front();
    }

    cout << "There are " << ndead << " dead particles.\n";

}
