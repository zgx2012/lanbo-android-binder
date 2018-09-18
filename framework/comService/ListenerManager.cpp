#include "ListenerManager.h"

extern p_listener* events = 0;
extern p_event_listener listenerHead = 0;
extern p_event_listener listenerTail = 0;


void initListenerManager() {
    events = new p_listener[MAX_EVENT_NUM];
    listeners = new _event_listener[MAX_LISTENER];
}

void addListener(p_event_listener l) {
    if (l == 0) return;

    p_event_listener tmp = listenerTail;

}

void addListener(const sp<IEventListener>& l, const String16& n, const std::vector<int>& events) {

}


p_event_listener findListener(const sp<IEventListener>& l) {
    p_event_listener tmp = listenerHead;
    while(tmp) {
        if (tmp->listener == l) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return 0;
}


