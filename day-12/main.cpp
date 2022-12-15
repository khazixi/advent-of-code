#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <queue>

typedef std::array<int64_t, 2> Point;
typedef std::array<int64_t, 3> DPoint;
typedef std::vector<std::string> Grid;

/*
struct Point {
    int64_t x;
    int64_t y;
    Point * parent;
    bool operator< (const Point &a) const{
        return this->x < a.x;
    }
    Point(int64_t x, int64_t y) : x{x}, y{y}, parent{nullptr} {}
};
 */

inline char get_position(const Grid &g, Point p) {
    return g.at(p[1]).at(p[0]);
}

int64_t get_height(char c) {
    if (c == 'S') return 0;
    if (c == 'E') return 25;
    return c - 97;
}

inline bool valid_position(const Grid &g, Point p) {
    return 0 <= p[0] && 0 <= p[1]
        && p[0] < g[0].size() && p[1] < g.size();
}

std::vector<Point> adjacent_value(const Grid &g, Point p) {
    std::array<Point, 4> tests {{
            {p[0] + 1, p[1] + 0},
            {p[0] - 1, p[1] + 0},
            {p[0] + 0, p[1] + 1},
            {p[0] + 0, p[1] - 1}
    }};

    std::vector<Point> out;
    for (Point t : tests ) {
        if (!valid_position(g, t)) continue;
        // if (get_height(get_position(g, t)) <= get_height(get_position(g, p)) + 1)
        if (get_height(get_position(g, t)) >= get_height(get_position(g, p)) - 1)
            out.push_back(t);
    }

    return out;
}

int main() {
    std::ifstream in("../input.txt");
    if (!in.is_open()) return 1;
    std::string line;
    Grid map;
    map.emplace_back();
    while (std::getline(in, line)) {
        map.back() += line.substr(0, line.find('\n') - 1);
        map.emplace_back();
    }
    map.pop_back();

    Point start = {0}, end = {0};
    int64_t x = 0, y = 0;
    for (auto &v : map) {
        for (auto c : v) {
            if (c == 'S') start = {x, y};
            if (c == 'E') end = {x, y};
            x++;
        }
        y++;
        x = 0;
    }
    std::cout << start[0] << " " << start[1] << "\n";
    std::cout << end[0] << " " << end[1] << "\n";

    std::vector<std::vector<bool>> visited;
    for (auto &row : map) {
        visited.push_back(std::vector<bool>());
        for (auto c : row) {
            visited.back().push_back(false);
        }
    }
    std::priority_queue<DPoint, std::vector<DPoint>, std::greater<>> queue;
    queue.push({0, end[0], end[1]});

    while (true) {
        DPoint temp = queue.top();
        queue.pop();
        if (visited[temp[2]][temp[1]])
            continue;
        visited[temp[2]][temp[1]] = true;

        Point temp_point = {temp[1], temp[2]};
        if (get_height(get_position(map, temp_point)) == 0) {
            std::cout << temp[0] << "\n";
            break;
        }

        for (auto &v : adjacent_value(map, {temp[1], temp[2]})) {
            queue.push({temp[0] + 1, v[0], v[1]});
            // std::cout << "[ " << temp[0] << " " << v[0] << " " << v[1] << "]";
        }
    }

}
