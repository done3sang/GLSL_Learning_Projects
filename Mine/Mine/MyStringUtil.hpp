//
//  MyStringUtil.hpp
//  MyGLSL
//
//  Created by xy on 08/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyStringUtil_hpp
#define MyStringUtil_hpp

#include <string.h>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyStatic;

class MyStringUtil final: private MyStatic {
public:
    static FORCEINLINE bool space(char c) {
        return ' ' == c;
    }
    
    static FORCEINLINE bool newline(char c) {
        return '\r' == c or '\n' == c;
    }
    
    static FORCEINLINE bool whitespace(char c) {
        return space(c) or newline(c);
    }
    
    static FORCEINLINE bool digit(char c) {
        return '0' <= c && c <= '9';
    }
    
    static FORCEINLINE bool uppercase(char c) {
        return 'A' <= c && c <= 'Z';
    }
    
    static FORCEINLINE bool lowercase(char c) {
        return 'a' <= c && c <= 'z';
    }
    
    static FORCEINLINE bool alpha(char c) {
        return uppercase(c) || lowercase(c);
    }
    
    static FORCEINLINE bool digit_alpha(char c) {
        return digit(c) || alpha(c);
    }
    
    static FORCEINLINE bool variable(char c) {
        return digit_alpha(c) || '_' == c;
    }
    
    static FORCEINLINE bool equal_string(const char* str1, const char* str2) {
        return strcmp(str1, str2) == 0;
    }
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyStringUtil_hpp */
