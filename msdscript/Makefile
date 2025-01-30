# Compiler
CXX = c++

# Compilation options: Use C++14 and add include path
CXXFLAGS = -std=c++14 -I/opt/homebrew/include

# Linker options: Add Catch2 library
LDFLAGS = -L/opt/homebrew/lib -lCatch2Main -lCatch2

# Program name
PROGRAM = msdscript

# Compilation rule
$(PROGRAM): main.cpp cmdline.cpp expr.cpp expr_test.cpp
	$(CXX) $(CXXFLAGS) main.cpp cmdline.cpp expr.cpp expr_test.cpp -o $(PROGRAM) $(LDFLAGS)

# Clean rule
clean:
	rm -f $(PROGRAM)

