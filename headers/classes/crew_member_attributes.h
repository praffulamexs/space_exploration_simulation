#ifndef crew_member_attributes_class
#define crew_member_attribites_class

#include "./species_attributes.h"

class CrewMemberAttributes: public SpeciesAttributes {
    protected:
        int travel_efficiency;
        int combat_maneuvers;
        int conflict_evasion;
        int system_recovery;

        int mining_ability;
        int offensive_performance;
        int defensive_performance;

    public:
        CrewMemberAttributes();
        CrewMemberAttributes(int, int);

        void getInfo();
        // operator+();
        // operator-();

        int captain_score();
        int pilot_score();
        int engineer_score();
        int mining_score();
        int weapon_score();
};

#endif

