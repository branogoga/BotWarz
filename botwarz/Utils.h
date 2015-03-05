#pragma once

#ifdef WIN32
    # define WHILE_TRUE __pragma( warning(push) ) \
        __pragma(warning(disable:4127)) \
        while (true) \
        __pragma(warning(pop))
#else
    #define WHILE_TRUE while( true )
#endif