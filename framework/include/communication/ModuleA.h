#ifndef FRAMEWORKS_MODULEA_H
#define FRAMEWORKS_MODULEA_H

#include "Communication.h"
#include "CommunicationModule.h"
#include "IReturnCallback.h"

namespace android
{

class ModuleA : public CommunicationModule
{
public:
    ModuleA(const char* name):CommunicationModule(name){}
    ModuleA(const String16& name):CommunicationModule(name){}
    ~ModuleA(){}
    // 重载父类的函数
    int methodCall(const char* name, const int method, va_list ap);
    int methodCallReturn(const char* name, int method, const sp<IReturnCallback>& callback, va_list ap);

private:
    // 定义本模块会处理的消息、支持的方法等.
    int methodSetValue(const char* from, va_list ap);
    int methodAddReturn(const char* from, int method, const sp<IReturnCallback>& callback, va_list ap);

}; // end class ModuleA

}; // end namespace android

#endif //FRAMEWORKS_MODULEA_H
