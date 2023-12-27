#include <iostream>
#include <fstream>

#ifndef COGE_MACROS_H
#define COGE_MACROS_H

#define WIDTH 1280
#define HEIGHT 720

#ifndef COGE_DONT_FILE_LOG
#ifndef COGE_LOG_FILE_PATH
#define COGE_LOG_FILE_PATH "coge_log.txt"
#endif
extern std::ofstream log_file;
#define FLOG(x) log_file << x << std::endl
#define FLOGnl(x) log_file << x
#else
#define FLOG(x)
#define FLOGnl(x)
#endif

#ifndef COGE_DONT_LOG
#define PRINT(x) std::cout << x << std::endl; FLOG(x)
#define PRINTnl(x) std::cout << x; FLOGnl(x)
#define LOG(x) std::clog << "COGE:LOG:" << x << std::endl; FLOG("COGE:LOG:" << x)
#define LOGnl(x) std::clog << "COGE:LOG:" << x; FLOGnl("COGE:LOG:" << x)
#else
#define PRINT(x)
#define PRINTnl(x)
#define LOG(x)
#define LOGnl(x)
#endif

#ifdef COGE_EXTREME_LOG
#define E_LOG(x) LOG(x)
#define E_LOGnl(x) LOGnl(x)
#define E_PRINT(x) PRINT(x)
#define E_PRINTnl(x) PRINTnl(x)
#else
#define E_LOG(x)
#define E_LOGnl(x)
#define E_PRINT(x)
#define E_PRINTnl(x)
#endif

#define WARN(x) std::cerr << "COGE:WARNING:" << x << std::endl; FLOG("COGE:WARNING:" << x)
#define WARNnl(x) std::cerr << "COGE:WARNING:" << x; FLOGnl("COGE:WARNING:" << x)
#define WARNPRINT(x) std::cout << x << std::endl;
#define WARNPRINTnl(x) std::cout << x;

#ifndef COGE_DESTROY_QUICK_UNDERSTAND
#define QUICK_UNDERSTAND LOG("---------------------------------Yay.-------------------------------------");
#endif

#endif