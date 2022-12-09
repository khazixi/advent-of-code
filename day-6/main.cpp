#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <set>

int solve(const std::string &str, const int cap) {
    std::deque<char> hold;
    int i = 1;
    for (char c : str) {
        std::set<char> cset;
        if (hold.size() == cap)
            hold.pop_front();
        hold.push_back(c);
        for (auto item: hold)
            cset.insert(item);
        if (cset.size() == cap)
            return i;
        ++i;
    }
    return i;
}

int main() {
    std::ifstream in("../input.txt");
    std::string line;
    in >> line;
    std::cout << "Then answer for part 1 is: " << solve(line, 4) << "\n";
    std::cout << "Then answer for part 2 is: " << solve(line, 14) << "\n";
}
