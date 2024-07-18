//
// Created by huhaolong on 2024/7/18.
//

#include <string>
#include <vector>

std::vector<int> buildNext(std::string P) {
    if (P.empty()) { return std::vector<int>(0); };

    std::vector<int> next(P.length());
    next[0] = -1;
    for (int i = 1; i < next.size(); i++) {
        int j = next[i - 1];
        while (0 <= j) {
            if (P[j] == P[i - 1]) {
                break;
            }
            j = next[j];
        }
        next[i] = j + 1;

    }

    return next;
}

int match(std::string T, std::string P) {
    auto next = buildNext(P);
    int n = T.length(), m = P.length();
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (j < 0 || T[i] == P[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    return i - j;
}