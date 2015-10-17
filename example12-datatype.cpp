/*
 * Adapted from
 * http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html
 *
 * Created by Misaka-10032 (longqic@andrew.cmu.edu) on 10/15/15.
 *
 * Example of non-blocking user-defined data type.
 */

#include <boost/mpi.hpp>
#include <iostream>
#include <string>
#include "GpsPosition.h"

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
    GpsPosition gpsPosition(1, 2, 3.3, "hello");
    gpsPosition.putExtra("extra");
    for (int i = 1; i < size; i++) {
      reqs[0] = world.isend(i, 0, gpsPosition);
    }
    std::string *ret_msgs = new std::string[size];
    for (int i = 1; i < size; i++) {
      reqs[i] = world.irecv(i, 1, ret_msgs[i]);
    }
    mpi::wait_all(reqs, reqs + size);
  } else {
    mpi::request reqs[2];
    std::string ret_msg = "success!";
    reqs[0] = world.isend(0, 1, ret_msg);
    GpsPosition gpsPosition;
    reqs[1] = world.irecv(0, 0, gpsPosition);
    mpi::wait_all(reqs, reqs + 2);
    std::cout << "This is slave" << world.rank() << std::endl;
    std::cout << gpsPosition.getDegrees() << std::endl;
    std::cout << gpsPosition.getMinutes() << std::endl;
    std::cout << gpsPosition.getSeconds() << std::endl;
    std::cout << gpsPosition.getDesc() << std::endl;
    std::cout << gpsPosition.getExtra() << std::endl;
    std::cout << "**********************" << std::endl;
  }

  return 0;
}