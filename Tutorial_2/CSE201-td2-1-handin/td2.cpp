/*
CSE201 - Object Oriented Programming C++
Tutorial 2 - Functions and parameter passing
Yubo Cai
Date: 2022-07-02
*/

#include <iostream> // std::cout, std::fixed
#include <iomanip>  // std::setprecision
#include <math.h>   // sin, cos
#include <limits>   // numeric_limits
#include <stdlib.h> // include rand
#include <cstdlib>
#include "td2.hpp"

// Exercise 1 - Fix the function signature
// 第一个把他编程reference能够修改参数，第二个去除掉reference让他不能够修改参数，第三个把返回变成double来返回小数点
// 这里我们需要pass by reference因为pass by value的话，我们不能够修改参数
void read_point(std::istream &in, // DO NOT CHANGE
                double &x,        // YOU CAN CHANGE THIS LINE
                double &y)        // YOU CAN CHANGE THIS LINE
{
  in >> x; // DO NOT CHANGE
  in >> y; // DO NOT CHANGE
}

// 这里我们要求不改变参数，所以我们不需要pass by reference, pass by value就可以了
double compute_distance(double x1,
                        double y1, // YOU CAN CHANGE THIS LINE
                        double x2, // YOU CAN CHANGE THIS LINE
                        double y2) // YOU CAN CHANGE THIS LINE
{
  x1 = (x1 - x2);       // DO NOT CHANGE
  x1 = x1 * x1;         // DO NOT CHANGE
  y1 = (y1 - y2);       // DO NOT CHANGE
  y1 = y1 * y1;         // DO NOT CHANGE
  return sqrt(x1 + y1); // DO NOT CHANGE
}

double td2_max(double first,  // YOU CAN CHANGE THIS LINE (apart from the function name td2_max)
               double second) // YOU CAN CHANGE THIS LINE
{
  if (first > second)
  {
    return first;
  }
  else
  {
    return second;
  }
}

// Exercise 2 - Generate a target and an obstacles
void generate_target(double &x1, double &y1)
{
  x1 = rand() % 100;
  y1 = rand() % 100;
}

void generate_obstacle(int &i, int &j)
{
  // 他的范围是0-9
  i = rand() % 9;
  j = rand() % 9;
}

// Exercise 3 - Generates multiple targets and obstacles
void generate_targets(double *targets, const int num_targets)
{
  for (int i = 0; i < num_targets; i++)
  {
    generate_target(targets[i * 2], targets[i * 2 + 1]);
  }
}

void generate_obstacles(int *obstacles, const int num_obstacles)
{
  for (int i = 0; i < num_obstacles; i++)
  {
    generate_obstacle(obstacles[i * 2], obstacles[i * 2 + 1]);
  }
}

// Exercise 4 - Sort
// 这里我们使用冒泡排序
void sort(double *targets, const int num_targets)
{
  for (int i = 0; i < num_targets; i++)
  {
    for (int j = i + 1; j < num_targets; j++)
    {
      if (targets[2 * i] > targets[2 * j])
      {
        double tmp1 = targets[2 * i];
        double tmp2 = targets[2 * i + 1];

        // 这里我们翻转两个数来实现冒泡排序
        targets[2 * i] = targets[2 * j];
        targets[2 * j] = tmp1;

        targets[2 * i + 1] = targets[2 * j + 1];
        targets[2 * j + 1] = tmp2;
      }
    }
  }
}

void sort(int *obstacles, const int num_obstacles)
{
  for (int i = 0; i < num_obstacles; i++)
  {
    for (int j = i + 1; j < num_obstacles; j++)
    {
      if (obstacles[2 * i] > obstacles[2 * j])
      {
        int tmp1 = obstacles[2 * i];
        int tmp2 = obstacles[2 * i + 1];

        obstacles[2 * i] = obstacles[2 * j];
        obstacles[2 * j] = tmp1;

        obstacles[2 * i + 1] = obstacles[2 * j + 1];
        obstacles[2 * j + 1] = tmp2;
      }
    }
  }
}

// Exercise 5 - Find collisions with targets and obstacles
double *find_collision(const double x, const double y,
                       double *targets, const int num_targets)
{
  for (int i = 0; i < num_targets; i++)
  {
    double distance = compute_distance(x, y, targets[2 * i], targets[2 * i + 1]);
    if (distance < 1)
    {
      return targets + 2 * i;
    }
  }

  return nullptr;
}

