/*
 *  Israel Ayala
 *  02/12/2023
 *  Implementation for the vehicle header file containing the vehicle 
 *  hierarchy. Derived three classes that structrue a more specific type 
 *  and will also use operator overloading
 */
#include "vehicle.h"

using namespace std;

/* VEHICLE BASE CLASS */
// Constructor
vehicle::vehicle() : type{nullptr}, suspension{""}, transmission{""}, 
                     num_tire{4} {}

// Constructor with arguments
vehicle::vehicle(char * type, string suspension, string transmission,
                 int num_tire) {
    if (type) {
        this->type = new char[strlen(type) + 1];
        strcpy(this->type, type);
    } else type = nullptr;

    this->suspension   = suspension;
    this->transmission = transmission;
    this->num_tire     = num_tire;
}

// Copy Constructor
vehicle::vehicle(const vehicle & source) {
    if (source.type) {
        this->type = new char[strlen(source.type) + 1];
        strcpy(this->type, source.type);
    } else type = nullptr;

    suspension   = source.suspension;
    transmission = source.transmission;
    num_tire     = source.num_tire;
}

// Destructor
vehicle::~vehicle() {
    if (type) delete [] type;
    type = nullptr;
    suspension = transmission = "";
    num_tire = 0;
}

// Assignment Operator
vehicle & vehicle::operator = (const vehicle & source) {
    // If current object equals object passed in
    if (this == & source)
        // Return the current object, no work needed
        return * this;

    // Otherwise, if we have dynamic, delete, set to nullptr
    if (type) {
        delete [] type;
        type = nullptr;
    }

    type = new char[strlen(source.type) + 1];
    strcpy(type, source.type);

    suspension   = source.suspension;
    transmission = source.transmission;
    num_tire     = source.num_tire;

    return * this;
}

// Input
istream & operator >> (istream & in, vehicle & source) {
    char temp[100];

    in.get(temp, 100, '\n'); in.ignore(100, '\n');
    source.type = new char[strlen(temp) + 1];
    strcpy(source.type, temp);

    return in;
}

// Output
ostream & operator << (ostream & out, const vehicle & source) {
    out << "\nType: " << source.type 
        << "\nSuspension: " << source.suspension
        << "\nTransmission: " << source.transmission
        << "\nStable tires: " << source.num_tire << endl;
    return out;
}

/*** Will use exception handling ***/
// Relational Operator
bool vehicle::operator > (const vehicle & compare) const {
    if (!type) return false;

    if (strcmp(type, compare.type) > 0)
        return true;
    return false;
}

bool vehicle::operator >= (const vehicle & compare) const {
    if (!type) return false;

    if (strcmp(type, compare.type) >= 0)
        return true;
    return false;
}

bool vehicle::operator < (const vehicle & compare) const {
    if (!type) return false;

    if (strcmp(type, compare.type) < 0)
        return true;
    return false;
}

bool vehicle::operator <= (const vehicle & compare) const {
    if (!type) return false;

    if (strcmp(type, compare.type) <= 0)
        return true;
    return false;
}

bool vehicle::operator == (const vehicle & compare) const {
    if (!type) return false;

    if (strcmp(type, compare.type) == 0)
        return true;
    return false;
}

// Add a vehicle
int vehicle::add(char * type, string suspension, string transmission,
                 string tire_type, int num_tire) {
    if (type) {
        this->type = new char[strlen(type) + 1];
        strcpy(this->type, type);
    } else type = nullptr;

    this->suspension   = suspension;
    this->transmission = transmission;
    this->num_tire     = num_tire;

    return 1;
}

// Generate a random number, can be assigned to data members
int vehicle::rng(int value) {
    // 1 through 10
    value = 1 + (rand() % 10);
    return value;
}

// Generates a random number assigned to a car's top speed
int vehicle::generate_speed(int value) {
    // Set a random value from 80 to 110 mph
    value = 80 + (rand() % 31);
    return value;
}

// Display the properties of a car
void vehicle::display_car() const {
     cout << "\nType: " << type 
          << "\nSuspension: " << suspension
          << "\nTransmission: " << transmission
          << "\nStable tires: " << num_tire << endl;
}

