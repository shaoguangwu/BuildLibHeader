#include "External.h"

void pause()
{
    std::cout << std::endl << "按任意键继续..." << std::endl;
    getchar();
}

StringVector findSpecificSuffix(const std::string& dir, const std::string& suffix)
{
    StringVector result;
    for (const auto& p : fs::directory_iterator(dir))
    {
        if (p.path().extension() == suffix)
        {
            result.push_back(p.path().filename().string());
        }
    }

    return result;
}

StringVector findLib(const StringVector& lib_list, const std::string& suff)
{
    StringVector result;
    for (const auto& str : lib_list)
    {
        if (utils4cpp::str::endsWith(str, suff, utils4cpp::str::CaseInsensitive))
        {
            result.push_back(str);
        }
    }
    return result;
}

StringVector removeSuffD(const StringVector& lib_list)
{
    StringVector result;
    for (const auto& str : lib_list)
    {
        if (!utils4cpp::str::endsWith(str, "d.lib", utils4cpp::str::CaseInsensitive))
        {
            result.push_back(str);
        }
    }
    return result;
}

std::string getTimeNow()
{
    std::time_t t = std::time(nullptr);
#ifdef _MSC_VER
    std::tm tm;
    localtime_s(&tm, &t);
#else
    std::tm tm = *std::localtime(&t);
#endif // _MSC_VER

    return utils4cpp::str::formatString("%04d-%02d-%02d %02d:%02d:%02d",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
        tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void writeLibHeader(const StringVector &libd_list, const StringVector& libr_list, const std::string& fileName)
{
    std::string dst_file = fileName.empty() ? "ImportLib.h" : fileName;
    std::string header_macro = fs::path(dst_file).filename().string();
    header_macro = utils4cpp::str::toUpper(header_macro);
    utils4cpp::str::replaceString(header_macro, ".", "_");
    
    std::string buff;
    std::ofstream stream(dst_file);

    // 写头注释
    buff = "// \n";
    buff += "// " + getTimeNow() + "\n";
    buff += "// " + std::string("shaoguang") + "\n";
    buff += "// \n\n";
    stream.write(buff.c_str(), buff.size());
    
    // 写开始保护宏
    buff = "#ifndef ";
    buff += header_macro + "\n";
    buff += "#define ";
    buff += header_macro + "\n\n";
    stream.write(buff.c_str(), buff.size());

    // #ifdef _DEBUG
    buff = "#ifdef _DEBUG // _DEBUG \n\n";
    stream.write(buff.c_str(), buff.size());

    // debug lib
    for (const auto& str : libd_list)
    {
        buff = "#    pragma comment(lib, " + str + ") \n";
        stream.write(buff.c_str(), buff.size());
    }

    // #else
    buff = "\n#else // _RELEASE \n\n";
    stream.write(buff.c_str(), buff.size());

    // release lib
    for (const auto& str : libr_list)
    {
        buff = "#    pragma comment(lib, " + str + ") \n";
        stream.write(buff.c_str(), buff.size());
    }
    // #endif
    buff = "\n#endif // #ifdef _DEBUG \n\n";
    stream.write(buff.c_str(), buff.size());

    // 写结束保护宏
    buff = "#endif " + std::string("// ") + header_macro;
    stream.write(buff.c_str(), buff.size());

    stream.close();
}