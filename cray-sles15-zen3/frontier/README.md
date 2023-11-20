# Frontier Spack Environment template usage

```
git clone --depth 1 -branch v0.20.2 https://github.com/spack/spack.git
cd spack
. ./share/spack/setup-env.sh
```

Clone the `spack.yaml` in this directory and activate the environment.
Uncomment lines 783 and 784, then change line 784 to the desired installation location.

Test environment with only one spec, `zlib%gcc@12.2.0`

```
[user@login02.frontier spack]$ spack install
==> Installing zlib-1.2.13-ed3qpa6ic45tc4bkrlt2ymc7ennqkkhv
==> No binary for zlib-1.2.13-ed3qpa6ic45tc4bkrlt2ymc7ennqkkhv found: installing from source
==> Using cached archive: /autofs/nccs-svm1_home1/user/frontier/projects/spack_env_template/spack/var/spack/cache/_source-cache/archive/b3/b3a24de97a8fdbc835b9833169501030b8977031bcb54b3b3ac13740f846ab30.tar.gz
==> No patches needed for zlib
==> zlib: Executing phase: 'edit'
==> zlib: Executing phase: 'build'
==> zlib: Executing phase: 'install'
==> zlib: Successfully installed zlib-1.2.13-ed3qpa6ic45tc4bkrlt2ymc7ennqkkhv
  Stage: 0.07s.  Edit: 0.78s.  Build: 0.60s.  Install: 0.25s.  Post-install: 0.63s.  Total: 2.58s
[+] /ccs/home/user/frontier/projects/spack_env_template/spack/opt/linux-sles15-zen3/gcc-12.2.0/zlib-1.2.13-ed3qpa6ic45tc4bkrlt2ymc7ennqkkhv
```

## Adding specs to the environment

### Get dependency list

To add `hdf5%gcc@12.2.0` to the environment, first check the concretization of the spec to find what external can be added:

```
[login02.frontier spack]$ spack spec -lINt hdf5%gcc@12.2.0
Input spec
--------------------------------
 -   [    ]  .hdf5%gcc@12.2.0

Concretized
--------------------------------
 -   um5brsy  [    ]  builtin.hdf5@1.14.1-2%gcc@12.2.0~cxx~fortran~hl~ipo~java~map+mpi+shared~szip~threadsafe+tools api=default build_system=cmake build_type=Release generator=make arch=linux-sles15-zen3
 -   6cjuu52  [b   ]      ^builtin.cmake@3.26.3%gcc@12.2.0~doc+ncurses+ownlibs~qt build_system=generic build_type=Release arch=linux-sles15-zen3
 -   zhzouiz  [bl  ]          ^builtin.ncurses@6.4%gcc@12.2.0~symlinks+termlib abi=none build_system=autotools arch=linux-sles15-zen3
 -   qmej4n6  [bl  ]          ^builtin.openssl@1.1.1-os%gcc@12.2.0~docs~shared build_system=generic certs=mozilla arch=linux-sles15-zen3
 -   ymrkh6a  [bl  ]      ^builtin.cray-mpich@8.1.23%gcc@12.2.0+wrappers build_system=generic arch=linux-sles15-zen3
 -   wh5zvat  [b   ]      ^builtin.gmake@4.4.1%gcc@12.2.0~guile build_system=autotools arch=linux-sles15-zen3
 -   yxf7edx  [b r ]      ^builtin.pkgconf@1.9.5%gcc@12.2.0 build_system=autotools arch=linux-sles15-zen3
[+]  ed3qpa6  [bl  ]      ^builtin.zlib@1.2.13%gcc@12.2.0+optimize+pic+shared build_system=makefile arch=linux-sles15-zen3
```

### Add external dependencies to the environment file

