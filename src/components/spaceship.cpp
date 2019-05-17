#include "../../headers/all_imports.h"
#include "../../headers/classes/spaceship.h"
#include "../../headers/classes/crew_member.h"

SpaceShip::SpaceShip(bool active) {
    this->name = "Agni";

    /*  Cargo Distribution  */
    this->fuel_capacity = rand() % 500 + 3500;
    this->food_capacity = rand() % 500 + 3200;
    this->crew_capacity = rand() % 25 + 25;
    this->scrap_capacity = rand() % 1000 + 1500;
    this->gold_capacity = rand() % 1000 + 3000;
    this->resources = new Resource(0);

    if(active) {
        int crew_number = rand() % 20 + (this->crew_capacity - 20);
        // crew_number = 5; //delete later
        for(int i = 0; i < crew_number; i++) {
            CrewMember crew_member;
            // cout << endl; // delete later
            // crew_member.getInfo(); //delete later
            this->crew.push_back(crew_member);
        }
        this->find_officers();
    } else {
        int crew_number = rand() % 20 + 5;
        // crew_number = 5; //delete later
        for(int i = 0; i < crew_number; i++) {
            CrewMember crew_member;
            // cout << endl; // delete later
            // crew_member.getInfo(); //delete later
            this->crew.push_back(crew_member);
        }
    }

    // this->defence = rand() % 40 + 60;
    // this->offence = rand() % 40 + 60;
    // this->mining = this->mining_ability();
    // this->travel_efficiency = rand() % 40 + 60;
    this->speed = rand() % 40 + 60;
    this->spaceship_health = rand() % 30 + 70;

    // this->getInfo(); // delete later
}

void SpaceShip::find_officers() {
    this->find_captain();
    // cout << "Captain Details : " << endl;
    // this->captain.getInfo(); //delete later

    // cout << endl;

    this->find_pilot();
    // cout << "Pilot Details : " << endl;
    // this->pilot.getInfo(); //delete later

    // cout << endl;

    this->find_engineer();
    // cout << "Engineer Details : " << endl;
    // this->engineer.getInfo(); //delete later

    // cout << endl;

    this->find_mining_officer();
    // cout << "Mining Officer Details : " << endl;
    // this->mining_officer.getInfo(); //delete later

    // cout << endl;

    this->find_weapon_officer();
    // cout << "Weapon Officer Details : " << endl;
    // this->weapon_officer.getInfo(); //delete later
}

string SpaceShip::getName() {
    return this->name;
}


void SpaceShip::getInfo() {
    cout << "Name of the Spaceship : " << this->name << endl;
    cout << "Fuel Capacity : " << this->fuel_capacity << endl;
    cout << "Food Capacity : " << this->food_capacity << endl;
    cout << "Crew Capacity : " << this->crew_capacity << endl;
    cout << "Defensive Performance : " << this->defensive_performance() << endl;
    cout << "Offensive Performance : " << this->offensive_performance() << endl;
    cout << "Mining Potential : " << this->mining_ability() << endl;
    cout << "Travel Effeciency : " << this->travel_efficiency() << endl;
    cout << "Spaceship Speed : " << this->speed << endl;
    cout << "Spaceship Health : " << this->spaceship_health << endl;
}

void SpaceShip::operator+(SpaceShip *spaceship) {
    for(int i=0; i<spaceship->crew.size(); i++) {
        if(this->crew.size() < this->crew_capacity) {
            this->crew.push_back(spaceship->crew[i]);
        }
    }
    this->resources = this->resources->operator+(spaceship->resources);
    
    int extra_food = 0;
    int extra_fuel = 0;
    int extra_gold = 0;
    int extra_scrap = 0;

    if(this->resources->get_food() > this->food_capacity) {
        extra_food = this->resources->get_food() - this->food_capacity;
    }
    
    if(this->resources->get_food() > this->food_capacity) {
        extra_fuel = this->resources->get_fuel() - this->fuel_capacity;
    }
    
    if(this->resources->get_food() > this->food_capacity) {
        extra_gold = this->resources->get_gold() - this->gold_capacity;
    }
    
    if(this->resources->get_food() > this->food_capacity) {
        extra_scrap = this->resources->get_scrap_metal() - this->scrap_capacity;
    }

    Resource *res = new Resource(extra_food, extra_fuel, extra_gold, extra_scrap);
    this->resources = this->resources->operator-(res);
    delete res;

}

