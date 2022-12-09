#include <utility>
#include <fstream>
#include <iostream>

enum Choices { rock = 1, paper = 2, scissors = 3 };
enum GameResults { lost = 0, draw = 3, win = 6, error = -1 };
std::pair<int, int> evaluate_game(char p1, char p2) {
    Choices p1_state;
    Choices p2_state;
    switch (p1) {
        case 'A': p1_state = Choices::rock;
            break;
        case 'B': p1_state = Choices::paper;
            break;
        case 'C': p1_state = Choices::scissors;
            break;
        default:
            return {GameResults::error, GameResults::error};
    }

    switch (p2) {
        case 'X':
            p2_state = Choices::rock;
            break;
        case 'Y':
            p2_state = Choices::paper;
            break;
        case 'Z':
            p2_state = Choices::scissors;
            break;
        default:
            return {GameResults::error, GameResults::error};
    }

    if (p1_state == p2_state) {
        return {draw + p1_state, draw + p2_state};
    } else if (
            p1_state == Choices::rock       && p2_state == Choices::scissors ||
            p1_state == Choices::scissors   && p2_state == Choices::paper ||
            p1_state == Choices::paper      && p2_state == Choices::rock
    ) {
        return {GameResults::win + p1_state, lost + p2_state};
    } else {
        return {GameResults::lost + p1_state, win + p2_state};
    }
}
Choices getPoint(GameResults res, Choices p1) {
    switch (res) {
        case GameResults::win:
            switch (p1) {
                case rock: return paper;
                case paper: return scissors;
                case scissors: return rock;
            }
            break;
        case GameResults::lost:
            switch (p1) {
                case rock: return scissors;
                case paper: return rock;
                case scissors: return paper;
            }
            break;
        case GameResults::draw:
            switch (p1) {
                case rock: return rock;
                case paper: return paper;
                case scissors: return scissors;
            }
            break;
    }
}

int eval_game2(char p1, char p2) {
    Choices p1_state;
    Choices p2_state;
    switch (p1) {
        case 'A': p1_state = Choices::rock;
            break;
        case 'B': p1_state = Choices::paper;
            break;
        case 'C': p1_state = Choices::scissors;
            break;
        default:
            return GameResults::error;
    }

    switch (p2) {
        case 'X':
            p2_state = Choices::rock;
            break;
        case 'Y':
            p2_state = Choices::paper;
            break;
        case 'Z':
            p2_state = Choices::scissors;
            break;
        default:
            return GameResults::error;
    }

    if (p2_state == rock)
        return getPoint(lost, p1_state) + GameResults::lost;
    else if (p2_state == paper)
        return getPoint(draw, p1_state) + GameResults::draw;
    else if (p2_state == scissors)
        return getPoint(win, p1_state) + win;
}

int main() {
    int p1_score = 0;
    int p2_score = 0;
    int alt_score = 0;
    std::ifstream in("../input.txt");
    std::string line;
    while (std::getline(in, line)) {
        auto score = evaluate_game(line.at(0), line.at(2));
        p1_score += score.first;
        p2_score += score.second;
        alt_score += eval_game2(line.at(0), line.at(2));
    }
    std::cout << "First Player Score: " << p1_score << "\n";
    std::cout << "Second Player Score: " << p2_score << "\n";
    std::cout << "New Score: " << alt_score << "\n";
}
