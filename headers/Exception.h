#pragma once

#include <exception>
#include <string>
namespace exceptionG
{
class geomException: public std::exception
    {
    public:
        geomException(const std::string& aError, std::size_t aCode) { aCode = myCode; myErrorDescription = aError;};
        const char* what() const noexcept override;

    private:
        std::size_t myCode{};
        std::string myErrorDescription;
    };
}
