#include "../../headers/all_imports.h"
#include "../../headers/classes/species.h"

Species::Species() {
    this->name = species_names[rand() % species_names.size()];
    this->attributes = new SpeciesAttributes();
    this->resources = new Resource(1);
    this->spaceship = new SpaceShip(true, this->attributes->get_diplomacy_score(), this->attributes->get_trading_score());
}

string Species::get_species_name() {
    return this->name;
}

int Species::diplomacy() {
    return this->attributes->get_diplomacy_score();
}

void Species::trade(SpaceShip *another_spaceship) {
    int trade_multiplier;
    bool traveler_trade = (rand() % 100 + 1) <= another_spaceship->trading();
    bool species_trade = (rand() % 100 + 1) <= this->attributes->get_trading_score();

    if(traveler_trade && species_trade) {
        trade_multiplier = 4;
        this->do_trading(another_spaceship, trade_multiplier);
    } else if(traveler_trade && !species_trade) {
        trade_multiplier = 3; // If they are bad at trading, they end up paying more
        this->do_trading(another_spaceship, trade_multiplier);
    } else if (!traveler_trade && species_trade) {
        trade_multiplier = 5; // If travelers are bad at trading, they end up paying more
        this->do_trading(another_spaceship, trade_multiplier);
    }
}

void Species::do_trading(SpaceShip *another_spaceship, int multiplier) {
    if(another_spaceship->resources->get_fuel() > 1000) {
        if((this->resources->get_food()-5000) > another_spaceship->resources->get_food()) {
            // FOOD
            int needed = another_spaceship->food_needed();
            if(another_spaceship->resources->get_gold() < (needed*multiplier)/4) {
                needed = (another_spaceship->resources->get_gold() * 4) / multiplier;
            }
            int cost = (needed*multiplier)/4;
            output_file << "                Got " << needed << " food for " << cost << " gold." << endl;
            Resource *res = new Resource(needed, 0, -cost, 0);
                another_spaceship->resources = another_spaceship->resources->operator+(res);
                this->resources = this->resources->operator-(res);
            delete res;
        }
    }

    if((this->resources->get_fuel()-5000) > another_spaceship->resources->get_fuel()) {
        // FUEL
        int needed = another_spaceship->fuel_needed();
        if(another_spaceship->resources->get_gold() < (needed*multiplier)/4) {
            needed = (another_spaceship->resources->get_gold() * 4) / multiplier;
        }
        int cost = (needed * multiplier) / 4;
        output_file << "                Got " << needed << " fuel for " << cost << " gold." << endl;
        Resource *res = new Resource(0, needed, -cost, 0);
            another_spaceship->resources = another_spaceship->resources->operator+(res);
            this->resources = this->resources->operator-(res);
        delete res;
    }

    if((this->resources->get_scrap_metal()-5000) > another_spaceship->resources->get_scrap_metal()) {
        // METAL
        int needed = another_spaceship->scrap_needed();
        if(another_spaceship->resources->get_gold() < (needed*multiplier)/4) {
            needed = (another_spaceship->resources->get_gold() * 4) / multiplier;
        }
        int cost = (needed*multiplier)/4;
        Resource *res = new Resource(0, 0, -cost, needed);
            output_file << "                Got " << needed << " scrap metal for " << cost << " gold." << endl;
            another_spaceship->resources = another_spaceship->resources->operator+(res);
            this->resources = this->resources->operator-(res);
        delete res;
    }

}

SpaceShip* Species::get_spaceship() {
    return this->spaceship;
}


