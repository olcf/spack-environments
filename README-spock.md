# OCLF User Environment - IN DEVELOPMENT

## This is untested placeholder.

This example is intended for use on Spock.

## Purpose

This guide meant as an example for a user to setup a Spack environment for application development using the OLCF 
provided files as a template.

The provided Spack environment files are intended to assist OLCF users in setup their development environment at the 
OLCF.  The base environment file includes the compilers and packages that are installed at the system level.

Traditionally, the user environment is modified by module files, so a user would add use  ``module load cmake/3.18.2`` to 
load CMake version 3.18.2 into their environment.  Using a Spack environment, a user can add an OLCF provided package
and build against it using Spack without having to load the module file separately.

The information presented here is a subset of what can be found at [the Spack documentation site](https://spack.readthedocs.io/).

## Definition

Spack environment - A set of Spack specs for the purpose of building, rebuilding and deploying in a coherent fashion.
External packages - An externally-installed package used by Spack, rather than building its own package.
Chained instance - A Spack instance that uses any packages installed 

## Getting Started

Clone this repo and the Spack repo, start a new Spack instance, and create and activate a new Spack environment:

```
## From a Spock login

> git clone https://code.ornl.gov/2ff/olcf-user-environments.git
> cd olcf-user-environments

> git clone https://github.com/spack/spack.git
> source spack/share/spack/setup-env.sh

> spack env create my_env spock/spack.yaml  ## does not exist currently
> spack env activate my_env
```

Now a user can add and install their dependencies with Spack and proceed with developing their application.

## Chained Spock Instances

The Spock Spack environment includes this configuration addition:

```
  upstreams:
    olcf:
      install_tree: /sw/spock/spack-envs/base/opt
```

This allows the user's newly created instance to use any package installed into the above directory as if it was
installed by the user.

## Add Dependencies to the environment

### Adding User-Defined Dependencies to the environment

These can be added to the `spack.yaml` by adding to the `spec` section.  A dependency that is not already installed
will be built via Spack once the environment is concretized and installed.

```
  specs:
  - cmake@3.18.2                            ## example from above
  - my_apps_dependency1@version%compiler    ## other explicitly defined specs
  - my_apps_dependency2@version%compiler
```

### Installing the Environment

When in the Spack environment, any packages that are added to the environment file can be installed via:

```
spack concretize -f
spack install
```

Alternatively, a user may install an individual package manually by:

```
spack install <my_app_dependencies@version%compiler>
```

## More Details

For more information regarding Spack and it's usage, please see [the Spack documentation](https://spack.readthedocs.io/).

For an extensive tutorial concerning Spack, go to [the Spack 101 tutorial](https://spack-tutorial.readthedocs.io/en/latest/).

For more information concerning chaining Spack instances, please see [here](https://spack.readthedocs.io/en/latest/chain.html#chaining-spack-installations).

## References
* [Spack](https://spack.readthedocs.io/) - package management tool
* [Spack 101 tutorial](https://spack-tutorial.readthedocs.io/en/latest/) - Spack tutorial

## Authors
* **Matt Belhorn** - *Initial work* [OLCF Spack Environments](https://github.com/mpbelhorn/olcf-spack-environments)
* **Jamie Finney**
