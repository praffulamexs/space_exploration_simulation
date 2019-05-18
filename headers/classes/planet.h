#ifndef planet_class
#define planet_class

#include "./resource.h"
#include "./species.h"
#include "./spaceship.h"

class Planet {
    private:
        string name;
        Resource *resources;
        Species *civilization;

    public:
        Planet();
        string get_name();
        void mining(SpaceShip*);
        int diplomacy();
        void trading(SpaceShip*);
        void conflict(SpaceShip*);
};

#endif

