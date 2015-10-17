/*
 * Adapted from
 * http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html
 *
 * Created by Misaka-10032 (longqic@andrew.cmu.edu) on 10/15/15.
 *
 * Example of reduce.
 */

#include <boost/mpi.hpp>
#include <iostream>
#include <cstdlib>
namespace mpi = boost::mpi;

int main()
{
  mpi::environment env;
  mpi::communicator world;

  std::srand(time(0) + world.rank());
  int my_number = std::rand();

  if (world.rank() == 0) {
    int minimum;
    reduce(world, my_number, minimum, mpi::minimum<int>(), 0);
    std::cout << "The minimum value is " << minimum << std::endl;
  } else {
    reduce(world, my_number, mpi::minimum<int>(), 0);
  }

  return 0;
}
