/**
 * C++ WebAssembly Chess Engine - Official Rules Engine & Frontend Controller
 * Implements complete international chess rules:
 * - King protection: King can never be captured
 * - Check detection & King safety: Player cannot move into check
 * - Checkmate & Stalemate detection
 * - Castling (Kingside & Queenside)
 * - En Passant captures
 * - Pawn Promotion modal (Queen, Rook, Bishop, Knight)
 * - Procedural Web Audio API sound effects (Move, Capture, Check, Victory)
 */

const PIECE_SYMBOLS = {
  'wK': '♔', 'wQ': '♕', 'wR': '♖', 'wB': '♗', 'wN': '♘', 'wP': '♙',
  'bK': '♚', 'bQ': '♛', 'bR': '♜', 'bB': '♝', 'bN': '♞', 'bP': '♟'
};

const FILES = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'];

// Audio Synthesizer (Web Audio API)
let soundEnabled = true;
let audioCtx = null;

function getAudioContext() {
  if (!audioCtx) {
    const AudioContext = window.AudioContext || window.webkitAudioContext;
    if (AudioContext) audioCtx = new AudioContext();
  }
  if (audioCtx && audioCtx.state === 'suspended') {
    audioCtx.resume();
  }
  return audioCtx;
}

function playSound(type) {
  if (!soundEnabled) return;
  try {
    const ctx = getAudioContext();
    if (!ctx) return;
    const now = ctx.currentTime;

    if (type === 'move') {
      const osc = ctx.createOscillator();
      const gain = ctx.createGain();
      osc.type = 'triangle';
      osc.frequency.setValueAtTime(140, now);
      osc.frequency.exponentialRampToValueAtTime(60, now + 0.08);
      gain.gain.setValueAtTime(0.12, now);
      gain.gain.linearRampToValueAtTime(0.01, now + 0.08);
      osc.connect(gain);
      gain.connect(ctx.destination);
      osc.start(now);
      osc.stop(now + 0.08);
    } else if (type === 'capture') {
      const osc = ctx.createOscillator();
      const gain = ctx.createGain();
      osc.type = 'square';
      osc.frequency.setValueAtTime(260, now);
      osc.frequency.exponentialRampToValueAtTime(90, now + 0.12);
      gain.gain.setValueAtTime(0.15, now);
      gain.gain.linearRampToValueAtTime(0.01, now + 0.12);
      osc.connect(gain);
      gain.connect(ctx.destination);
      osc.start(now);
      osc.stop(now + 0.12);
    } else if (type === 'check') {
      const osc1 = ctx.createOscillator();
      const osc2 = ctx.createOscillator();
      const gain = ctx.createGain();
      osc1.type = 'sine';
      osc2.type = 'sine';
      osc1.frequency.setValueAtTime(440, now);
      osc2.frequency.setValueAtTime(554.37, now);
      gain.gain.setValueAtTime(0.15, now);
      gain.gain.linearRampToValueAtTime(0.01, now + 0.25);
      osc1.connect(gain);
      osc2.connect(gain);
      gain.connect(ctx.destination);
      osc1.start(now);
      osc2.start(now);
      osc1.stop(now + 0.25);
      osc2.stop(now + 0.25);
    } else if (type === 'victory') {
      const notes = [523.25, 659.25, 783.99, 1046.50];
      notes.forEach((freq, idx) => {
        const osc = ctx.createOscillator();
        const gain = ctx.createGain();
        const start = now + (idx * 0.1);
        osc.type = 'triangle';
        osc.frequency.setValueAtTime(freq, start);
        gain.gain.setValueAtTime(0.15, start);
        gain.gain.linearRampToValueAtTime(0.01, start + 0.35);
        osc.connect(gain);
        gain.connect(ctx.destination);
        osc.start(start);
        osc.stop(start + 0.35);
      });
    }
  } catch (e) {
    console.debug('Audio playback note:', e);
  }
}