bool SpaceShip::operator==(SpaceShip *spaceship) {
    if(
        this->name == spaceship->name &&
        this->fuel_capacity == spaceship->fuel_capacity &&
        this->food_capacity == spaceship->food_capacity &&
        this->crew_capacity == spaceship->crew_capacity &&
        this->scrap_capacity == spaceship->scrap_capacity &&
        this->gold_capacity == spaceship->gold_capacity &&
        this->speed == spaceship->speed &&
        this->spaceship_health == spaceship->spaceship_health
    ) {
        return true;
    } else {
        return false;
    }
}

void SpaceShip::fuel_consume(int amount) {
    Resource *res = new Resource(0, amount, 0, 0);
    this->resources = this->resources->operator-(res);
    delete res;
}

// void SpaceShip::starved_to_death(int dead) {
//     for(int i=0; i < dead; i++) {
//         int death_id = rand() % this->crew.size();
//         this->crew.erase(this->crew.begin() + death_id);
//     }
// }

bool SpaceShip::travel(int distance) {
    // FOOD CONSUMPTION
    int food_consumed = (this->crew.size() + 5)*distance/20;
    int food_available = this->resources->get_food();
    if(food_available < food_consumed) {
        cout << "---LOW ON FOOD---" << endl;
        return true;
    }

    // FUEL CONSUMPTION
    int fuel_consumed = distance*5;
    fuel_consumed = (fuel_consumed * travel_efficiency()) / 100;
    int fuel_available = this->resources->get_fuel();
    if(fuel_available < fuel_consumed) {
        // Journey over if no fuel
        cout << "---LOW ON FUEL---" << endl;
        return true;
    }

    // SYSTEM RECOVERY
    int health_recoverable = 100 - this->spaceship_health;
    int can_be_recovered = distance/10;

    if(can_be_recovered < health_recoverable) {
        health_recoverable = can_be_recovered;
    }

    int metal_required = health_recoverable*100; // 100 metal scrap for 1 health of spaceship
    if(metal_required > this->resources->get_scrap_metal()) {
        metal_required = this->resources->get_scrap_metal();
    }

    health_recoverable = metal_required/100;
    this->spaceship_health = this->spaceship_health + health_recoverable;

    cout << "   Food Consumed : " << food_consumed << endl;
    cout << "   Fuel Consumed : " << fuel_consumed << endl;
    cout << "   Ship Health : " << this->spaceship_health << endl;
    cout << "   Material Consumed : " << metal_required << endl;

    Resource *res = new Resource(food_consumed, fuel_consumed, 0, metal_required);
    this->resources = this->resources->operator-(res);
    delete res;
    return false;
}

void SpaceShip::combat(SpaceShip *spaceship) {
    bool fighting = true;
    int *spaceship_health1 = new int(this->spaceship_health);
    int *spaceship_health2 = new int(spaceship->spaceship_health);

    SpaceShip *current_spaceship = this;
    SpaceShip *other_spaceship = spaceship;
    int *current_health = spaceship_health1;
    int *other_health = spaceship_health2;

    while(fighting) {
        // cout << "Inside while loop ... " << endl;
        int original_health = current_spaceship->spaceship_health;
        original_health = (original_health * 70) / 15;
        cout << "Current Health : " << *current_health << endl;
        // cout << "Current Health : " << original_health << endl;

        // cout << "Current Health TYPE : " << typeid(current_health).name() << endl;
        // cout << "ss1 Health : " << spaceship_health1 << endl;
        // cout << "ss2 Health : " << spaceship_health2 << endl;
        // fighting = false;
        
        if(*current_health < original_health) {
            //try to run if health below 30%
            if((rand() % 100 + 1) <= current_spaceship->conflict_evasaion()){
                cout << "Ran Away!" << endl;
                fighting = false;
                break;
            }
        } else {
            if((rand() % 100 + 1) <= other_spaceship->combat_maneuvers() && other_spaceship->resources->get_fuel() > 55) {
                // damage evaded
                other_spaceship->fuel_consume(rand()%5 + 1); // Fuel gets consumed to dodge attack
                cout << "Evaded!" << endl;
            } else {
                cout << "Fighting!" << endl;
                int damage = current_spaceship->offensive_performance() - (current_spaceship->offensive_performance()*other_spaceship->defensive_performance())/50;
                // if(damage > 10) {
                //     damage = 10;
                // }
                *other_health = *other_health - damage;
                other_spaceship->damage_dealt(damage);
            }

            // Changing conditions before next loop
            if(current_spaceship == this) {
                current_spaceship = spaceship;
                other_spaceship = this;
            } else {
                current_spaceship = this;
                other_spaceship = spaceship;
            }

            if(current_health == spaceship_health1) {
                current_health = spaceship_health2;
                other_health = spaceship_health1;
            } else {
                current_health = spaceship_health1;
                other_health = spaceship_health2;
            }
        }
    }

    // delete spaceship_health1;
    // delete spaceship_health2;
    // delete current_spaceship;
    // delete other_spaceship;
    // delete current_health;
}

