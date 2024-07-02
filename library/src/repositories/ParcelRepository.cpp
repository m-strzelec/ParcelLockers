#include "repositories/ParcelRepository.h"

ParcelPtr ParcelRepository::findByParcelId(int id) const {
    return findById<int>(id);
}