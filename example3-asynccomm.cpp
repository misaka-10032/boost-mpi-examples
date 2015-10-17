/*
 * Adapted from
 * http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html
 *
 * Created by Misaka-10032 (longqic@andrew.cmu.edu) on 10/15/15.
 *
 * Example of non-blocking msg passing.
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
    mpi::request *reqs = new mpi::request[size];
    std::string msg, out_msg = "Hello";
    for (int i = 1; i < size; i++) {
      reqs[0] = world.isend(i, 0, out_msg);
    }
    for (int i = 1; i < size; i++) {
      reqs[i] = world.irecv(i, 1, msg);
    }
    mpi::wait_all(reqs, reqs + size);
    std::cout << msg << "!" << std::endl;
  } else {
    mpi::request reqs[2];
    std::string msg, out_msg = "world";
    reqs[0] = world.isend(0, 1, out_msg);
    reqs[1] = world.irecv(0, 0, msg);
    mpi::wait_all(reqs, reqs + 2);
    std::cout << msg << ", ";
  }

  return 0;
}