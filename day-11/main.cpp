#include <iostream>
#include <vector>
#include <deque>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

struct Monkey {
    uint32_t inspected;
    uint32_t monkey_number;
    deque<uint64_t> starting_items;
    bool operation_is_multiply;
    bool multiplies_self;
    uint32_t operation_transform;
    uint32_t divisible_amount;
    uint32_t monkey_thrown_to_when_true;
    uint32_t monkey_thrown_to_when_false;

    Monkey(): monkey_number{0},
        inspected{0},
        starting_items(),
        operation_is_multiply{false},
        multiplies_self{false},
        operation_transform{0},
        divisible_amount{0},
        monkey_thrown_to_when_false{0},
        monkey_thrown_to_when_true{0} {}

};

vector<string> split(const string &s, const string &delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

int main() {
    ifstream in("../input.txt");
    vector<Monkey> monkeys;
    vector<string> temp;
    deque<uint64_t> numbers;
    string line;
    while (getline(in, line)) {
        if (line.substr(0, line.find(' ')) == "Monkey") {
            monkeys.emplace_back();
            monkeys.back().monkey_number = monkeys.size() - 1;
        } else if (line.substr(0, line.find(':')) == "  Starting items") {
            string examined = line.substr(18);
            temp = split(examined, ", ");
            for_each(temp.begin(), temp.end(),
                     [&](string &str){
                numbers.push_back(stoi(str));
            });
            monkeys.back().starting_items = numbers;
            numbers.erase(numbers.begin(), numbers.end());
        } else if (line.substr(0, line.find(':')) == "  Operation") {
            string examined = line.substr(19);
            if (examined.find('*') != string::npos) {
                temp = split(examined, " * ");
                monkeys.back().operation_is_multiply = true;
            } else {
                temp = split(examined, " + ");
                monkeys.back().operation_is_multiply = false;
            }
            if (temp.back() == "old") {
                monkeys.back().multiplies_self = true;
                monkeys.back().operation_transform = 0;
            } else {
                monkeys.back().multiplies_self = false;
                monkeys.back().operation_transform = stoi(temp.back());
            }
        }
        else if (line.substr(0, line.find(':')) == "  Test")
            monkeys.back().divisible_amount = stoi(line.substr(21));
        else if (line.substr(0, line.find(':')) == "    If true")
            monkeys.back().monkey_thrown_to_when_true = (uint32_t)line.at(line.length() - 1) - 48;
        else if (line.substr(0, line.find(':')) == "    If false")
            monkeys.back().monkey_thrown_to_when_false = (uint32_t)line.at(line.length() - 1) - 48;
    }

    uint64_t val, tval1, tval2;
    uint64_t mp = accumulate(monkeys.begin(), monkeys.end(), 1, [](auto& prod, Monkey& monk){
        return prod * monk.divisible_amount;
    });
    for (int i = 0; i < 10000; ++i) {
        for (auto &v : monkeys) {
            for (uint32_t num : v.starting_items) {
                v.inspected += 1;
                val = num;
                if (v.operation_is_multiply) {
                    if (v.multiplies_self)
                        tval1 = val * val;
                    else
                        tval1 = val * v.operation_transform;
                } else {
                    tval1 = val + v.operation_transform;
                }
                tval2 = tval1;
                if ((tval2) % v.divisible_amount == 0)
                    monkeys.at(v.monkey_thrown_to_when_true).starting_items.push_back(tval2 % mp);
                else
                    monkeys.at(v.monkey_thrown_to_when_false).starting_items.push_back(tval2 % mp);
                v.starting_items.pop_front();
            }
        }
    }

    vector<uint32_t> vals;
    for (auto &v : monkeys) {
        vals.push_back(v.inspected);
    }

    std::sort(vals.begin(), vals.end());
    for (auto &v : vals)
        cout << v << "\n";
    uint32_t part1_answer  = vals.end()[-1] * vals.end()[-2];
    cout << part1_answer << "\n";
}
