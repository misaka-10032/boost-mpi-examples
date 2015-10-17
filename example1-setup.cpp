/*
 * Adapted from
 * http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html
 *
 * Created by Misaka-10032 (longqic@andrew.cmu.edu) on 10/15/15.
 *
 * Example of boost-mpi setup.
 */

#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>

namespace mpi = boost::mpi;

int main()
{
  mpi::environment env;
  mpi::communicator world;
  std::cout << "I am process " << world.rank() << " of " << world.size()
      << "." << std::endl;
  return 0;
}