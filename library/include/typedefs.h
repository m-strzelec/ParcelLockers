#ifndef PARCELLOCKERS_TYPEDEFS_H
#define PARCELLOCKERS_TYPEDEFS_H

#include <memory>
#include <functional>

class Client;
class Order;
class Parcel;
class Address;

template<class T>
using Ptr = std::shared_ptr<T>;

typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Order> OrderPtr;
typedef std::shared_ptr<Parcel> ParcelPtr;
typedef std::shared_ptr<Address> AddressPtr;

template<class ModelPtr>
using Predicate = std::function<bool(ModelPtr)>;

typedef std::function<bool(ClientPtr)> ClientPredicate;
typedef std::function<bool(OrderPtr)> OrderPredicate;
typedef std::function<bool(ParcelPtr)> ParcelPredicate;
#endif //PARCELLOCKERS_TYPEDEFS_H
