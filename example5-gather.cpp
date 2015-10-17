/*
 * Adapted from
 * http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html
 *
 * Created by Misaka-10032 (longqic@andrew.cmu.edu) on 10/15/15.
 *
 * Example of gather.
 */

#include <boost/mpi.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
namespace mpi = boost::mpi;

int main()
{
  mpi::environment env;
  mpi::communicator world;

  std::srand(time(0) + world.rank());
  int my_number = std::rand();
  if (world.rank() == 0) {
    std::vector<int> all_numbers;
    gather(world, my_number, all_numbers, 0);
    for (int proc = 0; proc < world.size(); ++proc)
      std::cout << "Process #" << proc << " thought of "
          << all_numbers[proc] << std::endl;
  } else {
    gather(world, my_number, 0);
  }

  return 0;
}