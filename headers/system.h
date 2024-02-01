#include "component.h"
#include "entityAttributeManager.h"

struct moveSystem {
    void execute(EntityAttributeManager* componentManager, int eid)
    {
        posComponent npc;
        posComponent* pc = componentManager->get<posComponent>(eid);
        moveComponent* mc = componentManager->get<moveComponent>(eid);
        pc->x += mc->xSpeed;
        pc->y += mc->ySpeed;

        componentManager->set<posComponent>(eid, pc);
    }
};

void drawSystem(posComponent* pc, drawComponent* dc)
{
    for(int i = 0; i <= pc->y; i ++)
    {
        for(int j = 0; j < pc->x; j ++)
        {
            std::cout << " ";
        }

        if(i == pc->y)
            std::cout << dc->image;

        std::cout << std::endl;
    }
}
