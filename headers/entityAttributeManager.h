#include <string>
#include <unordered_map>
#include <utility>
#include <iostream>
#include "globalVars.h"
#include "entityAttributeArray.h"

#ifndef ENTITYATTRIBUTEMANAGER_H
#define ENTITYATTRIBUTEMANAGER_H

class EntityAttributeManager
{
    std::unordered_map<std::string, IEntityAttributeArray*> attributeMap;

public:
    EntityAttributeManager()
    {
    }

    ~EntityAttributeManager()
    {
    }

    // sets the right attribute in the right attribute array and adds attribute array to attribute array map if doesn't exist
    template<typename T>
    void set(int eid, T* attr = new T())
    {
        std::string attrKey = typeid(T).name();

        if(attributeMap[attrKey] == nullptr)
        {
            addAttributeArray<T>();
        }

        getAttributeArray<T>()->set(eid, attr);
    }

    // removes the right attribute from the right attribute array and removes the attribute array if empty
    template<typename T>
    void remove(int eid)
    {
        std::string attrKey = typeid(T).name();

        if(attributeMap[attrKey] != nullptr)
        {
            getAttributeArray<T>()->entityDestroyed(eid);

            if(getAttributeArray<T>()->size() == 0)
            {
                removeAttributeArray<T>();
            }
        }
    }

    void entityDestroyed(int eid)
    {
        if(attributeMap.size() > 0)
        {
            for(auto& i : attributeMap)
                i.second->entityDestroyed(eid);

            auto i = attributeMap.begin();
            while(i != attributeMap.end() && attributeMap.size() > 0)
            {
                IEntityAttributeArray* temp = i->second;
                if(temp->size() == 0)
                {
                    i = attributeMap.erase(i);
                    delete temp;
                }
                else
                {
                    i ++;
                }
            }
        }
    }

    // adds an attribute array to the attribute array map
    template<typename T>
    void addAttributeArray()
    {
        std::string attrKey = typeid(T).name();
        attributeMap[attrKey] = new EntityAttributeArray<T>;
    }

    // removes an attribute array from the map of attributes
    template<typename T>
    void removeAttributeArray()
    {
        std::string attrKey = typeid(T).name();
        IEntityAttributeArray* temp = attributeMap[attrKey];
        attributeMap.erase(attrKey);
        delete temp;
    }

    // returns the right attribute from the right attribute array
    template<typename T>
    T* get(int eid)
    {
        std::string attrKey = typeid(T).name();

        if(attributeMap.size() == 0 || attributeMap[attrKey] == nullptr)
            return new T();

        return getAttributeArray<T>()->get(eid);
    }

    template<typename T>
    EntityAttributeArray<T>* getAttributeArray()
    {
        std::string attrKey = typeid(T).name();
        return ((EntityAttributeArray<T>*)attributeMap[attrKey]);
    }
};

#endif // ENTITYATTRIBUTEMANAGER_H

