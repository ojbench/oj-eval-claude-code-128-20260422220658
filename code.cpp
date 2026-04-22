#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool check_win(const vector<string>& board, char c) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == c && board[i][1] == c && board[i][2] == c) return true;
    }
    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == c && board[1][i] == c && board[2][i] == c) return true;
    }
    // Check diagonals
    if (board[0][0] == c && board[1][1] == c && board[2][2] == c) return true;
    if (board[0][2] == c && board[1][1] == c && board[2][0] == c) return true;
    return false;
}

int main() {
    vector<string> board(3);
    int count_x = 0, count_o = 0;
    for (int i = 0; i < 3; ++i) {
        if (!(cin >> board[i])) return 0;
        for (char c : board[i]) {
            if (c == 'x') count_x++;
            else if (c == 'o') count_o++;
        }
    }

    // Invalid conditions based on counts
    if (count_x < count_o || count_x > count_o + 1) {
        cout << "invalid" << endl;
        return 0;
    }

    bool x_wins = check_win(board, 'x');
    bool o_wins = check_win(board, 'o');

    // Both cannot win
    if (x_wins && o_wins) {
        cout << "invalid" << endl;
        return 0;
    }

    // If x wins, count_x must be count_o + 1
    if (x_wins && count_x != count_o + 1) {
        cout << "invalid" << endl;
        return 0;
    }

    // If o wins, count_x must be count_o
    if (o_wins && count_x != count_o) {
        cout << "invalid" << endl;
        return 0;
    }

    // Check for "immediate stop" rule: once someone wins, the game ends.
    // However, the counts check above already covers some of this.
    // We also need to check if there are multiple winning lines that couldn't have been formed simultaneously.
    // For x: if x has multiple winning lines, they must share the last 'x' placed.
    // Wait, the problem says "once there are three of the same kind of pieces connected, stop immediately".
    // This means if x just won, it must be the last piece placed (so count_x == count_o + 1).
    // If we remove ANY of the x's, would x still be winning?
    // Actually, a simpler way: if x_wins, and we remove one 'x' that makes it NOT win, it could be valid.
    if (x_wins) {
        bool possible = false;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == 'x') {
                    vector<string> temp = board;
                    temp[i][j] = '-';
                    if (!check_win(temp, 'x')) {
                        possible = true;
                        break;
                    }
                }
            }
            if (possible) break;
        }
        if (!possible) {
            cout << "invalid" << endl;
            return 0;
        }
        cout << "win" << endl;
        return 0;
    }

    if (o_wins) {
        bool possible = false;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == 'o') {
                    vector<string> temp = board;
                    temp[i][j] = '-';
                    if (!check_win(temp, 'o')) {
                        possible = true;
                        break;
                    }
                }
            }
            if (possible) break;
        }
        if (!possible) {
            cout << "invalid" << endl;
            return 0;
        }
        cout << "lose" << endl;
        return 0;
    }

    if (count_x + count_o == 9) {
        cout << "tie" << endl;
    } else {
        cout << "ongoing" << endl;
    }

    return 0;
}
