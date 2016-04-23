#ifndef _STATIC_INCLUDE_H_
#define _STATIC_INCLUDE_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include <cassert>
#include <limits>
#include <typeinfo>
#include <utility>
#include <memory>
#include <algorithm>
#include <functional>
class ErrorMsg
{
public:
    ErrorMsg() {}
    ~ErrorMsg() {}
    
    template <typename Type>
    ErrorMsg & operator << (const Type & value)
    {
        stream_ << value;
        return *this;
    }
    
    std::string str() const         { return stream_.str(); }
    operator std::string () const   { return stream_.str(); }
    
private:
    
    std::stringstream stream_;
    ErrorMsg(const ErrorMsg &);
    ErrorMsg & operator = (ErrorMsg &);
};

typedef std::runtime_error ERR;
#endif
