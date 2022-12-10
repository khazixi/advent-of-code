#include <iostream>
#include <fstream>
#include <string>
#include <array>

using namespace std;
constexpr const array<int32_t, 6> signalStrengths {20, 60, 100, 140, 180, 220};

int checkCycle(int32_t val, int32_t cycle) {
    if (std::find(signalStrengths.cbegin(), signalStrengths.cend(), cycle) != signalStrengths.end()) {
        return cycle * val;
    }
    return 0;
}

void draw_pixel(int32_t val, int32_t cycle, array<bool, 40>& draw_positions) {
    for (auto b : draw_positions) {
        if (b) cout << "#";
        else cout << ".";
    }
    cout << "\n";
    draw_positions = {false};
}

int main() {
    ifstream in("../input.txt");
    if(!in.is_open()) {
        cout << "File did not open";
        return 1;
    }
    int32_t cycle = 0, reg = 1;
    int32_t part1_answer = 0;
    std::string line, p1, p2;
    int val;
    while (getline(in, line)) {
        p1 = line.substr(0, 4);
        if (line.size() > 5) val = stoi(line.substr(4));

        if (p1 == "noop") {
            cycle++;
            part1_answer += checkCycle(reg, cycle);
        } else if (p1 == "addx") {
            cycle++;
            part1_answer += checkCycle(reg, cycle);
            cycle++;
            part1_answer += checkCycle(reg, cycle);
            reg += val;
        }

    }

    in.clear();
    in.seekg(0, ios::beg);
    cycle = 0;
    reg = 1;
    cout << part1_answer << "\n";

    std::array<bool, 40> drawn_pixels {0};
    while (getline(in, line)) {
        p1 = line.substr(0, 4);
        if (line.size() > 5) val = stoi(line.substr(4));

        if (p1 == "noop") {
            cycle++;
            if (cycle % 40 == reg || cycle % 40 == reg + 2 || cycle % 40 == reg + 1) {
                if (cycle % 40 != 0) drawn_pixels[cycle % 40 - 1] = true;
                else drawn_pixels[39] = true;
            }
            if (cycle % 40 == 0 && cycle != 0) draw_pixel(val, cycle, drawn_pixels);
        } else if (p1 == "addx") {
            cycle++;
            if (cycle % 40 == reg || cycle % 40 == reg + 2 || cycle % 40 == reg + 1) {
                if (cycle % 40 != 0) drawn_pixels[cycle % 40 - 1] = true;
                else drawn_pixels[39] = true;
            }
            if (cycle % 40 == 0) draw_pixel(val, cycle, drawn_pixels);
            cycle++;
            if (cycle % 40 == reg || cycle % 40 == reg + 2 || cycle % 40 == reg + 1) {
                if (cycle % 40 != 0) drawn_pixels[cycle % 40 - 1] = true;
                else drawn_pixels[39] = true;
            }
            if (cycle % 40 == 0) draw_pixel(val, cycle, drawn_pixels);
            reg += val;
        }
    }

}
