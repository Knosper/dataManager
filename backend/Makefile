# Define compiler
CXX := clang++

# Define any compile-time flags
CXXFLAGS := -Wall -g -fPIC `pkg-config --cflags Qt5Widgets`

LDLIBS := -lpqxx -lpq `pkg-config --libs Qt5Widgets`
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
	@echo dataManager has been compiled

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJS) $(LDLIBS)

$(OBJDIR)/%.o: src/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

check_env:
	@echo "Checking environment variables:"
	@echo "BACKEND_VOLUME = $(BACKEND_VOLUME)"
	@echo "FRONTEND_VOLUME = $(FRONTEND_VOLUME)"
	@echo "NODE_ENV = $(NODE_ENV)"
	@echo "NODE_VERSION = $(NODE_VERSION)"
	@echo "POSTGRES_DB = $(POSTGRES_DB)"
	@echo "POSTGRES_HOST = $(POSTGRES_HOST)"
	@echo "POSTGRES_PASSWORD = $(POSTGRES_PASSWORD)"
	@echo "POSTGRES_USER = $(POSTGRES_USER)"
	@echo "POSTGRES_URL = $(POSTGRES_URL)"
	@echo "Authentication: (Add your authentication variables here if needed)"

clean:
	$(RM) -r $(OBJDIR) *~ $(MAIN)
