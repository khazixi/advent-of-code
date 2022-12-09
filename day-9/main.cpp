#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <set>

using namespace std;

int main() {
    ifstream in("../input.txt");
    stringstream ss("R 4\n"
                    "U 4\n"
                    "L 3\n"
                    "D 1\n"
                    "R 4\n"
                    "D 1\n"
                    "L 5\n"
                    "R 2");
    if(!in.is_open()) {
        cout << "The file was not opened\n";
        return 1;
    }

    // Part 1 Code
    std::string line;
    uint8_t p1, p2;
    array<int8_t, 2> head{0}, tail{0};
    set<array<int8_t, 2>> tail_positions;
    int8_t dfx, dfy;
    while (getline(in, line)) {
        p1 = line.substr(0, 1).at(0);
        p2 = stoi(line.substr(2, line.find('\n')));

        // Tail Move Section
        for (int i = 0; i < p2; ++i) {
            if (p1 == 'U') head[1] += 1;
            else if(p1 == 'D') head[1] -= 1;
            else if(p1 == 'R') head[0] += 1;
            else if(p1 == 'L') head[0] -= 1;
            // These warnings cannot
            dfx = head[0] - tail[0];
            dfy = head[1] - tail[1];
            if (abs(dfx) > 1|| abs(dfy) > 1) {
                if (dfx > 0)  tail[0] += 1;
                else if (dfx < 0)  tail[0] -= 1;
                if (dfy > 0)  tail[1] += 1;
                else if (dfy < 0)  tail[1] -= 1;
            }
            tail_positions.insert(tail);
        }
    }
    uint64_t part1_answer = tail_positions.size();

    // Clean up
    in.close();
    ifstream in2("../input.txt");
    if(!in2.is_open()) {
        cout << "The file was not opened\n";
        return 1;
    }
    head = {0};
    tail = {0}; // Not going to be used
    tail_positions.erase(tail_positions.begin(), tail_positions.end());
    array<array<int8_t, 2>, 9> tails = {0};
    while (getline(in2, line)) {
        p1 = line.substr(0, 1).at(0);
        p2 = stoi(line.substr(2, line.find('\n')));

        // Tail Move Section
        for (int i = 0; i < p2; ++i) {
            if (p1 == 'U') head[1] += 1;
            else if(p1 == 'D') head[1] -= 1;
            else if(p1 == 'R') head[0] += 1;
            else if(p1 == 'L') head[0] -= 1;

            dfx = head[0] - tails[0][0];
            dfy = head[1] - tails[0][1];
            if (abs(dfx) > 1|| abs(dfy) > 1) {
                if (dfx > 0)  tails[0][0] += 1;
                else if (dfx < 0)  tails[0][0] -= 1;
                if (dfy > 0)  tails[0][1] += 1;
                else if (dfy < 0)  tails[0][1] -= 1;
            }

            for (int j = 0; j < tails.size() - 1; ++j) {
                dfx = tails[j][0] - tails[j + 1][0];
                dfy = tails[j][1] - tails[j + 1][1];
                if (abs(dfx) > 1|| abs(dfy) > 1) {
                    if (dfx > 0)  tails[j + 1][0] += 1;
                    else if (dfx < 0)  tails[j + 1][0] -= 1;
                    if (dfy > 0)  tails[j + 1][1] += 1;
                    else if (dfy < 0)  tails[j + 1][1] -= 1;
                }
                tail_positions.insert(tails[8]);
            }
        }

    }
    uint64_t part2_answer = tail_positions.size();


    std::cout << "Part 1 Answer: " << part1_answer << "\n";
    std::cout << "Part 2 Answer: " << part2_answer << "\n";

}
