#ifndef ParseError_H
#define ParseError_H

#include "MessageException.h"

class ParseError : public MessageException
{
public:
    ParseError(std::string message) noexcept : MessageException(message) {};
};

#endif
