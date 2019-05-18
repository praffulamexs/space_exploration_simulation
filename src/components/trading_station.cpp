#include "../../headers/all_imports.h"
#include "../../headers/classes/trading_station.h"

TradingStation::TradingStation() {
    this->name = trading_stations_names[rand() % trading_stations_names.size()];
    this->species = new Species();
}

int TradingStation::trading_score() {
    return this->species->diplomacy();
}

void TradingStation::trade(SpaceShip *spaceship) {
    this->species->trade(spaceship);
}

string TradingStation::get_species_name() {
    return this->species->get_species_name();
}