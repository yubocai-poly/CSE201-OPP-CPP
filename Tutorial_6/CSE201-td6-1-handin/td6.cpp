#include <iostream>
#include "math.h"

#include "common.hpp"
#include "td6.hpp"

// Exercise 1: define the functions Target::get_status and Target::set_status

void Target::toggle_status()
{
  // Exercise 1: implement the toggle_status function
  TargetStatus status = get_status();
  if (status == destroyable)
  {
    set_status(unbreakable);
  }
  else if (status == unbreakable)
  {
    set_status(hidden);
  }
  else if (status == hidden)
  {
    set_status(destroyable);
  }
}

#if EXERCISE_2 == 1
// Exercise 2: fix the implementation of halve_distance
Coordinate halve_distance(const Coordinate &c1, const Coordinate &c2)
{
  Coordinate c_const;
  c_const.set_x((c1.get_x() + c2.get_x()) / 2);
  c_const.set_y((c1.get_y() + c2.get_y()) / 2);

  return c_const;
}
#endif

// Exercise 4: reduce the number of Coordinate instances
int count_half_segments(const Coordinate &start, const Coordinate &end, double min_distance)
{
  // Exercise 3: count the half segments
  // we apply the formula here
  Coordinate m = halve_distance(start, end);
  if (m.get_distance(start) >= min_distance)
  {
    return 1 + count_half_segments(start, m, min_distance) + count_half_segments(m, end, min_distance);
  }
  else
  {
    return 0;
  }
}
