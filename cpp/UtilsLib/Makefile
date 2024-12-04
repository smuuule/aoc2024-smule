# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Library name
LIBRARY = libUtilsLib.a

# Source and object files
SRCS = UtilsLib.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target: Build the static library
all: $(LIBRARY)

# Rule to create the static library
$(LIBRARY): $(OBJS)
	ar rcs $@ $^

# Rule to compile object files
%.o: %.cpp UtilsLib.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
.PHONY: clean
clean:
	rm -f $(OBJS) $(LIBRARY)

