//
//  MyTimerManager.cpp
//  MyGLSL
//
//  Created by Sang on 12/10/17.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <sys/time.h>
#include "MyObject.hpp"
#include "MyTimerManager.hpp"

MINE_NAMESPACE_BEGIN

MyTimerManager* MyTimerManager::_sharedTimerManager = nullptr;

MyTimerManager* MyTimerManager::sharedTimerManager(void) {
    if(!_sharedTimerManager) {
        _sharedTimerManager = new MyTimerManager;
        _sharedTimerManager->objectName("MyTimerManager");
    }
    return _sharedTimerManager;
}

void MyTimerManager::closeTimerManager(void) {
    if(_sharedTimerManager) {
        _sharedTimerManager->release();
        _sharedTimerManager = nullptr;
    }
}

double MyTimerManager::currentTime(void) const {
    struct timeval tv;
    double timeInSec(0.0f);
    
    if(0 == gettimeofday(&tv, nullptr)) {
        timeInSec = static_cast<double>(tv.tv_sec) + static_cast<double>(tv.tv_usec)/1000000.0;
    }
    return timeInSec;
}

void MyTimerManager::beginTiming(void) {
    _startTime = currentTime();
    _timing = true;
}

void MyTimerManager::stopTiming(void) {
    _elapsedTime = currentTime() - _startTime;
    _timing = false;
}

void MyTimerManager::beginTick(void) {
    _tickStartTime = currentTime();
}

void MyTimerManager::endTick(void) {
    _tickTime = currentTime() - _tickStartTime;
}

MINE_NAMESPACE_END
