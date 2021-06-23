# OCLF User Environment - IN DEVELOPMENT

## This is somewhat tested placeholder example.

## Purpose

This guide meant as an example for a user to setup a Spock environment for application development using the OLCF 
provided files as a template.

The provided Spack environment files are intended to assist OLCF users in setup their development environment at the 
OLCF.  The base environment file includes the compilers and packages that are installed at the system level.  
Currently, the user environment is modified by module files, so a user would add use  ``module load cmake/3.18.2`` to 
load CMake version 3.18.2 into their environment.  Using a Spack environment, a user can add an OLCF provided package
and build against it using Spack without having to load the module file separately.

## Getting Started

Clone this repo and the Spack repo, start a new Spack instance, and create and activate a new Spack environment:

```
git clone https://code.ornl.gov/2ff/olcf-user-environments.git
cd olcf-user-environments

git clone https://github.com/spack/spack.git
source spack/share/spack/setup-env.sh

spack env create my_env linux-rhel7-ppc64le/summit/spack.yaml
spack env activate my_env
```

Now a user can add and install their dependencies with Spack and proceed with developing their application.

## Add Dependencies to the environment

### Adding User-Defined Dependencies to the environment

These can be added to the `spack.yaml` by adding to the `spec` section.  A dependency that is not already installed
will be built via Spack once the environment is concretized and installed.

```
  specs:
  - my_apps_dependency1@version%compiler
  - my_apps_dependency2@version%compiler
```

### Adding OLCF Pre-Installed Dependencies

These can be added via the `spack.yaml` file by adding to the `packages` section.  This information was found on
Summit by finding a modulefile for the installed CMake package.  Use `module avail cmake` to find what is installed.

By marking the CMake package as `buildable: false` it will force Spack to use the externally installed CMake with the 
listed modulefile.

```
  specs:
  - cmake@3.18.2
  
  packages:
    # EXAMPLE
    cmake:
      version: [3.18.2]
      buildable: false
      externals:
      - spec: cmake@3.18.2
        modules:
        - cmake/3.18.2
```

### Installing Dependencies

When in the Spack environment, any packages that are added to the environment file can be installed onto the system via:

```
spack concretize -f
spack install
```

Alternatively, a user may install a package manually by:

```
spack install <my_app_dependencies@version%compiler>
```

## More Details

For more information regarding Spack and it's usage, please see [the Spack documentation](https://spack.readthedocs.io/).

For an extensive tutorial concerning Spack, go to [the Spack 101 tutorial](https://spack-tutorial.readthedocs.io/en/latest/).

For more information concerning adding external packages, please see [here](https://spack.readthedocs.io/en/latest/build_settings.html#external-packages).

## Best Practices

Here there be best practices.


## References
* [Spack](https://spack.readthedocs.io/) - package management tool
* [Spack 101 tutorial](https://spack-tutorial.readthedocs.io/en/latest/) - Spack tutorial

## Authors
* **Matt Belhorn** - *Initial work* [OLCF Spack Environments](https://github.com/mpbelhorn/olcf-spack-environments)
* **Jamie Finney**
