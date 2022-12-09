#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct Tree {
    long long val;
    bool isdir;
    Tree * parent;
    const std::string name;
    std::vector<Tree *> nodes;

    Tree(long long v, bool d, Tree * p, std::string n) : val(v), isdir(d), parent(p), name(std::move(n)) {}
};


int tree_calc(Tree * cwd, std::vector<int64_t> * values, std::vector<int64_t> * total) {
    int64_t sum = 0;
    int64_t val = 0;
    for (auto * tr : cwd->nodes) {
        if (tr->isdir) sum += tree_calc(tr, values, total);
        else {
            val += tr->val;
        }
    }
    sum += val;
    total->push_back(sum);
    if (sum <= 100000)
        values->push_back(sum);
    return sum;
}


long long part1(std::stringstream &str) {
    std::string line;
    Tree * cwd = nullptr;
    Tree * root = nullptr;
    while (std::getline(str, line)) {
        std::string sval1, sval2, sval3;
        sval1 = line.substr(0, line.find(' '));
        sval2 = line.substr(line.find(' ') + 1);
        sval3 = sval2.substr(sval2.find(' ') + 1);
        sval2 = sval2.substr(0, sval2.find(' '));
        if (line[0] == '$') {
            // Case 1 parse command
            if (sval2 == "cd") {
                if (sval3 == "/") {
                    root = new Tree(0, true, nullptr, "/");
                    cwd = root;
                } else if (sval3 == "..") {
                    cwd = cwd->parent;
                } else {
                    for (Tree * tr : cwd->nodes) {
                        if (tr->name == sval3) {
                            cwd = tr;
                            break;
                        }
                    }
                }
                continue;
            } else if (sval2 == "ls") {
                continue;
            } else {
                return -1;
            }
        }
        // Case 2 parses ls' output
        if (std::all_of(sval1.begin(), sval1.end(), ::isdigit)) {
            // Case 2A deals with parsing file
            cwd->nodes.push_back(new Tree(stoi(sval1), false, cwd, sval2));
        } else if (sval1 == "dir") {
            // Case 2B deals with parsing directory
            Tree * tempdir = new Tree(0, true, cwd, sval2);
            cwd->nodes.push_back(tempdir);
        } else {
            return -2;
        }

    }


    std::vector<int64_t> valv;
    std::vector<int64_t> totv;
    tree_calc(root, &valv, &totv);
    // Part 1 Value
    for (auto &v : totv) std::cout << v << "\n";
    int64_t total_filesize = totv.back();
    int64_t min_dir_size = total_filesize - 70000000 + 30000000;

    // Part 2
    std::sort(totv.begin(), totv.end());
    for (int64_t i : totv) {
        if (i > min_dir_size) return i;
    }
}

int main() {
    std::ifstream in("../input.txt");
    std::string line;
    std::string test = "$ cd /\n"
                       "$ ls\n"
                       "dir a\n"
                       "14848514 b.txt\n"
                       "8504156 c.dat\n"
                       "dir d\n"
                       "$ cd a\n"
                       "$ ls\n"
                       "dir e\n"
                       "29116 f\n"
                       "2557 g\n"
                       "62596 h.lst\n"
                       "$ cd e\n"
                       "$ ls\n"
                       "584 i\n"
                       "$ cd ..\n"
                       "$ cd ..\n"
                       "$ cd d\n"
                       "$ ls\n"
                       "4060174 j\n"
                       "8033020 d.log\n"
                       "5626152 d.ext\n"
                       "7214296 k";
    std::stringstream ss;
    std::stringstream sst(test);
     ss << in.rdbuf();
    return part1(ss);
}
