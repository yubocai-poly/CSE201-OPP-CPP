/*
CSE201 - Object Oriented Programming C++
Tutorial 1 - First C++ program (compiling and running) and Control Flow - 编译与运行第一个C++程序和控制流
Yubo Cai
Date: 2022-07-02
*/

#include <iostream> // std::cout, std::fixed
#include <iomanip>  // std::setprecision
#include <math.h>   // sin, cos
#include <limits>   // numeric_limits

// Exercise 1 - Find the maximum of two numbers
/**
 * @brief Computes the maximum between two numbers
 * @param first
 * @param second
 * @return the maximum between first and second
 */
double max(double first, double second)
{
    // IMPLEMENT YOUR CODE HERE
    if (first > second)
    {
        return first;
    }
    else
    {
        return second;
    }
}

// 我们添加一个辅助函数，用于计算两个数的最小值
/**
 * @brief Computes the maximum between two numbers
 * @param first
 * @param second
 * @return the maximum between first and second
 */
double min(double first, double second)
{
    if (first > second)
    {
        return second;
    }
    else
    {
        return first;
    }
}

// Exercise 2 - Read two numbers and print the maximum
/**
 * @brief Reads two numbers and output the maximum
 * @param cout Output stream to print the maximum
 * @param cin Input stream to read the input numbers
 * @return 0 if there are no errors
 */
int max_io(std::ostream &out, std::istream &in)
{
    // IMPLEMENT YOUR CODE HERE
    double first, second;
    in >> first >> second;
    out << "The maximum number is:" << max(first, second) << std::endl;

    // WARNING -- remember to output
    // "The maximum number is: " followed by the maximum number
}

// Exercise 3 - Read and print 5 numbers
/**
 * @brief read_doubles Read and prints a list of 5 numbers
 * @param cout Stream to print the numbers
 * @param cin Stream to read the numbers from
 * @return 0 if there are no errors
 */
int read_doubles(std::ostream &out, std::istream &in)
{
    double numbers[5];
    for (int i = 0; i < 5; i++)
    {
        in >> numbers[i];
    }

    // 打印数组
    for (int i = 0; i < 5; i++)
    {
        out << numbers[i] << " ";
    }
}

// Exercise 4 - Simulates the projectile trajectory
/**
 * @brief Computes the trajectory of a projectile
 * @param magnitude of the initial velocity vector of the projectile
 * @param angle of the initial velocity vector of the projectile
 * @param simulation_interval time interval used to simulate the projectile's
 * trajectory
 * @return the final position of the projectile before hitting the ground
 */
double simulate_projectile(const double magnitude,
                           const double angle,
                           const double simulation_interval)
{
    double PI = 3.14159265;
    double g = 9.8;

    // IMPLEMENT YOUR CODE HERE

    double x = 0, y = 0;
    double vx = magnitude * cos(angle * PI / 180);
    double vy = magnitude * sin(angle * PI / 180);
    double t = simulation_interval;

    if (angle == 0)
    {
        return 0;
    }

    while (y >= 0)
    {
        y = vy * t - 0.5 * g * t * t; // we need to first compute the y value

        if (y < 0)
        {
            return x;
        }

        x = vx * t;
        t = t + simulation_interval;
    }

    return x;
}

// Exercise 5 - Minimum distance from a target
/**
 * @brief Computes the minimum distance between the projectile trajectory
 * and a target
 * @param magnitude of the initial velocity vector of the projectile
 * @param angle of the initial velocity vector of the projectile
 * @param simulation_interval time interval used to simulate the projectile's
 * trajectory
 * @param x_target is the x coordinate of the target
 * @param y_target is the y coordinate of the target
 * @return the minimum distance from the projectile to the target
 */
double
compute_min_distance(const double magnitude,
                     const double angle,
                     const double simulation_interval,
                     const double x_target,
                     const double y_target)
{
    double distance = 1000000000000; // 我们预先设置一个较大的数

    double PI = 3.14159265;
    double g = 9.8;
    double x = 0, y = 0;
    double vx = magnitude * cos(angle * PI / 180);
    double vy = magnitude * sin(angle * PI / 180);
    double t = simulation_interval;

    while (y >= 0)
    {
        distance = min(distance, sqrt(pow(x - x_target, 2) + pow(y - y_target, 2)));
        y = vy * t - 0.5 * g * t * t; // we need to first compute the y value
        x = vx * t;
        t = t + simulation_interval;
    }

    return distance;
}

// Exercise 6 - Multiple projectiles
/**
 * @brief Computes the minimum distance between several projectile
 * trajectories and a  target
 * @param proj_magitude magnitudes of the projectiles
 * @param proj_angle angles of the projectiles
 * @param simulation_interval time interval used to simulate the projectile's
 * trajectory
 * @param x_target is the x coordinate of the target
 * @param y_target is the y coordinate of the target
 * @return the minimum distance
 */
double simulate_multiple_projectiles(const double proj_magnitude[],
                                     const double proj_angle[],
                                     const int total_projectile,
                                     const double simulation_interval,
                                     const double x_target,
                                     const double y_target)
{
    double min_distance = 1000000000000; // 我们预先设置一个较大的数
    for (int i = 0; i < total_projectile; i++)
    {
        min_distance = min(min_distance, compute_min_distance(proj_magnitude[i], proj_angle[i], simulation_interval, x_target, y_target));
    }

    return min_distance;
}

// Exercise 7 - Shooting game
/**
 * @brief Shooting game
 * @param out is the output stream to print the game's output
 * @param in is the input stream to read the game's input
 * @return 0 if the function terminates correctly
 */
int play_game(std::ostream &out, std::istream &in)
{
    double simulation_interval = 0.05;
    double distance = 0;

    // IMPLEMENT YOUR CODE HERE

    double x_target, y_target;
    const int total_projectile = 5;
    double proj_magnitude[total_projectile];
    double proj_angle[total_projectile];

    in >> x_target >> y_target; // 这里用户输入X和Y的坐标
    for (int i = 0; i < total_projectile; i++)
    {
        in >> proj_magnitude[i] >> proj_angle[i]; // 这里用户输入每个炮弹的速度和角度
    }

    distance = simulate_multiple_projectiles(proj_magnitude, proj_angle, total_projectile, simulation_interval, x_target, y_target);

    if (distance < 1)
    {
        out << "You hit the target" << std::endl;
    }
    else
    {
        out << "You did not hit the target" << std::endl;
    }

    // WARNING -- remember to output
    // "You hit the target" if a projectile hit target
    // "You did not hit the target" if it didn't
}