Here we need cmake, cray-mpich, gmake, pkgconf, and zlib.  zlib is already built from the initial install.  Looking at the `spack.yaml`, `cray-mpich` is available as a system package (marked `buildable: false` in the packages section.

Check for module for cmake:

```
[login02.frontier spack]$ module av cmake

----- /sw/frontier/spack-envs/base/modules/spack/linux-sles15-x86_64/Core ------
   cmake/3.21.2-dev    cmake/3.21.3    cmake/3.22.2    cmake/3.23.1    cmake/3.23.2 (D)

  Where:
   D:  Default Module

Use "module spider" to find all possible modules and extensions.
Use "module keyword key1 key2 ..." to search for all possible modules matching any of the "keys".
```

Add the default module to the spack.yaml (it has already been added for this example):

```
[login02.frontier spack]$ vi spack.yaml

  packages:
    ...
    #cmake/3.23.2
    cmake:
      version: [3.23.2]
      buildable: false
      externals:
      - spec: cmake@3.23.2
        modules:
        - cmake/3.23.2
    ...
```

Check for gmake module:

```
[login02.frontier spack]$ module av gmake

------/sw/frontier/spack-envs/base/modules/spack/linux-sles15-x86_64/Core -----
   gmake/4.3

Use "module spider" to find all possible modules and extensions.
Use "module keyword key1 key2 ..." to search for all possible modules matching any of the "keys".

```

Add this module to the `spack.yaml` (it has already been added for this example).

Check for `pkgconf` module:

```
[user@login02.frontier spack]$ module av pkgconf
No module(s) or extension(s) found!
Use "module spider" to find all possible modules and extensions.
Use "module keyword key1 key2 ..." to search for all possible modules matching any of the "keys".
```

There is no module for pkgconf, so let spack build this dependency.

### Add new spec to the environment file

Add `hdf5%gcc@12.2.0` to the spec list in the `spack.yaml` (for this example, uncomment line 6).

### Reconcretize

Now reconcretize the environment, forcing it to rerun the concretization for every spec using `-f`:

```
[login02.frontier spack]$spack concretize -f
==> Starting concretization
==> Environment concretized in 30.26 seconds.
==> Concretized zlib%gcc@12.2.0
[+]  ed3qpa6  zlib@1.2.13%gcc@12.2.0+optimize+pic+shared build_system=makefile arch=linux-sles15-zen3

==> Concretized hdf5%gcc@12.2.0
 -   ocoqvmv  hdf5@1.14.1-2%gcc@12.2.0~cxx~fortran~hl~ipo~java~map+mpi+shared~szip~threadsafe+tools api=default build_system=cmake build_type=Release generator=make arch=linux-sles15-zen3
 -   havxxen      ^cmake@3.23.2%gcc@12.2.0~doc+ncurses+ownlibs~qt build_system=generic build_type=Release arch=linux-sles15-zen3
 -   ymrkh6a      ^cray-mpich@8.1.23%gcc@12.2.0+wrappers build_system=generic arch=linux-sles15-zen3
 -   fn5thfy      ^gmake@4.3%gcc@12.2.0~guile build_system=autotools patches=599f134 arch=linux-sles15-zen3
 -   yxf7edx      ^pkgconf@1.9.5%gcc@12.2.0 build_system=autotools arch=linux-sles15-zen3
[+]  ed3qpa6      ^zlib@1.2.13%gcc@12.2.0+optimize+pic+shared build_system=makefile arch=linux-sles15-zen3
```

### Build Environment

To build and install the environment:
```
[login02.frontier spack]$spack install

==> cmake@3.23.2 : has external module in ['cmake/3.23.2']
[+] /sw/frontier/spack-envs/base/opt/linux-sles15-x86_64/gcc-7.5.0/cmake-3.23.2-4r4mpiba7cwdw2hlakh5i7tchi64s3qd (external cmake-3.23.2-havxxenwsjqyy6hfrom3odb46uww7lkd)
==> cray-mpich@8.1.23 : has external module in ['cray-mpich/8.1.23']
[+] /opt/cray/pe/mpich/8.1.23/ofi/gnu/9.1 (external cray-mpich-8.1.23-ymrkh6ags73rpllehq6osggzztejjk55)
==> gmake@4.3 : has external module in ['gmake/4.3']
[+] /sw/frontier/spack-envs/base/opt/linux-sles15-x86_64/gcc-7.5.0/gmake-4.3-32qt54ujpdxcat7ceg4vcjlmf2ze25j5 (external gmake-4.3-fn5thfyguubit5wh7byhh4lxazinszya)
==> Installing pkgconf-1.9.5-yxf7edx4vck3qbpkqlrpqigob4nhs2ta
==> No binary for pkgconf-1.9.5-yxf7edx4vck3qbpkqlrpqigob4nhs2ta found: installing from source
==> Fetching https://distfiles.dereferenced.org/pkgconf/pkgconf-1.9.5.tar.xz
==> No patches needed for pkgconf
==> pkgconf: Executing phase: 'autoreconf'
==> pkgconf: Executing phase: 'configure'
==> pkgconf: Executing phase: 'build'
==> pkgconf: Executing phase: 'install'
==> pkgconf: Successfully installed pkgconf-1.9.5-yxf7edx4vck3qbpkqlrpqigob4nhs2ta
  Stage: 1.46s.  Autoreconf: 0.00s.  Configure: 6.14s.  Build: 1.03s.  Install: 0.52s.  Post-install: 0.26s.  Total: 9.49s
[+] /ccs/home/user/frontier/projects/spack_env_template/spack/opt/linux-sles15-zen3/gcc-12.2.0/pkgconf-1.9.5-yxf7edx4vck3qbpkqlrpqigob4nhs2ta
[+] /ccs/home/user/frontier/projects/spack_env_template/spack/opt/linux-sles15-zen3/gcc-12.2.0/zlib-1.2.13-ed3qpa6ic45tc4bkrlt2ymc7ennqkkhv
==> Installing hdf5-1.14.1-2-ocoqvmvhyynwyiokrg5fyd4jes4b3ybc
==> No binary for hdf5-1.14.1-2-ocoqvmvhyynwyiokrg5fyd4jes4b3ybc found: installing from source
==> Fetching https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.14/hdf5-1.14.1/src/hdf5-1.14.1-2.tar.gz
==> Ran patch() for hdf5
==> hdf5: Executing phase: 'cmake'
==> hdf5: Executing phase: 'build'
==> hdf5: Executing phase: 'install'
==> hdf5: Successfully installed hdf5-1.14.1-2-ocoqvmvhyynwyiokrg5fyd4jes4b3ybc
  Stage: 46.00s.  Cmake: 33.67s.  Build: 21.29s.  Install: 7.82s.  Post-install: 2.65s.  Total: 1m 52.56s
[+] /ccs/home/user/frontier/projects/spack_env_template/spack/opt/linux-sles15-zen3/gcc-12.2.0/hdf5-1.14.1-2-ocoqvmvhyynwyiokrg5fyd4jes4b3ybc
```

As expected, cmake and gmake use the externally defined modules.  Pkgconf builds, then hdf5 builds.

## Summary of changes to spack environment file

```
spack:
  specs:
  - zlib%gcc@12.2.0
  - hdf5%gcc@12.2.0  ## this line was uncommented
## FIXME - add specs here!!!!
  packages:
    all:
      buildable: true
      compiler: [gcc@7.5.0, gcc]
      providers:
        blas: [openblas, cray-libsci]
        lapack: [openblas, cray-libsci]
        mpi: [cray-mpich]
        scalapack: [netlib-scalapack]
      target: [zen3]
      version: []
############# Externals added to build hdf5%gcc@12.2.0 as an example
    #cmake/3.23.2
    cmake:
      version: [3.23.2]
      buildable: false
      externals:
      - spec: cmake@3.23.2
        modules:
        - cmake/3.23.2
    #gmake/4.3
    gmake:
      version: [4.3]
      buildable: false
      externals:
      - spec: gmake@4.3
        modules:
        - gmake/4.3
#############
```
