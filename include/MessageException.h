#ifndef MessageException_H
#define MessageException_H

#include <string>

class MessageException : public std::exception
{
public:
    MessageException(std::string message) noexcept;
    ~MessageException() noexcept;
    std::string getMessage() const;
private:
    std::string msg;
};

#endif
