# Boost MPI examples

_Note: I'm not going to maintain this._

This repo follows the tutorial of the [official site](http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html). The official site doesn't provide the deployable source, so I'm doing it here. Tell me if the official site has it now, so that I can refer people there.

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
