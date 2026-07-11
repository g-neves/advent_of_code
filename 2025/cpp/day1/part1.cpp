#include <fstream>
#include <iostream>
#include <string>

using namespace std;


int rotate(int position, int direction, int steps) {
    position = (position + direction * steps) % 100;
    if (position < 0) {
        position += 100;
    }

    return position;
}

int get_steps(const string &line) {
    return stoi(line.substr(1));
}

int main() {
    // string input_name = "input_test.txt"; // Expected output: 3
    string input_name = "input.txt"; // 1055
    ifstream file(input_name);

    int zero_count = 0;
    int position = 50;
    int direction;
    int steps;
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line[0] == 'L') {
                direction = -1;
            } else {
                direction = 1;
            }
            steps = get_steps(line);

            position = rotate(position, direction, steps);
            if (position == 0) {
                zero_count++;
            }
        }

        file.close();
    } else {
        cerr << "Unable to open file: " << input_name << endl;
    }

    cout << "Total: " << zero_count << endl;

    return 0;
}
