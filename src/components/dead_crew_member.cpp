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
    // this->captain_score = crew_member.captain_score();
    // this->pilot_score = crew_member.pilot_score();
    // this->engineer_score = crew_member.engineer_score();
    // this->mining_score = crew_member.mining_score();
    // this->weapon_score = crew_member.weapon_score();
    this->place_of_death = place_of_death;
    this->time_of_death = time_of_death;

    cout << this->name << " dead!" << endl;
    cout << " Designation : " << this->role << endl;
    cout << this->age << " years old!" << endl;
}

