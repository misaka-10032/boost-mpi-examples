/*
 * Adapted from
 * http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html
 *
 * Created by Misaka-10032 (longqic@andrew.cmu.edu) on 10/15/15.
 *
 * Example of broadcast.
 */

#include <boost/mpi.hpp>
#include <iostream>
#include <string>
#include <boost/serialization/string.hpp>
namespace mpi = boost::mpi;

int main()
{
  mpi::environment env;
  mpi::communicator world;

  std::string value;
  if (world.rank() == 0) {
    value = "Hello, World!";
  }

  broadcast(world, value, 0);

  std::cout << "Process #" << world.rank() << " says " << value
      << std::endl;

  return 0;
}
