#ifndef species_class
#define species_class

#include "./species_attributes.h"
#include "./resource.h"
#include "./spaceship.h"

class Species {
    private:
        string name;
        SpeciesAttributes *attributes;
        Resource *resources;
        SpaceShip *spaceship;
        void do_trading(SpaceShip*, int);

    public:
        Species();
        int diplomacy();
        void trade(SpaceShip*);
        SpaceShip* get_spaceship();
};

#endif

