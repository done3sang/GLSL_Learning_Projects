//
//  MyTimerManager.hpp
//  MyGLSL
//
//  Created by Sang on 12/10/17.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyTimerManager_hpp
#define MyTimerManager_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingletonRef;

class MyTimerManager final: public MySingletonRef {
public:
    static MyTimerManager* sharedTimerManager(void);
    static void closeTimerManager(void);
    
    bool timing(void) const { return _timing; }
    double startTime(void) const { return _startTime; }
    double elapsedTime(void) const { return _elapsedTime; }
    double tickTime(void) const { return _tickTime; }
    
    void beginTiming(void);
    void stopTiming(void);
    
    void beginTick(void);
    void endTick(void);
    
    double currentTime(void) const;
    
private:
    MyTimerManager(void): _timing(false), _startTime(0.0),
        _elapsedTime(0.0), _tickStartTime(0.0), _tickTime(0.016) {}
    ~MyTimerManager(void) {}
    
    bool _timing;
    double _startTime;
    double _elapsedTime;
    double _tickStartTime;
    double _tickTime;
    
    static MyTimerManager *_sharedTimerManager;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyTimerManager_hpp */
