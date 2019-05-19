#include "../../headers/all_imports.h"
#include "../../headers/classes/crew_member.h"

// vector<string> crew_first_names;
// vector<string> crew_last_names;

CrewMember::CrewMember() {
    this->name = crew_first_names[rand() % crew_first_names.size()] + " " + crew_last_names[rand() % crew_last_names.size()];
    this->role = "Crew Member";
    this->age = rand() % 80 + 20;
    this->is_officer = false;
    this->attributes = new CrewMemberAttributes();
}

CrewMember::CrewMember(int species_diplomacy, int species_trading) {
    this->name = crew_first_names[rand() % crew_first_names.size()] + " " + crew_last_names[rand() % crew_last_names.size()];
    this->role = "Crew Member";
    this->age = rand() % 80 + 20;
    this->is_officer = false;
    this->attributes = new CrewMemberAttributes(species_diplomacy, species_trading);
}

int CrewMember::captain_score() {
    return this->attributes->captain_score();
}

int CrewMember::pilot_score() {
    return this->attributes->pilot_score();
}

int CrewMember::engineer_score() {
    return this->attributes->engineer_score();
}

int CrewMember::mining_score() {
    return this->attributes->mining_score();
}

int CrewMember::weapon_score() {
    return this->attributes->weapon_score();
}

void CrewMember::getInfo() {
    output_file << "                Name : " << this->name << endl;
    output_file << "                Age : " << this->age << endl;
    output_file << endl;
}

void CrewMember::change_officer_status(string designation) {
    this->role = designation;
    this->is_officer = !this->is_officer;
}

string CrewMember::get_name() {
    return this->name;
}

string CrewMember::get_designation() {
    return this->role;
}

int CrewMember::get_age() {
    return this->age;
}
