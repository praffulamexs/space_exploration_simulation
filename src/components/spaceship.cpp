#include "../../headers/all_imports.h"
#include "../../headers/classes/spaceship.h"
#include "../../headers/classes/crew_member.h"

SpaceShip::SpaceShip(bool active) {
    this->name = spaceship_names[rand() % spaceship_names.size()];

    /*  Cargo Distribution  */
    this->fuel_capacity = rand() % 1500 + 7000;
    this->food_capacity = rand() % 1500 + 5000;
    this->crew_capacity = rand() % 50 + 25;
    this->scrap_capacity = rand() % 1000 + 1500;
    this->gold_capacity = rand() % 1000 + 3000;
    this->resources = new Resource(0);

    if(active) {
        int crew_number = rand() % 20 + (this->crew_capacity - 20);
        for(int i = 0; i < crew_number; i++) {
            CrewMember crew_member;
            this->crew.push_back(crew_member);
        }
        this->find_officers();
    } else {
        int crew_number = rand() % 20 + 5;
        for(int i = 0; i < crew_number; i++) {
            CrewMember crew_member;
            this->crew.push_back(crew_member);
        }
    }
    this->speed = rand() % 40 + 60;
    this->spaceship_health = rand() % 30 + 70;
}

SpaceShip::SpaceShip(bool active, int species_diplomacy, int species_trading) {
    this->name = spaceship_names[rand() % spaceship_names.size()];

    /*  Cargo Distribution  */
    this->fuel_capacity = rand() % 1500 + 7000;
    this->food_capacity = rand() % 1500 + 5000;
    this->crew_capacity = rand() % 50 + 25;
    this->scrap_capacity = rand() % 1000 + 1500;
    this->gold_capacity = rand() % 1000 + 5000;
    this->resources = new Resource(0);

    if(active) {
        int crew_number = rand() % 20 + (this->crew_capacity - 20);
        for(int i = 0; i < crew_number; i++) {
            CrewMember crew_member(species_diplomacy, species_trading);
            this->crew.push_back(crew_member);
        }
        this->find_officers();
    } else {
        int crew_number = rand() % 20 + 5;
        for(int i = 0; i < crew_number; i++) {
            CrewMember crew_member;
            this->crew.push_back(crew_member);
        }
    }
    this->speed = rand() % 40 + 60;
    this->spaceship_health = rand() % 30 + 70;
}


void SpaceShip::find_officers() {
    this->find_captain();
    this->find_pilot();
    this->find_engineer();
    this->find_mining_officer();
    this->find_weapon_officer();
}

string SpaceShip::getName() {
    return this->name;
}


void SpaceShip::getInfo() {
    output_file << "    Spaceship : " << this->name << endl;
    output_file << "    Fuel Capacity : " << this->fuel_capacity << endl;
    output_file << "    Food Capacity : " << this->food_capacity << endl;
    output_file << "    Crew Capacity : " << this->crew_capacity << endl;
    output_file << "    Defensive Performance : " << this->defensive_performance() << endl;
    output_file << "    Offensive Performance : " << this->offensive_performance() << endl;
    output_file << "    Mining Potential : " << this->mining_ability() << endl;
    output_file << "    Travel Effeciency : " << this->travel_efficiency() << endl;
    output_file << "    Spaceship Speed : " << this->speed << endl;
    output_file << "    Spaceship Health : " << this->spaceship_health << endl;
}

