//
//  Header.h
//  MyGLSL
//
//  Created by xy on 27/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyPercompiled_hpp
#define MyPercompiled_hpp

//#define MINE_LIBRARY_PUSH #pragma GCC visibility push(default)
//#define MINE_LIBRARY_POP #pragma GCC visibility pop

#define MINE_NAMESPACE_BEGIN namespace Mine {
#define MINE_NAMESPACE_END }
#define USING_MINE_NAMESPACE using namespace Mine
#define MINE_NAMESPACE Mine

#ifdef MINE_DEBUG
#define FORCEINLINE inline
#else
#define FORCEINLINE inline __attribute__((always_inline))
#endif
#define FORCENOINLINE __attribute__((noinline))

#ifdef MINE_DEBUG
#include <cassert>
#define MINE_ASSERT(n) assert(n)
#define MINE_ASSERT2(n, d) assert(n && d)
#else
#define MINE_ASSERT(n)
#define MINE_ASSERT2(n, d)
#endif

#endif /* Header_h */
