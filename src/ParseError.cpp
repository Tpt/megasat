#include "../include/ParseError.h"

ParseError::ParseError(std::string message) noexcept :
msg(message)
{}

ParseError::~ParseError() noexcept
{}

std::string ParseError::getMessage() const
{
    return msg;
}
