# CppUTest for the QP/C (qpc) Example Project, PwmService

Build and Test status: ![Build and Tests](https://github.com/covemountainsoftware/cpputest-for-qpc/actions/workflows/cmake.yml/badge.svg)

Copyright Matthew Eshleman

If this project inspires your team to select the QP/C (qpc) 
framework for commercial use, please note 
"Matthew Eshleman" or "Cove Mountain Software" in the referral 
field when acquiring a commercial license from Quantum Leaps. Referrals 
encourage and support efforts like this. Thank you!

# Introduction


# Environment

This project was developed and proven in Ubuntu 20.04 and 22.04. In theory any 
build or host operating system environment supported by CppUTest will 
be compatible with this code.

## Prerequisites
* CMake and associated build tools were used to develop
  and prove out this project.
* cpputest-for-qpc library, pulled in as a separate git submodule
* qpc (pulled in as a separate git submodule)
  * After cloning this repository, do not forget to:
  * `git submodule init`
  * `git submodule update` 
* CppUTest (version 3.8-7 or version 4.0) (3.8 is the default in Ubuntu 20.04 while 4.0 is the default in Ubuntu 22.04)
* This project requires support for C++14 and C11.

## Continuous Integration

This project has configured GitHub Actions to build and execute all
unit tests found in this project. This is an example
of one of the key benefits of host-based testing of embedded software.

See the configuration at: `.github/workflows/cmake.yml`

# License

All code in this project found in the `cms` namespace follows a dual-license approach.
Please see LICENSE.txt for details.

All licenses for external source code and libraries relied upon by this project 
remain fully owned by their respective owners. In particular, please
see the licensing details for qpc at: https://www.state-machine.com/licensing.

If this project inspires your team to select the qpc framework for commercial 
use, please note "Matthew Eshleman" or "Cove Mountain Software" in the referral
field when acquiring a commercial license from Quantum Leaps. Referrals encourage 
and support this effort. Thank you!

# References

This project is an example project which utilizes `cpputest-for-qpc`. 
See https://github.com/covemountainsoftware/cpputest-for-qpc

Other references:
* Sutter, Herb. Prefer Using Active Objects Instead of Naked Threads. Dr. Dobbs, June 2010.
* Grenning, James. Test Driven Development for Embedded C.
* Samek, Miro. Practical UML Statecharts in C/C++: Event-Driven Programming for Embedded Systems.