void SpaceShip::damage_dealt(int damage) {
    if(damage > 10) {
        int officer_dead = rand() % 5;
        if(officer_dead == 0) {
            DeadCrewMember dead_officer(this->captain, 0, 0);
            this->dead_crew.push_back(dead_officer);
            this->find_captain();
        } else if(officer_dead == 1) {
            DeadCrewMember dead_officer(this->pilot, 0, 0);
            this->dead_crew.push_back(dead_officer);
            this->find_pilot();
        } else if(officer_dead == 2) {
            DeadCrewMember dead_officer(this->engineer, 0, 0);
            this->dead_crew.push_back(dead_officer);
            this->find_engineer();
        } else if(officer_dead == 3) {
            DeadCrewMember dead_officer(this->mining_officer, 0, 0);
            this->dead_crew.push_back(dead_officer);
            this->find_mining_officer();
        } else if(officer_dead == 4) {
            DeadCrewMember dead_officer(this->weapon_officer, 0, 0);
            this->dead_crew.push_back(dead_officer);
            this->find_weapon_officer();
        }
        // damage = damage - 1; // Keeping maximum number of deaths per kill to be 9
    }
    int number_of_dead = rand() % damage ;
    for(int i=0; i<number_of_dead; i++) {
        int dead = rand() % this->crew.size();
        DeadCrewMember dead_member(this->crew[dead], 0, 0);
        this->dead_crew.push_back(dead_member);
        this->crew.erase(this->crew.begin() + dead);
    }
}

void SpaceShip::trade(SpaceShip *spaceship) {
    int trade_multiplier;
    bool traveler_trade = (rand() % 100 + 1) <= this->trading();
    bool spaceship_trade = (rand() % 100 + 1) <= spaceship->trading();

    if(traveler_trade && spaceship_trade) {
        trade_multiplier = 4;
        this->do_trading(spaceship, trade_multiplier);
    } else if(traveler_trade && !spaceship_trade) {
        trade_multiplier = 2; // If they are bad at trading, they end up paying more
        this->do_trading(spaceship, trade_multiplier);
    } else if (!traveler_trade && spaceship_trade) {
        trade_multiplier = 6; // If travelers are bad at trading, they end up paying more
        this->do_trading(spaceship, trade_multiplier);
    }
}

