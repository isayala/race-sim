/*
 *  Israel Ayala
 *  02/10/2023
 *  The vehicle header file contains a hierarchy of a base class called
 *  vehicle followed by three derived classes that structure a specific
 *  type of vehicle. The base class will handle the type of vehicle, the
 *  type of suspension and transmission, the type of tires required on this
 *  vehicle and the number of stable tires.
 *  Operator overloading will also be present where ever applicable.
*/
#include <iostream>
#include <ctime>
#include <cstring>
#include <string>
#include <vector>
using std::string;

// A type of vehicle consists of a suspension, transmission and various
// attributes. Also using operators.
class vehicle {
    public:
        // Constructor
        vehicle();
        // Constructor with arguments
        vehicle(char * type, string suspension, string transmission,
                int num_tire);
        // Copy Constructor
        vehicle(const vehicle & source);
        // Destructor
        ~vehicle();
        // Assignment Operator
        vehicle & operator = (const vehicle & source);

        // Input
        friend std::istream & operator >> (std::istream & in, vehicle & source);
        // Output
        friend std::ostream & operator << (std::ostream & out, const vehicle & source);

        // Relational Operators
        bool operator >  (const vehicle & compare) const;
        bool operator >= (const vehicle & compare) const;
        bool operator <  (const vehicle & compare) const;
        bool operator <= (const vehicle & compare) const;
        bool operator == (const vehicle & compare) const;
        
        // Add a vehicle
        int add(char * type, string suspension, string transmission,
                string tire_type, int num_tire);
        // Display the properties of a car
        void display_car() const;
        // Change suspension
        int change_suspension(string suspension);
        // Change transmission
        int change_transmission(string tranmission);
        // Change tires, restores tires back to stable number
        int change_tire();
        // Generate a random number, can be assigned to data members
        int rng(int value);
        // Generates a random number assigned to a car's top speed
        int generate_speed(int value);

    protected:
        char * type;         // Type of vehicle
        string suspension;   // Type of suspension
        string transmission; // Type of transmission
        string tire_type;    // Type of tires
        int num_tire;        // Number of stable tires
};

/* LAP TIME IS MEMBER IN EACH DERIVED CLASS */
// Track style racecar
class circuit : public vehicle {
    public:
        // Constructor
        circuit();
        // Constructor with arguments
        circuit(char * name, int grip, int top_speed, int horsepower, float lap_time);
        // Copy Constructor
        circuit(const circuit & source);
        // Destructor
        ~circuit();
        // Assignment Operator
        circuit & operator = (const circuit & source);

        // Can generate a new car with randomnly generated values
        int add(char * name, int grip, int top_speed, int horsepower, float lap_time);
        // Return a car's best lap time
        float best_time();
        // Display a circuit style car
        void display() const;

    protected:
        char * name;    // Name of car
        int grip;       // Level of grip on tires
        int top_speed;  // Top speed achievable
        int horsepower; // Horsepower in the car
        float lap_time; // Vehicle's lap time
};

// Rally style racecar 
class rally : public vehicle {
    public:
        // Constructor
        rally();
        // Constructor with arguments
        rally(string name, int grnd_clear, int sus_trvl, int turbo, float lap_time);
        // Destructor
        ~rally();

        // Add a car
        int add(string name, int grnd_clear, int sus_trvl, int turbo, float lap_time);
        // Return a car's best lap time
        float best_time();
        // Display a rally car
        void display() const;

     protected:
        string name;    // Vehicle's name
        int grnd_clear; // Ground clearance
        int sus_trvl;   // Suspension travel
        int turbo;      // Top speed with turbo
        float lap_time; // Vehicle's lap time
};

// Drift style racecar
class drift : public vehicle {
    public:
        // Constructor
        drift();
        // Constructor with arguments
        drift(string name, int top_speed, int angle, int grip, float lap_time);
        // Destructor
        ~drift();
        
        // Add a new car
        int add(string name, int top_speed, int angle, int grip, float lap_time);
        // Calculate's the drift score
        int drift_score(); 
        // Return a car's best lap time
        float best_time();
        // Display a drift car
        void display();
        
    protected:
        string name;    // Car's name
        int top_speed;  // Car's speed
        int angle;      // How close car is to wall/corner/ or into turn
        int grip;       // Tire grip level
        float lap_time; // Car's lap time
};

/* Functions for the menu in main */
// Select a type of race, circuit, rally, or drift
int select_race();
// Options for a circuit
int circuit_racing();
// Options for a rally 
int rally_racing();
// Options for a drift
int drift_racing();
// Set the time for a random number generator
void set_time();
