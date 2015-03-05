#pragma once

#include "dll.h"

class DLL_API Testable
{
public:

    Testable();
    virtual ~Testable();

    unsigned add(unsigned i_number1, unsigned i_number2);
};