void SpaceShip::do_trading(SpaceShip *spaceship, int multiplier) {
    if(this->resources->get_fuel() > 800) {
        if (this->resources->get_food() < this->food_capacity) {
            // Needs food
            if(spaceship->resources->get_food() > (spaceship->food_capacity - 500)) {
                // Spaceship has excess of food resource
                int available_to_give = (spaceship->resources->get_food()) - (spaceship->food_capacity - 500);
                int needed = this->food_capacity - this->resources->get_food();
                if(needed < available_to_give) {
                    available_to_give = needed;
                }
                int cost = (available_to_give * multiplier)/4;
                if(cost > this->resources->get_gold()) {
                    cost = this->resources->get_gold();
                }
                // cout << "GOLD REMAINING : " << this->resources->get_gold() << endl;
                available_to_give = (cost * 4) / multiplier;
                Resource *res = new Resource(available_to_give, 0, -cost, 0);
                this->resources = this->resources->operator+(res);
                spaceship->resources = spaceship->resources->operator-(res);
                delete res;
                // cout << "GOLD REMAINING : " << this->resources->get_gold() << endl;
                cout << "Took food" << endl;
            }
        } else {
            if(spaceship->resources->get_food() < (spaceship->food_capacity - 500)) {
                // Traveler has excess of food resource
                int available_to_give = (this->resources->get_food()) - (this->food_capacity - 500);
                // cout << "available_to_give : " << available_to_give << endl;
                int needed = spaceship->food_capacity - spaceship->resources->get_food();
                if(needed < available_to_give) {
                    available_to_give = needed;
                }
                // cout << "available_to_give : " << available_to_give << endl;
                int cost = (available_to_give * multiplier)/4;
                if(cost > spaceship->resources->get_gold()) {
                    cost = spaceship->resources->get_gold();
                }
                // cout << "GOLD REMAINING : " << this->resources->get_gold() << endl;
                available_to_give = (cost * 4)/multiplier;
                // cout << "available_to_give : " << available_to_give << endl;
                Resource *res = new Resource(available_to_give, 0, -cost, 0);
                spaceship->resources = spaceship->resources->operator+(res);
                this->resources = this->resources->operator-(res);
                delete res;
                // cout << "GOLD REMAINING : " << this->resources->get_gold() << endl;
                cout << "Gave food" << endl;
            }
        }
    }

    if (this->resources->get_fuel() < this->fuel_capacity) {
        // cout << "1....." << endl;
        // Needs fuel
        if(spaceship->resources->get_fuel() > (spaceship->fuel_capacity - 500)) {
            // Spaceship has excess of fuel resource
            int available_to_give = (spaceship->resources->get_fuel()) - (spaceship->fuel_capacity - 500);
            int needed = this->fuel_capacity - this->resources->get_fuel();
            if(needed < available_to_give) {
                available_to_give = needed;
            }
            int cost = (available_to_give * multiplier)/4;
            if(cost > this->resources->get_gold()) {
                cost = this->resources->get_gold();
            }
            // cout << "GOLD REMAINING : " << this->resources->get_gold() << endl;
            available_to_give = (cost * 4)/multiplier;
            Resource *res = new Resource(0, available_to_give, -cost, 0);
            this->resources = this->resources->operator+(res);
            spaceship->resources = spaceship->resources->operator-(res);
            delete res;
            // cout << "GOLD REMAINING : " << this->resources->get_gold() << endl;
            cout << "Took fuel" << endl;
        }
    } else {
        // cout << "2....." << endl;
        if(this->resources->get_fuel() > (this->fuel_capacity - 500)) {
            // Traveler has excess of fuel resource
            int available_to_give = (this->resources->get_fuel()) - (this->fuel_capacity - 500);
            // cout << "available_to_give : " << available_to_give << endl;
            int needed = spaceship->fuel_capacity - spaceship->resources->get_fuel();
            if(needed < available_to_give) {
                available_to_give = needed;
            }
            // cout << "available_to_give : " << available_to_give << endl;
            int cost = (available_to_give * multiplier)/4;
            if(cost > spaceship->resources->get_gold()) {
                cost = spaceship->resources->get_gold();
            }
            // cout << "GOLD REMAINING : " << this->resources->get_gold() << endl;
            available_to_give = (cost * 4) / multiplier;
            // cout << "available_to_give : " << available_to_give << endl;
            Resource *res = new Resource(0, available_to_give, -cost, 0);
            spaceship->resources = spaceship->resources->operator+(res);
            this->resources = this->resources->operator-(res);
            delete res;
            // cout << "GOLD REMAINING : " << this->resources->get_gold() << endl;
            cout << "Gave fuel" << endl;
        }
    }


    if (this->resources->get_scrap_metal() < this->scrap_capacity) {
        // Needs Metal
        if(spaceship->resources->get_scrap_metal() > (spaceship->scrap_capacity - 500)) {
            // Spaceship has excess of metal resource
            int available_to_give = (spaceship->resources->get_scrap_metal()) - (spaceship->scrap_capacity - 500);
            int needed = this->scrap_capacity - this->resources->get_scrap_metal();
            if(needed < available_to_give) {
                available_to_give = needed;
            }
            int cost = (available_to_give * multiplier)/4;
            if(cost > this->resources->get_gold()) {
                cost = this->resources->get_gold();
            }
            cout << "GOLD REMAINING : " << this->resources->get_gold() << endl;
            available_to_give = (cost * 4) / multiplier;
            Resource *res = new Resource(0, 0, -cost, available_to_give);
            this->resources = this->resources->operator+(res);
            spaceship->resources = spaceship->resources->operator-(res);
            delete res;
            cout << "GOLD REMAINING : " << this->resources->get_gold() << endl;
            cout << "Took metal" << endl;
        }
    } else {
        if(this->resources->get_scrap_metal() > (this->scrap_capacity - 500)) {
            // Traveler has excess of metal resource
            int available_to_give = (this->resources->get_scrap_metal()) - (this->scrap_capacity - 500);
            // cout << "available_to_give : " << available_to_give << endl;
            int needed = spaceship->scrap_capacity - spaceship->resources->get_scrap_metal();
            if(needed < available_to_give) {
                available_to_give = needed;
            }
            // cout << "available_to_give : " << available_to_give << endl;
            int cost = (available_to_give * multiplier)/4;
            if(cost > spaceship->resources->get_gold()) {
                cost = spaceship->resources->get_gold();
            }
            // cout << "GOLD REMAINING : " << this->resources->get_gold() << endl;
            available_to_give = (cost * 4) / multiplier;
            // cout << "available_to_give : " << available_to_give << endl;
            Resource *res = new Resource(0, 0, -cost, available_to_give);
            spaceship->resources = spaceship->resources->operator+(res);
            this->resources = this->resources->operator-(res);
            delete res;
            // cout << "GOLD REMAINING : " << this->resources->get_gold() << endl;
            cout << "Gave metal" << endl;
        }
    }
}

