#ifndef tradingstation_class
#define tradingstation_class

#include "./spaceship.h"
#include "./resource.h"
#include "./species.h"

class TradingStation {
    private:
        string name;
        Species *species;

    public:
        TradingStation();
        int trading_score();
        void trade(SpaceShip*);
};

#endif

