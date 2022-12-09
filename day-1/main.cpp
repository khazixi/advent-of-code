#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main() {
    std::vector<int> elves;
    std::ifstream file_stream("../input.txt");
    std::string line;
    int temp_val = 0;
    if (!file_stream)
        std::cerr << "Could not open file stream";
    while (std::getline(file_stream, line)) {
        if (line.length() != 0) {
            temp_val += std::stoi(line);
        } else {
            elves.push_back(temp_val);
            temp_val = 0;
        }
    }
    std::sort(elves.begin(), elves.end());
    auto max_calories = std::max_element(elves.begin(), elves.end());
    std::cout << "max element: " << * max_calories << std::endl;
    std::cout << "top 3 elves: " << elves.end()[-1] + elves.end()[-2] + elves.end()[-3] << "\n";
}
