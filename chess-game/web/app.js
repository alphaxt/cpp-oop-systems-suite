/**
 * C++ WebAssembly Chess Engine - Frontend Controller
 * Connects browser click events to either:
 * 1. The compiled C++17 WebAssembly binary (via Module._makeMove)
 * 2. Or the fallback client rules engine (if WASM is not yet compiled)
 */

const PIECE_SYMBOLS = {
  'wK': '♔', 'wQ': '♕', 'wR': '♖', 'wB': '♗', 'wN': '♘', 'wP': '♙',
  'bK': '♚', 'bQ': '♛', 'bR': '♜', 'bB': '♝', 'bN': '♞', 'bP': '♟'
};

const FILES = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'];

// State
let isWasmActive = false;
let whiteTurn = true;
let selectedSquare = null;
let lastMove = null;
let moveHistory = [];
let capturedByWhite = [];
let capturedByBlack = [];
let isFlipped = false;

// Fallback Board State (8x8) mirroring C++ Board.cpp
let jsBoard = Array(8).fill(null).map(() => Array(8).fill(null));

function initJsBoard() {
  jsBoard = Array(8).fill(null).map(() => Array(8).fill(null));
  
  // Pawns
  for (let x = 0; x < 8; x++) {
    jsBoard[1][x] = 'wP';
    jsBoard[6][x] = 'bP';
  }
  // Rooks
  jsBoard[0][0] = 'wR'; jsBoard[0][7] = 'wR';
  jsBoard[7][0] = 'bR'; jsBoard[7][7] = 'bR';
  // Knights
  jsBoard[0][1] = 'wN'; jsBoard[0][6] = 'wN';
  jsBoard[7][1] = 'bN'; jsBoard[7][6] = 'bN';
  // Bishops
  jsBoard[0][2] = 'wB'; jsBoard[0][5] = 'wB';
  jsBoard[7][2] = 'bB'; jsBoard[7][5] = 'bB';
  // Queens
  jsBoard[0][3] = 'wQ';
  jsBoard[7][3] = 'bQ';
  // Kings
  jsBoard[0][4] = 'wK';
  jsBoard[7][4] = 'bK';
}

// Check if C++ WebAssembly module is loaded
function checkEngineMode() {
  if (typeof Module !== 'undefined' && Module._makeMove && Module._getPieceAt) {
    isWasmActive = true;
    Module._initGame();
    document.getElementById('engine-badge').innerHTML = 
      `<span class="status-dot"></span> ⚡ WebAssembly (C++17 Engine Active)`;
    document.getElementById('engine-mode-note').textContent = 
      "Direct execution via compiled C++17 binary in WebAssembly";
  } else {
    isWasmActive = false;
    initJsBoard();
    document.getElementById('engine-badge').innerHTML = 
      `<span class="status-dot" style="background: #3b82f6; box-shadow: 0 0 10px #3b82f6;"></span> 🟢 Browser Mode (Ready for WASM compilation)`;
    document.getElementById('engine-mode-note').textContent = 
      "Simulating C++ Board rules (Compile with emcc to switch to WASM)";
  }
}

// Get piece on square
function getPiece(x, y) {
  if (isWasmActive) {
    const ptr = Module._getPieceAt(x, y);
    return Module.UTF8ToString ? Module.UTF8ToString(ptr) : "";
  } else {
    return jsBoard[y][x] || "";
  }
}

// Execute move through C++ WASM or fallback
function executeMove(fromX, fromY, toX, toY) {
  if (isWasmActive) {
    const res = Module._makeMove(fromX, fromY, toX, toY);
    if (res === 1) {
      whiteTurn = Module._isWhiteTurn() === 1;
      return true;
    }
    return false;
  } else {
    // JavaScript fallback rules (exact C++ Piece logic)
    const piece = jsBoard[fromY][fromX];
    if (!piece) return false;
    const isPieceWhite = piece.startsWith('w');
    if (isPieceWhite !== whiteTurn) return false;

    const target = jsBoard[toY][toX];
    if (target && target.startsWith(isPieceWhite ? 'w' : 'b')) return false;

    // Movement validation
    if (!validateMove(piece, fromX, fromY, toX, toY)) return false;

    // Capture
    if (target) {
      if (target.startsWith('b')) capturedByWhite.push(target);
      else capturedByBlack.push(target);
    }

    jsBoard[toY][toX] = piece;
    jsBoard[fromY][fromX] = null;
    whiteTurn = !whiteTurn;
    return true;
  }
}

