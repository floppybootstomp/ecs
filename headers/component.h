#include "globalVars.h"

#ifndef COMPONENT_H
#define COMPONENT_H

struct posComponent
{
    int x;
    int y;
    posComponent() : x(0), y(0) {};
    posComponent(int px, int py) : x(px), y(py) {};
};

struct moveComponent
{
    int xSpeed;
    int ySpeed;
    moveComponent() : xSpeed(0), ySpeed(0) {};
    moveComponent(int sx, int sy) : xSpeed(sx), ySpeed(sy) {};
};

struct drawComponent
{
    char image;
    int color;
    drawComponent() : image(' '), color(LIGHT_PALLET) {};
    drawComponent(char i, int c) : image(i), color(c) {};
};

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void entityDestroyed(int eid) = 0;
    virtual int size() = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
    T* cptArray[MAX_ENTITIES];
    int cptArraySize = 0;
public:
    ComponentArray()
    {
        for(int i = 0; i < MAX_ENTITIES; i ++)
            cptArray[i] = nullptr;
    }

    ~ComponentArray()
    {
        for(int i = 0; i < MAX_ENTITIES; i ++)
            if(cptArray[i] != nullptr)
                delete cptArray[i];
    }

    // add a component to the component array
    void setComponent(int eid, T* component)
    {
        if(eid < MAX_ENTITIES && eid >= 0)
        {
            // increase array size if new element
            if(cptArraySize <= MAX_ENTITIES && cptArray[eid] == nullptr)
                cptArraySize ++;

            cptArray[eid] = component;
        }
    }

    // remove a component from the component array
    void removeComponent(int eid)
    {
        if(eid < MAX_ENTITIES && eid >= 0)
        {
            cptArray[eid] = nullptr;
            if(cptArraySize > 0)
                cptArraySize --;
        }
    }

    // destroy a component when entity is destroyed
    void entityDestroyed(int eid)
    {
        if(eid < MAX_ENTITIES && eid >= 0)
            removeComponent(eid);
    }

    // get a component from array
    T* getComponent(int eid)
    {
        T* rCpt;
        if(eid < MAX_ENTITIES && eid >= 0)
            rCpt = cptArray[eid];

        return rCpt;
    }

    // get a component from array
    T* &operator[](int eid)
    {
        T* rCpt;
        if(eid < MAX_ENTITIES && eid >= 0)
            rCpt = cptArray[eid];

        return rCpt;
    }

    // return size of entity array
    int size()
    {
        return cptArraySize;
    }
};

#endif // COMPONENT_H
