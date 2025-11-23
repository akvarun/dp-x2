import subprocess
import matplotlib.pyplot as plt
import os
import re

def run_problem1():
    print("Running Problem 1...")
    result = subprocess.run(["./Problem1/main"], capture_output=True, text=True)
    output = result.stdout
    
    penalties = []
    scores = []
    lengths = []
    
    # Format: Penalty | Max Score | Match Length
    lines = output.split('\n')
    start_parsing = False
    for line in lines:
        if "Penalty | Max Score | Match Length" in line:
            start_parsing = True
            continue
        if start_parsing and "|" in line:
            parts = line.split('|')
            if len(parts) == 3:
                try:
                    p = float(parts[0].strip())
                    s = float(parts[1].strip())
                    l = int(parts[2].strip())
                    penalties.append(p)
                    scores.append(s)
                    lengths.append(l)
                except ValueError:
                    continue
    
    # Plot Penalty vs Match Length
    plt.figure(figsize=(10, 6))
    plt.plot(penalties, lengths, marker='o', linestyle='-', color='b')
    plt.title('Problem 1: Penalty vs Optimal Common Substring Length')
    plt.xlabel('Penalty')
    plt.ylabel('Length of Substring')
    plt.grid(True)
    plt.savefig('graphs/problem1_length.png')
    plt.close()
    
    # Plot Penalty vs Score
    plt.figure(figsize=(10, 6))
    plt.plot(penalties, scores, marker='s', linestyle='--', color='r')
    plt.title('Problem 1: Penalty vs Max Score')
    plt.xlabel('Penalty')
    plt.ylabel('Max Score')
    plt.grid(True)
    plt.savefig('graphs/problem1_score.png')
    plt.close()
    print("Problem 1 graphs generated.")

def run_problem2():
    print("Running Problem 2...")
    result = subprocess.run(["./Problem2/main"], capture_output=True, text=True)
    output = result.stdout
    
    sizes = [] # Total elements (Rows * Cols)
    times = []
    memories = []
    labels = []
    
    # Parse Experiments output
    # Format: Rows x Cols | Time (us) | Max Size | Memory (approx KB)
    lines = output.split('\n')
    start_parsing = False
    for line in lines:
        if "Rows x Cols | Time (us)" in line:
            start_parsing = True
            continue
        if start_parsing and "|" in line:
            parts = line.split('|')
            if len(parts) == 4:
                try:
                    dims = parts[0].strip().split('x')
                    r = int(dims[0].strip())
                    c = int(dims[1].strip())
                    t = int(parts[1].strip())
                    m = float(parts[3].strip())
                    
                    total_elements = r * c
                    sizes.append(total_elements)
                    times.append(t)
                    memories.append(m)
                    labels.append(f"{r}x{c}")
                except ValueError:
                    continue

    # Plot Size vs Time
    plt.figure(figsize=(10, 6))
    plt.plot(sizes, times, marker='o', linestyle='-', color='g')
    plt.title('Problem 2: Matrix Size vs Running Time')
    plt.xlabel('Number of Elements (Rows * Cols)')
    plt.ylabel('Time (microseconds)')
    for i, txt in enumerate(labels):
        plt.annotate(txt, (sizes[i], times[i]), textcoords="offset points", xytext=(0,10), ha='center')
    plt.grid(True)
    plt.savefig('graphs/problem2_time.png')
    plt.close()

    # Plot Size vs Memory
    plt.figure(figsize=(10, 6))
    plt.plot(sizes, memories, marker='^', linestyle='-', color='m')
    plt.title('Problem 2: Matrix Size vs Memory Usage')
    plt.xlabel('Number of Elements (Rows * Cols)')
    plt.ylabel('Memory (KB)')
    for i, txt in enumerate(labels):
        plt.annotate(txt, (sizes[i], memories[i]), textcoords="offset points", xytext=(0,10), ha='center')
    plt.grid(True)
    plt.savefig('graphs/problem2_memory.png')
    plt.close()
    print("Problem 2 graphs generated.")

if __name__ == "__main__":
    if not os.path.exists('graphs'):
        os.makedirs('graphs')
    
    # Ensure binaries exist
    if not os.path.exists('./Problem1/main'):
        print("Compiling Problem 1...")
        subprocess.run(["g++", "-std=c++17", "-o", "Problem1/main", "Problem1/main.cpp"])
        
    if not os.path.exists('./Problem2/main'):
        print("Compiling Problem 2...")
        subprocess.run(["g++", "-std=c++17", "-o", "Problem2/main", "Problem2/main.cpp"])

    run_problem1()
    run_problem2()