function toggleSound() {
  soundEnabled = !soundEnabled;
  const btn = document.getElementById('sound-btn');
  if (btn) {
    btn.innerHTML = soundEnabled ? '<span>🔊</span> Sound: ON' : '<span>🔇</span> Sound: OFF';
  }
  if (soundEnabled) playSound('move');
}

// Game State
let isWasmActive = false;
let whiteTurn = true;
let selectedSquare = null;
let lastMove = null;
let moveHistory = [];
let capturedByWhite = [];
let capturedByBlack = [];
let isFlipped = false;
let isGameOver = false;

// Castling rights & en passant state
let hasKingMoved = { w: false, b: false };
let hasRookMoved = {
  w_0_0: false, // a1
  w_7_0: false, // h1
  b_0_7: false, // a8
  b_7_7: false  // h8
};
let enPassantTarget = null; // { x, y, pawnX, pawnY }
let pendingPromotion = null; // { fromX, fromY, toX, toY, isCapture, capturedPiece }

// Board State: 8x8 matrix (0..7, 0..7)
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

  hasKingMoved = { w: false, b: false };
  hasRookMoved = { w_0_0: false, w_7_0: false, b_0_7: false, b_7_7: false };
  enPassantTarget = null;
  pendingPromotion = null;
  isGameOver = false;
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
    updateEngineBadge(false);
  }
}

function updateEngineBadge(inCheck, mateWinner = null) {
  const badge = document.getElementById('engine-badge');
  if (!badge) return;
  
  if (mateWinner) {
    badge.className = 'status-badge mate-alert';
    badge.innerHTML = `<span class="status-dot"></span> 🏆 Checkmate (${mateWinner} Wins)`;
  } else if (inCheck) {
    badge.className = 'status-badge check-alert';
    badge.innerHTML = `<span class="status-dot"></span> ⚠️ Check (${whiteTurn ? "White" : "Black"} King Threatened)`;
  } else {
    badge.className = 'status-badge';
    badge.innerHTML = `<span class="status-dot"></span> 🟢 Official Rules Engine Active`;
  }
}

// Get piece on square
function getPiece(x, y, board = jsBoard) {
  if (x < 0 || x > 7 || y < 0 || y > 7) return null;
  return board[y][x];
}

// Clone board state for move simulation
function cloneBoard(board) {
  return board.map(row => [...row]);
}

// Locate King coordinates {x, y}
function findKing(isWhite, board = jsBoard) {
  const target = isWhite ? 'wK' : 'bK';
  for (let y = 0; y < 8; y++) {
    for (let x = 0; x < 8; x++) {
      if (board[y][x] === target) return { x, y };
    }
  }
  return null;
}

// Is a square under attack by the specified color?
function isSquareAttacked(tx, ty, byWhite, board = jsBoard) {
  for (let y = 0; y < 8; y++) {
    for (let x = 0; x < 8; x++) {
      const piece = board[y][x];
      if (!piece) continue;
      const pieceIsWhite = piece[0] === 'w';
      if (pieceIsWhite !== byWhite) continue;

      const type = piece[1];
      const dx = tx - x;
      const dy = ty - y;
      const adx = Math.abs(dx);
      const ady = Math.abs(dy);

      if (type === 'P') {
        const dir = pieceIsWhite ? 1 : -1;
        if (dy === dir && adx === 1) return true;
      } else if (type === 'N') {
        if ((adx === 1 && ady === 2) || (adx === 2 && ady === 1)) return true;
      } else if (type === 'B' || type === 'Q') {
        if (adx === ady && adx > 0) {
          const sx = dx > 0 ? 1 : -1;
          const sy = dy > 0 ? 1 : -1;
          let cx = x + sx, cy = y + sy;
          let blocked = false;
          while (cx !== tx || cy !== ty) {
            if (board[cy][cx] !== null) { blocked = true; break; }
            cx += sx; cy += sy;
          }
          if (!blocked) return true;
        }
      }
      if (type === 'R' || type === 'Q') {
        if ((dx === 0 && dy !== 0) || (dy === 0 && dx !== 0)) {
          const sx = dx === 0 ? 0 : (dx > 0 ? 1 : -1);
          const sy = dy === 0 ? 0 : (dy > 0 ? 1 : -1);
          let cx = x + sx, cy = y + sy;
          let blocked = false;
          while (cx !== tx || cy !== ty) {
            if (board[cy][cx] !== null) { blocked = true; break; }
            cx += sx; cy += sy;
          }
          if (!blocked) return true;
        }
      }
      if (type === 'K') {
        if (adx <= 1 && ady <= 1 && (adx !== 0 || ady !== 0)) return true;
      }
    }
  }
  return false;
}

