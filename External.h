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

// ���ҵ�ǰĿ¼�������ض���׺���ļ�, ��׺����.���� �硰.lib��
StringVector findSpecificSuffix(const std::string& dir, const std::string& suffix);

// Ѱ�Ҵ�d�Ͳ���d��lib
StringVector findLib(const StringVector& lib_list, const std::string& suff);

// ȥ����d��׺
StringVector removeSuffD(const StringVector& lib_list);

// format : YYYY-MM-DD hh:mm:ss
std::string getTimeNow();

void writeLibHeader(const StringVector &libd_list, const StringVector& libr_list, const std::string& fileName = "");

#endif // EXTERNAL_H
