#include "../headers/entityManager.h"

EntityManager::EntityManager()
{
    for(int i = 0; i < MAX_ENTITIES; i ++)
        availableIds.push(i);

    for(int i = 0; i < MAX_ENTITIES; i ++)
        entityId[i] = -1;
}

EntityManager::~EntityManager()
{
}

int EntityManager::addEntity()
{
    if(entityCount >= MAX_ENTITIES)
        return -1;

    int ae = availableIds.front();

    entityId[ae] = ae;
    availableIds.pop();
    entityCount ++;

    return ae;
}

int EntityManager::removeEntity(int eid)
{
    if(eid >= MAX_ENTITIES)
        return -1;

    int re = entityId[eid];

    entityId[eid] = -1;
    availableIds.push(re);
    entityCount --;

    return re;
}

int EntityManager::getEntity(int eid)
{
    if(eid >= MAX_ENTITIES)
        return -1;

    return entityId[eid];
}
