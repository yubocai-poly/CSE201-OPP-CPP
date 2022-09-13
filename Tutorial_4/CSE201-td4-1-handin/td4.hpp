/*
CSE201 - Object Oriented Programming C++
Tutorial 4 - Programming with classes
Yubo Cai
Date: 2022-07-02
*/

#ifndef TD4_HPP
#define TD4_HPP

#include <iostream>

#define EXERCISE_1 1
#define EXERCISE_2 1
#define EXERCISE_3 1
#define EXERCISE_4 1
#define EXERCISE_5 1
#define EXERCISE_6 1
#define EXERCISE_7 1

#endif // TD4_HPP

// Exercise 1 - A class for representing the coordinates of a point
class Coordinate
{
public:
    Coordinate();
    Coordinate(double x, double y);
    double get_x();
    double get_y();
    double get_distance(Coordinate);

private:
    double x;
    double y;
};

// Exercise 2 - Creating a class for the target
class Target
{
public:
    Target();
    Target(Coordinate, double);
    Coordinate get_position();
    double get_radius();
    void randomize();

private:
    double x, y, radius;
};

// Exercise 3 - Implement a Projectile class
class Projectile
{
public:
    Projectile(Coordinate, double, double);
    Projectile();
    Coordinate get_position();
    double get_velocity_x();
    double get_velocity_y();

    // Exercise 4 - Simulating the projectile’s motion
    void simulate_step(double);

    // Exercise 5 - Detecting the collision with a target
    bool intersect(Target);

private:
    double x, y, velocity_x, velocity_y;
};

// Exercise 6 - Recording the projectile’s trajectory
class Telemetry
{
public:
    Telemetry();
    ~Telemetry();
    int get_tot_points();
    void add_point(double, double, double);
    void get_point(int, double &, double &, double &);

private:
    int tot_points;
    int *x;
    int *y;
    int *time;
};

// Exercise 7 - Assembly all together: the game class
class Game
{
public:
    Game(Projectile projectile_other, Target target) : projectile(projectile_other), target(target)
    {
        time = 0;
    };
    Game(Projectile projectile_other) : Game(projectile_other, Target()) { target.randomize(); };
    void run(double simulation_interval);
    ~Game() {}
    Telemetry telemetry;

private:
    Projectile projectile;
    Target target;
    double time;
};
