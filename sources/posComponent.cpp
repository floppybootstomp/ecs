#include "../headers/posComponent.h"

/*
PosComponent::PosComponent()
{
}

PosComponent::~PosComponent()
{
    for(int i = 0; i < MAX_ENTITIES; i ++){
        removeComponent(i);
    }
}

void PosComponent::addComponent(int eid, int px, int py)
{
    if(eid >= MAX_ENTITIES)
        return;

    components[eid] = new pc(px, py);
}

void PosComponent::removeComponent(int eid)
{
    if(eid >= MAX_ENTITIES)
        return;

    if(components[eid] != nullptr)
        delete components[eid];
}

PosComponent::pc PosComponent::getComponent(int eid)
{
    pc rPc(0, 0);
    if(eid < MAX_ENTITIES)
        rPc = *components[eid];

    return rPc;
}

void PosComponent::setComponent(int eid, int px, int py)
{
    if(eid >= MAX_ENTITIES)
        return;

    components[eid]->x = px;
    components[eid]->y = py;
}
*/