// C++ Rule Mirror for Browser Fallback
function validateMove(piece, sx, sy, ex, ey) {
  const type = piece[1];
  const isWhite = piece[0] === 'w';
  const dx = ex - sx;
  const dy = ey - sy;
  const adx = Math.abs(dx);
  const ady = Math.abs(dy);

  switch (type) {
    case 'P': { // Pawn
      const dir = isWhite ? 1 : -1;
      const startRank = isWhite ? 1 : 6;
      // Single step forward
      if (dx === 0 && dy === dir && !jsBoard[ey][ex]) return true;
      // Double step from start
      if (dx === 0 && sy === startRank && dy === 2 * dir && !jsBoard[sy + dir][sx] && !jsBoard[ey][ex]) return true;
      // Diagonal capture
      if (adx === 1 && dy === dir && jsBoard[ey][ex]) return true;
      return false;
    }
    case 'R': { // Rook
      if (dx !== 0 && dy !== 0) return false;
      const stepX = dx === 0 ? 0 : (dx > 0 ? 1 : -1);
      const stepY = dy === 0 ? 0 : (dy > 0 ? 1 : -1);
      let cx = sx + stepX, cy = sy + stepY;
      while (cx !== ex || cy !== ey) {
        if (jsBoard[cy][cx]) return false;
        cx += stepX; cy += stepY;
      }
      return true;
    }
    case 'N': { // Knight
      return (adx === 1 && ady === 2) || (adx === 2 && ady === 1);
    }
    case 'B': { // Bishop
      if (adx !== ady) return false;
      const stepX = dx > 0 ? 1 : -1;
      const stepY = dy > 0 ? 1 : -1;
      let cx = sx + stepX, cy = sy + stepY;
      while (cx !== ex || cy !== ey) {
        if (jsBoard[cy][cx]) return false;
        cx += stepX; cy += stepY;
      }
      return true;
    }
    case 'Q': { // Queen (Rook + Bishop)
      return validateMove(isWhite ? 'wR' : 'bR', sx, sy, ex, ey) ||
             validateMove(isWhite ? 'wB' : 'bB', sx, sy, ex, ey);
    }
    case 'K': { // King
      return adx <= 1 && ady <= 1 && (adx !== 0 || ady !== 0);
    }
    default:
      return false;
  }
}

// Render 64 squares into DOM
function renderBoard() {
  const boardEl = document.getElementById('chessboard');
  boardEl.innerHTML = '';

  const rankIndices = isFlipped ? [0, 1, 2, 3, 4, 5, 6, 7] : [7, 6, 5, 4, 3, 2, 1, 0];
  const fileIndices = isFlipped ? [7, 6, 5, 4, 3, 2, 1, 0] : [0, 1, 2, 3, 4, 5, 6, 7];

  rankIndices.forEach(y => {
    fileIndices.forEach(x => {
      const isLight = (x + y) % 2 !== 0;
      const square = document.createElement('div');
      square.className = `square ${isLight ? 'light' : 'dark'}`;
      square.dataset.x = x;
      square.dataset.y = y;

      // Last move highlight
      if (lastMove && ((lastMove.fromX === x && lastMove.fromY === y) || 
                       (lastMove.toX === x && lastMove.toY === y))) {
        square.classList.add('last-move');
      }

      // Selected highlight
      if (selectedSquare && selectedSquare.x === x && selectedSquare.y === y) {
        square.classList.add('selected');
      }

      // Coordinate numbers
      if ((isFlipped && x === 7) || (!isFlipped && x === 0)) {
        const rankLabel = document.createElement('span');
        rankLabel.className = 'square-coord-rank';
        rankLabel.textContent = y + 1;
        square.appendChild(rankLabel);
      }
      if ((isFlipped && y === 7) || (!isFlipped && y === 0)) {
        const fileLabel = document.createElement('span');
        fileLabel.className = 'square-coord-file';
        fileLabel.textContent = FILES[x];
        square.appendChild(fileLabel);
      }

      // Piece display
      const pieceStr = getPiece(x, y);
      if (pieceStr) {
        const pieceEl = document.createElement('div');
        pieceEl.className = `piece ${pieceStr[0] === 'w' ? 'white' : 'black'}`;
        pieceEl.textContent = PIECE_SYMBOLS[pieceStr] || pieceStr[1];
        square.appendChild(pieceEl);
      }

      // Valid move indicator dot
      if (selectedSquare && selectedSquare.validMoves) {
        const isValid = selectedSquare.validMoves.some(m => m.x === x && m.y === y);
        if (isValid) {
          const dot = document.createElement('div');
          dot.className = 'valid-dot';
          square.appendChild(dot);
        }
      }

      square.addEventListener('click', () => handleSquareClick(x, y));
      boardEl.appendChild(square);
    });
  });

  // Turn badge
  const turnBadge = document.getElementById('turn-badge');
  turnBadge.textContent = whiteTurn ? "⚪ White's Turn" : "⚫ Black's Turn";
  turnBadge.style.color = whiteTurn ? "#f8fafc" : "#94a3b8";

  // Captured pieces
  document.getElementById('graveyard-white').textContent = capturedByBlack.map(p => PIECE_SYMBOLS[p]).join(' ');
  document.getElementById('graveyard-black').textContent = capturedByWhite.map(p => PIECE_SYMBOLS[p]).join(' ');
}

