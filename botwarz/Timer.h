#pragma once

#include <ctime>

class Timer
{
public:

    Timer()
    {
        m_start = std::clock();
    }

    virtual ~Timer()
    {
    }

    double  getTimeInMilliseconds() const
    {
        return (std::clock() - m_start) / (double)(CLOCKS_PER_SEC / 1000);
    }

private:
    std::clock_t    m_start;
};

