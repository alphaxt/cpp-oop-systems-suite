#include "Board.h"
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

static Board* g_board = nullptr;
static bool g_whiteTurn = true;
static std::string g_pieceBuffer;

extern "C" {

EMSCRIPTEN_KEEPALIVE
void initGame() {
    if (g_board) {
        delete g_board;
    }
    g_board = new Board();
    g_whiteTurn = true;
}

EMSCRIPTEN_KEEPALIVE
int makeMove(int startX, int startY, int endX, int endY) {
    if (!g_board) {
        initGame();
    }
    
    // Validate bounds
    if (startX < 0 || startX > 7 || startY < 0 || startY > 7 ||
        endX < 0 || endX > 7 || endY < 0 || endY > 7) {
        return 0;
    }

    Piece* p = g_board->getPiece(startX, startY);
    if (!p) return 0;

    // Enforce turn: White can only move white pieces, Black can only move black pieces
    if (p->getColor() != g_whiteTurn) {
        return 0;
    }

    // Target square cannot contain own piece
    Piece* target = g_board->getPiece(endX, endY);
    if (target && target->getColor() == p->getColor()) {
        return 0;
    }

    bool success = g_board->movePiece(startX, startY, endX, endY);
    if (success) {
        g_whiteTurn = !g_whiteTurn; // Switch turn
        return 1;
    }
    return 0;
}

EMSCRIPTEN_KEEPALIVE
const char* getPieceAt(int x, int y) {
    if (!g_board) {
        initGame();
    }
    
    Piece* p = g_board->getPiece(x, y);
    if (!p) {
        return "";
    }

    // Format: "wP", "wR", "bK", "bQ", etc.
    g_pieceBuffer = (p->getColor() ? "w" : "b") + p->getName();
    return g_pieceBuffer.c_str();
}

EMSCRIPTEN_KEEPALIVE
int isWhiteTurn() {
    return g_whiteTurn ? 1 : 0;
}

}
