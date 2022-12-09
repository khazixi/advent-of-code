#include <iostream>
#include <algorithm>
#include <ranges>
#include <fstream>
#include <vector>
#include <string>

bool contains_other_pair(int min1, int max1, int min2, int max2) {
    if (
        (min1 <= min2 && max2 <= max1) ||
        (min2 <= min1 && max1 <= max2)
    )
        return true;
    return false;
}

bool contains_overlap(int min1, int max1, int min2, int max2) {
    if (min1 == min2 || min1 == max2 ||
        min2 == max1 || max1 == max2
    )
        return true;
    if (min1 < max2) {
        if (max1 < min2) return false;
        return true;
    } else if (min2 < max1) {
        if (max2 < min1) return false;
        return true;
    }

    return false;
}

int main() {
    std::ifstream in("../input.txt");
    std::string line, r1, r2;
    int r1l, r1u, r2l, r2u;
    int matches_1 = 0;
    int matches_2 = 0;
    while (std::getline(in, line)) {
        r1 = line.substr(0, line.find(','));
        r2 = line.substr(line.find(',') + 1);

        r1l = std::stoi(r1.substr(0, r1.find('-')));
        r1u = std::stoi(r1.substr(r1.find('-') + 1));
        r2l = std::stoi(r2.substr(0, r2.find('-')));
        r2u = std::stoi(r2.substr(r2.find('-') + 1));

        if (contains_other_pair(r1l, r1u, r2l, r2u)) {
            matches_1 += 1;
        }

        if (contains_overlap(r1l, r1u, r2l, r2u))
            matches_2 += 1;
    }

    std::cout << "A " <<contains_overlap(5, 7, 7, 9)  << "\n";
    std::cout << "B " <<contains_overlap(2, 8, 3, 7)  << "\n";
    std::cout << "C " <<contains_overlap(6, 6, 4, 6)  << "\n";
    std::cout << "D " <<contains_overlap(2, 6, 4, 8)  << "\n";
    std::cout << "E " <<contains_overlap(2, 4, 6, 8)  << "\n";

    std::cout << matches_1  << "\n";
    std::cout << matches_2  << "\n";



}
