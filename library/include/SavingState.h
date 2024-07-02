#ifndef PARCELLOCKERS_SAVINGSTATE_H
#define PARCELLOCKERS_SAVINGSTATE_H

#include "model/Client.h"
#include "model/Address.h"
#include "model/Order.h"
#include "model/Parcel.h"
#include "nlohmann/json.hpp"

class SavingState {
public:

    static std::string toJSON(const ClientPtr& x)
    {
        nlohmann::json j = nlohmann::json::object();
        j["firstName"] = x->getFirstName();
        j["lastName"] = x->getLastName();
        j["personalID"] = x->getPersonalID();
        j["address"] = x->getAddress()->getAddressInfo();
        return j.dump();
    }

    static std::string toJSON(const ParcelPtr& x)
    {
        nlohmann::json j = nlohmann::json::object();
        j["id"] = x->getId();
        j["mass"] = x->getMass();
        j["inLocker"] = x->isInLocker();
        j["basePrice"] = x->getBasePrice();
        return j.dump();

    }
    static std::string toJSON(const OrderPtr& x)
    {
        nlohmann::json j = nlohmann::json::object();
        std::stringstream begin, end;
        begin<<x->getBeginTime(); end<<x->getEndTime();

        j["id"] = x->getId();
        j["client"] = x->getClient()->getClientInfo();
        j["parcel"] = x->getParcel()->getParcelInfo();
        j["address"] = x->getAddress()->getAddressInfo();
        j["beginTime"] = begin.str();
        j["endTime"] = end.str();
        j["sentCost"] = x->getSentCost();
        return j.dump();
    }
};

#endif //PARCELLOCKERS_SAVINGSTATE_H
