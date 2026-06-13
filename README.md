# Shortest Path Solver (Dijkstra & Bellman-Ford)

This is a C++ console application that solves the Shortest Path Problem for directed weighted graphs. It was created as a university project for the "Projektowanie i Analiza Algorytmów" (Design and Analysis of Algorithms) course.

## Features
- **Graph Representations**: Implements both Adjacency Matrix and Adjacency List using an object-oriented approach.
- **Algorithms**: 
  - Dijkstra's Algorithm (optimized with a Min-Heap / Priority Queue).
  - Bellman-Ford Algorithm (handles negative weights, optimized with an early-exit condition).
- **Graph Generator**: Built-in randomized graph generator using the Fisher-Yates shuffle to guarantee exact density constraints without duplicate edges or self-loops.
- **Benchmarking Suite**: Fully automated benchmarking system that measures algorithm performance across various vertex counts and graph densities.
- **Python Plotting**: Includes a Python script (`plot_results.py`) using Pandas and Seaborn to automatically generate performance charts from benchmark results.
- **LaTeX Report**: Contains a comprehensive academic report in Polish (`sprawozdanie/raport.tex`) detailing the implementations, complexities, and conclusions.

## Build and Run
1. Make sure you have `clang++` (or another C++17 compatible compiler) and `make` installed.
2. Compile the project:
   ```bash
   make
   ```
3. Run the application:
   ```bash
   ./shortest_path
   ```

## Dependencies for Plotting
To generate the performance charts, install the required Python packages:
```bash
pip install pandas matplotlib seaborn jinja2
```
Then run the script inside the `sprawozdanie/` directory:
```bash
cd sprawozdanie && python3 plot_results.py
```
