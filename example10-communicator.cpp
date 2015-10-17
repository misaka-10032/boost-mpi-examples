/*
 * Adapted from
 * http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html
 *
 * Created by Misaka-10032 (longqic@andrew.cmu.edu) on 10/15/15.
 *
 * Example of communicator.
 */

#include <boost/mpi.hpp>
#include <iostream>
#include <cstdlib>
#include <boost/serialization/vector.hpp>
namespace mpi = boost::mpi;

enum message_tags {msg_data_packet, msg_broadcast_data, msg_finished};

void generate_data(mpi::communicator local, mpi::communicator world) {
}

void collect_data(mpi::communicator local, mpi::communicator world) {
}

int main()
{
  mpi::environment env;
  mpi::communicator world;

  bool is_generator = world.rank() < 2 * world.size() / 3;
  mpi::communicator local = world.split(is_generator? 0 : 1);
  if (is_generator) generate_data(local, world);
  else collect_data(local, world);

  return 0;
}
