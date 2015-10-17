# Boost MPI examples
This repo follows the tutorial of the [official site](http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html). The official site doesn't provide the deployable source; thus this is what I am doing here.

## Build

```
mkdir build
cd build
cmake ..
make
```

## Run

For example, to run `example1-setup` with 4 processes:

```
mpirun -np 4 example1-setup
```