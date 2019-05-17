#include "../../headers/all_imports.h"
#include "../../headers/classes/crew_member.h"

CrewMember::CrewMember() {
    this->name = "Mogambo";
    this->role = "Crew Member";
    this->age = rand() % 80 + 20;
    this->is_officer = false;
    this->attributes = new CrewMemberAttributes();
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
    cout << "Name : " << this->name << endl;
    cout << "Age : " << this->age << endl;
    cout << "Officer : " << this->is_officer << endl;
    cout << "Attributes : " << endl;
    this->attributes->getInfo();
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

