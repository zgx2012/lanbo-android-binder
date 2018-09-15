#include <utils/String16.h>
#include <utils/Singleton.h>
#include "ModuleFactory.h"
#include "IReturnCallback.h"

namespace android
{

ANDROID_SINGLETON_STATIC_INSTANCE(ModuleFactory);

ModuleFactory::ModuleFactory():Singleton<ModuleFactory>(), pCommService(0),
    pModuleA(0),pModuleB(0),pModuleC(0) {

    //bpReturnMethod = bpReturnMethodImpl;
    //bnReturnMethod = bnReturnMethodImpl;
}

ModuleFactory::~ModuleFactory() {
    if (pCommService != 0) {
        delete pCommService;
        pCommService = 0;
    }
    if (pModuleA != 0) {
        delete pModuleA;
        pModuleA = 0;
    }
    if (pModuleB != 0) {
        delete pModuleB;
        pModuleB = 0;
    }
    if (pModuleA != 0) {
        delete pModuleC;
        pModuleC = 0;
    }
}

}; // end namespace android


