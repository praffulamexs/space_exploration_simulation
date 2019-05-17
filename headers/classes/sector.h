#ifndef sector_class
#define sector_class

#include "./spaceship.h"
#include "./trading_station.h"
#include "./planet.h"

class Sector {
    private:
        int sector_width;
        bool journey;
    public:
        Sector(SpaceShip*);
        bool journey_ended();
        void spaceship_encountered(SpaceShip*, SpaceShip*);
        void planet_encountered(Planet*, SpaceShip*);
        void empty_sector();
        void trading_station_encountered(TradingStation*, SpaceShip*);
        void abandoned_spaceship_encountered(SpaceShip*, SpaceShip*);
        void end_report();
};

#endif

