#include "./headers/all_imports.h"
#include "./headers/classes/sector.h"
#include "./headers/classes/spaceship.h"
#include "./headers/classes/species.h"

time_t now = time(0);
tm *ltm = localtime(&now);

vector<string> crew_first_names;
vector<string> crew_last_names;

vector<string> spaceship_names;
vector<string> planet_names;
vector<string> species_names;
vector<string> trading_stations_names;

ofstream output_file;
string output_file_name;

int current_sector;

void load_text_files();

int main(int inputs, char **args) {
    if(inputs != 2) {
        /* The number of parameters inserted in the command line */
        cerr << "The number of expected parameters do not match..." << endl;
        return 0;
    }
    else {
        srand(time(0));
        load_text_files();
        output_file_name = "output";
        output_file.open(output_file_name, ios::trunc);
        output_file.close();

        // cout << "Number of sec since January 1,1970:" << now << endl;

        // ltm->tm_year = ltm->tm_year + 3000;

        // print various components of tm structure.
        // cout << "Year" << ltm->tm_year << endl;
        // cout << "Month: " << 1 + ltm->tm_mon + 100 << endl;
        // cout << "Day: " << ltm->tm_mday << endl;
        // cout << "Time: " << 1 + ltm->tm_hour << ":";
        // cout << 1 + ltm->tm_min << ":";
        // cout << 1 + ltm->tm_sec << endl;

        output_file.open(output_file_name, ios::app);
        output_file << "Choosing a spaceship among : " << endl;

        vector<Species> species;
        for(int i=0;i<5; i++) {
            output_file << "    Spaceship " << i+1 << " : " << endl;
            Species ss;
            output_file << "        Name of the Species : " << ss.get_species_name() << endl;
            output_file << "        Name of the Spaceship : " << ss.get_spaceship()->getName() << endl;
            output_file << endl;
            species.push_back(ss);
            // delete ss;
        }

        int random = rand() % 5;

        /* Checking the value for the number of sectors*/
        int sector_number = stoi(args[1]);
        if (sector_number > 50 || sector_number < 1){
            cerr << "Please Enter a number between 1 and 50" << endl;
            return 0;
        }
        // sector_number = 1;

        output_file << "Spaceship chosen : " << endl;
        output_file << "    Species : " << species[random].get_species_name() << endl;
        species[random].get_spaceship()->getInfo();
        
        output_file << "        Captain :" << endl;
        species[random].get_spaceship()->get_captain_info();

        output_file << "        Pilot :" << endl;
        species[random].get_spaceship()->get_pilot_info();

        output_file << "        Engineer :" << endl;
        species[random].get_spaceship()->get_engineer_info();
        
        output_file << "        Mining Officer :" << endl;
        species[random].get_spaceship()->get_mining_officer_info();

        output_file << "        Weapon Officer :" << endl;
        species[random].get_spaceship()->get_weapon_officer_info();

        output_file << "\nThe Journey Begins...\n" << endl;

        output_file << "========================= Sector Beginning ===========================" << endl;

        for (int i = 0; i < sector_number; i++) {
            current_sector = i+1;
            output_file << "    Sector Number : " << i + 1 << endl;
            Sector *sector = new Sector(species[random].get_spaceship());
            if(sector->journey_ended()) {
                delete sector;
                break;
            } else {
                delete sector;
            }
            output_file << "    Resources left at the end of the sector :" << endl;
            species[random].get_spaceship()->resources->getInfo();
            output_file << endl;
            output_file << "======================== Sector End ===========================" << endl;
            output_file << endl;
        }

        output_file << "JOURNEY ENDED.\n" << endl;
        
        output_file << "Spaceship status :" << endl;
        species[random].get_spaceship()->getInfo();
        species[random].get_spaceship()->resources->getInfo();

        output_file << "    Captain :" << endl;
        species[random].get_spaceship()->get_captain_info();

        output_file << "    Pilot :" << endl;
        species[random].get_spaceship()->get_pilot_info();

        output_file << "    Engineer :" << endl;
        species[random].get_spaceship()->get_engineer_info();

        output_file << "    Mining Officer :" << endl;
        species[random].get_spaceship()->get_mining_officer_info();

        output_file << "    Weapon Officer :" << endl;
        species[random].get_spaceship()->get_weapon_officer_info();

        output_file << "    Crew Members :" << endl;
        species[random].get_spaceship()->get_crew_info();

        //deadcrewmembers
        output_file << "    Dead Crew Members :" << endl;
        species[random].get_spaceship()->get_dead_crew_info();

        output_file.close();
        // delete spaceship;
        return 0;
    }
}

void load_text_files() {
    ifstream crew_first_names_file, crew_last_names_file, spaceship_names_file, planet_names_file, species_names_file, trading_stations_names_file;

    // FIRST NAMES FOR CREW MEMBERS
    crew_first_names_file.open("./src/assets/crew/first_names.txt");
    if(!crew_first_names_file) {
        cerr << "Error Loading file." << endl;
    } else {
        while(!crew_first_names_file.eof()) {
            string x;
            crew_first_names_file >> x;
            crew_first_names.push_back(x);
        }
    }
    crew_first_names_file.close();

    // LAST NAMES FOR CREW MEMBERS
    crew_last_names_file.open("./src/assets/crew/last_names.txt");
    if(!crew_last_names_file) {
        cerr << "Error Loading file." << endl;
    } else {
        while(!crew_last_names_file.eof()) {
            string x;
            crew_last_names_file >> x;
            crew_last_names.push_back(x);
        }
    }
    crew_first_names_file.close();


    // NAMES FOR SPACESHIP
    spaceship_names_file.open("./src/assets/spaceship_names.txt");
    if(!spaceship_names_file) {
        cerr << "Error Loading file." << endl;
    } else {
        while(!spaceship_names_file.eof()) {
            string x;
            spaceship_names_file >> x;
            spaceship_names.push_back(x);
        }
    }
    crew_first_names_file.close();


    // NAMES FOR PLANETS
    planet_names_file.open("./src/assets/planet_names.txt");
    if(!planet_names_file) {
        cerr << "Error Loading file." << endl;
    } else {
        while(!planet_names_file.eof()) {
            string x;
            planet_names_file >> x;
            planet_names.push_back(x);
        }
    }
    crew_first_names_file.close();

    
    // NAMES FOR SPECIES
    species_names_file.open("./src/assets/species_names.txt");
    if(!species_names_file) {
        cerr << "Error Loading file." << endl;
    } else {
        while(!species_names_file.eof()) {
            string x;
            species_names_file >> x;
            species_names.push_back(x);
        }
    }
    crew_first_names_file.close();

    
    // NAMES FOR TRADING STATIONS
    trading_stations_names_file.open("./src/assets/trading_station_names.txt");
    if(!trading_stations_names_file) {
        cerr << "Error Loading file." << endl;
    } else {
        while(!trading_stations_names_file.eof()) {
            string x;
            trading_stations_names_file >> x;
            trading_stations_names.push_back(x);
        }
    }
    crew_first_names_file.close();

}
