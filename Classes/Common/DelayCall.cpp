//
// Created by farmer on 2018/7/8.
//

#include "DelayCall.h"
#include <mutex>

typedef struct {
    float time;
    float delay;
    int   count;
    std::function<void(void)> fun;
} tick_item;

static std::recursive_mutex dc_mutex;
static size_t dc_count = 0;
static std::map< size_t, tick_item > dc_funList;
static std::map< size_t, tick_item > dc_funListTemp;

void DelayCall::tick(float delta) {
    std::lock_guard<std::recursive_mutex> l(dc_mutex);
    std::vector<size_t> tmp;
    if (dc_funListTemp.empty() && dc_funList.empty()) {
        return;
    }
    for (std::map< size_t, tick_item >::const_iterator it = dc_funListTemp.begin(); it != dc_funListTemp.end(); ) {
        dc_funList[it->first] = it->second;
        ++it;
    }
    dc_funListTemp.clear();
    for (std::map< size_t, tick_item >::iterator it = dc_funList.begin(); it != dc_funList.end(); ) {
        it->second.time += delta;
        if (it->second.time - it->second.delay > 0.0001f) {
            it->second.count--;
            it->second.time = 0;
            it->second.fun();
            if (it->second.count <= 0) {
                tmp.push_back(it->first);
            }
        }
        ++it;
    }
    for (auto& it : tmp) {
        auto item = dc_funList.find(it);
        if (item != dc_funList.end()) {
            dc_funList.erase(item);
        }
    }
}

void DelayCall::add(std::function<void(void)> fun, float delay, int count) {
    std::lock_guard<std::recursive_mutex> l(dc_mutex);
    dc_funListTemp[dc_count++] = { 0, delay, count, fun };
}

void DelayCall::clear() {
    std::lock_guard<std::recursive_mutex> l(dc_mutex);
    dc_funList.clear();
    dc_funListTemp.clear();
}


