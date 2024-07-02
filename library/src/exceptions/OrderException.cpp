#include "exceptions/OrderException.h"

OrderException::OrderException(const std::string &what_arg) noexcept: logic_error(what_arg) {}
