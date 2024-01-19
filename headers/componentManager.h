#include <string>
#include <unordered_map>
#include <iostream>
#include "globalVars.h"
#include "component.h"

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

class ComponentManager
{
    std::unordered_map<std::string, IComponentArray*> componentMap;

public:
    ComponentManager();
    ~ComponentManager();

    // sets the right component in the right component array and adds component array to component array map if doesn't exist
    template<typename T>
    void setComponent(int eid, T* cpt = new T())
    {
        std::string cptKey = typeid(T).name();
        if(componentMap[cptKey] == nullptr)
        {
            addComponentArray<T>();
            std::cout << "added " << cptKey << " componentArray" << std::endl;
        }

        ((ComponentArray<T>*)componentMap[cptKey])->setComponent(eid, cpt);
    }

    // removes the right component from the right component array and removes the component array if empty
    template<typename T>
    void removeComponent(int eid)
    {
        std::string cptKey = typeid(T).name();
        if(componentMap[cptKey] != nullptr)
        {
            ((ComponentArray<T>*)componentMap[cptKey])->entityDestroyed(eid);

            if(componentMap[cptKey]->size() == 0)
            {
                removeComponentArray<T>();
                std::cout << "removed " << cptKey << " componentArray" << std::endl;
            }
        }
    }

    // adds a component array to the component array map
    template<typename T>
    void addComponentArray()
    {
        std::string cptKey = typeid(T).name();
        componentMap[cptKey] = new ComponentArray<T>;
    }

    // removes a component array from the map of components
    template<typename T>
    void removeComponentArray()
    {
        std::string cptKey = typeid(T).name();
        IComponentArray* temp = componentMap[cptKey];
        componentMap.erase(cptKey);
        delete temp;
    }

    // returns the right component from the right component array
    template<typename T>
    T* getComponent(int eid)
    {
        std::string cptKey = typeid(T).name();
        return ((ComponentArray<T>*)componentMap[cptKey])->getComponent(eid);
    }
};

#endif // COMPONENTMANAGER_H
