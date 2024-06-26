# My Dear ImGui Gui Project early state

This project is a scanner in a C++, to create a interactive GUI & 2learn nmap.

https://github.com/ocornut/imgui

## Features

- **Dear ImGui Integration:** Seamless integration of the Dear ImGui library for creating complex and portable graphical interfaces.
- **Modular Code:** The project is organized into separate modules for GUI components, data management, and utility functions, making the codebase easy to navigate and extend.
- **Makefile for Easy Compilation:** The project includes a Makefile for easy building and running on various platforms.

## Getting Started

### Prerequisites

Ensure you have the following installed:
- A C++ compiler (clang++ recommended)
- Make (for building the project using the Makefile)
- GLFW (lglfw) 
- OpenGL (lGL)
- dl (ldl)
- nmap

### Installing Dependencies (Ubuntu/Debian)

Execute the following command to install the required libraries:
``
sudo apt-get install libglfw3 libglfw3-dev libgl1-mesa-dev libglew-dev
``
### Cloning the Repository

Clone the repository and its submodules using the following command:

git clone --recurse-submodules git@github.com:Knosper/dataManager.git

### Building the Project

Navigate to the project directory and run the Makefile:

make


## Usage

After building the project, run the generated executable to start the application.

## License

This Dear Imgui open-sourced under the MIT license. See the [LICENSE.md](https://github.com/ocornut/imgui/blob/master/LICENSE.txt) file for details.

This stb_image is open-sourced under the MIT license. See the [LICENSE.md](http://nothings.org/stb) file for details.

## Acknowledgments

- Thanks to the creators and contributors of Dear ImGui && stb_image for their fantastic librarys.
- https://github.com/ocornut/imgui
