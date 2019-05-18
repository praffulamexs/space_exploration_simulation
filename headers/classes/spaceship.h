#ifndef spaceship_class
#define spaceship_class

#include "./resource.h"
#include "./crew_member.h"
#include "./dead_crew_member.h"
// #include  "./species.h"

class SpaceShip {
    private:
        string name;

        int fuel_capacity;
        int food_capacity;
        int crew_capacity;
        int scrap_capacity;
        int gold_capacity;
        
        int speed;
        int spaceship_health;

        void do_trading(SpaceShip*, int);
        // void starved_to_death(int);

        vector<CrewMember> crew;
        vector<DeadCrewMember> dead_crew;

        CrewMember captain;
        CrewMember pilot;
        CrewMember engineer;
        CrewMember mining_officer;
        CrewMember weapon_officer;

    public:
        SpaceShip(bool);
        SpaceShip(bool, int, int);

        int total_crew();
        Resource *resources;

        string getName();
        void getInfo();

        bool check_if_alive();

        void operator+(SpaceShip *);
        bool operator==(SpaceShip *);

        bool travel(int);
        void combat(SpaceShip*);

        void damage_dealt(int);
        void fuel_consume(int);

        void trade(SpaceShip*);

        void find_officers();

        void find_captain();
        void find_pilot();
        void find_engineer();
        void find_mining_officer();
        void find_weapon_officer();

        void get_captain_info();
        void get_pilot_info();
        void get_engineer_info();
        void get_mining_officer_info();
        void get_weapon_officer_info();

        void get_crew_info();
        void get_dead_crew_info();

        int get_speed();

        int diplomacy();
        int trading();
        int travel_efficiency();
        int combat_maneuvers();
        int conflict_evasaion();
        int system_recovery();

        int mining_ability();
        int defensive_performance();
        int offensive_performance();

        int food_needed();
        int fuel_needed();
        int scrap_needed();
        int gold_needed();
};

#endif

