/*  Israel Ayala
 *  02/10/2023
 *  Uses vehicle classes to create a type of car with randomly generated values.
 *  Race header file contains that racetrack where every car will be stored.
 *  The winner of the race is determined by the highest value in their respective 
 *  racetrack.
*/
#include "race.h"
#include <list>

using namespace std;

int main() {
    vehicle my_car;
    int top_speed  = 0;
    int angle      = 0;
    int horsepower = 0;
    int grip       = 0;
    int grnd_clear = 0;
    int sus_trvl   = 0;
    int turbo      = 0;
    float lap_time = 0;
    char name[30];
    string a_name = "";

    // Flag variables for menu. If > 1 do not generate cars again
    int c_flag = 0;
    int r_flag = 0;
    int d_flag = 0;
    int option = 0;
    int select = 0;
    float fastest = 0;

    circuit c_car;
    rally   r_car;
    drift   d_car;

    // DLL of type circuit
    dlist<circuit> c_race;
    // LIST of type rally
    list<rally> r_race;
    // DLL of type drift
    dlist<drift> d_race;

    set_time();

    cout << "\nWelcome to the racing program!" << endl;

    /* USE ASSIGNMENT OPERATORS TO ADD TO A LIST AND DISPLAY */
    do {
        // Select a race type
        select = select_race();
        switch (select) {
            // Work with a circuit race - USING A DLL
            case 1:
                option = circuit_racing(); 
                // Generate Cars
                if (option == 1) {
                    ++c_flag;
                    if (c_flag == 1) {
                        cout << endl;
                        for (int i = 0; i < 5; ++i) {
                            cout << "Enter the vehicle's name: ";
                            cin.get(name, 30, '\n'); cin.ignore(100, '\n');
                            c_car.add(name, lap_time, grip, top_speed, horsepower);
                            circuit * ptr = new circuit(c_car);
                            // Overloaded member += to add at the end of the list
                            c_race += ptr;
                        }
                    } else 
                        cout << "\nCars have already been generated for this race!" << endl;
                }
                // Display the cars
                if (option == 2)
                    // Overloaded << to display a DLL
                    cout << c_race;

                // Remove the last car
                if (option == 3) {
                    if (!c_race.remove()) {
                        cout << "\nThe list is empty!" << endl;
                        c_flag = 0;
                    }
                }

                // Declare Winner!
                if (option == 4) {
                    std::cout << "\nThe winner of the circuit race is:\n";
                    c_race.winner();
                }
                break;

            // Work with a rally race - USING A LIST
            case 2:
                option = rally_racing();
                // Generate cars
                if (option == 1) {
                    ++r_flag;
                    if (r_flag == 1) {
                        cout << endl;
                        for (int i = 0; i < 5; ++i) {
                            cout << "Enter the vehicle's name: ";
                            getline(cin, a_name);
                            r_car.add(a_name, grnd_clear, sus_trvl, turbo, lap_time);
                            r_race.push_back(r_car);
                        }
                    } else 
                        cout << "\nCars have already been generated for this list!" << endl;
                }

                // Display the cars
                if (option == 2) {
                    for (rally r : r_race)
                        r.display();
                }
                
                // Remove the last car
                if (option == 3) {
                    if (!r_race.empty())
                        r_race.erase(--r_race.end());
                    if (r_race.empty()) { 
                        cout << "\nList is empty!" << endl;
                        r_flag = 0;
                    }
                }

                // Declare winner
                if (option == 4) {
                    rally winner;
                    for (rally r : r_race) {
                        if (r.best_time() < fastest) {
                            fastest = r.best_time();
                            winner = r;
                        }
                    }
                    winner.display();
                }
                break;

            // Work with a drifting race - USING A DLL
            case 3:
                option = drift_racing();
                // Generate cars
                if (option == 1) {
                    ++d_flag;
                    if (d_flag == 1) {
                        ++d_flag;
                        cout << endl;
                        for (int i = 0; i < 5; ++i) {
                            cout << "Enter the vehicle's name: ";
                            getline(cin, a_name);
                            d_car.add(a_name, top_speed, angle, grip, lap_time);
                            drift * ptr = new drift(d_car);
                            // Overloaded member += to add at the end of the list
                            d_race += ptr;
                        }
                    } else
                        cout << "\nCars have already been generates for this list!" << endl;
                }

                // Display the cars
                if (option == 2) 
                    // Overloaded << to display a DLL
                    cout << d_race;
                
                // Remove the last car
                if (option == 3) {
                    if (!d_race.remove()) {
                        cout << "\nThe list is empty!" << endl;
                        d_flag = 0;
                    }
                }

                // Declare Winner!
                if (option == 4) {
                    cout << "\nThe winner of the drift race is:\n";
                    d_race.winner();
                }
                break;

            case 4:
                break;
        }
    } while (select != 4);

    return 0;
}
