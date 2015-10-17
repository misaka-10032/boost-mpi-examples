/*
 * Adapted from
 * http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html
 *
 * Created by Misaka-10032 (longqic@andrew.cmu.edu) on 10/15/15.
 *
 * Another example of reduce.
 */

#include <boost/mpi.hpp>
#include <iostream>
#include <string>
#include <functional>
#include <boost/serialization/string.hpp>
namespace mpi = boost::mpi;

namespace boost { namespace mpi {

    template<>
    struct is_commutative<std::plus<std::string>, std::string>
       : mpl::true_ { };

  } } // end namespace boost::mpi

int main()
{
  mpi::environment env;
  mpi::communicator world;

  std::string names[10] = { "zero ", "one ", "two ", "three ",
                            "four ", "five ", "six ", "seven ",
                            "eight ", "nine " };

  std::string result;
  reduce(world,
         world.rank() < 10? names[world.rank()]
                          : std::string("many "),
         result, std::plus<std::string>(), 0);

  if (world.rank() == 0)
    std::cout << "The result is " << result << std::endl;

  return 0;
}
