#ifndef PARCELLOCKERS_REPOSITORY_H
#define PARCELLOCKERS_REPOSITORY_H

#include <vector>
#include <string>
#include "typedefs.h"

template<class Model> class Repository {

protected:
    std::vector<Ptr<Model>> registry;

public:
    ~Repository() = default;

    Ptr<Model> getObject(int index) noexcept {
        try {
            return registry.at(index);
        } catch (std::out_of_range & e) {
            return nullptr;
        }
    }

    void addObject(Ptr<Model> model) {
        if (model == nullptr) return;
        registry.push_back(model);
    }

    void removeObject(Ptr<Model> model) {
        if (model == nullptr) return;
        for(auto i = registry.begin(); i != registry.end(); i++)
            if((*i) == model)
            {
                registry.erase(i);
                return;
            }
    }

    std::string report() const {
        std::string ret = "[";
        for (auto & curElem : registry)
            ret += '(' + curElem->getInfo() + "), ";
        ret = ret.substr(0, ret.size()-2) + ']';

        return ret;
    }

    size_t size() const noexcept {
        return registry.size();
    }

    std::vector<Ptr<Model>> findBy(Predicate<Ptr<Model>> matchingMethod) const {
        std::vector<Ptr<Model>> found;
        for (int i = 0; i < registry.size(); ++i) {
            Ptr<Model> curElem = registry[i];
            if (curElem != nullptr && matchingMethod(curElem)) found.push_back(curElem);
        }
        return found;
    }

    std::vector<Ptr<Model>> findAll()  {
        Predicate<Ptr<Model>> f = [](Ptr<Model> elem) -> bool { return true; };
        return findBy(f);
    }

    template<class ID>
    Ptr<Model> findById(ID id) const {
        Predicate<Ptr<Model>> f = [id](const Ptr<Model> & elem) -> bool {
            return elem->getId() == id;
        };
        auto found = findBy(f);
        return found.empty() ? nullptr : found[0];
    }
};

#endif //PARCELLOCKERS_REPOSITORY_H
