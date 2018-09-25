#ifndef FRAMEWORKS_LISTENERMANAGER_H
#define FRAMEWORKS_LISTENERMANAGER_H

#include <utils/Singleton.h>
#include <utils/List.h>
#include <utils/StrongPointer.h>
#include <cutils/hashmap.h>

#include "communication/Communication.h"
#include "BigBitSet.h"

namespace android
{

class ListenerManager : public Singleton<ListenerManager>
{
private:
    // 结构体 _event_listener
    typedef struct _event_listener {
        sp<IEventListener> listener;
        String16 name;
        BigBitSet events;
    } _event_listener;

    typedef struct _event_listener* p_event_listener;

public:
    ListenerManager();
    ~ListenerManager();
    // 初始化
    void initListenerManager();
    // 删除监听
    void removeListener(const sp<IEventListener>& l);
    // 添加监听
    void addListener(const sp<IEventListener>& l, const String16& n, const std::vector<int>& events);

    // 分发消息
    void dispatch(int event, const Parcelable* p);

private:
    void addEvents(p_event_listener value, const BigBitSet& events);
    void removeEvents(const sp<IEventListener>& l, const BigBitSet& events);

private:
    Hashmap* mListenerMap;
    Vector<List<p_event_listener>*> mEvents;
}; // end class ListenerManager

}; // end namespace android

#endif //FRAMEWORKS_LISTENERMANAGER_H
