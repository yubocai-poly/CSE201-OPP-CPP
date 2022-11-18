#ifndef TD6_HPP
#define TD6_HPP

// Enable the automatic grader for each exercises
#define EXERCISE_1 1
#define EXERCISE_2 1
#define EXERCISE_3 1
#define EXERCISE_4 1
#define EXERCISE_5 1
#define EXERCISE_6 1
#define EXERCISE_7 1

#include <iostream>
#include "common.hpp"

// Exercise 1: declare the TargetStatus enum here
enum TargetStatus
{
  destroyable,
  unbreakable,
  hidden,
};
// End of TargetStatus declaration

class Target
{
public:
  Target(Coordinate position_other, double radius) : position(position_other), radius(radius) {}
  Target() : Target(Coordinate(0, 0), 1.0) {}

  Coordinate get_position() const;
  double get_radius() const;

  bool operator==(const Target &other);
  bool operator!=(const Target &other);

  // Exercise 1: declare the get_status and set_status functions here
  TargetStatus get_status()
  {
    return status;
  }

  void set_status(TargetStatus status)
  {
    this->status = status;
  }

  // End of get_status and set_status

  void simulate_step(double simulation_interval);

  virtual void toggle_status();

  friend std::ostream &operator<<(std::ostream &os, const Target &c);

private:
  Coordinate position;
  double radius;

  // Exercise 1: declare a variable to hold the status here
  TargetStatus status;
};

Coordinate halve_distance(const Coordinate &c1, const Coordinate &c2); // Do not modify

// Exercise 4: reduce the number of Coordinate instances (modify the function's signature)
int count_half_segments(const Coordinate &start, const Coordinate &end, double min_distance);

// Exercise 5: Implement a generic function to compute the distance
// Here we use a template function here
template <typename D1, typename D2>
double get_distance(D1 d1, D2 d2)
{
  Coordinate c1 = d1.get_position();
  Coordinate c2 = d2.get_position();
  return c1.get_distance(c2);
}

// Declaration of the target list (the projectile list is in common.hpp)
class TargetListNode
{
public:
  TargetListNode(Target projectile);

  Target get_projectile();
  void set_next(TargetListNode *next);
  void set_prev(TargetListNode *prev);
  TargetListNode *get_next();
  TargetListNode *get_prev();

private:
  Target element;
  TargetListNode *next, *prev;
};

class TargetList
{
public:
  TargetList();
  ~TargetList();

  bool is_empty();
  void append(Target projectile);
  Target remove_from_head();
  Target remove_from_tail();

private:
  TargetListNode *head, *tail;
};
// End of list declaration

// Function templates for list operations
template <typename ListType>
void init_list(ListType *&list)
{
  list = new ListType();
}

template <typename ListType, typename ElementType>
void append(ListType *list,
            ElementType element)
{
  list->append(element);
}

// Exercise 6: define here the templates for is_list_empty, remove_from_head, and remove_from_tail
template <typename bool_l>
bool is_list_empty(bool_l *list)
{
  return list->is_empty();
}

template <typename ListType, typename ElementType>
void remove_from_head(ListType *list, ElementType &element)
{
  element = list->remove_from_head();
}

template <typename ListType, typename ElementType>
void remove_from_tail(ListType *list, ElementType &element)
{
  element = list->remove_from_tail();
}

// End of exercise 6

#if EXERCISE_7 == 1
template <typename ListType, typename ElementType>
void move(ListType *source, ListType *&destination, ElementType to_exclude)
{
  // Exercise 7: Implement the move function
  ElementType element;
  init_list(destination);
  while (!is_list_empty(source))
  {
    remove_from_head(source, element);
    if (element != to_exclude)
    {
      append(destination, element);
    }
  }
}
#endif

#endif // TD6_HPP