/* Functionality here can change */
// Change suspension
int vehicle::change_suspension(string suspension) {
    this->suspension = suspension; 
    return 1;
}

// Change transmission
int vehicle::change_transmission(string tranmission) {
    this->transmission = tranmission;
    return 1;
}

// Change tires, restores tires back to stable number
int vehicle::change_tire() {
    this->num_tire = 4;
    return 1;
}

/* CIRCUIT DERIVED CLASS */
// Constructor
circuit::circuit() : name{nullptr}, grip{0}, top_speed{0}, horsepower{0}, lap_time{0} {}

// Constructor with arguments
circuit::circuit(char * name, int grip, int top_speed, int horsepower, float lap_time) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    this->grip       = grip;
    this->top_speed  = top_speed;
    this->horsepower = horsepower;
    this->lap_time   = lap_time;
}

// Copy Constructor
circuit::circuit(const circuit & source) : vehicle(source) {
    name = new char[strlen(source.name) + 1];
    strcpy(name, source.name);
    grip       = source.grip;
    top_speed  = source.top_speed;
    horsepower = source.horsepower;
    lap_time   = source.lap_time;
}

// Destructor
circuit::~circuit() {
    if (name) delete [] name;
    name = nullptr;
    grip = top_speed = horsepower = 0;
    lap_time = 0;
}

// Assignment Operator
circuit & circuit::operator = (const circuit & source) {
    if (this == & source)
        return * this;
    if (name) {
        delete [] name;
        name = nullptr;
    }
      
    name = new char[strlen(source.name) + 1];
    strcpy(name, source.name);

    grip       = source.grip;
    top_speed  = source.top_speed;
    horsepower = source.horsepower;
    lap_time   = source.lap_time;

    return * this;
}

// Add a circuit car
int circuit::add(char * name, int grip, int top_speed, int horsepower, float lap_time) {
    if (!name) return 0;

    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    // Add the best lap time to the car
    this->grip       = vehicle::rng(grip);
    this->top_speed  = vehicle::generate_speed(top_speed);
    this->horsepower = vehicle::rng(horsepower);

    // Calculate the best time,
    // determined by setting a default lap time of 400 seconds then we
    // subtract a cars attributes as well as its speed divided by 2.
    this->lap_time = 400 - (this->top_speed / 2) - grip - horsepower;

    return 1;
}

// Display a circuit style car
void circuit::display() const {
    cout << "\nVehicle: " << name 
         << "\nTop speed: " << top_speed
         << "\nTire Grip: " <<  grip 
         << "\nHorsepower: " << horsepower
         << "\nLap time: " << lap_time << " seconds" << endl;
}

// Return the best lap time in a car
float circuit::best_time() {
    return this->lap_time;
}

/* RALLY DERIVED CLASS */
// Constructor
rally::rally() : name{""}, grnd_clear{0}, sus_trvl{0}, turbo{0}, lap_time{0} {}

// Constructor with arguments
rally::rally(string name, int grnd_clear, int sus_trvl, int turbo, float lap_time) {
    this->name       = name;
    this->grnd_clear = grnd_clear;
    this->sus_trvl   = sus_trvl;
    this->turbo      = turbo;
    this->lap_time   = lap_time;
}

// Destructor
rally::~rally() {
    name       = "";
    grnd_clear = 0;
    sus_trvl   = 0;
    turbo      = 0;
    lap_time   = 0;
}

// Add a car
int rally::add(string name, int grnd_clear, int sus_trvl, int turbo, float lap_time) {
    this->name       = name;
    this->grnd_clear = vehicle::rng(grnd_clear);
    this->sus_trvl   = vehicle::rng(sus_trvl);
    this->turbo      = vehicle::rng(turbo);
    // Default lap time for a rally race is 300 seconds
    this->lap_time   = 300 - this->grnd_clear - this->sus_trvl - this->turbo;

    return 1;
}

// Display a rally car
void rally::display() const {
    cout << "\nVehicle: " << name
         << "\nGround Clearance: " << grnd_clear 
         << "\nSuspension Travel: " << sus_trvl 
         << "\nTurbo Level: " << turbo
         << "\nBest Lap Time: " << lap_time << " seconds" << endl;
}

