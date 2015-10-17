/*
 * Adapted from
 * http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html
 *
 * Created by Misaka-10032 (longqic@andrew.cmu.edu) on 10/15/15.
 *
 * Example of user-defined data type.
 */

#include <boost/mpi.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/skeleton_and_content.hpp>
#include <boost/serialization/list.hpp>
#include <iostream>
#include <list>

namespace mpi = boost::mpi;

int main() {
  mpi::environment env;
  mpi::communicator world;
  const int list_len = 5;
  const int iterations = 3;

  if (world.rank() == 0) {
    // Generate the list and broadcast its structure
    std::list<int> l(list_len);
    broadcast(world, mpi::skeleton(l), 0);

    // Generate content several times and broadcast out that content
    mpi::content c = mpi::get_content(l);
    for (int i = 0; i < iterations; ++i) {
      // Generate new random values
      std::generate(l.begin(), l.end(), &random);

      // Broadcast the new content of l
      broadcast(world, c, 0);
    }

    // Notify the slaves that we're done by sending all zeroes
    std::fill(l.begin(), l.end(), 0);
    broadcast(world, c, 0);

  } else {

    // Receive the content and build up our own list
    std::list<int> l;
    broadcast(world, mpi::skeleton(l), 0);

    mpi::content c = mpi::get_content(l);
    int i = 0;
    do {
      broadcast(world, c, 0);

      // if all 0's is received, break the loop.
      if (std::find_if
             (l.begin(), l.end(),
              std::bind1st(std::not_equal_to<int>(), 0)) == l.end())
        break;

      // Compute some property of the data.
      for (std::list<int>::iterator it = l.begin(); it != l.end(); it++) {
        std::cout << *it << " ";
      }
      std::cout << std::endl;

      ++i;
    } while (true);

  }

  return 0;
}