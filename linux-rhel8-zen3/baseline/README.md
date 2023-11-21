# Spack Environment Template for the CADES Baseline cluster

This example is intended for use on the CADES Baseline cluster.

## Purpose

This guide meant as a brief example for a user to setup a Spack environment for application development using the OLCF 
provided files as a template.

The provided Spack environment files are intended to assist users in setup their development environment.
The base environment file includes the compilers and packages that are installed at the system level.

Traditionally, the user environment is modified by module files, so a user would add use ``module load openblas/0.3.23`` to 
load OpenBLAS version 0.3.23 into their environment.  Using a Spack environment, a user can add an OLCF provided package
and build against it using Spack without having to load the module file separately.

The information presented here is a subset of what can be found at [the Spack documentation site](https://spack.readthedocs.io/).

## Definition

Spack environment - A set of Spack specs for the purpose of building, rebuilding, and deploying in a coherent fashion.
External packages - An externally-installed package used by Spack, rather than building its own package.

## Getting Started

As an overview, the user will clone this repo and the Spack repo, start a new Spack instance, and create and activate
a new Spack environment.  Then use the environment to install the desired packages.

```
## From a Baseline login

> cd path/to/working/directory

> git clone https://github.com/spack/spack.git
> git checkout tags/v0.20.2 -b v0.20.2_branch  ## The current version of the Spack environment was tested against spack v0.20.2
> source spack/share/spack/setup-env.sh

> git clone https://github.com/olcf/spack-environments
> cp spack-environments/linux-rhel8-zen3/baseline/spack.yaml path/to/working/directory

## Modify the spack.yaml as needed.  Described below.

> spack env create my_env path/to/working/directory/spack.yaml
> spack env activate my_env

## Finally install the environment.  Described below.

> spack install
```

Now a user can add and install their dependencies with Spack and proceed with developing their application.

## Modifying the environment

### Adding Modules as Dependencies to the environment

The modules on Baseline can be used as dependencies, reducing build time.  As an example, the `openblas` package is
already installed on Baseline and is available as ``openblas/0.3.23``.  To use this as part of the environment add it to
the ``packages`` section of the ``spack.yaml`` file as shown below:

```
  packages:
    ...
    openblas:
      buildable: false
      version: [ 0.3.23 ]
      externals:
      - spec: openblas@0.3.23
        modules:
        - openblas/0.3.23-omp
```

This is included in the ``spack.yaml`` file, but has been commented out.  OpenMPI is also included as a commented out example as well.

### Adding User-Defined Dependencies to the environment

These can be added to the ``spack.yaml`` by adding to the ``specs`` list.  A dependency that is not already installed
will be built via Spack once the environment is concretized and installed.
Here the user can set specific variants and versions of packages as needed if spack defaults to one that is incompatible with
what is needed.

```
  specs:
  - openblas@0.3.23                                             ## example from above
  - my_apps_dependency1@version%compiler                        ## other explicitly defined specs
  - my_apps_dependency2 +variant1 ~variant 2 @version%compiler
```

## Installing the Environment

When in the Spack environment, any packages that are added to the environment file can be installed via:

```
> spack clean -ms      ## optional
> spack concretize -f
> spack install
```

If changes are made to the ``spack.yaml`` file, it is best to use the command ``spack concretize -f`` to force
Spack to fully concretize the environment.  Also, if a change is not reflected, ``spack clean -ms`` can be used
to clean the misc and source caches.  The flag ``-a`` can be used to clean all the Spack caches as well.

Alternatively, a user may install an individual package manually by:

```
> spack install --add my_app_dependencies@version %compiler@compilerversion
```

Here the ``--add`` flag will add the spec to the ``spack.yaml`` file.

## More Details

For more information regarding Spack and its usage, please see [the Spack documentation](https://spack.readthedocs.io/).

For an extensive tutorial concerning Spack, go to [the Spack 101 tutorial](https://spack-tutorial.readthedocs.io/en/latest/).

## References
* [Spack](https://spack.readthedocs.io/) - package management tool
* [Spack 101 tutorial](https://spack-tutorial.readthedocs.io/en/latest/) - Spack tutorial