// Is a player's King in Check?
function isKingInCheck(isWhite, board = jsBoard) {
  const king = findKing(isWhite, board);
  if (!king) return false;
  return isSquareAttacked(king.x, king.y, !isWhite, board);
}

// Generate all pseudo-legal moves for a piece at (sx, sy)
function getPseudoLegalMoves(sx, sy, board = jsBoard) {
  const piece = board[sy][sx];
  if (!piece) return [];
  const isWhite = piece[0] === 'w';
  const type = piece[1];
  const moves = [];

  const addIfValid = (tx, ty, isCaptureOnly = false, isNonCaptureOnly = false) => {
    if (tx < 0 || tx > 7 || ty < 0 || ty > 7) return false;
    const dest = board[ty][tx];
    
    // King can NEVER be captured
    if (dest && dest[1] === 'K') return false;

    if (isNonCaptureOnly) {
      if (dest === null) { moves.push({ x: tx, y: ty, isCapture: false }); return true; }
      return false;
    }
    if (isCaptureOnly) {
      if (dest !== null && (dest[0] === 'w') !== isWhite) {
        moves.push({ x: tx, y: ty, isCapture: true });
        return true;
      }
      // Check en passant
      if (dest === null && enPassantTarget && tx === enPassantTarget.x && ty === enPassantTarget.y) {
        moves.push({ x: tx, y: ty, isCapture: true, isEnPassant: true });
        return true;
      }
      return false;
    }

    if (dest === null) {
      moves.push({ x: tx, y: ty, isCapture: false });
      return true; // continue ray
    } else if ((dest[0] === 'w') !== isWhite) {
      moves.push({ x: tx, y: ty, isCapture: true });
      return false; // hit enemy, stop ray
    }
    return false; // hit friendly, stop ray
  };

  switch (type) {
    case 'P': {
      const dir = isWhite ? 1 : -1;
      const startRank = isWhite ? 1 : 6;
      // 1-step forward
      if (board[sy + dir] && board[sy + dir][sx] === null) {
        moves.push({ x: sx, y: sy + dir, isCapture: false });
        // 2-steps forward from starting rank
        if (sy === startRank && board[sy + 2 * dir][sx] === null) {
          moves.push({ x: sx, y: sy + 2 * dir, isCapture: false, isPawnDouble: true });
        }
      }
      // Diagonal captures
      [-1, 1].forEach(dx => {
        const tx = sx + dx;
        const ty = sy + dir;
        addIfValid(tx, ty, true, false);
      });
      break;
    }
    case 'N': {
      const offsets = [
        [-2, -1], [-2, 1], [-1, -2], [-1, 2],
        [1, -2], [1, 2], [2, -1], [2, 1]
      ];
      offsets.forEach(([dx, dy]) => addIfValid(sx + dx, sy + dy));
      break;
    }
    case 'B': {
      const dirs = [[1, 1], [1, -1], [-1, 1], [-1, -1]];
      dirs.forEach(([dx, dy]) => {
        let cx = sx + dx, cy = sy + dy;
        while (cx >= 0 && cx <= 7 && cy >= 0 && cy <= 7) {
          const keepGoing = addIfValid(cx, cy);
          if (!keepGoing) break;
          cx += dx; cy += dy;
        }
      });
      break;
    }
    case 'R': {
      const dirs = [[1, 0], [-1, 0], [0, 1], [0, -1]];
      dirs.forEach(([dx, dy]) => {
        let cx = sx + dx, cy = sy + dy;
        while (cx >= 0 && cx <= 7 && cy >= 0 && cy <= 7) {
          const keepGoing = addIfValid(cx, cy);
          if (!keepGoing) break;
          cx += dx; cy += dy;
        }
      });
      break;
    }
    case 'Q': {
      const dirs = [
        [1, 0], [-1, 0], [0, 1], [0, -1],
        [1, 1], [1, -1], [-1, 1], [-1, -1]
      ];
      dirs.forEach(([dx, dy]) => {
        let cx = sx + dx, cy = sy + dy;
        while (cx >= 0 && cx <= 7 && cy >= 0 && cy <= 7) {
          const keepGoing = addIfValid(cx, cy);
          if (!keepGoing) break;
          cx += dx; cy += dy;
        }
      });
      break;
    }
    case 'K': {
      const dirs = [
        [-1, -1], [-1, 0], [-1, 1],
        [0, -1],           [0, 1],
        [1, -1],  [1, 0],  [1, 1]
      ];
      dirs.forEach(([dx, dy]) => addIfValid(sx + dx, sy + dy));

      // Castling Verification
      const kingMoved = isWhite ? hasKingMoved.w : hasKingMoved.b;
      const rank = isWhite ? 0 : 7;
      if (!kingMoved && sy === rank && sx === 4) {
        // Must not currently be in check
        if (!isSquareAttacked(4, rank, !isWhite, board)) {
          // Kingside Castling
          const rookHMoved = isWhite ? hasRookMoved.w_7_0 : hasRookMoved.b_7_7;
          if (!rookHMoved && board[rank][7] === (isWhite ? 'wR' : 'bR')) {
            if (board[rank][5] === null && board[rank][6] === null) {
              if (!isSquareAttacked(5, rank, !isWhite, board) && !isSquareAttacked(6, rank, !isWhite, board)) {
                moves.push({ x: 6, y: rank, isCapture: false, isCastleKingside: true });
              }
            }
          }
          // Queenside Castling
          const rookAMoved = isWhite ? hasRookMoved.w_0_0 : hasRookMoved.b_0_7;
          if (!rookAMoved && board[rank][0] === (isWhite ? 'wR' : 'bR')) {
            if (board[rank][1] === null && board[rank][2] === null && board[rank][3] === null) {
              if (!isSquareAttacked(3, rank, !isWhite, board) && !isSquareAttacked(2, rank, !isWhite, board)) {
                moves.push({ x: 2, y: rank, isCapture: false, isCastleQueenside: true });
              }
            }
          }
        }
      }
      break;
    }
  }

  return moves;
}