void SpaceShip::operator+(SpaceShip *spaceship) {
    output_file << "            Crew Members added : " << spaceship->crew.size() << endl;
    for(int i=0; i<spaceship->crew.size(); i++) {
        if(this->crew.size() < this->crew_capacity) {
            this->crew.push_back(spaceship->crew[i]);
        }
    }
    output_file << "            Resources added : " << endl;
    output_file << "                Food : " << spaceship->resources->get_food() << endl;
    output_file << "                Fuel : " << spaceship->resources->get_fuel() << endl;
    output_file << "                Gold : " << spaceship->resources->get_gold() << endl;
    output_file << "                Metal : " << spaceship->resources->get_scrap_metal() << endl;

    this->resources = this->resources->operator+(spaceship->resources);
    
    int extra_food = 0;
    int extra_fuel = 0;
    int extra_gold = 0;
    int extra_scrap = 0;

    if(this->resources->get_food() > this->food_capacity) {
        extra_food = this->resources->get_food() - this->food_capacity;
    }
    
    if(this->resources->get_fuel() > this->food_capacity) {
        extra_fuel = this->resources->get_fuel() - this->fuel_capacity;
    }
    
    if(this->resources->get_gold() > this->food_capacity) {
        extra_gold = this->resources->get_gold() - this->gold_capacity;
    }
    
    if(this->resources->get_scrap_metal() > this->food_capacity) {
        extra_scrap = this->resources->get_scrap_metal() - this->scrap_capacity;
    }

    output_file << "            Extra Resources removed : " << endl;
    output_file << "                Food : " << extra_food << endl;
    output_file << "                Fuel : " << extra_fuel << endl;
    output_file << "                Gold : " << extra_gold << endl;
    output_file << "                Metal : " << extra_scrap << endl;

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

bool SpaceShip::travel(int distance) {

    output_file << "    Travel : " << endl;

    // FOOD CONSUMPTION
    int food_consumed = (this->crew.size() + 5)*distance/10;
    int food_available = this->resources->get_food();
    if(food_available < food_consumed) {
        output_file << "---LOW ON FOOD---" << endl;
        return true;
    }

    // FUEL CONSUMPTION
    int fuel_consumed = distance*7;
    fuel_consumed = (fuel_consumed * travel_efficiency()) / 100;
    int fuel_available = this->resources->get_fuel();
    if(fuel_available < fuel_consumed) {
        // Journey over if no fuel
        output_file << "---LOW ON FUEL---" << endl;
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

    output_file << "        Food Consumed : " << food_consumed << endl;
    output_file << "        Fuel Consumed : " << fuel_consumed << endl;
    output_file << "        Ship Health : " << this->spaceship_health << endl;
    output_file << "        Material Consumed : " << metal_required << endl;

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
        int original_health = current_spaceship->spaceship_health;
        original_health = (original_health * 70) / 100;

        if(current_spaceship->crew.size() < 1) {
            output_file << "                ------- " << current_spaceship->getName() << " have no crew left! -------" << endl;
            fighting = false;
            break;
        }

        if(current_spaceship->spaceship_health < 1) {
            output_file << "                ------- " << current_spaceship->getName() << " is destroyed! -------" << endl;
            fighting = false;
            break;
        } 

        if(*current_health < original_health || current_spaceship->crew.size() < 10) {
            //try to run if health below 30%
            int evasion = current_spaceship->conflict_evasaion();
            if((rand() % 100 + 1) <= evasion){
                output_file << "                " << current_spaceship->getName() << " ran away!" << endl;
                fighting = false;
                break;
            }
        } else {
            try {
                output_file << "                " << current_spaceship->getName() << " launched a missile!" << endl;
                if((rand() % 100 + 1) <= other_spaceship->combat_maneuvers() && other_spaceship->resources->get_fuel() > 55) {
                    // damage evaded
                    other_spaceship->fuel_consume(rand()%5 + 1); // Fuel gets consumed to dodge attack
                    output_file << "                " << other_spaceship->getName() << " evaded the attack!" << endl;
                } else {
                    int damage = current_spaceship->offensive_performance() - (current_spaceship->offensive_performance()*other_spaceship->defensive_performance())/100;
                    output_file << "                " << current_spaceship->getName() << " dealt " << damage << " damage to " << other_spaceship->getName() << endl;
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
            } catch (exception e) {
                fighting = false;
                break;
            }
        }
    }
}

void SpaceShip::damage_dealt(int damage) {
    if(damage > 10) {
        int officer_dead = rand() % 5;
        if(officer_dead == 0) {
            DeadCrewMember dead_officer(this->captain);
            output_file << "                    Captain Dead!" << endl;
            output_file << "                        Time Of Death : " << "asdasd" << endl;
            output_file << "                        Place of Death : Sector " << current_sector << endl;
            this->dead_crew.push_back(dead_officer);
            this->find_captain();
            output_file << "                    New Captain Chosen!" << endl;
            this->captain.getInfo();
        } else if(officer_dead == 1) {
            DeadCrewMember dead_officer(this->pilot);
            output_file << "                    Pilot Dead!" << endl;
            output_file << "                        Time Of Death : " << "asdasd" << endl;
            output_file << "                        Place of Death : Sector " << current_sector << endl;
            this->dead_crew.push_back(dead_officer);
            this->find_pilot();
            output_file << "                    New Pilot Chosen!" << endl;
            this->pilot.getInfo();
        } else if(officer_dead == 2) {
            DeadCrewMember dead_officer(this->engineer);
            output_file << "                    Engineer Dead!" << endl;
            output_file << "                        Time Of Death : " << "asdasd" << endl;
            output_file << "                        Place of Death : Sector " << current_sector << endl;
            this->dead_crew.push_back(dead_officer);
            this->find_engineer();
            output_file << "                    New Engineer Chosen!" << endl;
            this->engineer.getInfo();
        } else if(officer_dead == 3) {
            DeadCrewMember dead_officer(this->mining_officer);
            output_file << "                    Mining Officer Dead!" << endl;
            output_file << "                        Time Of Death : " << "asdasd" << endl;
            output_file << "                        Place of Death : Sector " << current_sector << endl;
            this->dead_crew.push_back(dead_officer);
            this->find_mining_officer();
            output_file << "                    New Mining Officer Chosen!" << endl;
            this->mining_officer.getInfo();
        } else if(officer_dead == 4) {
            DeadCrewMember dead_officer(this->weapon_officer);
            output_file << "                    Weapon Officer Dead!" << endl;
            output_file << "                        Time Of Death : " << "asdasd" << endl;
            output_file << "                        Place of Death : Sector " << current_sector << endl;
            this->dead_crew.push_back(dead_officer);
            this->find_weapon_officer();
            output_file << "                    New Weapon Officer Chosen!" << endl;
            this->weapon_officer.getInfo();
        }
        damage = 7; // Keeping maximum number of deaths per kill to be 9
    }
    int number_of_dead = rand() % damage + 1;
    if(number_of_dead > this->crew.size()) {
        number_of_dead = this->crew.size();
    }
    output_file << "                    " << number_of_dead <<" crew members dead!" << endl;
    for(int i=0; i<number_of_dead; i++) {
        int dead = rand() % this->crew.size();
        DeadCrewMember dead_member(this->crew[dead]);
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
                available_to_give = (cost * 4) / multiplier;
                Resource *res = new Resource(available_to_give, 0, -cost, 0);
                this->resources = this->resources->operator+(res);
                spaceship->resources = spaceship->resources->operator-(res);
                delete res;
                output_file << "                Took " << available_to_give << " food for " << cost << " gold." << endl;
            }
        } else {
            if(spaceship->resources->get_food() < (spaceship->food_capacity - 500)) {
                // Traveler has excess of food resource
                int available_to_give = (this->resources->get_food()) - (this->food_capacity - 500);
                int needed = spaceship->food_capacity - spaceship->resources->get_food();
                if(needed < available_to_give) {
                    available_to_give = needed;
                }
                // cout << "available_to_give : " << available_to_give << endl;
                int cost = (available_to_give * multiplier)/4;
                if(cost > spaceship->resources->get_gold()) {
                    cost = spaceship->resources->get_gold();
                }
                available_to_give = (cost * 4)/multiplier;
                Resource *res = new Resource(available_to_give, 0, -cost, 0);
                spaceship->resources = spaceship->resources->operator+(res);
                this->resources = this->resources->operator-(res);
                delete res;
                output_file << "                Gave " << available_to_give << " food for " << cost << " gold." << endl;
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
            available_to_give = (cost * 4)/multiplier;
            Resource *res = new Resource(0, available_to_give, -cost, 0);
            this->resources = this->resources->operator+(res);
            spaceship->resources = spaceship->resources->operator-(res);
            delete res;
            output_file << "                Took " << available_to_give << " fuel for " << cost << " gold." << endl;
        }
    } else {
        if(this->resources->get_fuel() > (this->fuel_capacity - 500)) {
            // Traveler has excess of fuel resource
            int available_to_give = (this->resources->get_fuel()) - (this->fuel_capacity - 500);
            int needed = spaceship->fuel_capacity - spaceship->resources->get_fuel();
            if(needed < available_to_give) {
                available_to_give = needed;
            }
            int cost = (available_to_give * multiplier)/4;
            if(cost > spaceship->resources->get_gold()) {
                cost = spaceship->resources->get_gold();
            }
            available_to_give = (cost * 4) / multiplier;
            Resource *res = new Resource(0, available_to_give, -cost, 0);
            spaceship->resources = spaceship->resources->operator+(res);
            this->resources = this->resources->operator-(res);
            delete res;
            output_file << "                Gave " << available_to_give << " fuel for " << cost << " gold." << endl;
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
            available_to_give = (cost * 4) / multiplier;
            Resource *res = new Resource(0, 0, -cost, available_to_give);
            this->resources = this->resources->operator+(res);
            spaceship->resources = spaceship->resources->operator-(res);
            delete res;
            output_file << "                Took " << available_to_give << " metal for " << cost << " gold." << endl;
        }
    } else {
        if(this->resources->get_scrap_metal() > (this->scrap_capacity - 500)) {
            // Traveler has excess of metal resource
            int available_to_give = (this->resources->get_scrap_metal()) - (this->scrap_capacity - 500);
            int needed = spaceship->scrap_capacity - spaceship->resources->get_scrap_metal();
            if(needed < available_to_give) {
                available_to_give = needed;
            }
            int cost = (available_to_give * multiplier)/4;
            if(cost > spaceship->resources->get_gold()) {
                cost = spaceship->resources->get_gold();
            }
            available_to_give = (cost * 4) / multiplier;
            Resource *res = new Resource(0, 0, -cost, available_to_give);
            spaceship->resources = spaceship->resources->operator+(res);
            this->resources = this->resources->operator-(res);
            delete res;
            output_file << "                Gave " << available_to_give << " metal for " << cost << " gold." << endl;
        }
    }
}

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
        if(this->crew.size() > 0) {
            crew_combat_score = crew_combat_score / (this->crew.size());
        } else {
            crew_combat_score = 0;
        }
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
        if(this->crew.size() > 0) {
            crew_engineer_score = crew_engineer_score / (this->crew.size());
        } else {
            crew_engineer_score = 0;
        }
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
    output_file << "    Spaceship Health : " << this->spaceship_health << endl;
    output_file << "    Crew Members Left : " << this->crew.size() << endl;
    if(this->spaceship_health <= 0) {
        return true;
    } else if(this->crew.size() == 0) {
        return true;
    } else {
        return false;
    }
}

void SpaceShip::get_captain_info() {
    this->captain.getInfo();
}

void SpaceShip::get_pilot_info() {
    this->pilot.getInfo();
}

void SpaceShip::get_engineer_info() {
    this->engineer.getInfo();
}

void SpaceShip::get_mining_officer_info() {
    this->mining_officer.getInfo();
}

void SpaceShip::get_weapon_officer_info() {
    this->weapon_officer.getInfo();
}

void SpaceShip::get_crew_info() {
    for(int i=0;i<this->crew.size(); i++) {
        this->crew[i].getInfo();
    }
}

void SpaceShip::get_dead_crew_info() {
    for(int i=0;i<this->dead_crew.size(); i++) {
        this->dead_crew[i].getInfo();
    }
}

int SpaceShip::get_speed() {
    return this->speed;
}


