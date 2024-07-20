//
// Created by huhaolong on 2024/7/19.
//

#include <string>
#include <vector>

std::vector<int> buildBC(std::string p) {
    std::vector<int> bc(256, -1);
    int m = p.length();
    for (int j = 0; j < m; j++) {
        bc[p[j]] = j;
    }
    return bc;
}

//SS: Suffix Size
//ss[i]表示p[0,j]的所有后缀与p[0,m-1]的所有后缀的最大匹配长度
//即ss[i] = max{ 0 <= s <= j + 1 | p(j-s, j] = p[m-s, m) }
//暴力解法的时间复杂度为O(n^2)；但实际上可以用动态规划去做，时间复杂度为O(n)
//该dp解法参考《邓俊辉数据结构》11.4.4节ss[]表的构造
//下面的lo表示当前最靠左（最小）的“后缀区间左端点”，hi为对应于lo的“后缀区间右端点”
std::vector<int> buildSS(std::string p) {
    if (p.empty()) { return std::vector<int>(0); }

    int m = p.length();
    std::vector<int> ss(m);
    ss[m - 1] = m;
    for (int j = m - 2, lo = m - 1, hi = m - 1; 0 <= j; j--) {
        if ((lo < j) && (ss[m - 1 - (hi - j)] < j - lo)) {
            ss[j] = ss[m - 1 - (hi - j)];
        } else {
            hi = j;
            if (lo > hi) { lo = hi; }
            while ((0 <= lo) && (p[lo] == p[m - 1 - (hi - lo)])) {
                lo--;
            }
            ss[j] = hi - lo;
        }
    }
    return ss;
}

//感觉是一个最难理解、根本无法自己想出来的算法。。。
//参考《邓俊辉数据结构》11.4.4由ss[]表构造gs[]表
//这个方法主要是将ss[j]分为两种贡献，然后将每种贡献赋到每个以它为候选者的gs[i]上，这样就相当于反向完成了所有gs[i]的设置
//这里最最最难注意到的是：
//1、gs[m - ss[j] - 1] = m - j - 1一定不会覆盖掉第一种候选情况，不然会出现前缀大于后缀的情况矛盾！！
//2、p[m - ss[j] - 1] != p[j - ss[j]]一定成立，否则MS[j]可以增加1矛盾！！
std::vector<int> buildGS(std::string p) {
    auto ss = buildSS(p);
    int m = p.length();
    std::vector<int> gs(m, m);
    for (int i = 0, j = m - 1; 0 <= j; j--) {
        if (j + 1 == ss[j]) {
            while (i < m - j - 1) {
                gs[i++] = m - j - 1;
            }
        }

    }
    for (int j = 0; j < m - 1; j++) {
        gs[m - ss[j] - 1] = m - j - 1; //最难理解的部分
    }
    return gs;
}

int match_BM(std::string t, std::string p) {
    int n = t.length(), m = p.length();
    auto bc = buildBC(p);
    auto gs = buildGS(p);
    int i = 0;
    while (i + m <= n) {
        int j = m - 1;
        while ((0 <= j) && (t[i + j] == p[j])) {
            j--;
        }
        if (j < 0) {
            return i;
        }
        i += std::max(gs[j], j - bc[t[i + j]]);
    }
    return -1;
}