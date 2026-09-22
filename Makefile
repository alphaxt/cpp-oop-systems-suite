CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

BIN_DIR = bin

all: dirs hospital hotel student
	@echo "All systems built successfully in $(BIN_DIR)/"

dirs:
	@mkdir -p $(BIN_DIR)

hospital:
	$(CXX) $(CXXFLAGS) -Ihospital-management/include hospital-management/src/*.cpp -o $(BIN_DIR)/hospital_system

hotel:
	$(CXX) $(CXXFLAGS) -Ihotel-management/include hotel-management/src/*.cpp -o $(BIN_DIR)/hotel_system

student:
	$(CXX) $(CXXFLAGS) -Istudent-management/include student-management/src/*.cpp -o $(BIN_DIR)/student_system

clean:
	rm -rf $(BIN_DIR)

.PHONY: all dirs hospital hotel student clean
