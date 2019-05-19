#include "../../headers/all_imports.h"
#include "../../headers/classes/dead_crew_member.h"

DeadCrewMember::DeadCrewMember() {
    this->place_of_death = current_sector;
    this->time_of_death = day;
}

void DeadCrewMember::set_death() {
    this->place_of_death = current_sector;
    this->time_of_death = day;
}

DeadCrewMember::DeadCrewMember(CrewMember crew_member) {
    this->name = crew_member.get_name();
    this->role = crew_member.get_designation();
    this->age = crew_member.get_age();
    this->is_officer = crew_member.is_officer;

    this->place_of_death = current_sector;
    this->time_of_death = day;
}

void DeadCrewMember::getInfo() {
    output_file << "                Name : " << this->name << endl;
    output_file << "                Age : " << this->age << endl;
    output_file << "                Role : " << this->role << endl;
    output_file << "                Place of Death : Sector " << this->place_of_death << endl;
    output_file << "                Day of Death : " << this->time_of_death << endl;

    output_file << endl;
}

// DeadCrewMember::~DeadCrewMember() {}
