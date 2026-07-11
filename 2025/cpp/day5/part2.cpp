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

void merge_intervals(std::vector<IDWindow> &available_ids) {
    using namespace std;

    sort(available_ids.begin(), available_ids.end(), [](const IDWindow &a, const IDWindow &b) {
        return a.start < b.start;
    });
    for (size_t i = 0; i < -1; i++) {
        if (i >= available_ids.size() - 1) {
            break;
        }
        if (available_ids[i].end >= available_ids[i+1].start-1) {
            available_ids[i].end = max(available_ids[i].end, available_ids[i+1].end);
            available_ids.erase(available_ids.begin() + i + 1);
            i--;
        }
    }
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

    long long total = 0;
    vector<IDWindow> available_ids;
    ifstream input(input_file);
    string line;

    while (getline(input, line)) {
        if (line.empty()) {
            break;
        }
        add_available_ids(available_ids, line);
    }

    merge_intervals(available_ids);

    for (auto &available_id: available_ids) {
        total += (available_id.end - available_id.start + 1);
    }

    cout << "Total: " << total << endl;
}

int main() {
    // std::string input_file = "input_test.txt"; // Expected output: 14
    std::string input_file = "input.txt"; // 357485433193284
    solve_day5_part1(input_file);

    return 0;
}
