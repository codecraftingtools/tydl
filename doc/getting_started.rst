.. Copyright 2021 Jeffrey A. Webb
   Copyright 2021 NTA, Inc.

===============
Getting Started
===============

Installation Instructions
=========================

Make sure that `Git <cc:git-install>` is installed and then pull down the
Tydl `source code`_ from `GitHub <cc:github>` using these commands::

  mkdir -p ~/git
  cd ~/git
  git clone https://github.com/codecraftingtools/tydl.git

No further installation steps are required at this time.

Project Structure
=================

The project :github-repo:`Git repository <>` contains following directory
tree, with some files and subdirectories omitted for simplicity::
   
  ├── examples
  │   ├── ex1
  │   │   ├── build.sh
  │   │   ├── generated
  │   │   │   ├── Child.hpp
  │   │   │   └── Parent.hpp
  │   │   └── src
  │   │       ├── ex1.cpp
  │   │       └── ex1.td
  │   └── [...]
  └── include
      ├── tydl
      │   ├── Concrete.hpp
      │   ├── Field.hpp
      │   ├── Members.hpp
      │   ├── Record.hpp
      │   ├── Sizing.hpp
      │   ├── Sugar.hpp
      │   ├── functions.hpp
      │   ├── locators.hpp
      │   └── primitives.hpp
      └── tydl.hpp

The :repo:`include` directory contains shared Tydl C++ library header files
that are used to implement auto-generated C++ type classes.  The programming
interface for these files may change over time, so direct inclusion of these
headers from 3rd-party code is discouraged.

The :repo:`examples/ex1` directory demonstrates what an external project that
relies on Tydl might look like.  This example uses the Tydl syntax to define
data types (see :repo:`examples/ex1/src/ex1.td`) and then uses the resulting
Tydl-generated C++ data type classes in an example program
(i.e. :repo:`examples/ex1/src/ex1.cpp`).

The :repo:`examples/ex1/generated` directory contains code that would be
automatically generated from the type definitions if a code generation tool
was implemented.  This directory would be generated as part of the example
project's build process.

The :repo:`examples/ex1/build.sh` script contains the commands used to
build the example code.

Build Process
=============

The example code should compile and run under `Ubuntu<cc:ubuntu>`.
The only real prequisite for this is having a C++ compiler installed,
which can be accomplished using this command::

  sudo apt-get install build-essential

Once a C++ compiler is installed, the example code can be compiled and
executed like this::

  cd ~/git/tydl/examples/ex1
  ./build.sh
  ./ex1
  
.. _source code: https://github.com/codecraftingtools/tydl
