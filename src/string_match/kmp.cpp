//
// Created by huhaolong on 2024/7/18.
//

#include <string>
#include <vector>

std::vector<int> buildNext(std::string p) {
    if (p.empty()) { return std::vector<int>(0); }

    int m = p.length();
    std::vector<int> next(m);
    int pm = next[0] = -1;
    for (int j = 1; j < m; j++) {
        while (0 <= pm && (p[pm] != p[j - 1])) {
            pm = next[pm];
        }
        pm += 1;
        next[j] = (p[pm] != p[j] ? pm : next[pm]);
    }

    return next;
}

// Knuth-Morris-Pratt match
int match_KMP(std::string t, std::string p) {
    auto next = buildNext(p);
    int n = t.length(), m = p.length();
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (j < 0 || t[i] == p[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }

    return j == m ? i - j : -1;
}