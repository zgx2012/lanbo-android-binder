#include <stdlib.h>
#include <string.h>

#include "ListenerManager.h"
#include "IEventListener.h"
#include "SomeArgs.h"

namespace android
{

static int hash(void* key) {
    return *((int*) key);
}

static bool equals(void* keyA, void* keyB) {
    return keyA == keyB;
}

static void* pointer(const sp<IEventListener>& l) {
    return (IInterface::asBinder(l)).get();
}

ANDROID_SINGLETON_STATIC_INSTANCE(ListenerManager);
ListenerManager::ListenerManager():Singleton<ListenerManager>() {
    initListenerManager();
}

ListenerManager::~ListenerManager() {
}

void ListenerManager::initListenerManager() {
    printf("%s\n", __FUNCTION__);
    //mEvents.setCapacity(MAX_EVENT_NUM);
    mEvents = (List<p_event_listener>**)malloc(MAX_EVENT_NUM * sizeof(List<p_event_listener>*));
    for(int i=0;i<MAX_EVENT_NUM;i++) {
        mEvents[i]=NULL;
    }
    mListenerMap = hashmapCreate(64, hash, equals);
}

void ListenerManager::removeListener(const sp<IEventListener>& l) {
    printf("%s\n", __FUNCTION__);
    RWLock::AutoWLock wLock(mRWLock);

    p_event_listener value = (p_event_listener)hashmapRemove(mListenerMap, pointer(l));
    if (value != NULL) {
        printf("%p, {%s, %p, %0lx}\n", pointer(l), value->name, pointer(value->listener), value->events.getValue());
    } else {
        printf("%p\n", pointer(l));
    }
    if (value == 0) return;

    if (value->name != NULL) {
        free(value->name);
    }

    removeEvents(l, value->events);

    delete value;
}

void ListenerManager::addListener(sp<IEventListener> l, const char* n, const std::vector<int>& events) {
    printf("%s %s %0lx\n", __FUNCTION__, n, pointer(l));
    BigBitSet eventSet, moreSet, mergedSet;
    for(int i=0;i<events.size();i++) {
        int index = ((~EVENT_MASK) & events[i]); // event unmark
        eventSet.markBit(index);
    }
    moreSet = eventSet;
    mergedSet = eventSet;
    printf("events: %0lx\n", mergedSet.getValue());

    printf("get old listener\n");
    RWLock::AutoWLock wLock(mRWLock);

    // 创建listener
    p_event_listener value = (p_event_listener)hashmapGet(mListenerMap, pointer(l));
    const std::vector<int> increased;
    if (value == 0) {
        printf("no old listener\n");
        value = new _event_listener;
    } else {
        // find diff events
        moreSet = ((~(value->events)) & eventSet); // moreSet = new event set - old event set
        mergedSet |= value->events; // mregedSet = new event set + old event set
    }
    value->events = mergedSet;
    value->listener = l;
    int len = n == NULL ? 0 : strlen(n);
    value->name = (char*)malloc(len+1);
    memcpy(value->name, n, len);
    value->name[len]=0;

    printf("save listener\n");
    // 将listener存到map中
    hashmapPut(mListenerMap, pointer(l), value);

    // 所有对应的event中，加入指向该listener的节点
    addEvents(value, moreSet);
}

void ListenerManager::addEvents(p_event_listener value, const BigBitSet& events) {
    printf("%s\n", __FUNCTION__);
    // 所有对应的event中，加入指向该listener的节点
    if (events.isEmpty()) return;
    int first = events.firstMarkedBit();
    int last = events.lastMarkedBit();

    printf("first %d, last %d\n", first, last);
    for(int i = first; i <= last; i++) {
        List<p_event_listener>* list = mEvents[i];
        if (list == NULL) {
            list = mEvents[i] = new List<p_event_listener>;
        }
        list->push_back(value);
    }
}

void ListenerManager::removeEvents(const sp<IEventListener>& l, const BigBitSet& events) {
    printf("%s\n", __FUNCTION__);
    if (events.isEmpty()) return;
    int first = events.firstMarkedBit();
    int last = events.lastMarkedBit();

    printf("first %d, last %d\n", first, last);
    for(int i = first; i <= last; i++) {
        // 循环mEvents[index]列表，删除 l
        List<p_event_listener>* list = mEvents[i];
        if (list == NULL) continue;
        List<p_event_listener>::iterator it = list->begin();
        bool find = false;
        for(; it != list->end(); it++) {
            if (pointer((*it)->listener) == pointer(l)) {
                printf("find item\n");
                find = true;
                break;
            }
        }
        if (find) {
            printf("erase item\n");
            list->erase(it);
        }
    }
}

void ListenerManager::dispatch(int event, const Parcelable* p) {
    int index = ((~EVENT_MASK) & event);
    printf("%s %d %d\n", __FUNCTION__, event, index);

    RWLock::AutoRLock rLock(mRWLock);
    const List<p_event_listener>* list = mEvents[index];
    if (list == NULL) return;
    List<p_event_listener>::const_iterator it = list->begin();
    for(; it != list->end(); it++) {
        printf("dispatch event to listener\n");
        SomeArgs* args = (SomeArgs*)p;
        printf("args: %s\n", args->arg1);
        (*it)->listener->onEvent(event, p);
    }
}

static bool callback(void* key, void* value, void* context) {
    const IEventListener* l = (IEventListener*) key;
    ListenerManager::p_event_listener pl = (ListenerManager::p_event_listener) value;
    printf("%p, {%s, %p, %0lx}\n", l, pl->name, pointer(pl->listener), pl->events.getValue());
    return true;
}

void ListenerManager::dump() {
    // start dump listeners
    printf("Events:\n");

    RWLock::AutoRLock rLock(mRWLock);
    for(int i = 0; i < MAX_EVENT_NUM; i++) {
        const List<p_event_listener>* list = mEvents[i];
        if (list == NULL || list->empty()) continue;
        printf("\n[%d]:", i);
        List<p_event_listener>::const_iterator it = list->begin();
        for(; it != list->end(); it++) {
            printf("->{%s, %p, %0lx}", (*it)->name, pointer((*it)->listener), (*it)->events.getValue());
        }
    }
    printf("\n");
    printf("Listeners:\n");
    hashmapForEach(mListenerMap, callback, NULL);
    //mListenerMap
}

}; // end namespace android
