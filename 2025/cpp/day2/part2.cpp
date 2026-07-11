#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solve_day2_part1(const string &input_name) {
    ifstream file(input_name);
    vector<string> tokens;
    string token;

    long long total = 0;
    
    while (getline(file, token, ',')) {
        tokens.push_back(token);
    }

    for (const auto &t : tokens) {
        for (int i = 0; i < t.size(); i++) {
            // Numbers are of type "start-end", so we need to split them by the '-' character
            if (t[i] == '-') {
                long long start = stoll(t.substr(0, i));
                long long end = stoll(t.substr(i + 1));
                for (long long j = start; j <= end; j++) {
                    // Now we check if the number is symmetric with respect to its middle.
                    string j_str = to_string(j);
                    if (j_str.size() % 2 != 0) {
                        continue;
                    }
                    if (j_str.substr(0, j_str.size() / 2) == j_str.substr(j_str.size() / 2)) {
                        total += j;
                }
            }
        }
    }
    }

    file.close();

    cout << "Result: " << total << endl;
}


int main() {
    string input_name = "input_test.txt"; // 1227775554
	// string input_name = "input.txt"; // 23039913998
    solve_day2_part1(input_name);
    return 0;
}
