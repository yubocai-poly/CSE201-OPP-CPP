/*
CSE201 - Object Oriented Programming C++
Tutorial 4 - Programming with classes
Yubo Cai
Date: 2022-07-02
*/

#include <iostream>
#include <math.h>
#include <stdlib.h> // include rand

#include "td4.hpp"

double PI = 3.14159265;
const double G_CONSTANT = 9.8;

// Exercise 1 - A class for representing the coordinates of a point
Coordinate::Coordinate()
{
    x = 0;
    y = 0;
}

Coordinate::Coordinate(double x, double y)
{
    this->x = x;
    this->y = y;
}

double Coordinate::get_x()
{
    return x;
}

double Coordinate::get_y()
{
    return y;
}

double Coordinate ::get_distance(Coordinate other)
{
    double x_diff = x - other.x;
    double y_diff = y - other.y;
    return sqrt(x_diff * x_diff + y_diff * y_diff);
}

// Exercise 2 - Creating a class for the target
Target::Target()
{
    x = 0;
    y = 0;
    radius = 1;
}

Target::Target(Coordinate coordinate, double radius1)
{
    x = coordinate.get_x();
    y = coordinate.get_y();
    radius = radius1;
}

Coordinate Target::get_position()
{
    Coordinate coordinate(x, y);
    return coordinate;
}

double Target::get_radius()
{
    return radius;
}

void Target::randomize()
{
    x = rand() % 100;
    y = rand() % 100;
}

// Exercise 3 - Implement a Projectile class
Projectile::Projectile()
{
    x = 0;
    y = 0;
    // 初始速度是1，角度是45度
    velocity_x = 1 * sqrt(2) / 2;
    velocity_y = 1 * sqrt(2) / 2;
}

Projectile::Projectile(Coordinate coordinate, double magnitude, double angle)
{
    x = coordinate.get_x();
    y = coordinate.get_y();
    velocity_x = magnitude * cos(angle * PI / 180);
    velocity_y = magnitude * sin(angle * PI / 180);
}

Coordinate Projectile::get_position()
{
    Coordinate coordinate(x, y);
    return coordinate;
}

double Projectile::get_velocity_x()
{
    return velocity_x;
}

double Projectile::get_velocity_y()
{
    return velocity_y;
}

// Exercise 4 - Simulating the projectile’s motion
void Projectile::simulate_step(double t)
{
    velocity_y = velocity_y - G_CONSTANT * t;
    x += velocity_x * t;
    y += velocity_y * t - 0.5 * G_CONSTANT * t * t;
}

// Exercise 5 - Detecting the collision with a target
bool Projectile::intersect(Target target)
{
    Coordinate position = target.get_position();
    double distance = position.get_distance(this->get_position());
    if (distance <= target.get_radius())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Exercise 6 - Recording the projectile’s trajectory
Telemetry::Telemetry()
{
    x = new double[10000];
    y = new double[10000];
    time = new double[10000];
    tot_points = 0;
}

Telemetry::~Telemetry()
{
    delete[] x;
    delete[] y;
    delete[] time;
}

int Telemetry::get_tot_points()
{
    return tot_points;
}

void Telemetry::add_point(double T, double X, double Y)
{
    x[tot_points] = X;
    y[tot_points] = Y;
    time[tot_points] = T;
    tot_points++;
}

void Telemetry::get_point(int i, double &Time, double &X, double &Y)
{
    X = x[i];
    Y = y[i];
    Time = time[i];
}


// Exercise 7 - Assembly all together: the game class
void Game::run(double simulation_interval)
{
    do
    {
        telemetry.add_point(time, projectile.get_position().get_x(), projectile.get_position().get_y());
        projectile.simulate_step(simulation_interval);
        time += simulation_interval;
    } while (!projectile.intersect(target) && projectile.get_position().get_y() >= 0);
}
