//
// Created by huhaolong on 2024/7/18.
//

#include <string>
#include <vector>


//根据自己理解写的，最普通没有优化的buildNext算法
std::vector<int> buildNextV1_Ugly(std::string p) {
    if (p.empty()) { return std::vector<int>(0); }

    std::vector<int> next(p.length());
    next[0] = -1;
    for (int i = 1; i < next.size(); i++) {
        int j = next[i - 1];
        while (0 <= j) {
            if (p[j] == p[i - 1]) {
                break;
            }
            j = next[j];
        }
        next[i] = j + 1;
    }

    return next;
}

//根据自己理解写的，优化后的buildNext算法（非常丑陋）
//优化的原因和方法可参考 https://www.xuetangx.com/learn/THU08091002048/THU08091002048/19318085/video/42986921?channel=i.area.learn_title
//pmt: Partial Match Table
std::vector<int> buildNextV2_Ugly(std::string p) {
    if (p.empty()) { return std::vector<int>(0); }

    int n = p.length();
    std::vector<int> pmt(n), next(n);
    pmt[0] = 0, next[0] = -1;
    for (int i = 1; i < n; i++) {
        int j = pmt[i - 1];
        while (0 < j && (p[j] != p[i])) {
            j = pmt[j - 1];
        }
        if (j == 0) {
            pmt[i] = p[0] == p[i] ? 1 : 0;
        } else {
            pmt[i] = j + 1;
        }

        //next表的更新依赖自身以及pmt表
        if (p[pmt[i - 1]] == p[i]) {
            next[i] = next[pmt[i - 1]];
        } else {
            next[i] = pmt[i - 1];
        }
    }

    return next;
}

//邓俊辉版本的buildNext优化版
//个人认为极其抽象，主要是没有解释t代表啥。
//实际上，t表示就是[0,j)的真前缀和真后缀的最长匹配，该算法使用迭代对t进行更新。
//1、当p[j] == p[t]时，t_{i+1}=t_{i}+1很好理解；
//2、当p[j] != p[t]时，t=next[t]这一步看起来好像是错的，由于next语义的改变，next[t]看起来会错过正确的t_{i+1}候选？
//实际上稍加观察会发现，我们既然已经知道p[t] != p[j]，那么要找的下一个t必然要满足p[t'] != p[t]（否则仍然会与p[j]不相等）。
//然而这恰好就是next数组所表达的语义！！t_{i}经过next的不断迭代后必然能得到t_{i+1}！！
std::vector<int> buildNextV2_TsingHuaDSA(std::string p) {
    int n = p.length();
    int j = 0;
    std::vector<int> next(n);
    int t = next[0] = -1;
    while (j < n - 1) {
        if (0 > t || p[j] == p[t]) {
            j++; t++;
            printf("j=%d,t=%d\n", j, t); //这里打印的结果与优化前的版本V1的next表是一致的
            next[j] = (p[j] != p[t] ? t : next[t]);
        } else {
            t = next[t];
        }
    }
    return next;
}

//根据buildNextV2_TsingHuaDSA，更容易理解、更简洁的优化版buildNext
std::vector<int> buildNextV2(std::string p) {
    if (p.empty()) { return std::vector<int>(0); }

    int n = p.length();
    std::vector<int> next(n);
    int pm = next[0] = -1;
    for (int i = 1; i < n; i++) {
        while (0 <= pm && (p[pm] != p[i - 1])) {
            pm = next[pm];
        }
        pm += 1;
        printf("pm[%d]=%d\n", i, pm);
        next[i] = (p[pm] != p[i] ? pm : next[pm]);
    }

    return next;
}

int match_KMP(std::string t, std::string p) {
    auto next = buildNextV2(p);
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