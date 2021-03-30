# OCLF User Environment Workflow Example- NOT FOR USE - IN DEVELOPMENT

Spack Environment files to assist OLCF users in setup their development environment at the OLCF.

## Workflow example code

### Summit RHEL7 example:

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

This will install several dependencies that are provided by the OLCF base environment and should execute quickly.  To see the installed packages, do `spack find` again.  You
