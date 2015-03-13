#include "./Logger.h"

#include <boost/noncopyable.hpp>

#include <fstream>
#include <memory>
#include <stdlib.h>
#include <string>

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
