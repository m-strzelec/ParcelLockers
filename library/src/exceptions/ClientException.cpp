#include "exceptions/ClientException.h"

ClientException::ClientException(const std::string &what_arg) noexcept: logic_error(what_arg) {}