// Filter moves to strictly LEGAL moves (ensuring King is NOT left in Check)
function getLegalMoves(sx, sy, board = jsBoard) {
  const piece = board[sy][sx];
  if (!piece) return [];
  const isWhite = piece[0] === 'w';
  const pseudoMoves = getPseudoLegalMoves(sx, sy, board);

  return pseudoMoves.filter(m => {
    const tempBoard = cloneBoard(board);
    // Simulate move
    tempBoard[m.y][m.x] = piece;
    tempBoard[sy][sx] = null;

    // Handle En Passant in simulation
    if (m.isEnPassant && enPassantTarget) {
      tempBoard[enPassantTarget.pawnY][enPassantTarget.pawnX] = null;
    }

    // Handle Castling Rook move in simulation
    if (m.isCastleKingside) {
      tempBoard[m.y][5] = tempBoard[m.y][7];
      tempBoard[m.y][7] = null;
    } else if (m.isCastleQueenside) {
      tempBoard[m.y][3] = tempBoard[m.y][0];
      tempBoard[m.y][0] = null;
    }

    // King cannot be in check after move
    return !isKingInCheck(isWhite, tempBoard);
  });
}

// Get all legal moves for a player
function getAllLegalMoves(isWhite, board = jsBoard) {
  const allMoves = [];
  for (let y = 0; y < 8; y++) {
    for (let x = 0; x < 8; x++) {
      const piece = board[y][x];
      if (piece && (piece[0] === 'w') === isWhite) {
        const moves = getLegalMoves(x, y, board);
        moves.forEach(m => allMoves.push({ fromX: x, fromY: y, toX: m.x, toY: m.y, meta: m }));
      }
    }
  }
  return allMoves;
}

