# Define compiler
CXX := clang++

# Define the directory for ImGui files, relative to the src directory
IMGUI_DIR := ../../imgui

# Define the directory for object files
OBJDIR := obj

# Define the C++ source files for ImGui and for your project
IMGUI_SOURCES := $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
IMGUI_SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
SRCS := $(wildcard src/*.cpp)

# Define the C++ object files for ImGui and for your project
IMGUI_OBJS := $(addprefix $(OBJDIR)/, $(notdir $(IMGUI_SOURCES:.cpp=.o)))
OBJS := $(SRCS:src/%.cpp=$(OBJDIR)/%.o)

# Include paths for ImGui and the backends
CXXFLAGS := -std=c++11 -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += -g -Wall -Wformat

# Libraries needed for linking (GLFW, GL, etc.)
LIBS := -lglfw -lGL -ldl -lGLEW

# Define the executable file
MAIN := dataManager

.PHONY: all clean

all: $(MAIN)
	@echo dataManager has been compiled

# Main target depends on project and ImGui object files
$(MAIN): $(OBJS) $(IMGUI_OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

# Pattern rule for project source files
$(OBJDIR)/%.o: src/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Pattern rule for ImGui source files
$(OBJDIR)/%.o: $(IMGUI_DIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(IMGUI_DIR)/backends/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo Cleaning...
	$(RM) -r $(OBJDIR)/* $(MAIN)
