#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <numeric>

int correction(char c) {
    if (isupper(c))
        return c - 38;
    return c - 96;
}

int main() {
    std::ifstream in("../input.txt");
    std::string line, l1, l2;
    std::vector<int> temp;
    std::vector<int> new_temp;
    while(std::getline(in, line)) {
        std::set<char> sl1, sl2;
        l1 = line.substr(0, line.length()/2);
        l2 = line.substr(line.length()/2);
        for (char c : l1)
            sl1.insert(c);
        for (char c : l2)
            sl2.insert(c);
        std::ranges::set_intersection(sl1, sl2, std::back_inserter(temp));
    }
    std::ranges::transform(temp.begin(), temp.end(),
                           temp.begin(), correction);
    int sum = std::accumulate(temp.begin(), temp.end(), 0);

    std::ifstream inf("../input.txt");
    std::string line1, line2, line3;
    std::vector<int> answer2;
    while (std::getline(inf, line1)) {
        std::set<char> sline1, sline2, sline3;
        std::vector<char> int1;
        std::vector<char> int2;

        std::getline(inf, line2);
        std::getline(inf, line3);
        for (char c: line1) sline1.insert(c);
        for (char c: line2) sline2.insert(c);
        for (char c: line3) sline3.insert(c);
        std::ranges::set_intersection(sline1, sline2,
                                      std::back_inserter(int1));
        std::ranges::set_intersection(sline1, sline3,
                                      std::back_inserter(int2));
        std::ranges::set_intersection(int1, int2,
                                      std::back_inserter(answer2));
    }
    std::ranges::transform(answer2.begin(), answer2.end(),
                           answer2.begin(),correction) ;
    int sum2 = std::accumulate(answer2.begin(), answer2.end(), 0);
    std::cout << sum << "\n";
    std::cout << sum2 << "\n";
}
