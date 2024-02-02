# Define compiler
CXX := clang

# Define any compile-time flags
CXXFLAGS := -Wall -g

# Define the directory for object files
OBJDIR := obj

# Define the C++ source files
SRCS := $(wildcard src/*.cpp)

# Define the C++ object files
OBJS := $(SRCS:src/%.cpp=$(OBJDIR)/%.o)

# Define the executable file
MAIN := dataManager

.PHONY: all clean

all: $(MAIN)
	@echo Simple compiler named mycc has been compiled

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJS)

$(OBJDIR)/%.o: src/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR) *~ $(MAIN)
