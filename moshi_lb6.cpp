#include <iostream>
#include <vector>
using namespace std;

const int n = 3;
enum class state { empty, x, o };

struct movestruct {
    int row;
    int col;
};

void print(const vector<vector<state>>& desk) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (desk[i][j] == state::empty)
                cout << " -";
            else if (desk[i][j] == state::x)
                cout << " x";
            else if (desk[i][j] == state::o)
                cout << " o";
        }
        cout << endl;
    }
    cout << endl;
}

bool checkwin(const vector<vector<state>>& desk, state player) {
    for (int i = 0; i < n; ++i) {
        bool win = true;
        for (int j = 0; j < n; ++j) {
            if (desk[i][j] != player) {
                win = false;
                break;
            }
        }
        if (win)
            return true;
        win = true;
        for (int j = 0; j < n; ++j) {
            if (desk[j][i] != player) {
                win = false;
                break;
            }
        }
        if (win)
            return true;
    }
    bool win = true;
    for (int i = 0; i < n; ++i) {
        if (desk[i][i] != player) {
            win = false;
            break;
        }
    }
    if (win)
        return true;
    win = true;
    for (int i = 0; i < n; ++i) {
        if (desk[i][n - i - 1] != player) {
            win = false;
            break;
        }
    }
    return win;
}

vector<movestruct> checkmoves(const vector<vector<state>>& desk) {
    vector<movestruct> possiblemove;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (desk[i][j] == state::empty) {
                movestruct move;
                move.row = i;
                move.col = j;
                possiblemove.push_back(move);
            }
        }
    }
    return possiblemove;
}

int minimax(vector<vector<state>>& desk, int depth, bool isMaximizingPlayer) {
    if (checkwin(desk, state::x))
        return 1;
    if (checkwin(desk, state::o))
        return -1;
    if (checkmoves(desk).empty())
        return 0;
    if (isMaximizingPlayer) {
        int maxeval = INT32_MIN;
        for (const movestruct& move : checkmoves(desk)) {
            desk[move.row][move.col] = state::x;
            int eval = minimax(desk, depth + 1, false);
            desk[move.row][move.col] = state::empty;
            maxeval = max(maxeval, eval);
        }
        return maxeval;
    }
    else {
        int mineval = INT32_MAX;
        for (const movestruct& move : checkmoves(desk)) {
            desk[move.row][move.col] = state::o;
            int eval = minimax(desk, depth + 1, true);
            desk[move.row][move.col] = state::empty;
            mineval = min(mineval, eval);
        }
        return mineval;
    }
}

void computer(vector<vector<state>>& desk) {
    int maxeval = INT32_MIN;
    movestruct bestmove;
    for (const movestruct& move : checkmoves(desk)) {
        desk[move.row][move.col] = state::x;
        int eval = minimax(desk, 0, false);
        desk[move.row][move.col] = state::empty;
        if (eval > maxeval) {
            maxeval = eval;
            bestmove = move;
        }
    }
    desk[bestmove.row][bestmove.col] = state::x;
}

void play() {
    vector<vector<state>> desk(n, vector<state>(n, state::empty));
    while (true) {
        int row, col;
        cout << " input : ";
        cin >> row >> col;
        row--; col--;
        if (row < 0 || row >= n || col < 0 || col >= n || desk[row][col] != state::empty) {
            cout << " input error" << endl;
            continue;
        }
        desk[row][col] = state::o;
        print(desk);
        if (checkwin(desk, state::o)) {
            cout << " win" << endl;
            break;
        }
        if (checkmoves(desk).empty()) {
            cout << " draw" << endl;
            break;
        }
        computer(desk);
        print(desk);
        if (checkwin(desk, state::x)) {
            cout << " fatality" << endl;
            break;
        }
        if (checkmoves(desk).empty()) {
            cout << " draw" << endl;
            break;
        }
    }
}

int main() {
    play();

    return 0;
}
