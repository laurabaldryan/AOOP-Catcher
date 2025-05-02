#  OOCatcher – CS323 Advanced OOP Project

This is a C++ project for simulating an anthropomorphic stick-figure body using connected line segments, developed as part of the CS323 Advanced Object-Oriented Programming course at the American University of Armenia.

---

## Objective

- Implement an anthropomorphic body composed of 5–6 segments
- Apply constraints to simulate realistic limb movement
- Enable the body to rotate its segments to grab or throw an object
- Detect successful object grabs based on proximity and contact
- Log movements and simulate interaction logic

---

##  Project Structure

```
OOCatcher/
├── data/ # Output files (e.g., moves.dat)
├── src/ # Source files (.cpp) and Header files (.h)
├── .vscode/ # VS Code tasks and config files
├── OOCatcherApp.exe # Executable (after build)
├── README.md # This file

```


---

## Build & Run Instructions

### Prerequisites

- A working installation of **g++** with C++17 or C++20 support for Windows
- VS Code 
- MinGW or MSYS2 toolchain added to system PATH

### Compile via Terminal

From inside the `OOCatcher/` folder, run:  g++ -std=c++17 -Iinclude src/*.cpp -o OOCatcherApp