/*   FINDING OFFICERS   */
/*   FINDING OFFICERS   */
/*   FINDING OFFICERS   */
/*   FINDING OFFICERS   */
/*   FINDING OFFICERS   */
/*   FINDING OFFICERS   */
/*   FINDING OFFICERS   */
/*   FINDING OFFICERS   */

void SpaceShip::find_captain() {
    int capt_id = 0;
    for(int i = 1; i < this->crew.size(); i++) {
        if(this->crew[capt_id].captain_score() < this->crew[i].captain_score() && !this->crew[i].is_officer) {
            capt_id = i;
        }
    }
    this->captain = this->crew[capt_id];
    this->crew.erase(this->crew.begin() + capt_id);
    this->captain.change_officer_status("Captain");
}

void SpaceShip::find_pilot() {
    int pilot_id = 0;
    for(int i = 1; i < this->crew.size(); i++) {
        if(this->crew[pilot_id].pilot_score() < this->crew[i].pilot_score() && !this->crew[i].is_officer) {
            pilot_id = i;
        }
    }
    this->pilot = this->crew[pilot_id];
    this->crew.erase(this->crew.begin() + pilot_id);
    this->pilot.change_officer_status("Pilot");
}

void SpaceShip::find_engineer() {
    int engineer_id = 0;
    for(int i = 1; i < this->crew.size(); i++) {
        if(this->crew[engineer_id].engineer_score() < this->crew[i].engineer_score() && !this->crew[i].is_officer) {
            engineer_id = i;
        }
    }
    this->engineer = this->crew[engineer_id];
    this->crew.erase(this->crew.begin() + engineer_id);
    this->engineer.change_officer_status("Engineer");
}

void SpaceShip::find_mining_officer() {
    int mining_officer_id = 0;
    for(int i = 1; i < this->crew.size(); i++) {
        if(this->crew[mining_officer_id].mining_score() < this->crew[i].mining_score() && !this->crew[i].is_officer) {
            mining_officer_id = i;
        }
    }
    this->mining_officer = this->crew[mining_officer_id];
    this->crew.erase(this->crew.begin() + mining_officer_id);
    this->mining_officer.change_officer_status("Mining Officer");
}

void SpaceShip::find_weapon_officer() {
    int weapon_officer_id = 0;
    for(int i = 1; i < this->crew.size(); i++) {
        if(this->crew[weapon_officer_id].weapon_score() < this->crew[i].weapon_score() && !this->crew[i].is_officer) {
            weapon_officer_id = i;
        }
    }
    this->weapon_officer = this->crew[weapon_officer_id];
    this->crew.erase(this->crew.begin() + weapon_officer_id);
    this->weapon_officer.change_officer_status("Weapon Officer");
}

