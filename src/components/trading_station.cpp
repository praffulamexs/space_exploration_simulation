#include "../../headers/all_imports.h"
#include "../../headers/classes/trading_station.h"

TradingStation::TradingStation() {
    this->name = "Example";
    this->species = new Species();
}

int TradingStation::trading_score() {
    return this->species->diplomacy();
}

void TradingStation::trade(SpaceShip *spaceship) {
    this->species->trade(spaceship);
}

