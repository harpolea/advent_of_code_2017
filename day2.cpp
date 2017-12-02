#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

using namespace std;

auto pass_str_to_ints(string str_input) {
    vector <vector <int>> inputs;

    stringstream instream(str_input);
    string input;

    while (getline(instream, input)) {
        vector <int> temp;
        istringstream in( input );
        copy(istream_iterator<int>( in ), istream_iterator<int>(),
            back_inserter( temp ) );
        inputs.push_back(temp);
    }

    return inputs;

}

auto checksum(vector <vector <int>> input) {
    int sum = 0;
    for (vector<vector<int> >::iterator it = input.begin(); it != input.end(); ++it) {
        int smallest = it->front();
        int largest = it->at(1);
        if (smallest > largest) {
            smallest = it->at(1);
            largest = it->front();
        }

        for (vector<int>::iterator jt = it->begin()+2; jt != it->end(); ++jt) {
            if (*jt < smallest) smallest = *jt;
            if (*jt > largest) largest = *jt;
        }

        sum += (largest - smallest);

    }
    return sum;
}

auto divisible_checksum(vector <vector <int>> input) {
    int sum = 0;
    bool break_row;
    for (vector<vector<int> >::iterator it = input.begin(); it != input.end(); ++it) {
        break_row = false;
        for (vector<int>::iterator jt = it->begin(); jt != it->end(); ++jt) {
            for (vector<int>::iterator kt = jt+1; kt != it->end(); ++kt) {
                if (*jt % *kt == 0) {
                    sum += *jt / *kt;
                    break_row = true;
                    break;
                } else if (*kt % *jt == 0) {
                    sum += *kt / *jt;
                    break_row = true;
                    break;
                }
            }
            if (break_row) break;
        }
    }
    return sum;
}

int main() {
    string test_str = "5 1 9 5\n7 5 3\n2 4 6 8";

    int sum = checksum(pass_str_to_ints(test_str));

    if (checksum(pass_str_to_ints(test_str)) != 18) {
        cerr << "Checksum of test input is not equal to 18\n";
    }

    string puzzle_str = "104	240	147	246	123	175	372	71	116	230	260	118	202	270	277	292\n740	755	135	205	429	822	844	90	828	115	440	805	526	91	519	373\n1630	991	1471	1294	52	1566	50	1508	1367	1489	55	547	342	512	323	51\n1356	178	1705	119	1609	1409	245	292	1434	694	405	1692	247	193	1482	1407\n2235	3321	3647	212	1402	3711	3641	1287	2725	692	1235	3100	123	144	104	101\n1306	1224	1238	186	751	734	1204	1275	366	149	1114	166	1118	239	153	943\n132	1547	1564	512	2643	2376	2324	2159	1658	107	1604	145	2407	131	2073	1878\n1845	91	1662	108	92	1706	1815	1797	1728	1150	1576	83	97	547	1267	261\n78	558	419	435	565	107	638	173	93	580	338	52	633	256	377	73\n1143	3516	4205	3523	148	401	3996	3588	300	1117	2915	1649	135	134	182	267\n156	2760	1816	2442	2985	990	2598	1273	167	821	138	141	2761	2399	1330	1276\n3746	3979	2989	161	4554	156	3359	173	3319	192	3707	264	762	2672	4423	2924\n3098	4309	4971	5439	131	171	5544	595	154	571	4399	4294	160	6201	4329	5244\n728	249	1728	305	2407	239	691	2241	2545	1543	55	2303	1020	753	193	1638\n260	352	190	877	118	77	1065	1105	1085	1032	71	87	851	56	1161	667\n1763	464	182	1932	1209	640	545	931	1979	197	1774	174	2074	1800	939	161";

    sum = checksum(pass_str_to_ints(puzzle_str));

    cout << "checksum = " << sum << '\n';

    string test_str2 = "5 9 2 8\n9 4 7 3\n3 8 6 5";

    if (divisible_checksum(pass_str_to_ints(test_str2)) != 9) {
        cerr << "Divisible checksum of test input is not equal to 9\n";
    }

    sum = divisible_checksum(pass_str_to_ints(puzzle_str));

    cout << "divisible checksum = " << sum << '\n';

}
