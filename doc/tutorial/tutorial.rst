.. Copyright 2021 Jeffrey A. Webb
   Copyright 2021 NTA, Inc.

========
Tutorial
========

Simple Record
=============

For our first example, let us consider a very simple data structure: a
`record`_ with two one-`byte`_ fields.

.. table:: Simple Data Structure
   
   +--------+------------------------+
   | Field  | Type                   |
   +========+========================+
   | a      | 8-Bit Unsigned Integer |
   +--------+------------------------+
   | b      | 8-Bit Unsigned Integer |
   +--------+------------------------+

When stored in `byte-addressable`_ memory (e.g. RAM), the data structure
is layed out like this:

.. table:: Memory Layout of Simple Data Structure

   +-------------+---------+
   | Byte Offset | Content |
   +=============+=========+
   | 0           | ``a``   |
   +-------------+---------+
   | 1           | ``b``   |
   +-------------+---------+

A straight-forward Tydl declaration for this data structure can be
constructed by creating a file named ``Simple.tyd`` containing:

.. code-block:: none
  :linenos:
  :caption: Simple.tyd
  
  import all: from: Tydl.Data

  Simple: Record
    fields:
      a: UInt8
      b: UInt8

Without diving into every detail of the Tydl syntax, here is a brief
explanation of this declaration:

Line 1
  Import all declarations from the nested ``Tydl.Data`` namespace into file
  scope.  The relevant declarations for this example are the ``Record``
  and ``UInt8`` data types.
  
Line 3
  Declare a new Tydl data ``Record`` named ``Simple``.

Lines 4-6
  The ``fields`` attribute of a data ``Record`` contains a list of key, value
  pairs that specify the name and data type of each record member.  The order
  the fields are listed in determines the order they are stored in memory,
  unless a location is explicitly specified.

For those that prefer a more C-like syntax, the following alternative
declaration is equivalent to the one above:

.. code-block:: none
  :linenos:
  :caption: Simple.tyd (Alternate Syntax)

  import(all:, from: Tydl.Data);
   
  Simple: Record {fields: {a: UInt8; b: UInt8}};
  
Hopefully, the declarations are readable, and the meaning intuitive.  Those
who are curious can refer to the `Wumps <cc:wumps>` documentation to find
more detailed information on the low-level syntax that serves as a foundation
for the Tydl language.

Now that we have described our data structure using the Tydl syntax, we can
use the ``tydl`` command-line tool to generate a C++ *smart structure* class
that implements this type::

  tydl --generate=cpp_class --entity=Simple Simple.tyd

This results in the following directory tree being created::

  └── generated
      └── Simple.hpp

A C++ program that utilizes the auto-generated *smart structure* class for
this ``Simple`` record might look like this:

.. code-block:: c++
  :linenos:
  :caption: simple_test.cpp
            
  #include <generated/Simple.hpp>
  #include <iostream>

  int main()
  {
    using namespace std;

    Simple s1, s2;

    // chained setters
    s1.a(1)
      .b(2);

    // assignment operators
    s2.a = 10;
    s2.b = s1.b;
    
    // getter
    cout << s1.a() << endl;

    return 0;
  }

Record with Multi-Byte Fields
=============================

For our second example, let us consider another simple data structure: a
`record`_ with two multi-byte fields.

.. table:: Simple2 Data Structure
   
   +--------+----------------------------+
   | Field  | Type                       |
   +========+============================+
   | a      | `16-Bit Unsigned Integer`_ |
   +--------+----------------------------+
   | b      | `16-Bit Unsigned Integer`_ |
   +--------+----------------------------+

When stored in `byte-addressable`_ memory (e.g. RAM) on a little-`endian`_
machine, the data structure is layed out like this:

.. table:: Memory Layout of Simple2 Data Structure (Little-Endian)

   +-------------+--------------------------------------------+
   | Byte Offset | Content                                    |
   +=============+============================================+
   | 0           | Least-Significant Byte of ``a`` (Bits 7-0) |
   +-------------+--------------------------------------------+
   | 1           | Most-Significant Byte of ``a`` (Bits 15-8) |
   +-------------+--------------------------------------------+
   | 2           | Least-Significant Byte of ``b`` (Bits 7-0) |
   +-------------+--------------------------------------------+
   | 3           | Most-Significant Byte of ``b`` (Bits 15-8) |
   +-------------+--------------------------------------------+

