//
//  MyStringUtil.hpp
//  MyGLSL
//
//  Created by xy on 08/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyStringUtil_hpp
#define MyStringUtil_hpp

#include "MyTemplate.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyStringUtil {
public:
    static bool space(char c) {
        return ' ' == c;
    }
    
    static bool newline(char c) {
        return '\r' == c or '\n' == c;
    }
    
    static bool whitespace(char c) {
        return space(c) or newline(c);
    }
    
    static bool digit(char c) {
        return '0' <= c && c <= '9';
    }
    
    static bool uppercase(char c) {
        return 'A' <= c && c <= 'Z';
    }
    
    static bool lowercase(char c) {
        return 'a' <= c && c <= 'z';
    }
    
    static bool alpha(char c) {
        return uppercase(c) || lowercase(c);
    }
    
    static bool digit_alpha(char c) {
        return digit(c) || alpha(c);
    }
    
    static bool variable(char c) {
        return digit_alpha(c) || '_' == c;
    }
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyStringUtil_hpp */
