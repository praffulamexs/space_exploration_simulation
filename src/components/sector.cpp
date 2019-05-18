#include "../../headers/all_imports.h"
#include "../../headers/classes/sector.h"
#include "../../headers/classes/spaceship.h"
#include "../../headers/classes/species.h"
#include "../../headers/classes/planet.h"
#include "../../headers/classes/trading_station.h"

Sector::Sector(SpaceShip *traveler){
    this->journey = false;
    this->sector_width = rand() % 80 + 20;
    int random = rand() % 100 + 1;

    output_file << "    Distance Covered : " << this->sector_width << endl;

    // ltm->tm_mday = ltm->tm_mday + 1;
    // ltm->tm_hour = ltm->tm_hour + 1;
    // ltm->tm_min = ltm->tm_min + 2;

    // cout << "ltm" << ltm << endl;

    if(traveler->travel(this->sector_width) || traveler->check_if_alive()) {
        this->journey = true;
    } else {
        /*  Probability of being encountered by a Spaceship  */
        if(random <= 35) {
            output_file << "        Spaceship Encountered" << endl;
            SpaceShip *spaceship = new SpaceShip(true);
                this->spaceship_encountered(traveler, spaceship);
            delete spaceship;
        }
        /*  Probability of being encountered by a Planet  */
        else if(random > 35 && random <=60) {
            output_file << "        Planet Encountered" << endl;
            Planet *planet = new Planet();
                this->planet_encountered(planet, traveler);
            delete planet;
        }
        /*  Probability of being encountered by a Trading Station  */
        else if(random > 60 && random <=75) {
            output_file << "        Trading Station Encountered" << endl;
            TradingStation *trading_station = new TradingStation();
                this->trading_station_encountered(trading_station, traveler);
            delete trading_station;
        }
        /*  Probability of finding an Empty Sector  */
        else if(random > 75 && random <=90) {
            output_file << "        Empty Sector" << endl;
            this->empty_sector();
        }
        /*  Probability of being encountered by an Abandoned Spaceship  */
        else if(random > 90) {
            output_file << "        Abandoned Spaceship Encountered" << endl;
            SpaceShip *abandoned_spaceship = new SpaceShip(false);
                this->abandoned_spaceship_encountered(abandoned_spaceship, traveler);
            delete abandoned_spaceship;
        }

    }
}

void Sector::spaceship_encountered(SpaceShip *spaceship, SpaceShip *spaceship_encountered) {
    // cout << "Just checking food : " << spaceship->resources->get_food() << endl;
    int diplomacy1 = spaceship->diplomacy();
    int diplomacy2 = spaceship_encountered->diplomacy();
    if(diplomacy1 > 70) {
        diplomacy1 = 70;
    }
    if(diplomacy2 > 70) {
        diplomacy2 = 70;
    }

    output_file << "            Captains of both the spaceships are negotiating..." << endl;

    bool condition1 = (rand() % 100 + 1) <= diplomacy1;
    bool condition2 = (rand() % 100 + 1) <= diplomacy2;
    if (condition1 && condition2) {
        output_file << "            Negotiation Successful. Trading..." << endl;
        spaceship->trade(spaceship_encountered);
        output_file << "            Trading Completed." << endl;
    } else {
        output_file << "            Negotiation Unsuccessful. Preparing for combat..." << endl;
        output_file << "            COMBAT BEGINS!" << endl;
        spaceship->combat(spaceship_encountered);
        output_file << "            COMBAT OVER" << endl;
    }
}

void Sector::planet_encountered(Planet *planet, SpaceShip *spaceship) {
    output_file << "            Negotiation with the species found on planet " << planet->get_name() << " to either allow to mine or trade." << endl;
    int diplomacy1 = spaceship->diplomacy();
    int diplomacy2 = planet->diplomacy();
    if(diplomacy1 > 70) {
        diplomacy1 = 70;
    }
    if(diplomacy2 > 70) {
        diplomacy2 = 70;
    }

    bool condition1 = (rand() % 100 + 1) <= diplomacy1;
    bool condition2 = (rand() % 100 + 1) <= diplomacy2;
    if(condition1 && condition2) {
        output_file << "            Agreed for Mining." << endl;
        planet->mining(spaceship);
    } else if(condition1 || condition2) {
        output_file << "            Agreed for Trade." << endl;
        planet->trading(spaceship);
    } else {
        output_file << "            Negotiation Unsuccessful. Species launched a spaceship for battle..." << endl;
        output_file << "            COMBAT BEGINS!" << endl;
        planet->conflict(spaceship);
        output_file << "            COMBAT OVER!" << endl;
    }
}

void Sector::trading_station_encountered(TradingStation *trading_station, SpaceShip *spaceship) {
    output_file << "            Trading with species - " << trading_station->get_species_name() << endl;
    trading_station->trade(spaceship);
}

void Sector::empty_sector() {
    // consume fuel and food and do rebuild
}

void Sector::abandoned_spaceship_encountered(SpaceShip *abandoned_spaceship, SpaceShip *spaceship) {
    spaceship->operator+(abandoned_spaceship);
}

void Sector::end_report() {

}

bool Sector::journey_ended() {
    return this->journey;
}