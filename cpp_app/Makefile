# Define compiler
CXX := g++

INCLUDES := -Iinclude/class -Iinclude/utils -I/usr/include/mysql
# Define the directory for ImGui files, relative to the src directory
IMGUI_DIR := ../imgui

# Define the directory for object files
OBJDIR := obj

DIRS := $(OBJDIR) $(OBJDIR)/utils $(OBJDIR)/class $(OBJDIR)/class/Data $(OBJDIR)/class/Database $(OBJDIR)/class/Data/MenuItems

# Define the C++ source files for ImGui and for your project
IMGUI_SOURCES := $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
IMGUI_SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
SRCS := $(wildcard src/*.cpp) $(wildcard src/utils/*.cpp) $(wildcard src/class/*.cpp) $(wildcard src/class/Data/*.cpp) $(wildcard src/class/Database/*.cpp) $(wildcard src/class/Data/MenuItems/*.cpp)


# Define the C++ object files for ImGui and for your project
IMGUI_OBJS := $(addprefix $(OBJDIR)/, $(notdir $(IMGUI_SOURCES:.cpp=.o)))
OBJS := $(SRCS:src/%.cpp=$(OBJDIR)/%.o)
OBJS := $(OBJS:src/utils/%.cpp=$(OBJDIR)/utils/%.o)
OBJS := $(OBJS:src/class/%.cpp=$(OBJDIR)/class/%.o)
OBJS := $(OBJS:src/class/Data/%.cpp=$(OBJDIR)/class/Data/%.o)
OBJS := $(OBJS:src/class/Database/%.cpp=$(OBJDIR)/class/Database/%.o)
OBJS := $(OBJS:src/class/Data/MenuItems/%.cpp=$(OBJDIR)/class/Data/MenuItems/%.o)

# After SRCS and OBJS definitions
$(info SRCS = $(SRCS))
$(info OBJS = $(OBJS))

# Include paths for ImGui and the backends
CXXFLAGS := -std=c++11 -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += -g -Wall -Wformat

# Libraries needed for linking (GLFW, GL, etc.)
LIBS := -lmysqlclient -lglfw -lGL -ldl -lGLEW  -lsqlite3


# Define the executable file
MAIN := dataManager

.PHONY: all clean

all: directories $(MAIN)
	@echo dataManager has been compiled

# Create directories target
directories: | $(DIRS)

$(DIRS):
	@mkdir -p $@

# Main target depends on project and ImGui object files
$(MAIN): $(OBJS) $(IMGUI_OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

# Pattern rule for project source files in the root src directory
$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Pattern rule for project source files in the src/utils directory
$(OBJDIR)/utils/%.o: src/utils/%.cpp | $(OBJDIR)/utils
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Pattern rule for project source files in the src/class directory
$(OBJDIR)/class/%.o: src/class/%.cpp | $(OBJDIR)/class
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Pattern rule for project source files in the src/class/Data directory
$(OBJDIR)/class/Data/%.o: src/class/Data/%.cpp | $(OBJDIR)/class/Data
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Pattern rule for project source files in the src/class/Database directory
$(OBJDIR)/class/Database/%.o: src/class/Database/%.cpp | $(OBJDIR)/class/Database
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Pattern rule for project source files in the src/class/MenuItems directory
$(OBJDIR)/class/Data/MenuItems/%.o: src/class/Data/MenuItems/%.cpp | $(OBJDIR)/class/Data/MenuItems
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(IMGUI_DIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(IMGUI_DIR)/backends/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MAIN): | directories

clean:
	@echo Cleaning application objects...
	find $(OBJDIR) -type f ! -name 'imgui*' -delete
	$(RM) $(MAIN)

# Rebuild only app
re: clean all

fclean:
	@echo Cleaning...
	$(RM) -r $(OBJDIR)/* $(MAIN)

# Rebuild all
fre: fclean all