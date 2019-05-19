#ifndef all_imports
#define all_imports

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

extern tm *ltm;
extern vector<string> crew_first_names;
extern vector<string> crew_last_names;
extern vector<string> spaceship_names;
extern vector<string> planet_names;
extern vector<string> species_names;
extern vector<string> trading_stations_names;

extern ofstream output_file;
extern string output_file_name;

extern int current_sector;
extern int day;

#endif

