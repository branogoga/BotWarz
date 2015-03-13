#pragma once

#pragma warning(push)
#pragma warning(disable: 4251 /* Shared_ptr going across Dll (Test) */ )

#include "dll.h"

#include <boost/noncopyable.hpp>

#include <fstream>
#include <memory>
#include <stdlib.h>
#include <string>

class DLL_API Logger : boost::noncopyable
{
public:

    Logger()
    {
    }

    Logger(
        const std::string& i_szFilename
        )
    {
        open(i_szFilename);
    }

    virtual ~Logger()
    {
        close();
    }

    template<class T>
    Logger& operator<<(T value)
    {
        m_log << value;
        return *this;
    }

    Logger& operator<<(std::ostream& (* /*endlPar*/) (std::ostream& os))
    {
        m_log << std::endl;
        return *this;
    }

    void open(
        const std::string& i_szFilename
        )
    {
        m_log.open(i_szFilename);
    }

    bool is_open() const
    {
        return m_log.is_open();
    }

    void close()
    {
        m_log.close();
    }

    std::ostream& getLog()
    {
        return m_log;
    }

private:
    std::ofstream m_log;
};

#pragma warning(pop)