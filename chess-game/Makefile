CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
SRC_DIR := src
BUILD_DIR := build
TARGET := ChessGame

EMCC := emcc
EMFLAGS := -std=c++17 -O3 -Iinclude -s WASM=1 -s EXPORTED_RUNTIME_METHODS='["UTF8ToString"]' -s NO_EXIT_RUNTIME=1

SOURCES := $(filter-out $(SRC_DIR)/wasm_bridge.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

WASM_SOURCES := $(SRC_DIR)/Bishop.cpp $(SRC_DIR)/Board.cpp $(SRC_DIR)/King.cpp $(SRC_DIR)/Knight.cpp $(SRC_DIR)/Pawn.cpp $(SRC_DIR)/Piece.cpp $(SRC_DIR)/Queen.cpp $(SRC_DIR)/Rook.cpp $(SRC_DIR)/wasm_bridge.cpp

.PHONY: all clean run wasm

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	./$(TARGET)

wasm:
	$(EMCC) $(EMFLAGS) $(WASM_SOURCES) -o web/chess.js
	@echo "WebAssembly compiled successfully to web/chess.js and web/chess.wasm!"

clean:
	rm -rf $(BUILD_DIR) $(TARGET) web/chess.js web/chess.wasm
