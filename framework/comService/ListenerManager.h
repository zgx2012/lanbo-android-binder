#ifndef FRAMEWORKS_LISTENERMANAGER_H
#define FRAMEWORKS_LISTENERMANAGER_H

#include "Communication.h"

// 结构体 _event_listener
typedef struct _event_listener {
    sp<IEventListener> listener,
    String16 name;
    std::vector<int> events;
    struct _event_listener* next;
} _event_listener;

typedef struct _event_listener* p_event_listener;
extern p_event_listener listenerHead;
extern p_event_listener listenerTail;

// 添加 listener
void addListener(p_event_listener l);

// 结构体 _listener
typedef struct _listener {
    p_event_listener l;
    typedef struct _listener* next;
} _listener;
typedef struct _listener* p_listener;

extern p_listener* events;

// 初始化
void initListenerManager();

// 添加监听
void addListener(const sp<IEventListener>& l, const String16& n, const std::vector<int>& events);

// 查找监听
p_event_listener findListener(const sp<IEventListener>& l);

#endif //FRAMEWORKS_LISTENERMANAGER_H
