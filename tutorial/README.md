# OCLF User Environment Workflow Example- NOT FOR USE - IN DEVELOPMENT

Spack Environment files to assist OLCF users in setup their development environment at the OLCF.

## Workflow example code

### Summit RHEL7 example:

#### Install dependencies

Create and activate the Summit RHEL7 base environment as shown in the root of this tutorial.

Execute the following command:

```
spack find
==> 0 installed packages
```

Your output may differ if you have already installed some packages.  In this example we will install BLAS++ using Spack, then build a test application using it.

To install BLAS++, execute the following:

```
spack install blaspp@2020.10.02 %gcc@4.8.5
```

This will install several dependencies that are provided by the OLCF base environment and should execute quickly.  To see the installed packages, do `spack find` again.

#### Build example application

Now that BLAS++ is installed, build the example application by executing the following:

```
mkdir build && cd build
cmake ..
make
```

You now have an application called `test1` in the `tutorial/build` directory.

To execute the application:

```
./test1
```

#### Simulate change to a dependency.

Here we will update the dependency manually so that we can simulate a bugfix or a new feature being added to BLAS++ that we wish to include in our example application.  To do this navigate to and edit the file `$SPACK_ROOT/var/spack/repos/builtin/packages/blaspp/package.py`.  Add the following at line 21:

```
20:    version('master', branch='master')
   #### LINE ADDED BELOW ####
21:    version('2020.10.03', sha256='36e45bb5a8793ba5d7bc7c34fc263f91f92b0946634682937041221a6bf1a150',
22:        url='https://bitbucket.org/icl/blaspp/downloads/blaspp-2020.10.02.tar.gz')
23:    version('2020.10.02', sha256='36e45bb5a8793ba5d7bc7c34fc263f91f92b0946634682937041221a6bf1a150')
```

This tells Spack that a new version of BLAS++ has been added to Spack, as you can see we have pointed it to previous version so nothing will change except for the version number.  Spack will prefer the newer version by default.  In a real workflow, your team would be notified that there is a new change via the BLAS++ team or via some other method.

#### Install new version of dependency

Similar to before, to install the new version of BLAS++ we do:

```
spack install blaspp@2020.10.03 %gcc@4.8.5
```

Executing `spack find` should show a new version of BLAS++ installed

```
> spack find
==> In environment my_env_cmake
==> Root specs
blaspp   blaspp 

-- no arch / gcc@4.8.5 ------------------------------------------
blaspp%gcc@4.8.5 

-- linux-rhel7-ppc64le / gcc@4.8.5 ------------------------------
blaspp@2020.10.02  blaspp@2020.10.03  cuda@10.1.243  netlib-lapack@3.8.0
```

#### Re-build example application

From within the `tutorial/build` directory still, we now delete our existing application and CMake files and rebuild:

```
rm -rf *           ### Careful to be in tutorial/build directory ###
cmake ..
make
```

Re-run the application by executing:

```
./test1
```