// User Square Click
function handleSquareClick(x, y) {
  hideToast();
  const clickedPiece = getPiece(x, y);

  if (!selectedSquare) {
    // Click 1: Select a piece of current turn
    if (!clickedPiece) return;
    const isPieceWhite = clickedPiece[0] === 'w';
    if (isPieceWhite !== whiteTurn) {
      showToast(`It is ${whiteTurn ? "White's" : "Black's"} turn!`);
      return;
    }

    // Calculate valid moves to display guide dots
    const validMoves = [];
    for (let ty = 0; ty < 8; ty++) {
      for (let tx = 0; tx < 8; tx++) {
        if (isWasmActive) {
          // In WASM mode, test movement
          if (tx !== x || ty !== y) validMoves.push({ x: tx, y: ty });
        } else {
          if (validateMove(clickedPiece, x, y, tx, ty)) {
            const target = jsBoard[ty][tx];
            if (!target || target[0] !== clickedPiece[0]) {
              validMoves.push({ x: tx, y: ty });
            }
          }
        }
      }
    }

    selectedSquare = { x, y, piece: clickedPiece, validMoves };
    renderBoard();
  } else {
    // Click 2: If clicking own other piece, switch selection
    if (clickedPiece && (clickedPiece[0] === 'w') === whiteTurn) {
      selectedSquare = null;
      handleSquareClick(x, y);
      return;
    }

    // Attempt Move
    const fromX = selectedSquare.x;
    const fromY = selectedSquare.y;
    const piece = selectedSquare.piece;

    const moveSuccessful = executeMove(fromX, fromY, x, y);

    if (moveSuccessful) {
      lastMove = { fromX, fromY, toX: x, toY: y };
      recordMove(piece, fromX, fromY, x, y);
      selectedSquare = null;
      renderBoard();
    } else {
      showToast("Illegal Move for " + getPieceFullName(piece[1]));
      selectedSquare = null;
      renderBoard();
    }
  }
}

function getPieceFullName(char) {
  const map = { 'P': 'Pawn', 'R': 'Rook', 'N': 'Knight', 'B': 'Bishop', 'Q': 'Queen', 'K': 'King' };
  return map[char] || 'Piece';
}

function recordMove(piece, fx, fy, tx, ty) {
  const notation = `${piece[1] !== 'P' ? piece[1] : ''}${FILES[fx]}${fy + 1} → ${FILES[tx]}${ty + 1}`;
  
  if (piece[0] === 'w') {
    moveHistory.push({ white: notation, black: '' });
  } else {
    if (moveHistory.length > 0) {
      moveHistory[moveHistory.length - 1].black = notation;
    } else {
      moveHistory.push({ white: '...', black: notation });
    }
  }

  updateMoveTable();
}

function updateMoveTable() {
  const tbody = document.getElementById('move-table-body');
  tbody.innerHTML = '';
  moveHistory.forEach((m, idx) => {
    const row = document.createElement('tr');
    row.innerHTML = `
      <td style="color: var(--text-muted);">${idx + 1}.</td>
      <td><strong>${m.white}</strong></td>
      <td><strong>${m.black || ''}</strong></td>
    `;
    tbody.appendChild(row);
  });
  
  const container = document.getElementById('move-history-container');
  container.scrollTop = container.scrollHeight;
}

function showToast(msg) {
  const toast = document.getElementById('engine-toast');
  toast.textContent = msg;
  toast.classList.add('active');
}

function hideToast() {
  const toast = document.getElementById('engine-toast');
  toast.classList.remove('active');
}

function resetGame() {
  selectedSquare = null;
  lastMove = null;
  moveHistory = [];
  capturedByWhite = [];
  capturedByBlack = [];
  whiteTurn = true;
  hideToast();

  if (isWasmActive) {
    Module._initGame();
  } else {
    initJsBoard();
  }
  updateMoveTable();
  renderBoard();
}

function flipBoard() {
  isFlipped = !isFlipped;
  renderBoard();
}

// Bootstrap
window.addEventListener('DOMContentLoaded', () => {
  checkEngineMode();
  renderBoard();
});
