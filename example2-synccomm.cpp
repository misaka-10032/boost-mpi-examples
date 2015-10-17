/*
 * Adapted from
 * http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html
 *
 * Created by Misaka-10032 (longqic@andrew.cmu.edu) on 10/15/15.
 *
 * Example of block communication.
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

  int size = world.size();
  if (size <= 1) {
    std::cout << "Need more than 1 processes to play around."
        << std::endl;
    return -1;
  }

  if (world.rank() == 0) {
    for (int i = 1; i < size; i++) {
      world.send(i, 0, std::string("Hello"));
    }
    std::string msg;
    for (int i = 1; i < size; i++) {
      world.recv(i, 1, msg);
    }
    std::cout << msg << "!" << std::endl;
  } else {
    std::string msg;
    world.recv(0, 0, msg);
    std::cout << msg << ", ";
    std::cout.flush();
    world.send(0, 1, std::string("world"));
  }

  return 0;
}