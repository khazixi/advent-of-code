#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ranges>
#include <algorithm>
#include <array>
#include <numeric>

using namespace std;

uint64_t part1(vector<vector<int8_t>> &mat) {
    uint64_t dim = mat.size() - 1;
    uint64_t v = 4 * dim ;
    for (int y = 1; y < dim; ++y) {
        for (int x = 1; x < dim; ++x) {
            vector<int8_t> vy0;
            vector<int8_t> vy1;
            int x0 = *std::max_element(mat[y].begin(), mat[y].begin() + x);
            int x1 = *std::max_element(mat[y].begin() + x + 1, mat[y].end());
            for_each(mat.begin(), mat.begin() + y, [&](vector<int8_t> &v){ vy0.push_back(v[x]); } );
            for_each(mat.begin() + y + 1, mat.end(), [&](vector<int8_t> &v){ vy1.push_back(v[x]); } );
            int y0 = *max_element(vy0.begin(), vy0.end());
            int y1 = *max_element(vy1.begin(), vy1.end());
            if (mat[y][x] > x0 || mat[y][x] > x1 || mat[y][x] > y0 || mat[y][x] > y1 ) {
                v += 1;
            }
        }
    }
    return v;
}

uint64_t calc_distance(vector<int8_t> &v, int8_t tr) {
    vector<int8_t> a;
    for (int8_t i : v) {
        if (i >= tr) return a.size() + 1;
        a.push_back(i);
    }
    return a.size();
}

uint64_t part2(vector<vector<int8_t>> &mat) {
    vector<uint64_t> values;
    for (int y = 1; y < mat.size() - 1; ++y) {
        for (int x = 1; x < mat.size() - 1; ++x) {
            vector<int8_t> vy0i, vy1i;
            auto &cur = mat[y][x];
            auto vx0 = vector<int8_t>(mat[y].begin(), mat[y].begin() + x);
            auto vx1 = vector<int8_t>(mat[y].begin() + x + 1, mat[y].end());
            for(int i = 0; i < y; ++i) vy0i.push_back(mat[i][x]);
            for(int i = y + 1; i < mat.size(); ++i) vy1i.push_back(mat[i][x]);
            reverse(vx0.begin(), vx0.end());
            reverse(vy0i.begin(), vy0i.end());
            std::array<uint64_t, 4> scores = {
                    calc_distance(vx0, cur), calc_distance(vx1, cur),
                    calc_distance(vy0i, cur), calc_distance(vy1i, cur)
            };
            values.push_back(accumulate(scores.begin(), scores.end(), 1, multiplies<>()));
        }
    }
    return *max_element(values.begin(), values.end());
}

int main() {
    ifstream in("../../input.txt");
    stringstream sst("30373\n"
                     "25512\n"
                     "65332\n"
                     "33549\n"
                     "35390");
    vector<vector<int8_t>> matrix;
    string line;
    while (getline(in, line)) {
        vector<int8_t> temp;
        for(char c : line) {
            if (c == '\n') continue;
            temp.push_back(c);
        }
        matrix.push_back(temp);
    }
    cout << part1(matrix) << "\n";
    cout << part2(matrix) << "\n";
}
