#ifdef __ANDROID__

#include "utils/log.h"
#include <android/log.h>
using namespace oi;

void printstr(String str){
	__android_log_print(ANDROID_LOG_INFO, "oi_Log", "%s", str.toCString());
}

void printwar(String str){
	__android_log_print(ANDROID_LOG_WARN, "oi_Log", "%s", str.toCString());
}

void printerr(String str){
	__android_log_print(ANDROID_LOG_ERROR, "oi_Log", "%s", str.toCString());
}

LogCallback Log::errorc = printerr, Log::warningc = printwar, Log::printc = printstr;

#endif