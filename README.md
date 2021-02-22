# OCLF User Environment - NOT FOR USE - IN DEVELOPMENT

## This is non-working, untested placeholder example.

Spack Environment files to assist OLCF users in setup their development environment at the OLCF.

## Getting Started

Clone this repo and the Spack repo, start a new Spack instance,
and create and activate a new Spack environment:

```
git clone https://code.ornl.gov/2ff/olcf-user-environments.git
cd olcf-user-environments

git clone https://github.com/spack/spack.git
source spack/share/spack/setup-env.sh

spack env create my_env linux-rhel7-ppc64le/summit/spack.yaml
spack env activate my_env
```

Now a user can load and install their dependencies with Spack and proceed with developing their application.

## Add Dependencies

### Adding User-Defined Dependencies

These can be added to the `spack.yaml` by adding to the `spec` section.
```
  specs:
  - my_apps_dependency1@version%compiler
  - my_apps_dependency2@version%compiler
```

### Adding OLCF Pre-Installed Dependencies

These can be added via the `spack.yaml` file by adding to the `packages` section.

```
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

 or, once the environment is activated, manually by:

```
spack install <my_app_dependencies@version%compiler>
```

## More Details

Here there be more information about each step.

## Best Practices

Here there be best practices.


## References
* [Spack](https://spack.readthedocs.io/) - package management tool

## Authors
* **Matt Belhorn** - *Initial work* [OLCF Spack Environments](https://github.com/mpbelhorn/olcf-spack-environments)
* **Jamie Finney**
