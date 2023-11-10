# Compiler and compiler flags
CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -Wextra
SDIR = sources
ODIR = objects
SOURCES = $(wildcard $(SDIR)/*.cpp)
OBJECTS = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SOURCES))
TARGET = geimu.exe

# Targets and rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(ODIR)/* $(TARGET)
