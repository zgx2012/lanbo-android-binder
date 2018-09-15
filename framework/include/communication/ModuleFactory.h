#ifndef FRAMEWORKS_MODULEFACTORY_H
#define FRAMEWORKS_MODULEFACTORY_H

#include <utils/Singleton.h>
#include "Communication.h"
#include "BaseModuleFactory.h"
#include "ModuleA.h"
#include "ModuleB.h"
#include "ModuleC.h"

namespace android
{

class ModuleFactory : public Singleton<ModuleFactory>, public BaseModuleFactory
{
public:
    ~ModuleFactory();
    ModuleFactory();

public:
    virtual CommunicationModule* getModule(const char* name) {
        if (name == 0) return 0;
        String16 moduleName = String16(name);
        if      (moduleName == String16(MODULE_NAME_A)) { return getModuleA(); }
        else if (moduleName == String16(MODULE_NAME_B)) { return getModuleB(); }
        else if (moduleName == String16(MODULE_NAME_C)) { return getModuleC(); }
        else if (moduleName == String16(MODULE_COMM_SERVICE)) { return getCommService(); }

        return 0;
    }

    inline CommunicationModule* getCommService() {
        if (pCommService == 0) {
            pCommService = new ModuleC(MODULE_COMM_SERVICE);
        }
        return pCommService;
    }

private:
    inline CommunicationModule* getModuleA() {
        if (pModuleA == 0) {
            pModuleA = new ModuleA(MODULE_NAME_A);
        }
        return pModuleA;
    }

    inline CommunicationModule* getModuleB() {
        if (pModuleB == 0) {
            pModuleB = new ModuleB(MODULE_NAME_B);
        }
        return pModuleB;
    }

    inline CommunicationModule* getModuleC() {
        if (pModuleC == 0) {
            pModuleC = new ModuleC(MODULE_NAME_C);
        }
        return pModuleC;
    }



private:
    CommunicationModule *pCommService;
    CommunicationModule *pModuleA, *pModuleB, *pModuleC;

}; // end class ModuleFactory

}; // end namespace android

#endif //FRAMEWORKS_MODULEFACTORY_H
