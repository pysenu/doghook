/*
 * gameinfo.hpp
 *
 *  Created on: May 11, 2017
 *      Author: nullifiedcat
 */

#ifndef GAMEINFO_HPP_
#define GAMEINFO_HPP_

#include "common.h"

#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

/*
 * make -j4 -e GAME=tf2
 */

// http://stackoverflow.com/questions/2335888/how-to-compare-string-in-c-conditional-preprocessor-directives
constexpr int c_strcmp( char const* lhs, char const* rhs ) {
    return (('\0' == lhs[0]) && ('\0' == rhs[0])) ? 0
        :  (lhs[0] != rhs[0]) ? (lhs[0] - rhs[0])
        : c_strcmp( lhs+1, rhs+1 );
}

#ifdef BUILD_GAME
constexpr bool IsTF2() { return !c_strcmp(TO_STRING(BUILD_GAME), "tf2"); }
constexpr bool IsTF2C() { return !c_strcmp(TO_STRING(BUILD_GAME), "tf2c"); }
constexpr bool IsHL2DM() { return !c_strcmp(TO_STRING(BUILD_GAME), "hl2dm"); }
constexpr bool IsCSS() { return !c_strcmp(TO_STRING(BUILD_GAME), "css"); }

constexpr bool IsTF() { return IsTF2() || IsTF2C(); }

// This one is supposed to be `if constexpr` but I have to upgrade to gcc7
#define IF_GAME(x) if (x)

#else
inline bool IsTF2() { return g_AppID == 440; }
inline bool IsTF2C() { return g_AppID == 243750; }
inline bool IsHL2DM() { return g_AppID == 320; }
inline bool IsCSS() { return g_AppID == 240; }

inline bool IsTF() { return IsTF2() || IsTF2C(); }

#define IF_GAME(x) if (x)

#endif

#ifndef FORCE_SINGLE_GAME
#define CURRENT_APPID g_AppID
#else
#define CURRENT_APPID (SINGLE_APPID)
#endif

#endif /* GAMEINFO_HPP_ */