// Return a car's best lap time
float rally::best_time() {
    return lap_time;
}

/* DRIFT DERIVED CLASS */
// Constructor
drift::drift() : name{""}, top_speed{0}, angle{0}, grip{0}, lap_time{0} {}

// Constructor with arguments
drift::drift(string name, int top_speed, int angle, int grip, float lap_time) {
    this->name      = name;
    this->top_speed = top_speed;
    this->angle     = angle;
    this->grip      = grip;
    this->lap_time  = lap_time;
}

// Destructor
drift::~drift() {
    name      = "";
    top_speed = 0;
    angle     = 0;
    grip      = 0;
    lap_time  = 0;
}

// Create a new drifting car with random values generated into its attributes
int drift::add(string name, int top_speed, int angle, int grip, float lap_time) {
    this->name      = name;
    this->top_speed = vehicle::generate_speed(top_speed);
    this->angle     = vehicle::rng(angle);
    this->grip      = vehicle::rng(grip);
    // Default lap time for a drift race is 200 seconds
    this->lap_time  = 200 - (this->top_speed / 2) - angle - grip;

    return 1;
}

// How to calculate drift score?
//  - Each drifting car has a unique value in its top speed, drifting angle,
//    tire grip, and lap time.
//  - If top speed helps with lap time, and drifting angle achieves a tighter turn,
//    a tire's grip allows this to happen . . .
//  - We can add all the values of the car's attributes, this could determine 
//    an "average score".
//      - A car with x amount of horsepower can be expected to perform a certain way.
// A drift score is determined by a car's attributes excluded the lap time
// This is because it could be beneficial in situations where it shouldn't be.
// For example, if a car is very slow then a larger number is set to it's best 
// lap time. Then this large number is added onto the drifting score benefitting
// the slower driver. 
int drift::drift_score() {
    return top_speed + angle + grip;
}

// Return best lap time
float drift::best_time() {
    return lap_time;
}

// Display a drift car
void drift::display() {
    cout << "\nVehicle: " << name
         << "\nTop Speed: " << top_speed 
         << "\nDrift Angle: " << angle
         << "\nTire Grip: " << grip
         << "\nDrift Score: " << drift_score() 
         << "\nBest Lap Time: " << lap_time << " seconds" << endl;
}

/* MENU OPTIONS FOR MAIN */
// Select a type of race, circuit, rally, or drift
int select_race() {
    int option = 0;

    do {
        cout << "\nPlease select a race you would like to compete in"
             << "\n1: Circuit Racing"
             << "\n2: Rally Racing"
             << "\n3: Drift Racing"
             << "\n4: Quit" << endl;
        cin >> option; cin.ignore(100, '\n'); 
    } while (option < 1 || option > 4);

    return option;
}

// Options for a circuit
int circuit_racing() {
    int option = 0;

    do {
        cout << "\nWelcome to Circuit Racing!\n"
                "\nWhat would you like to do?"
                "\n1: Generate cars"
                "\n2: Display cars"
                "\n3: Remove car in front of list"
                "\n4: Race!" << endl;
        cin >> option; cin.ignore(100, '\n');
    } while (option < 1 || option > 4);
    return option;
}

// Options for a rally
int rally_racing() {
    int option = 0;

    do {
        cout << "\nWelcome to Rally Racing!\n"
                "\nWhat would you like to do?"
                "\n1: Generate cars"
                "\n2: Display cars"
                "\n3: Remove last car"
                "\n4: Race!" << endl;
        cin >> option; cin.ignore(100, '\n');
    } while (option < 1 || option > 4);
    return option;
}

// Options for a drift
int drift_racing() {
    int option = 0;

    do {
        cout << "\nWelcome to Drift Racing!\n"
                "\nWhat would you like to do?"
                "\n1: Generate cars"
                "\n2: Display cars"
                "\n3: Remove last car"
                "\n4: Race!" << endl;
        cin >> option; cin.ignore(100, '\n');
    } while (option < 1 || option > 4);
    return option;
}

// Sets a new time for the rng function
void set_time() {
    srand(time(0));
}


