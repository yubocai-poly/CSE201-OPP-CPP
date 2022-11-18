/*
CSE201 - Object Oriented Programming C++
Tutorial 5 - Operator overloading, static class members, class inheritance, dynamic allocation of objects.
Yubo Cai
Date: 2022-07-02
*/

#include <iostream>
#include <math.h>

#include "td5.hpp"

// -----------------------------------------------------------------------------
// Exercise 1
// -----------------------------------------------------------------------------

// Define the arithmetic operators
// 文件在td5.hpp中

// -----------------------------------------------------------------------------
// Exercise 2
// -----------------------------------------------------------------------------

// Define the comparison operators
// 文件在td5.hpp中

// -----------------------------------------------------------------------------
// Exercise 3
// -----------------------------------------------------------------------------
// Initialize the static data members
double Coordinate::max_x = 0;
double Coordinate::max_y = 0;

void Coordinate::reset_max()
{
  max_x = 0;
  max_y = 0;
}

double Coordinate::get_x_max()
{
  return max_x;
}

double Coordinate::get_y_max()
{
  return max_y;
}

#if EXERCISE_4 == 1
// -----------------------------------------------------------------------------
// Exercise 4
// -----------------------------------------------------------------------------

DroppingProjectile::DroppingProjectile(Coordinate position_other,
                                       double magnitude,
                                       double angle) : Projectile(position_other, magnitude, angle)
{
  // IMPLEMENT YOUR CODE HER
}

DroppingProjectile::DroppingProjectile() : Projectile()
{
  // IMPLEMENT YOUR CODE HER
}

DroppingProjectile::~DroppingProjectile()
{
  // IMPLEMENT YOUR CODE HERE
}

void DroppingProjectile::simulate_step(double time_interval)
{
  // IMPLEMENT YOUR CODE HERE
  const double g = 9.8;
  position = Coordinate(position.get_x() + velocity_x * time_interval,
                        position.get_y() + velocity_y * time_interval - 0.5 * g * time_interval * time_interval);
  velocity_y = velocity_y - g * time_interval;
  if (velocity_y < 0)
  {
    velocity_x = 0;
  }
}

#endif

// -----------------------------------------------------------------------------
// Exercise 6
// -----------------------------------------------------------------------------

ListNode::ListNode(Projectile projectile)
{
  // IMPLEMENT YOUR CODE HERE
  element = projectile;
  next = nullptr;
}

Projectile ListNode::get_projectile()
{
  // IMPLEMENT YOUR CODE HERE
  return element;
}

void ListNode::set_next(ListNode *next)
{
  // IMPLEMENT YOUR CODE HERE
  this->next = next;
}

ListNode *ListNode::get_next()
{
  // IMPLEMENT YOUR CODE HERE
  return next;
}

// -----------------------------------------------------------------------------
// Exercise 7
// -----------------------------------------------------------------------------

List::List()
{
  // IMPLEMENT YOUR CODE HERE
  head = nullptr;
  tail = nullptr;
}

List::~List()
{
  // IMPLEMENT YOUR CODE HERE
  // 销毁链表
  delete head;
  delete tail;
}

bool List::is_empty()
{
  // IMPLEMENT YOUR CODE HERE
  if (head == nullptr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void List::append(Projectile projectile)
{
  // IMPLEMENT YOUR CODE HERE
  if (head == nullptr)
  {
    head = new ListNode(projectile);
    tail = head;
  }
  else
  {
    tail->set_next(new ListNode(projectile));
    tail = tail->get_next();
  }
}

Projectile List::remove_from_top()
{
  // IMPLEMENT YOUR CODE HERE
  Projectile temp = head->get_projectile();
  if (head->get_next() == nullptr)
  {
    head = nullptr;
    tail = nullptr;
  }
  else
  {
    head = head->get_next();
  }

  return temp;
}

// -----------------------------------------------------------------------------
// Exercise 8
// -----------------------------------------------------------------------------

PtrListNode::PtrListNode(Projectile *projectile)
{
  // IMPLEMENT YOUR CODE HERE
  element = projectile;
  next = nullptr;
}

Projectile *PtrListNode::get_projectile()
{
  // IMPLEMENT YOUR CODE HERE
  return element;
}

void PtrListNode::set_next(PtrListNode *next)
{
  // IMPLEMENT YOUR CODE HERE
  this->next = next;
}

PtrListNode *PtrListNode::get_next()
{
  // IMPLEMENT YOUR CODE HERE
  return next;
}

PtrList::PtrList()
{
  // IMPLEMENT YOUR CODE HERE
  head = nullptr;
  tail = nullptr;
}

PtrList::~PtrList()
{
  // IMPLEMENT YOUR CODE HERE
  // 销毁链表
  delete head;
  delete tail;
}

bool PtrList::is_empty()
{
  // IMPLEMENT YOUR CODE HERE
  if (head == nullptr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void PtrList::append(Projectile *projectile)
{
  // IMPLEMENT YOUR CODE HERE
  if (head == nullptr)
  {
    head = new PtrListNode(projectile);
    tail = head;
  }
  else
  {
    tail->set_next(new PtrListNode(projectile));
    tail = tail->get_next();
  }
}

Projectile *PtrList::remove_from_top()
{
  // IMPLEMENT YOUR CODE HERE
  Projectile *temp = head->get_projectile();
  if (head->get_next() == nullptr)
  {
    head = nullptr;
    tail = nullptr;
  }
  else
  {
    head = head->get_next();
  }

  return temp;
}

// -----------------------------------------------------------------------------
// DO NOT MODIFY THE FOLLOWING CODE
// -----------------------------------------------------------------------------

double Coordinate::get_distance(Coordinate other)
{
  return hypot(x - other.get_x(), y - other.get_y());
}

Projectile::Projectile(Coordinate position_other,
                       double magnitude,
                       double angle)
{
  double PI = 3.14159265;

  position = position_other;
  velocity_x = magnitude * cos(angle * PI / 180);
  velocity_y = magnitude * sin(angle * PI / 180);
}

Projectile::Projectile() : Projectile(Coordinate(), 1, 45)
{
}

Projectile::~Projectile(){};

Coordinate Projectile::get_position()
{
  return position;
}

double Projectile::get_velocity_x()
{
  return velocity_x;
}

double Projectile::get_velocity_y()
{
  return velocity_y;
}

void Projectile::simulate_step(double time_interval)
{
  const double g = 9.8;

  position = Coordinate(position.get_x() + velocity_x * time_interval,
                        position.get_y() + velocity_y * time_interval +
                            0.5 * (-g) * time_interval * time_interval);
  velocity_y = velocity_y - g * time_interval;
}

bool Projectile::operator==(const Projectile &other)
{
  return (position.get_x() == other.position.get_x() &&
          position.get_y() == other.position.get_y() &&
          velocity_x == other.velocity_x &&
          velocity_y == other.velocity_y);
}

void simulate_full_trajectory(std::ostream &out, double simulation_interval,
                              Projectile *projectile_ptr)
{
  while (projectile_ptr->get_position().get_y() >= 0)
    projectile_ptr->simulate_step(simulation_interval);
}

#if EXERCISE_4 == 1
void simulate_full_trajectory(std::ostream &out, double simulation_interval,
                              DroppingProjectile &projectile)
{
  while (projectile.get_position().get_y() >= 0)
    projectile.simulate_step(simulation_interval);
}

#endif