bool intersect_obstacle(double x1, double y1,
                        const int i, const int j)
{
  if ((x1 >= i * 10) && (x1 <= (i + 1) * 10) && (y1 >= j * 10) && (y1 <= (j + 1) * 10))
  {
    return true;
  }
  else
  {
    return false;
  }
}

int *find_collision(const double x, const double y,
                    int *obstacles, const int num_obstacles)
{
  for (int i = 0; i < num_obstacles; i++)
  {
    if (intersect_obstacle(x, y, obstacles[2 * i], obstacles[2 * i + 1]))
    {
      return obstacles + 2 * i;
    }
  }

  return nullptr;
}

// Exercise 6 - Remove target
void remove_target(double *targets, int &tot_targets, double *target_to_remove)
{
  for (int i = 0; i < tot_targets; i++)
  {
    if (targets + 2 * i == target_to_remove)
    {
      for (int j = i; j < tot_targets - 1; j++)
      {
        // 这里我们把后面的数往前移动
        targets[2 * j] = targets[2 * (j + 1)];
        targets[2 * j + 1] = targets[2 * (j + 1) + 1];
      }
      tot_targets--;
      break;
    }
  }
}

// Exercise 7 - Simulate projectiles
bool simulate_projectile(const double magnitude, const double angle,
                         const double simulation_interval,
                         double *targets, int &tot_targets,
                         int *obstacles, int tot_obstacles)
{
  // 我们先设置常量
  double PI = 3.14159265;
  double g = 9.8;

  // 我们先设置初始值
  double x, y = 0;
  double vx = magnitude * cos(angle * PI / 180);
  double vy = magnitude * sin(angle * PI / 180);
  double t = simulation_interval;

  while (1)
  {
    if (find_collision(x, y, obstacles, tot_obstacles) != nullptr)
    {
      return false;
    }

    // 我们先计算下一个点的位置
    // 这里我们设置一个target的指针，如果这个指针不为空，说明我们找到了一个target
    double *target;
    target = find_collision(x, y, targets, tot_targets);
    if (target != nullptr)
    {
      remove_target(targets, tot_targets, target);
      return true;
    }
    y = vy * t - 0.5 * g * t * t;
    // 如果在y轴上的位置小于0，说明我们的弹丸已经落地了，然后我们没有返回因此我们返回false
    if (y <= 0)
    {
      return false;
    }
    x = vx * t;
    t += simulation_interval;
  }
}

// The following function implement the main loop of the game --- nothing to do here
void game_loop(std::ostream &out, std::istream &in,
               const int max_projectiles,
               int *obstacles, const int num_obstacles,
               double *targets, const int num_targets)
{
  int remaining_projectiles = max_projectiles;
  int remaining_targets = num_targets;

  while (remaining_projectiles > 0 && remaining_targets > 0)
  {
    double magnitude, angle;

    out << "Insert the magnitude and angle for the projectile: ";
    read_point(in, magnitude, angle);

    if (simulate_projectile(magnitude, angle, 0.01,
                            targets, remaining_targets,
                            obstacles, num_obstacles))
    {
      out << "You hit one target!" << std::endl;
    }
    else
    {
      out << "You missed the target..." << std::endl;
    }

    remaining_projectiles--;
  }

  if (remaining_targets == 0)
  {
    out << "You won!" << std::endl;
  }
  else
  {
    out << "You lost!" << std::endl;
  }
}

void run_game(std::ostream &out, std::istream &in)
{
  int tot_projectiles = 5;
  int num_obstacles = 3;
  int num_targets = 2;
  int obstacles[num_obstacles * 2];
  double targets[num_targets * 2];

  // Generate random targets
  generate_targets(targets, num_targets);
  sort(obstacles, num_targets);

  // Generate random obstacles
  generate_obstacles(obstacles, num_obstacles);
  sort(obstacles, num_obstacles);

  out << "List of obstacles:";
  for (int i = 0; i < num_obstacles; i++)
    out << " (" << obstacles[2 * i]
        << "," << obstacles[2 * i + 1] << ")";
  out << std::endl;

  out << "List of targets:";
  for (int i = 0; i < num_targets; i++)
    out << " (" << targets[2 * i]
        << "," << targets[2 * i + 1] << ")";
  out << std::endl;

  // Game loop
  game_loop(out, in,
            tot_projectiles,
            obstacles,
            num_obstacles,
            targets, num_targets);
}
