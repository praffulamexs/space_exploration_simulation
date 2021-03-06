#include "../../headers/all_imports.h"
#include "../../headers/classes/resource.h"

Resource::Resource(int val) {
    if(val ==0){
        /* SPACESHIP */
        this->food = rand() % 1800 + 3100;
        this->fuel = rand() % 800 + 6200;
        this->gold = rand() % 2000 + 3500;
        this->scrap_metal = rand() % 200 + 400;
    } else if(val == 1) {
        /* SPECIES */
        this->food = rand() % 50000 + 5000;
        this->fuel = rand() % 50000 + 5000;
        this->gold = rand() % 50000 + 5000;
        this->scrap_metal = rand() % 50000 + 5000;
    } else if(val == 2) {
        /* PLANET */
        this->food = rand() % 200000 + 15000;
        this->fuel = rand() % 200000 + 15000;
        this->gold = rand() % 200000 + 15000;
        this->scrap_metal = rand() % 200000 + 15000;
    }
}

Resource::Resource(int new_food, int new_fuel, int new_gold, int new_scrap_metal) {
    this->food = new_food;
    this->fuel = new_fuel;
    this->gold = new_gold;
    this->scrap_metal = new_scrap_metal;
}

int Resource::get_food() {
    return this->food;
}

int Resource::get_fuel() {
    return this->fuel;
}

int Resource::get_gold() {
    return this->gold;
}

int Resource::get_scrap_metal() {
    return this->scrap_metal;
}


Resource* Resource::operator+(Resource *a) {
    this->food = this->food + a->food;
    this->fuel = this->fuel + a->fuel;
    this->gold = this->gold + a->gold;
    this->scrap_metal = this->scrap_metal + a->scrap_metal;
    return this;
}

Resource* Resource::operator-(Resource *a) {
    this->food = this->food - a->food;
    this->fuel = this->fuel - a->fuel;
    this->gold = this->gold - a->gold;
    this->scrap_metal = this->scrap_metal - a->scrap_metal;
    return this;
}

void Resource::getInfo() {
    output_file << "        Food : " << this->food << endl;
    output_file << "        Fuel : " << this->fuel << endl;
    output_file << "        Gold : " << this->gold << endl;
    output_file << "        Scrap Metal : " << this->scrap_metal << endl;
}

