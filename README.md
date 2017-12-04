# Boost MPI examples
This repo follows the tutorial of the [official site](http://www.boost.org/doc/libs/1_59_0/doc/html/mpi/tutorial.html). The official site doesn't provide the deployable source; thus this is what I am doing here.

## Build (using foss toolchain)

```
mkdir build
cd build
cmake ..
make
```

## Build (using Intel toolchain)

For instance on a Slurm-based HPC system:

```
module load devel/Boost/1.65.1-intel-2017a
module load devel/CMake/3.9.4-intel-2017a

mkdir build.intel
cd build.intel
CXX=icpc cmake ../src
make -j $SLURM_NTASKS_PER_NODE
```

## Run

For example, to run `example1-setup` with 4 processes:

```
mpirun -np 4 example1-setup
```

On a Slurm-based cluster:

```
srun -n $SLURM_NTASKS ./example<>...
```