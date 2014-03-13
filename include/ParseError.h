#ifndef ParseError_H
#define ParseError_H

#include <string>

class ParseError : public std::exception
{
public:
    ParseError(std::string message) noexcept;
    ~ParseError() noexcept;
    std::string getMessage() const;
private:
    std::string msg;
};

#endif