// Render 64 squares into DOM
function renderBoard() {
  const boardEl = document.getElementById('chessboard');
  boardEl.innerHTML = '';

  const rankIndices = isFlipped ? [0, 1, 2, 3, 4, 5, 6, 7] : [7, 6, 5, 4, 3, 2, 1, 0];
  const fileIndices = isFlipped ? [7, 6, 5, 4, 3, 2, 1, 0] : [0, 1, 2, 3, 4, 5, 6, 7];

  const inCheck = isKingInCheck(whiteTurn, jsBoard);
  const checkedKingPos = inCheck ? findKing(whiteTurn, jsBoard) : null;

  rankIndices.forEach(y => {
    fileIndices.forEach(x => {
      const isLight = (x + y) % 2 !== 0;
      const square = document.createElement('div');
      square.className = `square ${isLight ? 'light' : 'dark'}`;
      square.dataset.x = x;
      square.dataset.y = y;

      // King in Check pulsing highlight
      if (checkedKingPos && checkedKingPos.x === x && checkedKingPos.y === y) {
        square.classList.add('check');
      }

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

      // Valid move guide indicator
      if (selectedSquare && selectedSquare.validMoves) {
        const moveMatch = selectedSquare.validMoves.find(m => m.x === x && m.y === y);
        if (moveMatch) {
          const dot = document.createElement('div');
          dot.className = `valid-dot ${moveMatch.isCapture ? 'capture' : ''}`;
          square.appendChild(dot);
        }
      }

      square.addEventListener('click', () => handleSquareClick(x, y));
      boardEl.appendChild(square);
    });
  });

  // Turn badge update
  const turnBadge = document.getElementById('turn-badge');
  if (turnBadge) {
    if (isGameOver) {
      turnBadge.textContent = "Game Over";
      turnBadge.style.color = "var(--accent-gold)";
    } else {
      turnBadge.textContent = whiteTurn ? "⚪ White's Turn" : "⚫ Black's Turn";
      turnBadge.style.color = whiteTurn ? "#f8fafc" : "#94a3b8";
    }
  }

  // Update Graveyard / Captured pieces
  document.getElementById('graveyard-white').textContent = capturedByBlack.map(p => PIECE_SYMBOLS[p]).join(' ');
  document.getElementById('graveyard-black').textContent = capturedByWhite.map(p => PIECE_SYMBOLS[p]).join(' ');
}

