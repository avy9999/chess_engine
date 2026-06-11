#include "../include/movegenerator.h"
#include "../include/utils.h"

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
                
                for (const auto& k : allKnightMoves){
                    // check board bounds and opponent pieces
                    if (k.first >= 0 && k.second >= 0 && k.first < 8 && k.second < 8){
                        char target = pos.board[k.first][k.second];
                        // add valid moves to vector
                        if (isEmptySquare(target) || isEnemyPiece(target, pos.sideToMove)){
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
                
                for (const auto& k : allKingMoves){
                    // check board bounds and opponent pieces
                    if (k.first >= 0 && k.second >= 0 && k.first < 8 && k.second < 8){
                        char target = pos.board[k.first][k.second];
                        // add valid moves to vector
                        if (isEmptySquare(target) || isEnemyPiece(target, pos.sideToMove)){
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
                    if (isEnemyPiece(target, pos.sideToMove)){
                        moves.emplace_back(Move(i, j, i+1, j-1));
                    }
                }
                if (i+1 < 8 && j+1 < 8){
                    char target = pos.board[i+1][j+1];
                    if (isEnemyPiece(target, pos.sideToMove)){
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
                    if (isEnemyPiece(target, pos.sideToMove)){
                        moves.emplace_back(Move(i, j, i-1, j-1));
                    }
                }
                if (i-1 >= 0 && j+1 < 8){
                    char target = pos.board[i-1][j+1];
                    if (isEnemyPiece(target, pos.sideToMove)){
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
                // move determination where bishop can slide over
                std::vector<std::pair<int, int>> movements = {
                    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
                };

                // now loop through every diagonal bishop can go until blocked or out of board 
                for (const auto& k : movements){
                    int m = i + k.first;
                    int n = j + k.second;
                    while(m >= 0 && m < 8 && n >= 0 && n < 8){
                        char target = pos.board[m][n];
                        if (isEmptySquare(target)){
                            moves.emplace_back(Move(i, j, m, n));
                        } else if (isEnemyPiece(target, pos.sideToMove)) {
                            moves.emplace_back(Move(i, j, m, n));
                            break;
                        } else{
                            break;
                        }
                        m += k.first;
                        n += k.second;
                    }
                }
            }
        }
    }
    return moves;
}

std::vector<Move> MoveGenerator::generateRookMoves(const Position& pos){
    std::vector<Move> moves;

    for(int i=0; i<8; ++i){
        for(int j=0; j<8; ++j){
            // checks if the square has a rook
            if ((pos.board[i][j] == 'r' && pos.sideToMove == 'b') || (pos.board[i][j] == 'R' && pos.sideToMove == 'w')){
                // move determination where rook can slide over
                std::vector<std::pair<int, int>> movements = {
                    {-1, 0}, {0, 1}, {1, 0}, {0, -1}
                };

                // now loop through particular row & column until blocked or out of board
                for (const auto& k : movements){
                    int m = i + k.first;
                    int n = j + k.second;
                    while(m >= 0 && m < 8 && n >= 0 && n < 8){
                        char target = pos.board[m][n];
                        if (isEmptySquare(target)){
                            moves.emplace_back(Move(i, j, m, n));
                        } else if (isEnemyPiece(target, pos.sideToMove)) {
                            moves.emplace_back(Move(i, j, m, n));
                            break;
                        } else{
                            break;
                        }
                        m += k.first;
                        n += k.second;
                    }
                }
            }
        }
    }
    return moves;
}

std::vector<Move> MoveGenerator::generateQueenMoves(const Position& pos){
    std::vector<Move> moves;

    for(int i=0; i<8; ++i){
        for(int j=0; j<8; ++j){
            // checks if the square has a queen
            if ((pos.board[i][j] == 'q' && pos.sideToMove == 'b') || (pos.board[i][j] == 'Q' && pos.sideToMove == 'w')){
                // move determination where queen can slide over
                std::vector<std::pair<int, int>> movements = {
                    {-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
                };

                // now loop through particular row, column & diagonals until blocked or out of board
                for (const auto& k : movements){
                    int m = i + k.first;
                    int n = j + k.second;
                    while(m >= 0 && m < 8 && n >= 0 && n < 8){
                        char target = pos.board[m][n];
                        if (isEmptySquare(target)){
                            moves.emplace_back(Move(i, j, m, n));
                        } else if (isEnemyPiece(target, pos.sideToMove)) {
                            moves.emplace_back(Move(i, j, m, n));
                            break;
                        } else{
                            break;
                        }
                        m += k.first;
                        n += k.second;
                    }
                }
            }
        }
    }
    return moves;
}

// generate all possible moves
std::vector<Move> MoveGenerator::generateAllMoves(const Position& pos){
    std::vector<Move> moves;
    
    std::vector<Move> knightMoves = generateKnightMoves(pos);
    std::vector<Move> pawnMoves = generatePawnMoves(pos);
    std::vector<Move> kingMoves = generateKingMoves(pos);
    std::vector<Move> bishopMoves = generateBishopMoves(pos);
    std::vector<Move> rookMoves = generateRookMoves(pos);
    std::vector<Move> queenMoves = generateQueenMoves(pos);

    moves.insert(moves.end(), knightMoves.begin(), knightMoves.end());
    moves.insert(moves.end(), pawnMoves.begin(), pawnMoves.end());
    moves.insert(moves.end(), kingMoves.begin(), kingMoves.end());
    moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());
    moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());
    moves.insert(moves.end(), queenMoves.begin(), queenMoves.end());

    return moves;
}

void MoveGenerator::makeMove(Position& pos, const Move& move){
    
    // this makes a move on the board
    char piece = pos.board[move.fromRow][move.fromCol];

    pos.board[move.toRow][move.toCol] = piece;
    pos.board[move.fromRow][move.fromCol] = '.';

    pos.sideToMove = (pos.sideToMove == 'w') ? 'b':'w';
}

// this checks if any function attacks the square
bool MoveGenerator::isSquareAttacked(
    const Position& pos,
    int row,
    int col,
    char attackingSide
){
    return
        checkPawnAttack(pos, row, col, attackingSide) ||
        checkKnightAttack(pos, row, col, attackingSide) ||
        checkKingAttack(pos, row, col, attackingSide) ||
        checkDiagonalAttack(pos, row, col, attackingSide) ||
        checkStraightAttack(pos, row, col, attackingSide);
}

// checking if pawn attacks the square
bool MoveGenerator::checkPawnAttack(const Position& pos, int row, int col, char attackingSide){
    int pawnDir = attackingSide == 'w' ? 1 : -1;
    char pawn = attackingSide =='w' ? 'P' : 'p';
    if (row+pawnDir >= 0 && row+pawnDir<8 && col-1>=0 && pos.board[row+pawnDir][col-1] == pawn){
            return true;
    }
    if (row+pawnDir >= 0 && row+pawnDir<8 && col+1<8 && pos.board[row+pawnDir][col+1]==pawn){
        return true;
    }
    return false;
}

// checking if knight attacks the square
bool MoveGenerator::checkKnightAttack(const Position& pos, int row, int col, char attackingSide){
    std::vector<std::pair<int, int>> knightMoves = {
        {-1, -2}, {1, -2}, {-1, 2}, {1, 2}, {-2, -1}, {-2, 1}, {2, -1}, {2, 1}   
    };

    char knight = attackingSide == 'w' ? 'N' : 'n';
    
    for (const auto& k : knightMoves){
        if (row+k.first >= 0 && row+k.first<8 && col+k.second>=0 && col+k.second<8 && pos.board[row+k.first][col+k.second] == knight){
            return true;
        }
    }
    return false;
}

// checking if king attacks the square
bool MoveGenerator::checkKingAttack(const Position& pos, int row, int col, char attackingSide){
    std::vector<std::pair<int, int>> kingMoves = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
    };
    
    char king = attackingSide == 'w' ? 'K' : 'k';

    for (const auto& k : kingMoves){
        if (row+k.first >= 0 && row+k.first<8 && col+k.second>=0 && col+k.second<8 && pos.board[row+k.first][col+k.second] == king){
            return true;
        }
    }
    return false;
}

// checking if bishop or queen attacks the diagonal squares
bool MoveGenerator::checkDiagonalAttack(const Position& pos, int row, int col, char attackingSide){
    std::vector<std::pair<int, int>> diagonalMoves = {
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    }; 

    char bishop = attackingSide == 'w' ? 'B' : 'b';
    char queen = attackingSide == 'w' ? 'Q' : 'q';

    for (const auto& k : diagonalMoves){
        int i = row;
        int j = col;
        while (i+k.first >= 0 && i+k.first<8 && j+k.second>=0 && j+k.second<8){
            if (pos.board[i+k.first][j+k.second]==bishop || pos.board[i+k.first][j+k.second]==queen){
                return true;
            } else if (pos.board[i+k.first][j+k.second] == '.'){
                i+=k.first;
                j+=k.second;
            } else{
                break;
            }
        }
    }
    return false;
}

bool MoveGenerator::checkStraightAttack(const Position& pos, int row, int col, char attackingSide){
    std::vector<std::pair<int, int>> axesMoves = {
        {-1, 0}, {0, 1}, {1, 0}, {0, -1}
    };

    char rook = attackingSide == 'w' ? 'R' : 'r';
    char queen = attackingSide == 'w' ? 'Q' : 'q';

    for (const auto& k : axesMoves){
        int i = row;
        int j = col;
        while (i+k.first >= 0 && i+k.first<8 && j+k.second>=0 && j+k.second<8){
            if (pos.board[i+k.first][j+k.second]==rook || pos.board[i+k.first][j+k.second]==queen){
                return true;
            } else if (pos.board[i+k.first][j+k.second] == '.'){
                i+=k.first;
                j+=k.second;
            } else{
                break;
            }
        }
    }
    return false;
}