#include <iostream>
#include <algorithm>
#include "td7.hpp"

// Exercise 4 - Filter elements of a vector
std::vector<int> reverse_even(std::vector<int> input_vector)
{
  // Implement your code here
  std::vector<int> output_vector;
  for (int i = 0; i < input_vector.size(); i++)
  {
    if (input_vector[i] % 2 == 0)
    {
      output_vector.push_back(input_vector[i]);
    }
  }
  // return in the reverse order
  return std::vector<int>(output_vector.rbegin(), output_vector.rend());
}

// Exercise 5 - Build a vector of coordinates
std::vector<Coordinate> same_coordinates(std::vector<double> list_of_x,
                                         std::vector<double> list_of_y)
{
  // Implement your code here
  std::vector<Coordinate> output_vector;
  for (int i = 0; i < list_of_x.size(); i++)
  {
    for (int j = 0; j < list_of_y.size(); j++)
    {
      if (list_of_x[i] == list_of_y[j])
      {
        output_vector.push_back(Coordinate(list_of_x[i], list_of_y[j]));
      }
    }
  }
  return output_vector;
}

// Exercise 6 - Using the algorithm libraries
std::vector<int> filter_max(std::vector<int> max_vector,
                            std::vector<int> other_vector)
{
  // Implement your code here
  std::vector<int> output_vector;
  std::sort(max_vector.begin(),max_vector.end());
    std::sort(other_vector.begin(),other_vector.end());
  for (auto i : other_vector)
  {
    std::vector<int>::iterator it = std::find(max_vector.begin(), max_vector.end(), i);
    if (it == max_vector.end())
    {
      output_vector.push_back(i);
    }
  }
  return output_vector;
}
