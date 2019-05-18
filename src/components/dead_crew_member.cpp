#include "../../headers/all_imports.h"
#include "../../headers/classes/dead_crew_member.h"

DeadCrewMember::DeadCrewMember() {}

DeadCrewMember::DeadCrewMember(int place, int time) {
    this->place_of_death = place;
    this->time_of_death = time;
}

void DeadCrewMember::set_death(int place, int time) {
    this->place_of_death = place;
    this->time_of_death = time;
}

DeadCrewMember::DeadCrewMember(CrewMember crew_member, int place, int time) {
    this->name = crew_member.get_name();
    this->role = crew_member.get_designation();
    this->age = crew_member.get_age();
    this->is_officer = crew_member.is_officer;

    this->place_of_death = place_of_death;
    this->time_of_death = time_of_death;
}

void DeadCrewMember::getInfo() {
    output_file << "                Name : " << this->name << endl;
    output_file << "                Age : " << this->age << endl;
    output_file << "                Role : " << this->role << endl;
}
