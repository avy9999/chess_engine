#include <iostream>
#include "../include/position.h"
#include <string>
#include <ranges>
#include <string_view>

using namespace std;

// this initialises a chess board with initial position and rules
Position::Position(){
    initializeBoard();
    sideToMove = 'w';
    castlingRights[0] = castlingRights[1] = castlingRights[2] = castlingRights[3] = true;
    enPassantRow = -1;
    enPassantCol = -1;
    halfMoveClock = 0;
    fullMoveNumber = 0;
}

// function to put . in each cell of the board
void Position::initializeBoard(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            board[i][j] = '.';
        }
    }
}

// it prints the current board positions
void Position::printBoard(){
    int index = 8;
    for (int i = 0; i < 8; i++){
        cout << index-- << " ";
        for (int j = 0; j < 8; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "  ";
    for (char i = 'a'; i < 'i'; i++){
        cout << i << " ";
    }
}

// this function loads a FEN string and initialises a board according to it which includes positions, castling rights, en passant, half time and full move
void Position::loadFEN(const std::string& fen){
    
    initializeBoard();
    int index = 0;

    // this places chess pieces positions on the board
    for (int i = 0; i < 8 && fen[index] != ' '; i++){
        int j = 0;
        while(fen[index]!='/' && fen[index]!=' '){
            if (isdigit(fen[index])){
                j+=fen[index]-'0';
            }
            else{
                board[i][j]=fen[index];
                j++;
            }
            index++;
        }
        if(fen[index]=='/') index++;
    }

    index++;

    // which side to move
    sideToMove = fen[index];
    index+=2;

    // castling rights
    castlingRights[0] = castlingRights[1] = castlingRights[2] = castlingRights[3] = false;
    if (fen[index]!='-'){
        while (fen[index]!=' '){
            if(fen[index]=='K') castlingRights[0] = true;
            if(fen[index]=='Q') castlingRights[1] = true;
            if(fen[index]=='k') castlingRights[2] = true;
            if(fen[index]=='q') castlingRights[3] = true;
            index++;
        }
    }
    else{
        index++;
    }
    index++;

    // en passant if there is any
    if (fen[index]!='-'){
        enPassantCol = fen[index] - 'a';
        index++;
        enPassantRow = 8 - (fen[index] - '0');
        index++;
    }
    else{
        enPassantCol = -1;
        enPassantRow = -1;
        index++;
    }
    index++;

    // half move
    int half = 0;
    while(fen[index]!=' '){
        half = 10 * half + (fen[index] - '0');
        index++;
    }
    halfMoveClock = half;
    index++;

    // full move
    int full = 0;
    while(index<fen.size()){
        full = 10 * full + (fen[index] - '0');
        index++;
    }
    fullMoveNumber = full;
}