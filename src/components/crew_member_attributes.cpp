#include "../../headers/all_imports.h"
#include "../../headers/classes/crew_member_attributes.h"

CrewMemberAttributes::CrewMemberAttributes() {
    this->travel_efficiency = rand() % 100 + 1;
    this->combat_maneuvers = rand() % 100 + 1;
    this->conflict_evasion = rand() % 100 + 1;
    this->system_recovery = rand() % 100 + 1;
    this->mining_ability = rand() % 100 + 1;
    this->offensive_performance = rand() % 100 + 1;
    this->defensive_performance = rand() % 100 + 1;
}

CrewMemberAttributes::CrewMemberAttributes(int species_diplomacy, int species_trading) {
    this->diplomacy = rand() % species_diplomacy + 1;
    this->trading = rand() % species_trading + 1;

    this->travel_efficiency = rand() % 100 + 1;
    this->combat_maneuvers = rand() % 100 + 1;
    this->conflict_evasion = rand() % 100 + 1;
    this->system_recovery = rand() % 100 + 1;
    this->mining_ability = rand() % 100 + 1;
    this->offensive_performance = rand() % 100 + 1;
    this->defensive_performance = rand() % 100 + 1;
}

void CrewMemberAttributes::getInfo() {
    cout << "   travel_efficiency : " << this->travel_efficiency << endl;
    cout << "   combat_maneuvers : " << this->combat_maneuvers << endl;
    cout << "   conflict_evasion : " << this->conflict_evasion << endl;
    cout << "   system_recovery : " << this->system_recovery << endl;
    cout << "   mining_ability : " << this->mining_ability << endl;
    cout << "   offensive_performance : " << this->offensive_performance << endl;
    cout << "   defensive_performance : " << this->defensive_performance << endl;
    cout << "   diplomacy : " << this->diplomacy << endl;
    cout << "   trading : " << this->trading << endl;

    cout << "       Captain Score : " << this->captain_score() << endl;
    cout << "       Pilot Score : " << this->pilot_score() << endl;
    cout << "       Engineer Score : " << this->engineer_score() << endl;
    cout << "       Mining Score : " << this->mining_score() << endl;
    cout << "       Weapon Score : " << this->weapon_score() << endl;
}

int CrewMemberAttributes::captain_score() {
    int score = (this->diplomacy + this->trading) / 2;
    return score;
}

int CrewMemberAttributes::pilot_score() {
    int score = (this->travel_efficiency + this->combat_maneuvers + this->conflict_evasion)/3;
    return score;
}
int CrewMemberAttributes::engineer_score() {
    int score = (this->travel_efficiency + this->combat_maneuvers + this->conflict_evasion + this->defensive_performance + this->system_recovery) / 5;
    return score;
}
int CrewMemberAttributes::mining_score() {
    int score = this->mining_ability;
    return score;
}
int CrewMemberAttributes::weapon_score() {
    int score = (this->offensive_performance + this->defensive_performance) / 2;
    return score;
}

