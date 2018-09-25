#include "CommunicationModule.h"

namespace android
{

CommunicationModule::CommunicationModule(const char* name) {
    //mName.setTo(name);
    mName = String16(name);
}

CommunicationModule::CommunicationModule(const String16& name) {
    mName = name;
}

CommunicationModule::~CommunicationModule() {
}

int CommunicationModule::sendEvent(const char* name, const char* to, const int event, const Parcelable* parcelable) {
    return RESULT_NO_ERROR;
}

int CommunicationModule::sendEventSync(const char* name, const char* to, const int event) {
    return RESULT_NO_ERROR;
}

int CommunicationModule::addEventListener(const char* name, const sp<IEventListener>& listener, const std::vector<int>& eventVector) {
    return RESULT_NO_ERROR;
}

int CommunicationModule::methodCall(const char* name, const int method, va_list ap) {
    return RESULT_NO_ERROR;
}

int CommunicationModule::methodCallReturn(const char* name, const int method, const sp<IReturnCallback>& callback, va_list ap) {
    return RESULT_NO_ERROR;
}

}; // end namespace android

