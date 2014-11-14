#include "../include/MessageException.h"

MessageException::MessageException(std::string message) noexcept :
msg(message)
{}

MessageException::~MessageException() noexcept
{}

std::string MessageException::getMessage() const
{
    return msg;
}
