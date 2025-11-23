#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct Result {
    int maxSize;
    int bottomRightRow;
    int bottomRightCol;
};

// Function to solve Largest Zero Sub-matrix
Result solve(const vector<vector<uint8_t>>& matrix) {
    int m = matrix.size();
    if (m == 0) return {0, -1, -1};
    int n = matrix[0].size();
    
    // DP table
    // Using int to ensure we can handle sizes > 255
    // Although the prompt hints at using a byte, 1000x1000 can have size 1000.
    vector<vector<int>> dp(m, vector<int>(n, 0));
    
    int maxSize = 0;
    int bestR = -1;
    int bestC = -1;
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 0) { // We are looking for 0s
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
                }
                
                if (dp[i][j] > maxSize) {
                    maxSize = dp[i][j];
                    bestR = i;
                    bestC = j;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }
    
    return {maxSize, bestR, bestC};
}

// Generate random boolean matrix
vector<vector<uint8_t>> generateMatrix(int rows, int cols) {
    vector<vector<uint8_t>> mat(rows, vector<uint8_t>(cols));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    
    for(int i=0; i<rows; ++i) {
        for(int j=0; j<cols; ++j) {
            mat[i][j] = dis(gen);
        }
    }
    return mat;
}

int main() {
    // Verification with small manual example
    cout << "--- Verification Example ---" << endl;
    // 0 1 1
    // 0 0 0
    // 0 0 0
    // 1 0 0
    vector<vector<uint8_t>> exMat = {
        {0, 1, 1},
        {0, 0, 0},
        {0, 0, 0},
        {1, 0, 0}
    };
    Result res = solve(exMat);
    cout << "Max Size: " << res.maxSize << endl;
    cout << "Bottom-Right: (" << res.bottomRightRow << ", " << res.bottomRightCol << ")" << endl;
    cout << "----------------------------" << endl << endl;

    // Experiments
    cout << "--- Experiments ---" << endl;
    vector<pair<int, int>> sizes = {
        {10, 10},
        {10, 100},
        {10, 1000},
        {100, 1000},
        {1000, 1000}
    };
    
    cout << "Rows x Cols | Time (us) | Max Size | Memory (approx KB)" << endl;
    
    for (auto p : sizes) {
        int r = p.first;
        int c = p.second;
        
        auto mat = generateMatrix(r, c);
        
        auto start = high_resolution_clock::now();
        Result rRes = solve(mat);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        // Approx memory for DP table (int = 4 bytes) + Matrix (uint8_t = 1 byte)
        long long memBytes = (long long)r * c * 4 + (long long)r * c * 1;
        double memKB = memBytes / 1024.0;
        
        cout << r << " x " << c << " | " << duration.count() << " | " << rRes.maxSize << " | " << fixed << setprecision(2) << memKB << endl;
    }

    return 0;
}
