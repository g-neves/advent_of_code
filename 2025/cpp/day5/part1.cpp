#include <iostream>
#include <fstream>
#include <vector>



typedef struct {
    long long start;
    long long end;
} IDWindow;


int is_fresh(std::vector<IDWindow> &available_ids, long long line) {
    for (auto &available_id: available_ids) {
        if (line >= available_id.start && line <= available_id.end) {
            return 1;
        }
    }
    return 0;
}

void add_available_ids(std::vector<IDWindow> &available_ids, std::string line) {
    long long start;
    long long end;
    size_t del_position = line.find('-');
    start = std::stoll(line.substr(0, del_position));
    end = std::stoll(line.substr(del_position + 1));

    available_ids.push_back(IDWindow{start, end});
}

void solve_day5_part1(std::string input_file) {
    using namespace std;

    int total = 0;
    int is_splitted = 0;
    vector<IDWindow> available_ids;
    ifstream input(input_file);
    string line;

    while (getline(input, line)) {
        if (line.empty()) {
            is_splitted = 1;
            continue;
        }

        if (is_splitted) {
            long long id = stoll(line);
            total += is_fresh(available_ids, id);
            continue;
        }

        add_available_ids(available_ids, line);
    }

    cout << "Total: " << total << endl;
}

int main() {
    // std::string input_file = "input_test.txt"; // Expected output: 3
    std::string input_file = "input.txt"; // 737
    solve_day5_part1(input_file);

    return 0;
}
