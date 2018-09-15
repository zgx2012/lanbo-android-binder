#ifndef FRAMEWORKS_MODULEC_H
#define FRAMEWORKS_MODULEC_H

#include "Communication.h"
#include "CommunicationModule.h"
#include "IReturnCallback.h"

namespace android
{

class ModuleC : public CommunicationModule
{
public:
    ModuleC(const char* name):CommunicationModule(name){}
    ModuleC(const String16& name):CommunicationModule(name){}
    ~ModuleC(){}

public:
    int methodCall(const char* name, const int method, va_list ap);
    int methodCallReturn(const char* name, const int method, const sp<IReturnCallback>& callback, va_list ap);

}; // end class ModuleC

}; // end namespace android

#endif //FRAMEWORKS_MODULEC_H
