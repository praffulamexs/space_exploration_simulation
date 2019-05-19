#ifndef dead_crew_member_class
#define dead_crew_member_class

#include "./crew_member.h"

class DeadCrewMember: public CrewMember {
    private:
        int place_of_death;
        int time_of_death;
    public:
        DeadCrewMember();
        DeadCrewMember(CrewMember);
        void set_death();
        void getInfo();

};

#endif

