#include "globalVars.h"

#ifndef ENTITYATTRIBUTEARRAY_H
#define ENTITYATTRIBUTEARRAY_H

class IEntityAttributeArray
{
public:
    virtual ~IEntityAttributeArray() = default;
    virtual void entityDestroyed(int eid) = 0;
    virtual int size() = 0;
};

template<typename T>
class EntityAttributeArray : public IEntityAttributeArray
{
    T* eaArray[MAX_ENTITIES];
    int eaArraySize = 0;
public:
    EntityAttributeArray()
    {
        for(int i = 0; i < MAX_ENTITIES; i ++)
            eaArray[i] = nullptr;
    }

    ~EntityAttributeArray()
    {
        for(int i = 0; i < MAX_ENTITIES; i ++)
            if(eaArray[i] != nullptr)
                delete eaArray[i];
    }

    // add an attribute to the attribute array
    void set(int eid, T* attribute)
    {
        if(eid < MAX_ENTITIES && eid >= 0)
        {
            // increase array size if new element
            if(eaArraySize <= MAX_ENTITIES && eaArray[eid] == nullptr)
                eaArraySize ++;

            eaArray[eid] = attribute;
        }
    }

    // remove an attribute from the attribute array
    void remove(int eid)
    {
        if(eid < MAX_ENTITIES && eid >= 0)
        {
            if(eaArray[eid] != nullptr)
            {
                eaArray[eid] = nullptr;
                if(eaArraySize > 0)
                    eaArraySize --;
            }
        }
    }

    // destroy an attribute when entity is destroyed
    void entityDestroyed(int eid)
    {
        if(eid < MAX_ENTITIES && eid >= 0)
            remove(eid);
    }

    // get an attribute from array
    T* get(int eid)
    {
        T* rAttr = new T();
        if(eid < MAX_ENTITIES && eid >= 0 && eaArray[eid] != nullptr)
            rAttr = eaArray[eid];

        return rAttr;
    }

    // get an attribute from array
    T* &operator[](int eid)
    {
        return get(eid);
    }

    // return size of entity array
    int size()
    {
        return eaArraySize;
    }
};

#endif // ENTITYATTRIBUTEARRAY_H

