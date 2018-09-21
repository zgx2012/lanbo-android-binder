#ifndef FRAMEWORKS_LISTENERMANAGER_H
#define FRAMEWORKS_LISTENERMANAGER_H

#include "Communication.h"
#include <List.h>
#include <BigBitSet.h>
#include <StrongPointer.h>
#include <Singleton.h>
#include <hashmap.h>

namespace android
{

class ListenerManager : public Singleton<ListenerManager>
{
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
    void dispatch(int event, Parcelable* p);

private:
    // 结构体 _event_listener
    typedef struct _event_listener {
        sp<IEventListener> listener;
        String16 name;
        BigBitSet events;
    } _event_listener;

    typedef struct _event_listener* p_event_listener;

private:
    HashMap* mListenerMap;
    Vector<List<p_event_listener>> mEvents;
}; // end class ListenerManager

}; // end namespace android

#endif //FRAMEWORKS_LISTENERMANAGER_H
