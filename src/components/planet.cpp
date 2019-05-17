#include "../../headers/all_imports.h"
#include "../../headers/classes/planet.h"

Planet::Planet() {
    this->name = "Asgard";
    this->resources = new Resource(2);
    this->civilization = new Species();
}

int Planet::diplomacy() {
    return this->civilization->diplomacy();
}

void Planet::mining(SpaceShip *spaceship) {
    int mining_ability = spaceship->mining_ability();
    int food_needed = spaceship->food_needed();
    int fuel_needed = spaceship->fuel_needed();
    int gold_needed = spaceship->gold_needed();
    int scrap_needed = spaceship->scrap_needed();

    int food;
    int fuel;
    int gold;
    int scrap;

    if(food_needed < mining_ability) {
        food = food_needed;
    } else {
        food = (food_needed * mining_ability)/100;
    }

    if(fuel_needed < mining_ability) {
        fuel = fuel_needed;
    } else {
        fuel = (fuel_needed * mining_ability)/100;
    }

    if(gold_needed < mining_ability) {
        gold = gold_needed;
    } else {
        gold = (gold_needed * mining_ability) / 100;
    }

    if(scrap_needed < mining_ability) {
        scrap = scrap_needed;
    } else {
        scrap = (scrap_needed * mining_ability) / 100;
    }

    Resource *mined = new Resource(food, fuel, gold, scrap);
    spaceship->resources = spaceship->resources->operator+(mined);
    delete mined;
}

void Planet::trading(SpaceShip *spaceship) {
    this->civilization->trade(spaceship);
}

void Planet::conflict(SpaceShip *spaceship) {
    spaceship->combat(this->civilization->get_spaceship());
}

