#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <deque>
#include <array>

int main() {
    std::ifstream file("../input.txt");
    std::array<std::deque<char>, 9> boxes;
    std::string line, data;

    // Parses the First part of the data into a file
    for (int i = 0; i < 8; ++i) {
        std::getline(file, line);
        for (int pos = 1, j = 0;
             pos < line.size();
             pos += 4, ++j) {
            if (line.at(pos) == ' ') continue;
            if (64 < line.at(pos) && line.at(pos) < 91)
                boxes.at(j).push_front(line.at(pos));
        }
    }

    std::getline(file, line); // trash read

    int count, from, to;
    while (std::getline(file, line)) {
        int counter = 0;
        count = 0;
        from = 0;
        to = 0;
        std::istringstream istr(line);
        while(std::getline(istr, data, ' ')) {
            if (std::all_of(data.begin(), data.end(), ::isdigit)) {
                int val = std::stoi(data);
                switch (counter) {
                    case 1: count = val; break;
                    case 3: from = val - 1; break;
                    case 5: to = val - 1; break;
                    default: break;
                }
            }
            counter++;
        }
        // Part 1 Code
        /*
        for (int i = 0; i < count; ++i) {
            auto val = boxes.at(from).back();
            boxes.at(to).push_back(val);
            boxes.at(from).pop_back();
        }
        */
        // Part 2 Code
        for (int i = count; i > 0; --i) {
            auto pos = boxes.at(from).size() - i;
            auto val = boxes.at(from).at(pos);
            boxes.at(to).push_back(val);
            boxes.at(from).erase(std::prev(boxes.at(from).end(), i));
        }
    }

    for (auto &val : boxes) {
        std::cout << val.back();
    }
}
