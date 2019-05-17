#include "../../headers/all_imports.h"
#include "../../headers/classes/sector.h"
#include "../../headers/classes/spaceship.h"
#include "../../headers/classes/planet.h"
#include "../../headers/classes/trading_station.h"

Sector::Sector(SpaceShip *traveler){
    this->journey = false;
    this->sector_width = rand() % 75 + 25;
    int random = rand() % 100 + 1;

    cout << "Crew Members : " << traveler->total_crew() << endl;
    cout << "Food : " << traveler->resources->get_food() << endl;
    cout << "Fuel : " << traveler->resources->get_fuel() << endl;
    cout << "Gold : " << traveler->resources->get_gold() << endl;
    cout << "Metal : " << traveler->resources->get_scrap_metal() << endl;
    cout << "SECTOR WIDTH : " << this->sector_width << endl;

    if(traveler->travel(this->sector_width) || traveler->check_if_alive()) {
        this->journey = true;
    } else {
        /*  Probability of being encountered by a Spaceship  */
        if(random <= 35) {
            cout << "Spaceship Encountered..." << endl;
            SpaceShip *spaceship = new SpaceShip(true);
                this->spaceship_encountered(traveler, spaceship);
            delete spaceship;
        }
        /*  Probability of being encountered by a Planet  */
        else if(random > 35 && random <=60) {
            cout << "Planet Encountered..." << endl;
            Planet *planet = new Planet();
                this->planet_encountered(planet, traveler);
            delete planet;
        }
        /*  Probability of being encountered by a Trading Station  */
        else if(random > 60 && random <=75) {
            cout << "Trading Station Encountered..." << endl;
            TradingStation *trading_station = new TradingStation();
                this->trading_station_encountered(trading_station, traveler);
            delete trading_station;
        }
        /*  Probability of finding an Empty Sector  */
        else if(random > 75 && random <=90) {
            cout << "Empty Sector..." << endl;
            this->empty_sector();
        }
        /*  Probability of being encountered by an Abandoned Spaceship  */
        else if(random > 90) {
            cout << "Abandoned Spaceship Encountered..." << endl;
            SpaceShip *abandoned_spaceship = new SpaceShip(false);
                this->abandoned_spaceship_encountered(abandoned_spaceship, traveler);
            delete abandoned_spaceship;
        }

        cout << "Crew Members : " << traveler->total_crew() << endl;
        cout << "Food : " << traveler->resources->get_food() << endl;
        cout << "Fuel : " << traveler->resources->get_fuel() << endl;
        cout << "Gold : " << traveler->resources->get_gold() << endl;
        cout << "Metal : " << traveler->resources->get_scrap_metal() << endl;
        cout << "-------------Sector-------------" << endl;
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
    bool condition1 = (rand() % 100 + 1) <= diplomacy1;
    bool condition2 = (rand() % 100 + 1) <= diplomacy2;
    if (condition1 && condition2) {
        spaceship->trade(spaceship_encountered);
    } else {
        cout << "----IN COMBAT-----" << endl;
        spaceship->combat(spaceship_encountered);
    }
}

void Sector::planet_encountered(Planet *planet, SpaceShip *spaceship) {
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
        cout << "mining..." << endl;
        planet->mining(spaceship);
    } else if(condition1 || condition2) {
        cout << "trading..." << endl;
        planet->trading(spaceship);
    } else {
        cout << "conflict..." << endl;
        planet->conflict(spaceship);
    }
}

void Sector::trading_station_encountered(TradingStation *trading_station, SpaceShip *spaceship) {
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