Note that when stored in `byte-addressable`_ memory (e.g. RAM) on a
big-`endian`_ machine, the same data structure is layed out in a slightly
different way:

.. table:: Memory Layout of Simple2 Data Structure (Big-Endian)

   +-------------+--------------------------------------------+
   | Byte Offset | Content                                    |
   +=============+============================================+
   | 0           | Most-Significant Byte of ``a`` (Bits 15-8) |
   +-------------+--------------------------------------------+
   | 1           | Least-Significant Byte of ``a`` (Bits 7-0) |
   +-------------+--------------------------------------------+
   | 2           | Most-Significant Byte of ``b`` (Bits 15-8) |
   +-------------+--------------------------------------------+
   | 3           | Least-Significant Byte of ``b`` (Bits 7-0) |
   +-------------+--------------------------------------------+

If we want to make sure that the data structure is stored or transmitted in a
consistent way, regardless of the machine architecture, we can make use of
the ``byte_order`` ``Record`` attribute, as shown below:

.. code-block:: none
  :linenos:
  :caption: Simple2.tyd
  :emphasize-lines: 4
  
  import all: from: Tydl.Data

  Simple2: Record
    byte_order: most_significant_first
    fields:
      a: UInt16
      b: UInt16

If the ``byte_order`` attribute is not specified, then the machine's native
byte order will be used for efficiency.

Record with Floating-Point Fields
=================================

In this example, let us consider a third simple data structure: a `record`_
with two 32-bit floating-point fields, stored in little-`endian`_ format.

.. table:: Coordinates Data Structure
   
   +--------+---------------------------------------------+
   | Field  | Type                                        |
   +========+=============================================+
   | x      | `IEEE 754 Single-Precision Floating-Point`_ |
   +--------+---------------------------------------------+
   | y      | `IEEE 754 Single-Precision Floating-Point`_ |
   +--------+---------------------------------------------+

When stored in `byte-addressable`_ memory (e.g. RAM) on a little-`endian`_
machine, the data structure is layed out like this:

.. table:: Memory Layout of Coordinates Data Structure (Little-Endian)

   +-------------+------------------------------------------------------+
   | Byte Offset | Content                                              |
   +=============+======================================================+
   | 0           | Least-Significant Byte of ``x``                      |
   |             | (Fraction Bits 7-0)                                  |
   +-------------+------------------------------------------------------+
   | 1           | 2nd Least-Significant Byte of ``x``                  |
   |             | (Fraction Bits 15-8)                                 |
   +-------------+------------------------------------------------------+
   | 2           | 2nd Most-Significant Byte of ``x``                   |
   |             | (Exponent Bit 0, Fraction Bits 22-16)                |
   +-------------+------------------------------------------------------+
   | 3           | Most-Significant Byte of ``x``                       |
   |             | (Sign Bit, Exponent Bits 7-1)                        |
   +-------------+------------------------------------------------------+
   | 4           | Least-Significant Byte of ``y``                      |
   |             | (Fraction Bits 7-0)                                  |
   +-------------+------------------------------------------------------+
   | 5           | 2nd Least-Significant Byte of ``y``                  |
   |             | (Fraction Bits 15-8)                                 |
   +-------------+------------------------------------------------------+
   | 6           | 2nd Most-Significant Byte of ``y``                   |
   |             | (Exponent Bit 0, Fraction Bits 22-16)                |
   +-------------+------------------------------------------------------+
   | 7           | Most-Significant Byte of ``y``                       |
   |             | (Sign Bit, Exponent Bits 7-1)                        |
   +-------------+------------------------------------------------------+

Once again, the Tydl declaration is straight-forward:

.. code-block:: none
  :linenos:
  :caption: Coordinates.tyd
  
  import all: from: Tydl.Data

  Coordinates: Record
    byte_order: least_significant_first
    fields:
      x: Float32
      y: Float32

.. _record:
    https://en.wikipedia.org/wiki/Record_(computer_science)

.. _byte:
    https://en.wikipedia.org/wiki/Integer_(computer_science)#Bytes_and_octets

.. _byte-addressable:
    https://en.wikipedia.org/wiki/Byte_addressing

.. _16-Bit Unsigned Integer:
    https://en.wikipedia.org/wiki/Integer_(computer_science)#Short_integer

.. _endian:
    https://en.wikipedia.org/wiki/Endianness

.. _IEEE 754 Single-Precision Floating-Point:
    https://en.wikipedia.org/wiki/Single-precision_floating-point_format
