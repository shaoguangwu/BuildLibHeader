#ifndef EXTERNAL_H
#define EXTERNAL_H

#include <cstdio>
#include <ctime>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>

#include "StringUtils.h"

namespace fs = std::filesystem;
using StringVector = std::vector<std::string>;

void pause();

// 查找当前目录下所有特定后缀的文件, 后缀带“.”， 如“.lib”
StringVector findSpecificSuffix(const std::string& dir, const std::string& suffix);

// 寻找带d和不带d的lib
StringVector findLib(const StringVector& lib_list, const std::string& suff);

// 去掉带d后缀
StringVector removeSuffD(const StringVector& lib_list);

// format : YYYY-MM-DD hh:mm:ss
std::string getTimeNow();

void writeLibHeader(const StringVector &libd_list, const StringVector& libr_list, const std::string& fileName = "");

#endif // EXTERNAL_H
