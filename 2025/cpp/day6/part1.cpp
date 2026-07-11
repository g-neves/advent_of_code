#include <iostream>
#include <fstream>
#include <sstream>

long long perform_operation(std::vector<long long>& numbers, std::string operation) {
    long long result = 0;
    if (operation == "+") {
        for (auto num : numbers) {
            result += num;
        }
    } else if (operation == "*") {
        result = 1;
        for (auto num : numbers) {
            result *= num;
        }
    }
    return result;
}

void populate_array(std::vector<std::vector<long long>>& array, std::vector<std::string> first_row) {
    using namespace std;
    for (size_t i = 0; i < first_row.size(); ++i) {
        first_row[i].erase(
            std::remove(first_row[i].begin(), first_row[i].end(), ' '),
            first_row[i].end()
        );
        if (first_row[i].empty()) {
            continue;
        }
        array.push_back(std::vector<long long>());
    }
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    using namespace std;

    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void solve_day6_part1(std::string input_file) {
    using namespace std;

    long long total = 0;
    ifstream input(input_file);
    string line;
    vector<vector<long long>> arr;
    int is_last_line = 0;
    int is_populated = 0;
    vector<string> ops;

    while (getline(input, line)) {

        vector<string> numbers = split(line, ' ');

        if (!is_populated) {
            populate_array(arr, numbers);
            is_populated = 1;
        }

        if (numbers[0] == "*" || numbers[0] == "+") {
            is_last_line = 1;
        }

        int j = 0;
        for (size_t i = 0; i < numbers.size(); ++i) {
            string num_trimmed = numbers[i];
            num_trimmed.erase(
                remove(num_trimmed.begin(), num_trimmed.end(), ' '),
                num_trimmed.end()
            );
            if (num_trimmed.empty()) {
                continue;
            }

            if (!is_last_line) {
                arr[j].push_back(stoi(num_trimmed));
            } else {
                if (num_trimmed == "*" || num_trimmed == "+") {
                    ops.push_back(num_trimmed);
                }
            }

            j++;
        }
    }

    for (size_t i = 0; i < arr.size(); ++i) {
        total += perform_operation(arr[i], ops[i]);
    }

    cout << "Total: " << total << endl;
}


int main() {
    // std::string input_file = "input_test.txt"; // Expected output: 4277556
    std::string input_file = "input.txt"; // 7326876294741 
    solve_day6_part1(input_file);
}