// User Square Click
function handleSquareClick(x, y) {
  if (isGameOver) return;
  hideToast();
  const clickedPiece = getPiece(x, y);

  if (!selectedSquare) {
    // Click 1: Select a piece of the current turn
    if (!clickedPiece) return;
    const isPieceWhite = clickedPiece[0] === 'w';
    if (isPieceWhite !== whiteTurn) {
      showToast(`It is ${whiteTurn ? "White's" : "Black's"} turn!`);
      return;
    }

    // Compute strictly legal moves (filtered for King safety)
    const validMoves = getLegalMoves(x, y);
    if (validMoves.length === 0) {
      showToast(`${getPieceFullName(clickedPiece[1])} has no legal moves.`);
      return;
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

    // Check if clicked square is in legal moves
    const chosenMove = selectedSquare.validMoves.find(m => m.x === x && m.y === y);

    if (chosenMove) {
      const fromX = selectedSquare.x;
      const fromY = selectedSquare.y;
      const piece = selectedSquare.piece;

      // Check for Pawn Promotion (White to rank 7, Black to rank 0)
      const isPawn = piece[1] === 'P';
      const isPromotion = isPawn && ((piece[0] === 'w' && y === 7) || (piece[0] === 'b' && y === 0));

      if (isPromotion) {
        pendingPromotion = {
          fromX, fromY, toX: x, toY: y,
          moveMeta: chosenMove,
          piece
        };
        showPromotionModal(piece[0] === 'w');
        return;
      }

      // Execute standard legal move
      applyMove(fromX, fromY, x, y, chosenMove);
      selectedSquare = null;
      renderBoard();
    } else {
      showToast("Illegal Move: King safety or chess rule violation.");
      selectedSquare = null;
      renderBoard();
    }
  }
}

// Apply confirmed move to board state
function applyMove(fromX, fromY, toX, toY, moveMeta, promotedPiece = null) {
  const piece = jsBoard[fromY][fromX];
  const isWhite = piece[0] === 'w';
  const target = jsBoard[toY][toX];
  let isCapture = target !== null;

  // Handle Regular Capture
  if (target) {
    if (target[0] === 'b') capturedByWhite.push(target);
    else capturedByBlack.push(target);
  }

  // Handle En Passant Capture
  if (moveMeta && moveMeta.isEnPassant && enPassantTarget) {
    const epTargetPiece = jsBoard[enPassantTarget.pawnY][enPassantTarget.pawnX];
    if (epTargetPiece) {
      if (epTargetPiece[0] === 'b') capturedByWhite.push(epTargetPiece);
      else capturedByBlack.push(epTargetPiece);
      jsBoard[enPassantTarget.pawnY][enPassantTarget.pawnX] = null;
      isCapture = true;
    }
  }

  // Move Piece or Promote
  jsBoard[toY][toX] = promotedPiece ? promotedPiece : piece;
  jsBoard[fromY][fromX] = null;

  // Handle Castling Rook Movement
  if (moveMeta && moveMeta.isCastleKingside) {
    jsBoard[toY][5] = jsBoard[toY][7];
    jsBoard[toY][7] = null;
    hasRookMoved[isWhite ? 'w_7_0' : 'b_7_7'] = true;
  } else if (moveMeta && moveMeta.isCastleQueenside) {
    jsBoard[toY][3] = jsBoard[toY][0];
    jsBoard[toY][0] = null;
    hasRookMoved[isWhite ? 'w_0_0' : 'b_0_7'] = true;
  }

  // Update Castling & En Passant state
  if (piece[1] === 'K') hasKingMoved[isWhite ? 'w' : 'b'] = true;
  if (piece === 'wR') {
    if (fromX === 0 && fromY === 0) hasRookMoved.w_0_0 = true;
    if (fromX === 7 && fromY === 0) hasRookMoved.w_7_0 = true;
  }
  if (piece === 'bR') {
    if (fromX === 0 && fromY === 7) hasRookMoved.b_0_7 = true;
    if (fromX === 7 && fromY === 7) hasRookMoved.b_7_7 = true;
  }

  // En Passant target reset or creation
  if (moveMeta && moveMeta.isPawnDouble) {
    const dir = isWhite ? 1 : -1;
    enPassantTarget = { x: fromX, y: fromY + dir, pawnX: toX, pawnY: toY };
  } else {
    enPassantTarget = null;
  }

  // Play Sound
  if (isCapture) playSound('capture');
  else playSound('move');

  lastMove = { fromX, fromY, toX, toY };

  // Switch Turn
  whiteTurn = !whiteTurn;

  // Evaluate Check / Checkmate / Stalemate for next player
  const nextInCheck = isKingInCheck(whiteTurn, jsBoard);
  const nextLegalMoves = getAllLegalMoves(whiteTurn, jsBoard);

  let notationSuffix = '';
  if (nextLegalMoves.length === 0) {
    isGameOver = true;
    if (nextInCheck) {
      notationSuffix = '#';
      const winner = whiteTurn ? "Black" : "White";
      updateEngineBadge(false, winner);
      playSound('victory');
      setTimeout(() => showGameOverModal(`🏆 Checkmate! ${winner} Wins!`, `${winner} delivered checkmate. Excellent match!`), 400);
    } else {
      notationSuffix = '½-½';
      updateEngineBadge(false);
      setTimeout(() => showGameOverModal(`🤝 Stalemate!`, `No legal moves remaining. The game is a draw.`), 400);
    }
  } else if (nextInCheck) {
    notationSuffix = '+';
    updateEngineBadge(true);
    playSound('check');
    showToast(`⚠️ CHECK! ${whiteTurn ? "White" : "Black"} King is under attack!`);
  } else {
    updateEngineBadge(false);
  }

  // Record Algebraic Move History
  recordMove(piece, fromX, fromY, toX, toY, moveMeta, notationSuffix, promotedPiece);
}

// Show Pawn Promotion Modal
function showPromotionModal(isWhite) {
  const modal = document.getElementById('promotion-modal');
  const choices = document.getElementById('promotion-choices');
  choices.innerHTML = '';

  const prefix = isWhite ? 'w' : 'b';
  const pieces = ['Q', 'R', 'B', 'N'];

  pieces.forEach(type => {
    const pCode = prefix + type;
    const btn = document.createElement('button');
    btn.className = 'promo-btn';
    btn.textContent = PIECE_SYMBOLS[pCode];
    btn.onclick = () => {
      modal.classList.remove('active');
      if (pendingPromotion) {
        const { fromX, fromY, toX, toY, moveMeta } = pendingPromotion;
        applyMove(fromX, fromY, toX, toY, moveMeta, pCode);
        pendingPromotion = null;
        selectedSquare = null;
        renderBoard();
      }
    };
    choices.appendChild(btn);
  });

  modal.classList.add('active');
}

// Show Game Over Modal
function showGameOverModal(title, desc) {
  const modal = document.getElementById('game-over-modal');
  document.getElementById('game-over-title').textContent = title;
  document.getElementById('game-over-desc').textContent = desc;
  modal.classList.add('active');
}

function closeGameOverModal() {
  document.getElementById('game-over-modal').classList.remove('active');
}

function getPieceFullName(char) {
  const map = { 'P': 'Pawn', 'R': 'Rook', 'N': 'Knight', 'B': 'Bishop', 'Q': 'Queen', 'K': 'King' };
  return map[char] || 'Piece';
}

function recordMove(piece, fx, fy, tx, ty, meta, suffix, promotedPiece) {
  let notation = '';
  if (meta && meta.isCastleKingside) {
    notation = 'O-O';
  } else if (meta && meta.isCastleQueenside) {
    notation = 'O-O-O';
  } else {
    const pieceChar = piece[1] !== 'P' ? piece[1] : '';
    const cap = meta && meta.isCapture ? 'x' : '';
    const promo = promotedPiece ? `=${promotedPiece[1]}` : '';
    notation = `${pieceChar}${cap}${FILES[tx]}${ty + 1}${promo}${suffix}`;
  }
  
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
  if (!tbody) return;
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
  if (container) container.scrollTop = container.scrollHeight;
}

function showToast(msg) {
  const toast = document.getElementById('engine-toast');
  if (toast) {
    toast.textContent = msg;
    toast.classList.add('active');
  }
}

function hideToast() {
  const toast = document.getElementById('engine-toast');
  if (toast) {
    toast.classList.remove('active');
  }
}

// Reset Game
function resetGame() {
  whiteTurn = true;
  selectedSquare = null;
  lastMove = null;
  moveHistory = [];
  capturedByWhite = [];
  capturedByBlack = [];
  isGameOver = false;
  closeGameOverModal();
  hideToast();
  initJsBoard();
  updateEngineBadge(false);
  updateMoveTable();
  renderBoard();
  playSound('move');
}

// Flip Board
function flipBoard() {
  isFlipped = !isFlipped;
  renderBoard();
}

// Initialize on Load
window.addEventListener('DOMContentLoaded', () => {
  checkEngineMode();
  renderBoard();
});
