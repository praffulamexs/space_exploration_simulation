#ifndef crew_member_class
#define crew_member_class

#include "./crew_member_attributes.h"

class CrewMember {
    protected:
        string name;
        string role;
        int age;
        
        CrewMemberAttributes *attributes;

    public:
        bool is_officer;
        
        string get_name();
        string get_designation();
        int get_age();

        int captain_score();
        int pilot_score();
        int engineer_score();
        int mining_score();
        int weapon_score();

        CrewMember();
        CrewMember(int, int);
        void getInfo();
        void change_officer_status(string);

};

#endif

