# Compiler and compiler flags
CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -Wextra -lncursesw
SDIR = sources
ODIR = objects
SOURCES = $(wildcard $(SDIR)/*.cpp)
OBJECTS = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SOURCES))
TARGET = geimu.exe

# Targets and rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -rf $(ODIR)/* $(TARGET)
