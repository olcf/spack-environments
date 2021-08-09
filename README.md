OLCF Spack Environments Templages

[OLCF Documentaton for spack environments](https://docs.olcf.ornl.gov/software/spack_env/index.html)

## Purpose

This guide meant as an example for a user to setup a Spack environment for application development using the OLCF 
provided files as a template.

The provided Spack environment files are intended to assist OLCF users in setup their development environment at the 
OLCF.  The base environment file includes the compilers and packages that are installed at the system level.

Traditionally, the user environment is modified by module files, so a user would add use  ``module load cmake/3.18.2`` to 
load CMake version 3.18.2 into their environment.  Using a Spack environment, a user can add an OLCF provided package
and build against it using Spack without having to load the module file separately.

Spack documentation can be found [here](https://spack.readthedocs.io/).
