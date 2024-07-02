#ifndef PARCELLOCKERS_PARCELEXCEPTION_H
#define PARCELLOCKERS_PARCELEXCEPTION_H

#include <stdexcept>

class ParcelException : public std::logic_error {
public:
    explicit ParcelException(const std::string & what_arg) noexcept;
};

#endif //PARCELLOCKERS_PARCELEXCEPTION_H
