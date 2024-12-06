/** --------
*	Author: MJSaif  &&  AKUL
*	Project Name: NUMERIC TIC TAC TOE
*	Created: 01 July 2024, Sunday ...
*	Time: 00:10:14 (Bangladesh)
**/

#include<bits/stdc++.h>
#include <graphics.h>
using namespace std;

#define ll long long
#define nl '\n'

// Game board, used for output and determining the result
vector<string> board(10, "   ");   // containing 3 spaces initially....

// Draw the board on the window
void boardPrint(int res, int move_of, vector<int> win_comb = {}) {
    cleardevice();

    int width = getmaxx();
    int height = getmaxy();
    int startX = (width - 300) / 2;
    int startY = (height - 300) / 2;

    // Set text style
    int font = BOLD_FONT;
    int direction = HORIZ_DIR;
    int char_size = 3;
    settextstyle(font, direction, char_size);

    // Draw the title
    setcolor(YELLOW);
    int titleX = width / 2;
    int titleY = startY - 70;
    outtextxy(titleX - textwidth("NUMERIC TIC-TAC-TOE") / 2, titleY, "NUMERIC TIC-TAC-TOE");

    // Draw the author line
    setcolor(LIGHTGREEN);
    int authorY = titleY + 30;
    outtextxy(titleX - textwidth("By: MJ Saif && Akul.") / 2, authorY, "By: MJ Saif && Akul.");

    // Draw grid lines
    setcolor(LIGHTMAGENTA);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j){
            int x = startX + i * 100;
            int y = startY + j * 100;
            rectangle(x, y, x + 100, y + 100);
        }
    }

    // Draw the moves on the board
    setcolor(LIGHTCYAN);
    for (int i = 1; i <= 9; ++i) {
        int x = startX + ((i - 1) % 3) * 100 + 50;
        int y = startY + ((i - 1) / 3) * 100 + 50;
        if (board[i][0] != ' ') {
            outtextxy(x - 10, y - 10, const_cast<char*>(board[i].c_str()));
        }
    }

    // Draw winning line if game is over and there's a winner
    if (!win_comb.empty()) {
        setcolor(RED);
        setlinestyle(SOLID_LINE, 0, 3);
        int x1 = startX + ((win_comb[0] - 1) % 3) * 100 + 50;
        int y1 = startY + ((win_comb[0] - 1) / 3) * 100 + 50;
        int x2 = startX + ((win_comb[2] - 1) % 3) * 100 + 50;
        int y2 = startY + ((win_comb[2] - 1) / 3) * 100 + 50;
        line(x1, y1, x2, y2);
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    }

    if(res == -1){
        // Draw the move
        setcolor(YELLOW);
        int moveX = width / 2;
        int moveY = startY + 330;
        if(move_of){
            outtextxy(moveX - textwidth("Move of Player 01(X)") / 2, moveY, "Move of Player 01(X)");
        }else{
            outtextxy(moveX - textwidth("Move of Player 02(O)") / 2, moveY, "Move of Player 02(O)");
        }

    }else{
        // Draw the result
        setcolor(YELLOW);
        int resX = width / 2;
        int resY = startY + 350;
        outtextxy(resX - textwidth("GAME FINISHED!!") / 2, resY - 25, "GAME FINISHED!!");
        if(res == 0){
            outtextxy(resX - textwidth("IT'S  A  DRAW") / 2, resY, "IT'S  A  DRAW");
        }else{
            if(res == 1){
                outtextxy(resX - textwidth("PLAYER 01(X) WINS") / 2, resY, "PLAYER 01(X) WINS");
            }else{
                outtextxy(resX - textwidth("PLAYER 02(O) WINS") / 2, resY, "PLAYER 02(O) WINS");
            }
        }
    }

    delay(20);    // 20 ms delay korbo......
}

// mouse click detect kora.....
int mouseClick(int startX, int startY){
    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            // jotokkon na porjonto Point (x,y) box er vitore na thakbe totokkon porjonto cholbe eita.....
            if (x >= startX && x <= startX + 300 && y >= startY && y <= startY + 300) {
                int col = (x - startX) / 100;
                int row = (y - startY) / 100;
                return row * 3 + col + 1;   // using this so that our index come between (1-9) ... 1D ...
            }
        }
    }
}

// update:  mouse click diya input neya...
void takingMoves(unordered_set<int> &st, int n, int startX, int startY){
    cout << nl;

    // Available moves of current player
    cout << "  Available moves of Player 0" << (n ? "1(X)" : "2(O)") << " are: " << nl << "  ";
    for (auto &it : st) {
        cout << it << "  ";
    }
    cout << nl;

    bool fl = true;
    string ch = (n ? "X" : "O");
    while (fl) {
        cout << nl << "  Player 0" << (n ? "1(X)" : "2(O)") << nl;

        // mouse click detect kora.....
        int idx = mouseClick(startX, startY);

        // The move
        cout << "  Please give your Move: ";
        int move;
        cin >> move;
        if (st.count(move) && (board[idx] == "   " || (move + '0') > board[idx][2])) {
            ch += '-';
            ch += (move + '0');
            board[idx] = ch;
            st.erase(move);
            fl = false;
        } else {
            cout << "  Invalid Move..!" << nl << "  Give a Valid Move.... Please.." << nl;
        }
    }
}

// Check if there is a winner
vector<int> winner_chq() {
    vector<vector<int>> win_combinations = {
        {1, 5, 9}, {3, 5, 7}, // Diagonal
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, // Horizontal
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9}  // Vertical
    };

    for (const auto& comb : win_combinations) {
        if (board[comb[0]][0] != ' ' && board[comb[0]][0] == board[comb[1]][0] && board[comb[0]][0] == board[comb[2]][0]) {
            return comb;
        }
    }
    return {};
}

// Check if the game is a draw
bool drawcheck() {
    for (int i = 1; i < 10; i++) {
        if (board[i][0] == ' ') {
            return false;
        }
    }
    return true;
}

int main(){
    unordered_set<int> num_pl01 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    unordered_set<int> num_pl02 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    cout << nl << "Welcome to The Game!!" << nl;
    cout << "Disclaimer: Here Player 01 Plays with 'X' & Player 02 Plays with 'O'" << nl;

    // Initialize the graphics mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int width = getmaxx();
    int height = getmaxy();
    int startX = (width - 300) / 2;
    int startY = (height - 300) / 2;

    int cnt = 1;
    boardPrint(-1, cnt);

    while (true) {
        if (cnt) {
            takingMoves(num_pl01, cnt, startX, startY);
        } else {
            takingMoves(num_pl02, cnt, startX, startY);
        }

        auto res = winner_chq();
        if (!res.empty()) {
            boardPrint((cnt ? 1 : 2), cnt, res);
            getch();
            break;
        }

        if (drawcheck()) {
            boardPrint(0, cnt);
            getch();
            break;
        }

        cnt = 1 - cnt;          // cnt^=1;
        boardPrint(-1, cnt);
    }

    cout << "Game Finished. Press any key to exit...";
    int ign;            cin>>ign;
    closegraph();
    return 0;
}

