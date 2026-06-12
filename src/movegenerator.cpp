#include "../include/movegenerator.h"
#include "../include/utils.h"

std::vector<Move> MoveGenerator::generateKnightMoves(const Position& pos) {
    std::vector<Move> moves;

    // this loops over all squares
    for(int i=0; i<8; ++i){
        for(int j=0; j<8; ++j){
            // checks if square has knight of pos.sideToMove
            if (isFriendlyPiece(pos.board[i][j], pos.sideToMove) && isPieceType(pos.board[i][j], 'n')){
                // generate all 8 possible knight moves
                std::vector <std:: pair <int, int>> allKnightMoves = {
                    {i-1, j-2}, {i+1, j-2}, {i-1, j+2}, {i+1, j+2}, {i-2, j-1}, {i-2, j+1}, {i+2, j-1}, {i+2, j+1}
                };
                
                for (const auto& k : allKnightMoves){
                    // check board bounds and opponent pieces
                    if (isInsideBoard(k.first, k.second)){
                        char target = pos.board[k.first][k.second];
                        // add valid moves to vector
                        if (isEmptySquare(target) || isEnemyPiece(target, pos.sideToMove)){
                            moves.push_back(Move(i, j, k.first, k.second));
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
            if (isFriendlyPiece(pos.board[i][j], pos.sideToMove) && isPieceType(pos.board[i][j], 'k')){
                // generate all 8 possible king moves
                std::vector <std:: pair <int, int>> allKingMoves = {
                    {i-1, j-1}, {i-1, j}, {i-1, j+1}, {i, j-1}, {i, j+1}, {i+1, j-1}, {i+1, j}, {i+1, j+1}
                };
                
                for (const auto& k : allKingMoves){
                    // check board bounds and opponent pieces
                    if (isInsideBoard(k.first, k.second)){
                        char target = pos.board[k.first][k.second];
                        // add valid moves to vector
                        if (isEmptySquare(target) || isEnemyPiece(target, pos.sideToMove)){
                            moves.push_back(Move(i, j, k.first, k.second));
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

    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){

            if (isFriendlyPiece(pos.board[i][j], pos.sideToMove) &&
                isPieceType(pos.board[i][j], 'p'))
            {
                int direction = (pos.sideToMove == 'w') ? -1 : 1;
                int startRow  = (pos.sideToMove == 'w') ? 6 : 1;

                // single push
                if (isInsideBoard(i + direction, j) &&
                    isEmptySquare(pos.board[i + direction][j]))
                {
                    moves.push_back(
                        Move(i, j,
                             i + direction, j)
                    );
                }

                // double push
                if (i == startRow &&
                    isEmptySquare(pos.board[i + direction][j]) &&
                    isEmptySquare(pos.board[i + 2 * direction][j]))
                {
                    moves.push_back(
                        Move(i, j,
                             i + 2 * direction, j)
                    );
                }

                // capture left
                if (isInsideBoard(i + direction, j - 1))
                {
                    char target =
                        pos.board[i + direction][j - 1];

                    if (isEnemyPiece(target, pos.sideToMove))
                    {
                        moves.push_back(
                            Move(i, j,
                                 i + direction,
                                 j - 1)
                        );
                    }
                }

                // capture right
                if (isInsideBoard(i + direction, j + 1))
                {
                    char target =
                        pos.board[i + direction][j + 1];

                    if (isEnemyPiece(target, pos.sideToMove))
                    {
                        moves.push_back(
                            Move(i, j,
                                 i + direction,
                                 j + 1)
                        );
                    }
                }
            }
        }
    }

    return moves;
}

std::vector<Move> MoveGenerator::generateBishopMoves(const Position& pos){

    static const std::vector<std::pair<int,int>> directions = {
        {-1,-1},
        {-1, 1},
        { 1,-1},
        { 1, 1}
    };

    return generateSlidingMoves(pos, 'b', directions);
}

std::vector<Move> MoveGenerator::generateRookMoves(const Position& pos){

    static const std::vector<std::pair<int,int>> directions = {
        {-1,0},
        {0,1},
        {1,0},
        {0,-1}
    };

    return generateSlidingMoves(pos, 'r', directions);
}

std::vector<Move> MoveGenerator::generateQueenMoves(const Position& pos){

    static const std::vector<std::pair<int,int>> directions = {
        {-1,0},
        {0,1},
        {1,0},
        {0,-1},
        {-1,-1},
        {-1,1},
        {1,-1},
        {1,1}
    };

    return generateSlidingMoves(pos, 'q', directions);
}

// helper function for generating sliding moves
std::vector<Move> MoveGenerator::generateSlidingMoves(const Position& pos, char pieceType, const std::vector<std::pair<int,int>>& directions){
    std::vector<Move> moves;

    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){

            if (isFriendlyPiece(pos.board[i][j], pos.sideToMove) &&
                isPieceType(pos.board[i][j], pieceType))
            {
                for(const auto& dir : directions){

                    int m = i + dir.first;
                    int n = j + dir.second;

                    while(isInsideBoard(m, n)){

                        char target = pos.board[m][n];

                        if(isEmptySquare(target)){
                            moves.push_back(Move(i, j, m, n));
                        }
                        else if(isEnemyPiece(target, pos.sideToMove)){
                            moves.push_back(Move(i, j, m, n));
                            break;
                        }
                        else{
                            break;
                        }

                        m += dir.first;
                        n += dir.second;
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
        if (isInsideBoard(row+k.first, col+k.second) && pos.board[row+k.first][col+k.second] == knight){
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
        if (isInsideBoard(row+k.first, col+k.second) && pos.board[row+k.first][col+k.second] == king){
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
        while (isInsideBoard(i+k.first, j+k.second)){
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
        while (isInsideBoard(i+k.first, j+k.second)){
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

// this function checks if the king is in check or not
bool MoveGenerator::isKingInCheck(const Position& pos, char side){

    // determine attacking side
    char attackingSide = side == 'b' ? 'w' : 'b';

    for(int i=0; i<8; ++i){
        for(int j=0; j<8; ++j){
            // checks if square has king of side
            if (isFriendlyPiece(pos.board[i][j], side) && isPieceType(pos.board[i][j], 'k')) {
                return isSquareAttacked(pos, i, j, attackingSide);
            }
        }
    }

    return false;
}

// generate all legal moves
std::vector<Move> MoveGenerator::generateLegalMoves(const Position& pos){
    std::vector<Move> legalMoves;

    // this generate all possible moves from the current position
    auto moves = generateAllMoves(pos);

    for (const auto& move : moves){
        // create a copy of current position
        Position copy = pos;

        // make a move on the copy position
        makeMove(copy, move);

        if (!isKingInCheck(copy, pos.sideToMove)){
            legalMoves.push_back(move);
        }
    }

    return legalMoves;
}