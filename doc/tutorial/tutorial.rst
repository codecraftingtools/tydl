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
constructed by creating a file named ``Simple.td`` containing:

.. code-block:: none
  :linenos:
  :caption: Simple.td
  
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
  in which the fields are listed determines the order they are stored in
  memory, unless a location is explicitly specified.

For those that prefer a more C-like syntax, the following alternative
declaration is equivalent to the one above:

.. code-block:: none
  :linenos:
  :caption: Simple.td (Alternate Syntax)

  import(all:, from: Tydl.Data);
   
  Simple: Record {fields: {a: UInt8; b: UInt8}};
  
Hopefully, the declarations are readable, and the meaning intuitive.  Those
who are curious can refer to the `Wumps <cc:wumps>` documentation to find
more detailed information on the low-level syntax that serves as a foundation
for the Tydl language.

Now that we have described our data structure using the Tydl syntax, we can
use the ``tydl`` command-line tool to generate a C++ *smart structure* class
that implements this type::

  tydl --generate=cpp_class --entity=Simple Simple.td

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
    uint8_t a = s1.a();

    cout << a << endl;
    return 0;
  }

Record with Nested Fields
=========================

For our second example, let us consider a slightly more complex data
structure: a `record`_ with nested fields.

.. table:: Nested Data Structure
   
   +--------+----------------------------+
   | Field  | Type                       |
   +========+============================+
   | s1     | ``Simple`` Data Structure  |
   +--------+----------------------------+
   | s2     | ``Simple`` Data Structure  |
   +--------+----------------------------+

This record contains two instances of the ``Simple`` data structure described
in the previous section.  When stored in `byte-addressable`_ memory
(e.g. RAM), the data structure is layed out like this:

.. table:: Memory Layout of Nested Data Structure

   +-------------+-----------------------+
   | Byte Offset | Content               |
   +=============+=======================+
   | 0           | ``a`` Field of ``s1`` |
   +-------------+-----------------------+
   | 1           | ``b`` Field of ``s1`` |
   +-------------+-----------------------+
   | 2           | ``a`` Field of ``s2`` |
   +-------------+-----------------------+
   | 3           | ``b`` Field of ``s2`` |
   +-------------+-----------------------+

A Tydl declaration for this data structure might look like this:

.. code-block:: none
  :linenos:
  :caption: Nested.td
  
  import all: from: Tydl.Data

  Nested: Record
    fields:
      s1: Simple
      s2: Simple

This declaration assumes that the Tydl definition of the ``Simple`` data
structure from the previous section is also available.

The API for accessing nested fields of an auto-generated C++ *smart
structure* class is illustrated in the following C++ program:

.. code-block:: c++
  :linenos:
  :caption: nested_test.cpp
            
  #include <generated/Nested.hpp>
  #include <iostream>

  int main()
  {
    using namespace std;

    Nested n;
    Simple s;
    
    // chained setters
    n.s1.a(1)
        .b(2);
    s.a(3)
     .b(4);
    
    // assignment operators
    n.s2.a = 5;
    n.s2.b = n.s1.b;
    n.s1 = s;
  
    // getter
    uint8_t a = n.s1.a();
    s = n.s2();
    
    cout << a << endl;
    return 0;
  }

Record with Multi-Byte Fields
=============================

For our next example, let us consider another simple data structure: a
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
the ``scalar_storage_order`` ``Record`` attribute, as shown below:

.. code-block:: none
  :linenos:
  :caption: Simple2.td
  :emphasize-lines: 4
  
  import all: from: Tydl.Data

  Simple2: Record
    scalar_storage_order: most_significant_first
    fields:
      a: UInt16
      b: UInt16

If the ``scalar_storage_order`` attribute is not specified, then the
machine's native byte order will be used for efficiency.  The name of this
attribute (the `scalar`_ part, in particular) was chosen for consistency with
the equivalent `Ada Scalar Storage Order`_ and `GCC scalar_storage_order type
attribute`_ constructs.

Record with Floating-Point Fields
=================================

In this example, let us consider yet another simple data structure: a
`record`_ with two 32-bit floating-point fields, stored in little-`endian`_
format.

.. table:: Coordinates Data Structure
   
   +--------+---------------------------------------------+
   | Field  | Type                                        |
   +========+=============================================+
   | x      | `IEEE 754 Single-Precision Floating-Point`_ |
   +--------+---------------------------------------------+
   | y      | `IEEE 754 Single-Precision Floating-Point`_ |
   +--------+---------------------------------------------+

The details of the `IEEE 754 Single-Precision Floating-Point`_ format can be
found in the Wikipedia article:

.. image:: ../images/ieee_754_single_float.*
   :width: 100%

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
  :caption: Coordinates.td
  
  import all: from: Tydl.Data

  Coordinates: Record
    scalar_storage_order: least_significant_first
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

.. _Ada Scalar Storage Order:
    https://gcc.gnu.org/onlinedocs/gcc-4.8.5/gnat_rm/Scalar_005fStorage_005fOrder.html

.. _scalar:
    https://en.cppreference.com/w/cpp/types/is_scalar

.. _GCC scalar_storage_order type attribute:
    https://gcc.gnu.org/onlinedocs/gcc/Common-Type-Attributes.html

.. _IEEE 754 Single-Precision Floating-Point:
    https://en.wikipedia.org/wiki/Single-precision_floating-point_format
