#include "../include/movegenerator.h"

std::vector<Move> MoveGenerator::generateKnightMoves(const Position& pos) {
    std::vector<Move> moves;

    // this loops over all squares
    for(int i=0; i<8; ++i){
        for(int j=0; j<8; ++j){
            // checks if square has knight of pos.sideToMove
            if ((pos.board[i][j] == 'n' && pos.sideToMove == 'b') || (pos.board[i][j] == 'N' && pos.sideToMove == 'w')){
                // generate all 8 possible knight moves
                std::vector <std:: pair <int, int>> allKnightMoves = {
                    {i-1, j-2}, {i+1, j-2}, {i-1, j+2}, {i+1, j+2}, {i-2, j-1}, {i-2, j+1}, {i+2, j-1}, {i+2, j+1}
                };
                
                for (auto k : allKnightMoves){
                    // check board bounds and opponent pieces
                    if (k.first >= 0 && k.second >= 0 && k.first < 8 && k.second < 8){
                        char target = pos.board[k.first][k.second];
                        // add valid moves to vector
                        if (target == '.' || (isupper(target) && pos.sideToMove == 'b') || (islower(target) && pos.sideToMove == 'w')){
                            moves.emplace_back(Move(i, j, k.first, k.second));
                        }
                    }      
                }
            }
        }
    }
    return moves;
}

std::vector<Move> MoveGenerator::generateKingMoves(const Position& pos){
    std::vector<Move> moves;
    
    for(int i=0; i<8; ++i){
        for(int j=0; j<8; ++j){
            // checks if square has king of pos.sideToMove
            if ((pos.board[i][j] == 'k' && pos.sideToMove == 'b') || (pos.board[i][j] == 'K' && pos.sideToMove == 'w')){
                // generate all 8 possible king moves
                std::vector <std:: pair <int, int>> allKingMoves = {
                    {i-1, j-1}, {i-1, j}, {i-1, j+1}, {i, j-1}, {i, j+1}, {i+1, j-1}, {i+1, j}, {i+1, j+1}
                };
                
                for (auto k : allKingMoves){
                    // check board bounds and opponent pieces
                    if (k.first >= 0 && k.second >= 0 && k.first < 8 && k.second < 8){
                        char target = pos.board[k.first][k.second];
                        // add valid moves to vector
                        if (target == '.' || (isupper(target) && pos.sideToMove == 'b') || (islower(target) && pos.sideToMove == 'w')){
                            moves.emplace_back(Move(i, j, k.first, k.second));
                        }
                    }      
                }
            }
        }
    }
    return moves;
}

std::vector<Move> MoveGenerator::generatePawnMoves(const Position& pos){
    std::vector<Move> moves;
    
    for(int i=0; i<8; ++i){
        for(int j=0; j<8; ++j){
            // checks if square has pawn of pos.sideToMove
            if (pos.board[i][j] == 'p' && pos.sideToMove == 'b'){
                // generate all possible pawn moves for black
                // single forward move
                if (i+1 < 8 && pos.board[i+1][j] == '.'){
                    moves.emplace_back(Move(i, j, i+1, j));
                }
                // double forward move only when pawn on its initial position
                if (i==1 && pos.board[3][j]=='.' && pos.board[2][j]=='.'){
                    moves.emplace_back(Move(i, j, i+2, j));
                }
                // capture moves
                if (i+1 < 8 && j-1 >= 0){
                    char target = pos.board[i+1][j-1];
                    if (isupper(target)){
                        moves.emplace_back(Move(i, j, i+1, j-1));
                    }
                }
                if (i+1 < 8 && j+1 < 8){
                    char target = pos.board[i+1][j+1];
                    if (isupper(target)){
                        moves.emplace_back(Move(i, j, i+1, j+1));
                    }
                }
            }
            if (pos.board[i][j] == 'P' && pos.sideToMove == 'w'){
                // generate all possible pawn moves for white
                // single forward move
                if (i-1 >=0 && pos.board[i-1][j] == '.'){
                    moves.emplace_back(Move(i, j, i-1, j));
                }
                // double forward move only when pawn on its initial position
                if (i==6 && pos.board[4][j]=='.' && pos.board[5][j]=='.'){
                    moves.emplace_back(Move(i, j, i-2, j));
                }
                // capture moves
                if (i-1 >= 0 && j-1 >= 0){
                    char target = pos.board[i-1][j-1];
                    if (islower(target)){
                        moves.emplace_back(Move(i, j, i-1, j-1));
                    }
                }
                if (i-1 >= 0 && j+1 < 8){
                    char target = pos.board[i-1][j+1];
                    if (islower(target)){
                        moves.emplace_back(Move(i, j, i-1, j+1));
                    }
                }
            }
        }
    }
    return moves;
}

std::vector<Move> MoveGenerator::generateBishopMoves(const Position& pos){
    std::vector<Move> moves;

    for(int i=0; i<8; ++i){
        for(int j=0; j<8; ++j){
            // checks if the square has a bishop
            if ((pos.board[i][j] == 'b' && pos.sideToMove == 'b') || (pos.board[i][j] == 'B' && pos.sideToMove == 'w')){
                int m = i;
                int n = j;
                while(m-1>=0 && n-1>=0){
                    char target = pos.board[m-1][n-1];
                    if (target == '.'){
                        moves.emplace_back(Move(i, j, m-1, n-1));
                    }
                    else if ((isupper(target) && pos.sideToMove=='b') || (islower(target) && pos.sideToMove == 'w')){
                        moves.emplace_back(Move(i, j, m-1, n-1));
                        break;
                    }
                    else{
                        break;
                    }
                    m--;
                    n--;
                }
                m = i;
                n = j;
                while(m-1>=0 && n+1<8){
                    char target = pos.board[m-1][n+1];
                    if (target == '.'){
                        moves.emplace_back(Move(i, j, m-1, n+1));
                    }
                    else if ((isupper(target) && pos.sideToMove=='b') || (islower(target) && pos.sideToMove == 'w')){
                        moves.emplace_back(Move(i, j, m-1, n+1));
                        break;
                    }
                    else{
                        break;
                    }
                    m--;
                    n++;
                }
                m = i;
                n = j;
                while(m+1<8 && n-1>=0){
                    char target = pos.board[m+1][n-1];
                    if (target == '.'){
                        moves.emplace_back(Move(i, j, m+1, n-1));
                    }
                    else if ((isupper(target) && pos.sideToMove=='b') || (islower(target) && pos.sideToMove == 'w')){
                        moves.emplace_back(Move(i, j, m+1, n-1));
                        break;
                    }
                    else{
                        break;
                    }
                    m++;
                    n--;
                }
                m = i;
                n = j;
                while(m+1<8 && n+1<8){
                    char target = pos.board[m+1][n+1];
                    if (target == '.'){
                        moves.emplace_back(Move(i, j, m+1, n+1));
                    }
                    else if ((isupper(target) && pos.sideToMove=='b') || (islower(target) && pos.sideToMove == 'w')){
                        moves.emplace_back(Move(i, j, m+1, n+1));
                        break;
                    }
                    else{
                        break;
                    }
                    m++;
                    n++;
                }
            }
        }
    }
    return moves;
}