# Assignment 2: Dynamic Programming Algorithms

This repository contains the solutions for Assignment 2, implementing two Dynamic Programming algorithms in C++.

## Prerequisites

-   **C++ Compiler**: `g++` supporting C++17 (e.g., GCC 7+ or Clang 5+).
-   **Python 3**: For running experiments and generating graphs.
-   **Matplotlib**: Python library for plotting graphs.
    ```bash
    pip3 install matplotlib
    ```

## Project Structure

-   `Problem1/`: Contains the source code for the "Weighted Approximate Common Substring" problem.
-   `Problem2/`: Contains the source code for the "Largest Zero Sub-matrix" problem.
-   `graphs/`: Directory where generated graphs are saved.
-   `Report.pdf`: Final report with design, analysis, and results.
-   `generate_graphs.py`: Python script to automate compilation, execution, and graph generation.

## How to Run

### Option 1: Automated (Recommended)
Use the provided Python script to compile both programs, run the experiments, and generate the graphs automatically.

```bash
python3 generate_graphs.py
```

### Option 2: Manual Compilation & Execution

#### Problem 1: Weighted Approximate Common Substring
```bash
# Compile (requires C++17)
g++ -std=c++17 -o Problem1/main Problem1/main.cpp

# Run
./Problem1/main
```

#### Problem 2: Largest Zero Sub-matrix
```bash
# Compile (requires C++17)
g++ -std=c++17 -o Problem2/main Problem2/main.cpp

# Run
./Problem2/main
```

## Results
After running the programs, the experimental results (running time, memory usage, etc.) will be printed to the console. If you use the automated script, graphs will be generated in the `graphs/` directory.