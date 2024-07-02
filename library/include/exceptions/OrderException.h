#ifndef PARCELLOCKERS_ORDEREXCEPTION_H
#define PARCELLOCKERS_ORDEREXCEPTION_H

#include <stdexcept>

class OrderException : public std::logic_error {
public:
    explicit OrderException(const std::string & what_arg) noexcept;
};

#endif //PARCELLOCKERS_ORDEREXCEPTION_H
