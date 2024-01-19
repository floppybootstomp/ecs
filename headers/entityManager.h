#include <queue>
#include "globalVars.h"

#ifndef ENTITY_H
#define ENTITY_H


class EntityManager
{
    int entityId[MAX_ENTITIES];
    int entityCount = 0;

    std::queue<int> availableIds;
public:
    EntityManager();
    ~EntityManager();

    // adds entity and returns added entity id
    int addEntity();

    // removes entity and returns removed entity id
    int removeEntity(int eid);

    int getEntity(int eid);
};

#endif // ENTITY_H
