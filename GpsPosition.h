/*
 * Adapted from
 * http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html
 *
 * Created by Misaka-10032 (longqic@andrew.cmu.edu) on 10/15/15.
 *
 * User-defined class for MPI.
 */

#ifndef BOOST_MPI_EXAMPLES_GPS_POSITION_H
#define BOOST_MPI_EXAMPLES_GPS_POSITION_H

#include <boost/mpi/datatype.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <string>

class GpsPosition
{
private:
  friend class boost::serialization::access;

  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & degrees;
    ar & minutes;
    ar & seconds;
    ar & desc;
    ar & extra;
  }

  int degrees;
  int minutes;
  float seconds;
  std::string desc;
  std::string extra;

public:
  GpsPosition(){};
  GpsPosition(int d,
              int m,
              float s,
              std::string desc
  ) :
     degrees(d),
     minutes(m),
     seconds(s),
     desc(desc)
  {}
  inline int getDegrees() { return degrees; }
  inline int getMinutes() { return minutes; }
  inline float getSeconds() { return seconds; }
  inline std::string getDesc() { return desc; }
  inline void putExtra(std::string extra) { this->extra = extra; }
  inline std::string getExtra() { return extra; }
};

/* Don't add this if there's string or list. */
//BOOST_IS_MPI_DATATYPE(GpsPosition)

/* Add this for optimization*/
BOOST_IS_BITWISE_SERIALIZABLE(GpsPosition)

#endif //BOOST_MPI_EXAMPLES_GPS_POSITION_H
