#ifndef FRAMEWORKS_MODULE_COMMSERVICE_H
#define FRAMEWORKS_MODULE_COMMSERVICE_H

#include "Communication.h"
#include "CommunicationModule.h"
#include "IReturnCallback.h"

namespace android
{

class CommServiceModule : public CommunicationModule
{
public:
    CommServiceModule(const char* name):CommunicationModule(name){}
    CommServiceModule(const String16& name):CommunicationModule(name){}
    ~CommServiceModule(){}
    // 重载父类的函数
    int sendEvent(const char* from, const char* to, const int event, const Parcelable* parcelable);
    int addEventListener(const char* name, const sp<IEventListener>& listener, const std::vector<int>& eventVector);
    int removeEventListener(const sp<IEventListener>& listener);
}; // end class CommService

}; // end namespace android

#endif //FRAMEWORKS_MODULE_COMMSERVICE_H
