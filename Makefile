CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
SRC      := $(wildcard src/*.cpp)
TARGET   := parking_system

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: all
	./$(TARGET)

test: tests/test_fee.cpp src/fee_calculation.cpp src/utils.cpp src/vehicle_exit.cpp src/receipt_records.cpp src/slot_management.cpp
	$(CXX) $(CXXFLAGS) -o test_fee $^
	./test_fee
	rm -f test_fee

clean:
	rm -f $(TARGET) test_fee parking_active.txt parking_records.txt
