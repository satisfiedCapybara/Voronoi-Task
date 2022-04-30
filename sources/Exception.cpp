//
// Created by semen on 11.09.2021.
//
#include <iostream>
#include "headers/Exception.h"

const char *exceptionG::geomException::what() const noexcept
{
    std::cout << myErrorDescription;
    std::cout << "Приплыли" <<std::endl;
    return exception::what();
}
