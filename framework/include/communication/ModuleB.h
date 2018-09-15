#ifndef FRAMEWORKS_MODULEB_H
#define FRAMEWORKS_MODULEB_H

#include "Communication.h"
#include "CommunicationModule.h"
#include "IReturnCallback.h"

namespace android
{

class ModuleB : public CommunicationModule
{
public:
    ModuleB(const char* name):CommunicationModule(name){}
    ModuleB(const String16& name):CommunicationModule(name){}
    ~ModuleB(){}

public:
    int methodCall(const char* name, const int method, va_list ap);
    int methodCallReturn(const char* name, const int method, const sp<IReturnCallback>& callback, va_list ap);

}; // end class ModuleB

}; // end namespace android

#endif //FRAMEWORKS_MODULEB_H
