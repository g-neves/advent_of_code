#include <iostream>
#include <fstream>
#include <vector>


int can_lift_and_remove(std::vector<std::string>& lines, int row, int col) {
    using namespace std;

    int has_up = row > 0 ? 1 : 0;
    int has_down = row < lines.size() - 1 ? 1 : 0;
    int has_left = col > 0 ? 1 : 0;
    int has_right = col < lines[row].length() - 1 ? 1 : 0;

    if (lines[row][col] == '.') {
        return 0;
    }

    char* str_builder = new char[8];

    // Up-down
    if (has_up) {
        str_builder[0] = lines[row - 1][col];
    } else {
        str_builder[0] = '.';
    }
    if (has_down) {
        str_builder[1] = lines[row + 1][col];
    } else {
        str_builder[1] = '.';
    }

    // Left-right
    if (has_left) {
        str_builder[2] = lines[row][col - 1];
    } else {
        str_builder[2] = '.';
    }
    if (has_right) {
        str_builder[3] = lines[row][col + 1];
    } else {
        str_builder[3] = '.';
    }

    // Diagonals
    if (has_up && has_left) {
        str_builder[4] = lines[row - 1][col - 1];
    } else {
        str_builder[4] = '.';
    }
    if (has_up && has_right) {
        str_builder[5] = lines[row - 1][col + 1];
    } else {
        str_builder[5] = '.';
    }
    if (has_down && has_left) {
        str_builder[6] = lines[row + 1][col - 1];
    } else {
        str_builder[6] = '.';
    }
    if (has_down && has_right) {
        str_builder[7] = lines[row + 1][col + 1];
    } else {
        str_builder[7] = '.';
    }

    int counter = 0;
    for (int i = 0; i < 8; i++) {
        if (str_builder[i] == '@') {
            counter++;
        }
    }

    delete[] str_builder;

    int can_lift = counter < 4 ? 1 : 0;

    if (can_lift) {
        lines[row][col] = '.';
    }

    return can_lift;
}

void solve_day4_part2(const std::string& input) {
    using namespace std;

    int total = 0;
    int iterate_again = 1;

    ifstream file(input);
    string line;
    vector<string> lines;

    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << input << endl;
    }

    while (iterate_again) {
        iterate_again = 0;
        for (int row = 0; row < lines.size(); row++) {
            for (int col = 0; col < lines[row].length(); col++) {
                int can_lift = can_lift_and_remove(lines, row, col);
                if (can_lift) {
                    total++;
                    iterate_again = 1;
                }
            }
        }
    }

    cout << "Total: " << total << endl;
}


int main() {
    // std::string input = "input_test.txt"; // Expected output: 43
    std::string input = "input.txt"; // 8587
    solve_day4_part2(input);

    return 0;
}
