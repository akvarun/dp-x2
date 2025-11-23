#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <iomanip>
#include <map>

using namespace std;

// Structure to hold the result
struct Result {
    double maxScore;
    string sub1;
    string sub2;
    int start1; // 0-based index in s1
    int start2; // 0-based index in s2
    int length;
};

// Function to solve Weighted Approximate Common Substring
Result solve(const string& s1, const string& s2, const map<char, double>& weights, double penalty) {
    int n = s1.length();
    int m = s2.length();
    
    // DP table initialization
    // dp[i][j] stores the max score ending at s1[i-1] and s2[j-1]
    vector<vector<double>> dp(n + 1, vector<double>(m + 1, 0.0));
    
    double maxScore = 0.0;
    int endIdx1 = 0;
    int endIdx2 = 0;
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            double currentWeight = -penalty;
            if (s1[i-1] == s2[j-1]) {
                if (weights.find(s1[i-1]) != weights.end()) {
                    currentWeight = weights.at(s1[i-1]);
                } else {
                    // Fallback if char not in map (should not happen based on problem desc)
                    currentWeight = 1.0; 
                }
            }
            
            dp[i][j] = max(0.0, dp[i-1][j-1] + currentWeight);
            
            if (dp[i][j] > maxScore) {
                maxScore = dp[i][j];
                endIdx1 = i;
                endIdx2 = j;
            }
        }
    }
    
    string resSub1 = "";
    string resSub2 = "";
    int currI = endIdx1;
    int currJ = endIdx2;
    
    while (currI > 0 && currJ > 0 && dp[currI][currJ] > 0) {
        resSub1 += s1[currI-1];
        resSub2 += s2[currJ-1];
        currI--;
        currJ--;
    }
    
    reverse(resSub1.begin(), resSub1.end());
    reverse(resSub2.begin(), resSub2.end());
    
    return {maxScore, resSub1, resSub2, currI, currJ, (int)resSub1.length()};
}

// Helper to generate random string
string generateString(int length) {
    string s = "";
    static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 25);
    
    for (int i = 0; i < length; ++i) {
        s += alphanum[dis(gen)];
    }
    return s;
}

string generateStringFreq(int length, const map<char, double>& freqs) {
    string s = "";
    vector<char> chars;
    vector<double> weights;
    for(auto const& [key, val] : freqs) {
        chars.push_back(key);
        weights.push_back(val);
    }
    
    random_device rd;
    mt19937 gen(rd());
    discrete_distribution<> d(weights.begin(), weights.end());
    
    for(int i=0; i<length; ++i) {
        s += chars[d(gen)];
    }
    return s;
}

int main() {
    cout << "--- Verification Example ---" << endl;
    string exS1 = "ABCAABCAA";
    string exS2 = "ABBCAACCBBBBBB";
    map<char, double> exWeights;
    for(char c = 'A'; c <= 'Z'; ++c) exWeights[c] = 1.0; // Default weight 1
    double exPenalty = 2.0; // Default penalty
    
    
    Result res = solve(exS1, exS2, exWeights, exPenalty);
    cout << "Max Score: " << res.maxScore << endl;
    cout << "Substring 1: " << res.sub1 << endl;
    cout << "Substring 2: " << res.sub2 << endl;
    cout << "Start 1: " << res.start1 << endl;
    cout << "Start 2: " << res.start2 << endl;
    cout << "----------------------------" << endl << endl;

    // --- Scenario 1 ---
    cout << "--- Scenario 1 Experiments ---" << endl;
    int len1 = 1000;
    int len2 = 1000;
    string s1_sc1 = generateString(len1);
    string s2_sc1 = generateString(len2);
    
    Result res_sc1 = solve(s1_sc1, s2_sc1, exWeights, 2.0);
    cout << "Length 1: " << len1 << ", Length 2: " << len2 << endl;
    cout << "Max Score: " << res_sc1.maxScore << endl;
    cout << "Match Length: " << res_sc1.length << endl;
    cout << "----------------------------" << endl << endl;

    // --- Scenario 2 ---
    cout << "--- Scenario 2 Experiments ---" << endl;
    // Frequencies
    map<char, double> freqs = {
        {'E', 12.7}, {'T', 9.1}, {'A', 8.2}, {'O', 7.5}, {'I', 7.0}, {'N', 6.7}, {'S', 6.3}, {'H', 6.1}, {'R', 6.0}, {'D', 4.3},
        {'L', 4.0}, {'C', 2.8}, {'U', 2.8}, {'M', 2.4}, {'W', 2.4}, {'F', 2.2}, {'G', 2.0}, {'Y', 2.0}, {'P', 1.9}, {'B', 1.5},
        {'V', 1.0}, {'K', 0.8}, {'J', 0.2}, {'X', 0.2}, {'Q', 0.1}, {'Z', 0.1}
    };
    
    double minWeight = 0.1;
    double maxWeight = 12.7;
    
    string s1_sc2 = generateStringFreq(len1, freqs);
    string s2_sc2 = generateStringFreq(len2, freqs);
    
    double step = (maxWeight - minWeight) / 11.0;
    
    cout << "Penalty | Max Score | Match Length" << endl;
    for (int k = 1; k <= 10; ++k) {
        double p = minWeight + k * step;
        Result r = solve(s1_sc2, s2_sc2, freqs, p);
        cout << fixed << setprecision(2) << p << " | " << r.maxScore << " | " << r.length << endl;
    }

    return 0;
}
