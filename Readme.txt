-------------------------------------------------------------------------------------------------------------------------------------

Project Title - A Journey Of Space Exploration

Student Id - 6336164
Name - Prafful Jagtap

-------------------------------------------------------------------------------------------------------------------------------------

Instructions :
    Compile : 
        cd <Directory>
        CC -std=c++11 -o JSE ./main.cpp ./src/components/*.cpp
    
    Run :
        ./JSE <number of sectors>

-------------------------------------------------------------------------------------------------------------------------------------

Project Structure :
    Folder Name :
        - File Name

-------------------------------------------------------------------------------------------------------------------------------------

Project Structure :
    - main.cpp - *Application Logic*
    headers :
        - all_imports.h - Contains all the imports from libraries and global variables
        classes : *All the class declaration*
            - crew_member_attributes.h
            - crew_member.h
            - dead_crew_member.h
            - planet.h
            - resource.h
            - setor.h
            - spaceship.h
            - species_attributes.h
            - species.h
            - trading_station.h
    src :
        assets : *text files*
            - planet_names.txt
            - spaceship_names.txt
            - species_names.txt
            - trading_station_names.txt
            crew : *text files for crew member names*
                - first_names.txt
                - last_names.txt
        components : *All the class definitions*
            - crew_member_attributes.cpp
            - crew_member.cpp
            - dead_crew_member.cpp
            - planet.cpp
            - resource.cpp
            - setor.cpp
            - spaceship.cpp
            - species_attributes.cpp
            - species.cpp
            - trading_station.

-------------------------------------------------------------------------------------------------------------------------------------

Simulation Logic :

1. The simulation takes the number of sectors as input from the command line at the beginning. The program terminates if the
number is less than 1 or greater than 50.

2. 5 objects of the class Species are created out of which one is chosen randomly using rand() function. Every Species have their
own spaceship, so that spaceship is chosen as our traveler for our journey.

3. A loop is run between 0 and the input value(-1) and for every iteration an object of class Sector is created.

4. At the beginning of the journey, the resources consumed are calculated for the distance traveled in that sector. If the resources
have been depleted enough for the journey to get over, then the loop will be terminated. Otherwise the journey will continue. In 
case if the spaceship has been in a battle in previous sector and their spaceship health has depleted to 0 or crew members have all
died, then the journey will be terminated.

5. A random number is generate between 1 and 100. If the number is between 1 and 35, a spaceship is encountered. If the number
is between 36 and 60, a planet is encountered. If the number is between 61 and 75, a Trading Station is encountered. If the number
is between 76 and 90, an empty sector is encountered. If the number is between 91 and 100, an abandoned spaceship is encountered.

6. In case of a spaceship encounter, if the diplomacies of both the captains match, then they will trade. If not, then they will
have a combat. In case of trading, if either of the captains have better trading skills than the other, then that spaceship will be
benefited (by giving less gold for goods) and vice versa. In case of combat, The spaceship will try to run away if the number of
crew is less or if the spaceship health is low. Depending on the skills of the crew, the spaceship can evade attacks and reduce
the damage taken by the spaceship from a missile, launched by the enemy. A number of crew members and the officers die when damage
is taken.

7. In case of a planet encounter, the travelers will meet any species residing on that planet. If the diplomacy levels match,
the species may allow the traveler to do mining on their planet. In case if only either of them are happy with this encounter,
then they will agree on trade. Otherwise there will be a conflict and the species will launch a spaceship for battle.

8. In case of a trading station encounter, the travelers will come in contact with another alien species. Depending on their trading
skills, either of them will be benefited or both will have a fair trade if their trading skills are good.

9. In case of an empty sector, the traveler will not come in contact with anyone and will just end up using resources while traveling.

10. In case the travelers come in contact with an abandoned spaceship, the traveler will take the resources they have left and also
accommodate the remaining crew members of that spaceship on theirs.

11. At the end of the simulation the remaining resources, crew information, officers information and dead crew member information
will be displayed in the output file. In case the journey ends because of some other reason, then the reason will be stated as well.

-------------------------------------------------------------------------------------------------------------------------------------