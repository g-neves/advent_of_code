#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


void solve_day3_part1(std::string const &input) {
    using namespace std;

    int total = 0;

    ifstream file(input);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            int len_line = line.length();
            size_t max_id = 0;
            size_t sec_max_id = 1;
            if (line[1] > line[0]) {
                max_id = 1;
                sec_max_id = 0;
            }
            for (size_t i = 2; i < len_line -1; i++) {
                if (line[i] > line[max_id]) {
                    sec_max_id = len_line - 1;
                    max_id = i;
                } else if (line[i] > line[sec_max_id]) {
                    sec_max_id = i;
                }
            }

            if (line[sec_max_id] < line[len_line - 1]) {
                sec_max_id = len_line - 1;
            }

            int num = (line[max_id] - '0') * 10 + (line[sec_max_id] - '0');
            total += num;
        }

        file.close();
    } else {
        cerr << "Unable to open file: " << input << endl;
    }



    cout << "Total: " << total << endl;
}





int main() {
    // std::string input = "input_test.txt"; // 357
    std::string input = "input.txt"; // 17085
    solve_day3_part1(input);
    return 0;
}