/*  ACTIVITIES CARRIED OUT BY THE SPACESHIP  */
/*  ACTIVITIES CARRIED OUT BY THE SPACESHIP  */
/*  ACTIVITIES CARRIED OUT BY THE SPACESHIP  */
/*  ACTIVITIES CARRIED OUT BY THE SPACESHIP  */
/*  ACTIVITIES CARRIED OUT BY THE SPACESHIP  */
/*  ACTIVITIES CARRIED OUT BY THE SPACESHIP  */
/*  ACTIVITIES CARRIED OUT BY THE SPACESHIP  */
/*  ACTIVITIES CARRIED OUT BY THE SPACESHIP  */
/*  ACTIVITIES CARRIED OUT BY THE SPACESHIP  */

int SpaceShip::diplomacy() {
    return this->captain.captain_score();
}

int SpaceShip::trading() {
    return this->captain.captain_score();
}

int SpaceShip::travel_efficiency() {
    int travel_score = (this->pilot.pilot_score() + this->engineer.engineer_score()) / 2;
    return travel_score;
}

int SpaceShip::combat_maneuvers() {
    int combat_score;
        int officer_score = (this->pilot.pilot_score() + this->engineer.engineer_score()) / 2;
        int crew_combat_score = 0;
        for(int i=0; i < this->crew.size(); i++) {
            crew_combat_score += (this->crew[i].pilot_score() + this->crew[i].engineer_score()) / 2;
        }
        crew_combat_score = crew_combat_score / (this->crew.size());
        crew_combat_score = (crew_combat_score + this->crew.size()) / 2;
        // The more number of crew members, the better the score and vice versa.
        combat_score = (crew_combat_score + 2 * officer_score) / 3;
        // Multiplier of 2 for officer score because his abilities should affect the overall performance of combat.
        combat_score = combat_score*2/3; // better to have less evasion
        return combat_score;
}

int SpaceShip::conflict_evasaion() {
    int evasion_score = (this->pilot.pilot_score() + this->engineer.engineer_score()) / 2;
    return evasion_score;
}

int SpaceShip::system_recovery() {
    int recovery_score;
        int engineer_score = this->engineer.engineer_score();
        int crew_engineer_score = 0;
        for(int i=0; i < this->crew.size(); i++) {
            crew_engineer_score += this->crew[i].engineer_score();
        }
        crew_engineer_score = crew_engineer_score/(this->crew.size());
        crew_engineer_score = (crew_engineer_score + this->crew.size()) / 2;
        // The more number of crew members, the better the score and vice versa.
        recovery_score = (crew_engineer_score + 2*engineer_score)/3;
        // Multiplier of 2 for officer score because his abilities should affect the overall performance of system recovery.
    return recovery_score;
}

int SpaceShip::mining_ability() {
    int mining_score;
        int officer_score = this->mining_officer.mining_score();
        int crew_mining_score = 0;
        for(int i=0; i < this->crew.size(); i++) {
            crew_mining_score += this->crew[i].mining_score();
        }
        crew_mining_score = crew_mining_score/(this->crew.size());
        crew_mining_score = (crew_mining_score + this->crew.size()) / 2;
        // The more number of crew members, the better the score and vice versa.
        mining_score = (crew_mining_score + 2*officer_score)/3;
        // Multiplier of 2 for officer score because his abilities should affect the overall performance of mining. 
    return mining_score;
}

int SpaceShip::defensive_performance() {
    int defensive_score = (this->engineer.engineer_score() + this->weapon_officer.weapon_score())/2;
    return defensive_score;
}

int SpaceShip::offensive_performance() {
    int offensive_score = this->weapon_officer.weapon_score();
    return offensive_score;
}

int SpaceShip::food_needed() {
    int capacity = this->food_capacity;
    int food = this->resources->get_food();
    return (capacity - food);
}

int SpaceShip::fuel_needed() {
    int capacity = this->fuel_capacity;
    int fuel = this->resources->get_fuel();
    return (capacity - fuel);
}

int SpaceShip::gold_needed() {
    int capacity = this->gold_capacity;
    int gold = this->resources->get_gold();
    return (capacity - gold);
}

int SpaceShip::scrap_needed() {
    int capacity = this->scrap_capacity;
    int scrap = this->resources->get_scrap_metal();
    return (capacity - scrap);
}

int SpaceShip::total_crew() {
    return this->crew.size();
}

bool SpaceShip::check_if_alive() {
    if(this->spaceship_health <= 0) {
        return true;
    } else if(this->crew.size() == 0) {
        return true;
    } else {
        return false;
    }
}

