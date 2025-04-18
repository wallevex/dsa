//
// Created by huhaolong on 2024/7/18.
//

#pragma once

#include <string>
#include <vector>

std::vector<int> buildNext(std::string p);
int match_KMP(std::string t, std::string p);

std::vector<int> buildBC(std::string p);
std::vector<int> buildSS(std::string p);
std::vector<int> buildGS(std::string p);
int match_BM(std::string p, std::string t);
