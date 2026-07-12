#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <string>
#include <map>


std::string remove_spaces(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}

long long perform_operation_str(std::vector<std::string>& numbers, std::string operation) {
    using namespace std;

    long long result = 0;
    if (operation == "*") {
        result = 1;
    }

    vector<string> nums;
    vector<long long> nums_ll;
    for (size_t i = 0; i < numbers[0].length(); i++) {
        nums.push_back("");
    }

    for (size_t i = 0; i < numbers[0].length(); i++) {
        for (size_t j = 0; j < numbers.size(); j++) {
            nums[i] += numbers[j][i];
        }
    }

    for (auto num : nums) {
        string num_wo_spaces = remove_spaces(num);
        if (num_wo_spaces.empty()) {
            continue;
        }
        nums_ll.push_back(stoll(num_wo_spaces));
    }

    for (auto num : nums_ll) {
        if (operation == "+") {
            result += num;
        } else if (operation == "*") {
            result *= num;
        }
    }

    return result;
}


std::map<long long, int> get_space_indexes(std::vector<std::string> lines) {
    using namespace std;

    map<long long,int> spaces = map<long long, int>();

    for (auto line : lines) {
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ' ') {
                spaces[i]++;
            }
        }
    }

    return spaces;
}

std::vector<int> get_common_spaces(const std::map<long long, int>& spaces, int max_separator, int max_id) {
    using namespace std;

    vector<int> common_spaces;
    for (const auto& space : spaces) {
        if (space.second == max_separator) {
            common_spaces.push_back(space.first);
        }
    }

    common_spaces.push_back(-1);
    common_spaces.push_back(max_id);
    sort(common_spaces.begin(), common_spaces.end());

    return common_spaces;
}

int find_max_separator(const std::map<long long, int>& spaces) {
    int max_separator = 0;
    for (const auto& space : spaces) {
        if (space.second > max_separator) {
            max_separator = space.second;
        }
    }
    return max_separator;
}

std::vector<std::string> get_operations(const std::vector<std::string>& lines) {
    using namespace std;

    vector<string> operations;
    for (size_t i = 0; i < lines[lines.size() - 1].length(); i++) {
        if (lines[lines.size()-1][i] != ' ') {
            operations.push_back(string(1, lines[lines.size()-1][i]));
        }
    }

    return operations;
}

std::vector<std::vector<std::string>> construct_matrix(
    std::vector<std::string> lines,
    std::vector<int> common_spaces
) {
    using namespace std;

    vector<vector<string>> matrix;
    for (size_t i = 0; i < common_spaces.size() - 1; i++) {
        vector<string> row;
        for (auto line : lines) {
          row.push_back(line.substr(
              common_spaces[i] + 1,
              common_spaces[i + 1] - common_spaces[i] - 1
          ));
        }

        matrix.push_back(row);
    }

    return matrix;
}


int find_longest_line(const std::vector<std::string>& lines) {
    int max_length = 0;
    for (const auto& line : lines) {
        if (line.length() > max_length) {
            max_length = line.length();
        }
    }
    return max_length;
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

void include_trailing_spaces(std::vector<std::string>& lines, int max_length) {
    for (auto& line : lines) {
        while (line.length() < max_length) {
            line += " ";
        }
    }
}

void solve_day6_part2(std::string input_file) {
    using namespace std;

    long long total = 0;
    ifstream input(input_file);
    string line;
    vector<string> lines;

    while (getline(input, line)) {
        lines.push_back(line);
    }

    vector<string> operations = get_operations(lines);
    lines = vector<string>(lines.begin(), lines.end() - 1);
    int longest_line = find_longest_line(lines);
    include_trailing_spaces(lines, longest_line);
    map<long long, int> spaces = get_space_indexes(lines);
    int max_separator = find_max_separator(spaces);
    vector<int> common_spaces = get_common_spaces(spaces, max_separator, lines[0].length());
    vector<vector<string>> matrix = construct_matrix(lines, common_spaces);

    for (size_t i = 0; i < matrix.size(); i++) {
        total += perform_operation_str(matrix[i], operations[i]);
    }

    cout << "Total: " << total << endl;
}


int main() {
    // std::string input_file = "input_test.txt"; // Expected output: 3263827 
    std::string input_file = "input.txt"; // 10756006415204
    solve_day6_part2(input_file);
}
