#include "./headers/all_imports.h"
#include "./headers/classes/sector.h"
#include "./headers/classes/spaceship.h"


int main(int inputs, char **args) {
    if(inputs != 2) {
        /* The number of parameters inserted in the command line */
        cerr << "The number of expected parameters do not match..." << endl;
        return 0;
    }
    else {
        srand(time(0));

        vector<SpaceShip*> spaceships;
        for(int i=0; i<5; i++) {
            SpaceShip *ss = new SpaceShip(true);
            spaceships.push_back(ss);
            delete ss;
        }

        int random = rand() % 5;
        SpaceShip *spaceship = spaceships[random];

        /* Checking the value for the number of sectors*/
        int sector_number = stoi(args[1]);
        if (sector_number > 50 || sector_number < 1){
            cerr << "Please Enter a number between 1 and 50" << endl;
            return 0;
        }

        // spaceship->resources = new Resource(200, 200, 200, 200);
        for (int i = 0; i < sector_number; i++) {
            cout << "Sector Number : " << i+1 << endl;
            Sector *sector = new Sector(spaceship);
            if(sector->journey_ended()) {
                cout << "ENDED" << endl;
                delete sector;
                break;
            } else {
                cout << "NOT YET" << endl;
                delete sector;
            }
        }

        delete spaceship;
        return 0;
    }
}


