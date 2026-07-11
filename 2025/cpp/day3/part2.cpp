#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

int* find_max_digits(std::string const &line) {
    int len_line = line.length();
    int* idxs = new int[12];
    size_t start = 0;
    for (int i = 0; i < 12; i++) {
        for (int j = start; j < len_line-12+i+1; j++) {
            if (line[j] > line[idxs[i]]) {
                idxs[i] = j;
            }
        }
        start = idxs[i] + 1;
        if (i < 11) {
            idxs[i+1] = idxs[i] + 1;
        }
    }

    return idxs;
}

void solve_day3_part1(std::string const &input) {
    using namespace std;

    long long total = 0;

    ifstream file(input);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            int* max_digits = find_max_digits(line);
            char* digits_str = new char[13];
            for (int i = 0; i < 12; i++) {
                digits_str[i] = line[max_digits[i]];
            }
            digits_str[12] = '\0';

            long long num = atoll(digits_str);
            total += num;

            delete[] max_digits;
            delete[] digits_str;
        }

        file.close();
    } else {
        cerr << "Unable to open file: " << input << endl;
    }

    cout << "Total: " << total << endl;
}





int main() {
    // std::string input = "input_test.txt"; // 3121910778619
    std::string input = "input.txt"; // 169408143086082
    solve_day3_part1(input);
    return 0;
}
