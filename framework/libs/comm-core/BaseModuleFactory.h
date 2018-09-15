#ifndef FRAMEWORKS_BASEMODULEFACTORY_H
#define FRAMEWORKS_BASEMODULEFACTORY_H

#include "comm.h"

namespace android
{
extern BaseModuleFactory* gModuleFactory;

class BaseModuleFactory
{
public:
    BaseModuleFactory(){}
    virtual ~BaseModuleFactory(){}
    virtual CommunicationModule* getModule(const char* name) {
        return 0;
    }
}; // end class BaseModuleFactory

}; // end namespace android

#endif //FRAMEWORKS_BASEMODULEFACTORY_H
