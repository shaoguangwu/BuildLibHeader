//
// wsg 2019-10-10
//

#include "External.h"

// argv[1] : debug lib 所在目录
// argv[2] : debug lib 文件后缀
// argv[3] : release lib 所在目录
// argv[4] : release lib 文件后缀
// argv[5] : H文件名

int main(int argc, char *argv[])
{
    if (argc < 6)
    {
        std::cout << "输入参数应为: " << std::endl;
        std::cout << "argv[1] debug lib目录 : " << std::endl;
        std::cout << "argv[2] debug lib后缀 : " << std::endl;
        std::cout << "argv[3] reles lib目录 : " << std::endl;
        std::cout << "argv[4] reles lib后缀 : " << std::endl;
        std::cout << "argv[5] 头文件文件名 : " << std::endl;
        pause();
        return 0;
    }
    
    std::cout << "debug lib目录 : " << argv[1] << std::endl;
    std::cout << "debug lib后缀 : " << argv[2] << std::endl;
    std::cout << "reles lib目录 : " << argv[3] << std::endl;
    std::cout << "reles lib后缀 : " << argv[4] << std::endl;
    std::cout << "头文件*.h文件名 : " << argv[5] << std::endl;

    // 查找debug lib
    auto lib_list = findSpecificSuffix(argv[1], ".lib");
    auto libd_list = findLib(lib_list, argv[2]);
    std::cout << "debug lib x " << libd_list.size() << std::endl;

    // 查找release lib
    lib_list = findSpecificSuffix(argv[3], ".lib");
    auto libr_list = findLib(lib_list, argv[4]);
    libr_list = removeSuffD(libr_list);
    std::cout << "release lib x " << libr_list.size() << std::endl;

    writeLibHeader(libd_list, libr_list, argv[5]);

    pause();
    return 0;
}