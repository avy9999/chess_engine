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
                std::vector <std:: pair <int, int>> normalKingMoves = {
                    {i-1, j-1}, {i-1, j}, {i-1, j+1}, {i, j-1}, {i, j+1}, {i+1, j-1}, {i+1, j}, {i+1, j+1}
                };
                
                for (const auto& k : normalKingMoves){
                    // check board bounds and opponent pieces
                    if (isInsideBoard(k.first, k.second)){
                        char target = pos.board[k.first][k.second];
                        // add valid moves to vector
                        if (isEmptySquare(target) || isEnemyPiece(target, pos.sideToMove)){
                            moves.push_back(Move(i, j, k.first, k.second));
                        }
                    }      
                }
                // castle moves
                bool kingInCheck = isKingInCheck(pos, pos.sideToMove);
                if (pos.sideToMove == 'w'){
                    // kingside castle
                    if (pos.castlingRights[0] 
                        && pos.board[7][5] == '.' 
                        && pos.board[7][6] == '.' 
                        && !kingInCheck
                        && !isSquareAttacked(pos, 7, 5, 'b') 
                        && !isSquareAttacked(pos, 7, 6, 'b')
                        && pos.board[7][7] == 'R'){
                            moves.emplace_back(Move(i, j, i, j+2));
                    }
                    // queenside castle
                    if (pos.castlingRights[1] 
                        && pos.board[7][1] == '.' 
                        && pos.board[7][2] == '.' 
                        && pos.board[7][3] == '.' 
                        && !kingInCheck
                        && !isSquareAttacked(pos, 7, 2, 'b') 
                        && !isSquareAttacked(pos, 7, 3, 'b')
                        && pos.board[7][0] == 'R'){
                            moves.emplace_back(Move(i, j, i, j-2));
                    }
                } else {
                    // kingside castle
                    if (pos.castlingRights[2] 
                        && pos.board[0][5] == '.' 
                        && pos.board[0][6] == '.' 
                        && !kingInCheck
                        && !isSquareAttacked(pos, 0, 5, 'w') 
                        && !isSquareAttacked(pos, 0, 6, 'w')
                        && pos.board[0][7] == 'r'){
                            moves.emplace_back(Move(i, j, i, j+2));
                    }
                    // queenside castle
                    if (pos.castlingRights[3] 
                        && pos.board[0][1] == '.' 
                        && pos.board[0][2] == '.' 
                        && pos.board[0][3] == '.' 
                        && !kingInCheck
                        && !isSquareAttacked(pos, 0, 2, 'w') 
                        && !isSquareAttacked(pos, 0, 3, 'w')
                        && pos.board[0][0] == 'r'){
                            moves.emplace_back(Move(i, j, i, j-2));
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

                    // normal capture
                    if (isEnemyPiece(target, pos.sideToMove))
                    {
                        moves.push_back(
                            Move(i, j,
                                 i + direction,
                                 j - 1)
                        );
                    }
                    
                    // en passant capture
                    if (i + direction == pos.enPassantRow &&
                        j - 1 == pos.enPassantCol)
                    {
                        Move move(i, j,
                                i + direction,
                                j - 1);

                        move.isEnPassant = true;

                        moves.push_back(move);
                    }
                }

                // capture right
                if (isInsideBoard(i + direction, j + 1))
                {
                    char target =
                        pos.board[i + direction][j + 1];

                    // normal capture
                    if (isEnemyPiece(target, pos.sideToMove))
                    {
                        moves.push_back(
                            Move(i, j,
                                 i + direction,
                                 j + 1)
                        );
                    }
                    
                    // en passant capture
                    if (i + direction == pos.enPassantRow &&
                        j + 1 == pos.enPassantCol)
                    {
                        Move move(i, j,
                                i + direction,
                                j + 1);

                        move.isEnPassant = true;

                        moves.push_back(move);
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
    
    // clearing en passant squares
    pos.enPassantRow = -1;
    pos.enPassantCol = -1;

    // this makes a move on the board
    char piece = pos.board[move.fromRow][move.fromCol];

    // determine pawn, king and rook
    char king = pos.sideToMove == 'w' ? 'K' : 'k';
    char rook = pos.sideToMove == 'w' ? 'R' : 'r';
    char pawn = pos.sideToMove == 'w' ? 'P' : 'p';

    // determine captured piece
    char captured = pos.board[move.toRow][move.toCol];

    // white rook captured so disable white castling rights
    if (captured == 'R') {
        if (move.toRow == 7 && move.toCol == 0)
            pos.castlingRights[1] = false;

        if (move.toRow == 7 && move.toCol == 7)
            pos.castlingRights[0] = false;
    }

    // black rook captured so disable black castling rights
    if (captured == 'r') {
        if (move.toRow == 0 && move.toCol == 0)
            pos.castlingRights[3] = false;

        if (move.toRow == 0 && move.toCol == 7)
            pos.castlingRights[2] = false;
    }
    

    if (piece == king){
        // check if its a castle move
        if (isCastleMove(move)){
            pos.board[move.toRow][move.toCol] = king;
            pos.board[move.fromRow][move.fromCol] = '.';
            // updates castle rights
            if (pos.sideToMove == 'w'){
                pos.castlingRights[0] = false;
                pos.castlingRights[1] = false;
            }
            else{
                pos.castlingRights[2] = false;
                pos.castlingRights[3] = false;
            }
            // move rook according to the castle type
            if (move.toCol == 2){
                pos.board[move.toRow][3] = rook;
                pos.board[move.fromRow][0] = '.';
            } else{
                pos.board[move.toRow][5] = rook;
                pos.board[move.fromRow][7] = '.';
            }
        }
        else{
            // normal king moves
            pos.board[move.toRow][move.toCol] = piece;
            pos.board[move.fromRow][move.fromCol] = '.';
            // updates castle rights as king is displaced from his position
            if (pos.sideToMove == 'w'){
                pos.castlingRights[0] = false;
                pos.castlingRights[1] = false;
            }
            else{
                pos.castlingRights[2] = false;
                pos.castlingRights[3] = false;
            }
        }
    } else if (piece == rook){
        // normal rook moves but also updates castle rights as it displaced
        pos.board[move.toRow][move.toCol] = piece;
        pos.board[move.fromRow][move.fromCol] = '.';
        if (pos.sideToMove == 'w') {
            if (move.fromRow == 7 && move.fromCol == 7)
                pos.castlingRights[0] = false; // K

            if (move.fromRow == 7 && move.fromCol == 0)
                pos.castlingRights[1] = false; // Q
        }
        else {
            if (move.fromRow == 0 && move.fromCol == 7)
                pos.castlingRights[2] = false; // k

            if (move.fromRow == 0 && move.fromCol == 0)
                pos.castlingRights[3] = false; // q
        }
    } else if (piece == pawn){
        if (move.isEnPassant){
            pos.board[move.toRow][move.toCol] = piece;
            pos.board[move.fromRow][move.fromCol] = '.';

            int capturedPawnRow =
                (pos.sideToMove == 'w')
                ? move.toRow + 1
                : move.toRow - 1;

            pos.board[capturedPawnRow][move.toCol] = '.';
        } else if (abs(move.fromRow-move.toRow) == 2){
            // double forward pawn move
            pos.enPassantRow = (move.fromRow + move.toRow) / 2;
            pos.enPassantCol = move.fromCol;
            pos.board[move.toRow][move.toCol] = piece;
            pos.board[move.fromRow][move.fromCol] = '.';
        } else{
            // normal pawn moves
            pos.board[move.toRow][move.toCol] = piece;
            pos.board[move.fromRow][move.fromCol] = '.';
        }
    } else{
        // normal moves
        pos.board[move.toRow][move.toCol] = piece;
        pos.board[move.fromRow][move.fromCol] = '.';
    }

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

// detects if it is a checkmate
bool MoveGenerator::isCheckmate(const Position& pos){
    return isKingInCheck(pos, pos.sideToMove) && generateLegalMoves(pos).empty();
}

// detects if it is a stalemate
bool MoveGenerator::isStalemate(const Position& pos){
    return !isKingInCheck(pos, pos.sideToMove) && generateLegalMoves(pos).empty();
}