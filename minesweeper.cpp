#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

const int N = 9, M = 9, B = 10;
int board[N][M], revealed[N][M];

void placeBombs() {
    int placed = 0;
    while(placed < B) {
        int r = rand() % N, c = rand() % M;
        if(board[r][c]== -1) continue;
        board[r][c]= -1; placed++;
        for(int dr=-1; dr<=1; dr++)
            for(int dc=-1; dc<=1; dc++)
                if(r+dr>=0 && r+dr<N && c+dc>=0 && c+dc<M && board[r+dr][c+dc]!= -1)
                    board[r+dr][c+dc]++;
    }
}

void printBoard() {
    cout << "   ";
    for(int i=0;i<M;i++) cout << i << " ";
    cout << endl;
    for(int i=0;i<N;i++){
        cout << i << " ";
        for(int j=0;j<M;j++){
            if(revealed[i][j]) cout << (board[i][j]==-1?'B':board[i][j]) << " ";
            else cout << "# ";
        }
        cout << endl;
    }
}

void reveal(int r, int c) {
    if(r<0 || r>=N || c<0 || c>=M || revealed[r][c]) return;
    revealed[r][c]=1;
    if(board[r][c]==0)
        for(int dr=-1; dr<=1; dr++)
            for(int dc=-1; dc<=1; dc++)
                reveal(r+dr, c+dc);
}

int main() {
    srand(time(0));
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            board[i][j]=0, revealed[i][j]=0;
    placeBombs();
    while(1){
        printBoard();
        int r,c;
        cout<<"Enter row and col: "; cin>>r>>c;
        if(board[r][c]== -1){ cout<<"Game Over!\n"; break; }
        reveal(r,c);
    }
    return 0;
}
