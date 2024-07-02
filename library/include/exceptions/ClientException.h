#ifndef PARCELLOCKERS_CLIENTEXCEPTION_H
#define PARCELLOCKERS_CLIENTEXCEPTION_H

#include <stdexcept>

class ClientException : public std::logic_error {
public:
    explicit ClientException(const std::string & what_arg) noexcept;
};

#endif //PARCELLOCKERS_CLIENTEXCEPTION_H
