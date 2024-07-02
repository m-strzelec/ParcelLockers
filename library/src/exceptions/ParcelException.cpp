#include "exceptions/ParcelException.h"

ParcelException::ParcelException(const std::string &what_arg) noexcept: logic_error(what_arg) {}
