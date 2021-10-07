.. Copyright 2021 Jeffrey A. Webb
   Copyright 2021 NTA, Inc.

========
Tutorial
========

.. _Simple Data Structure:

Simple Record
=============

For our first example, let us consider a very simple data structure: a
`record`_ with two one-`byte`_ fields.

.. table:: Simple Data Structure
   
   +--------+----------------------------+
   | Field  | Type                       |
   +========+============================+
   | First  | `8-Bit Unsigned Integer`_  |
   +--------+----------------------------+
   | Second | `8-Bit Unsigned Integer`_  |
   +--------+----------------------------+

When stored in `byte-addressable`_ memory (e.g. RAM), the data structure
is layed out like this:

.. table:: Memory Layout of Simple Data Structure

   +-------------+------------+
   | Byte Offset | Content    |
   +=============+============+
   | 0           | ``First``  |
   +-------------+------------+
   | 1           | ``Second`` |
   +-------------+------------+

A straight-forward Tydl declaration for this data structure can be
constructed by creating a file named ``Simple.td`` containing:

.. code-block:: none
  :linenos:
  :caption: Simple.td
  
  import
    identifiers: all
    from:
      Tydl
      Tydl.Data

  Simple: Record
    fields:
      First: Field
        type: 'Unsigned Integer'
          bit_width: 8
      Second: Field
        type: 'Unsigned Integer'
          bit_width: 8

Although this is not the place for us to discuss every nuance of the Tydl
syntax, it would be helpful to spend some time stepping through this
declaration line-by-line.

Lines 1-5
  The first statement is an `import <import>` directive that brings all the
  identifiers declared in the ``Tydl`` and ``Tydl.Data`` namespaces into file
  scope.  The relevant identifiers for this example are ``Record``, ``Field``
  and ``Unsigned Integer``.  The syntax construct used to represent
  directives, referred to as a *call*, is also used to represent function
  calls, macro invocations, and data type specializations or extensions.  A
  *call* consists of an identifier followed by an indented list of key-value
  pairs, one per line, that represent the *arguments* passed to the
  directive, function, macro, etc.

  .. code-block:: none
    :linenos:
    
    import
      identifiers: all
      from:
        Tydl
        Tydl.Data

Line 1
  The presence of an identifier followed by a series of indented lines
  indicates that the entity corresponding to the identifier should be
  *called*.  In this case, the ``import`` identifier corresponds to a
  built-in directive, and *calling* it translates to executing the directive.

Line 2
  The indentation indicates that this line should be interpreted an argument
  to the `import <import>` directive.  It consists of a *key* (i.e. an
  identifier followed by a colon) representing the name of the argument being
  specified followed by the value for that argument.  In the context of the
  `import <import>` directive, the ``identifiers`` argument is used to
  indicate the identifiers that should be imported from the specified
  namespace.  This argument may be either a single identifier or a list of
  identifiers.  Passing in the identifier ``all`` (as is done here) is a
  special case that indicates everything declared in the specified namespaces
  should be imported.

Line 3
  The presence of a key (in this case ``from``) followed by a series of
  indented lines indicates that a list is being supplied as the argument
  value.  In general, the ``from`` argument may be either a single (possibly
  dotted) identifier, or a list of identifiers indicating the source
  namespaces that identifiers will be imported from.

Line 4-5
  List of namespaces that identifiers will be imported from.  The period
  (``.`` character) is referred to as the *member operator*, and in this case
  indicates that the ``Data`` namespace being referenced is nested under the
  parent ``Tydl`` namespace.
  
Lines 7-14
  This statement declares a new specialized data `Record <Record>` named
  ``Simple``.

  .. code-block:: none
    :linenos:
    :lineno-start: 7
   
    Simple: Record
      fields:
        First: Field
          type: 'Unsigned Integer'
            bit_width: 8
        Second: Field
          type: 'Unsigned Integer'
            bit_width: 8
          
Line 7
  The presence of a key-value pair at file scope indicates that the specified
  value (in this case, a specialized data `Record <Record>` entity) should be
  added to the namespace associated with this file (in this case, the root
  namespace) under the name specified by the key (in this case ``Simple``).
  The following indented lines indicate the *call* construct, which in the
  case of a data type like `Record <Record>`, indicates that the arguments
  are to be interpreted as *attributes* that specialize, constrain, or extend
  the data type in some way.  This is similar to specifying class `template`_
  arguments in C++.

Lines 8
  The `fields <fields>` attribute of a data `Record <Record>` is a list of
  key-value pairs that specify the names and properties of each member in the
  record.  The order in which the fields are listed determines the order they
  are stored in memory, unless a location is explicitly specified.

Lines 9, 12
  Each value in the list of key-value pairs is typically a `Field <Field>`
  entity.  The corresponding keys indicate the field names.  In this case,
  our data record has two fields, named ``First`` and ``Second``.

Lines 10, 13
  The ``type`` attribute of a `Field <Field>` specifies the data type of the
  field.  The use of single quotes are required to reference the names of a
  *complex identifiers* that have unusual characters (in this case, spaces)
  in the name.  Simple aliases (e.g. ``UInt``) for many entities are
  available for those who find this naming convention objectionable.

Lines 11, 14
  The ``bit_width`` attribute of an `Unsigned Integer <Unsigned Integer>`
  entity specifies the number of bits used to represent the associated value.

Now that we have discussed this example in detail, you will hopefully find
the rest of the declarations in this tutorial readable, and the meaning
intuitive, even though you may not understand all the details of the syntax
at this point.  Those who are curious can refer to the `Wumps <cc:wumps>`
documentation to find more detailed information on the low-level syntax that
serves as a foundation for the Tydl language.

It is also worth noting that although this tutorial favors the use of more
verbose, explicit formatting for clarity, there are alternative, more compact
ways of expressing things.  The following declaration, for example, is
equivalent to the one we just discussed above:

.. code-block:: none
  :linenos:
  :caption: Simple.td (Alternate Syntax)

  import all from: (Tydl, Tydl.Data)
   
  Simple: Record
    fields:
      First:  UInt 8
      Second: UInt 8
  
Now that we have described our data structure using the Tydl syntax, the next
step is to use the ``tydl`` command-line tool to generate a C++ *smart
structure* class that implements this type::

  tydl --generate=cpp_class --entity=Simple Simple.td

This results in the following directory tree being created::

  └── generated
      └── Simple.hpp

A C++ program that utilizes the auto-generated *smart structure* class for
this ``Simple`` record might look something like this:

.. code-block:: c++
  :linenos:
  :caption: simple_test.cpp
            
  #include <generated/Simple.hpp>
  #include <iostream>

  int main()
  {
    using namespace std;

    // instantiation
    Simple s1, s2;

    // functional setters
    s1.First(1)
    s1.Second(2)
    
    // chained setters
    s1.First(1)
      .Second(2);

    // explicit setters
    tydl::set(s1.First, 1);
    tydl::set(s1.Second, 2);

    // assignment operators
    s2.First = 10;
    s2.Second = s2.First;
    
    // functional getter
    uint8_t first = s1.First();

    // explicit getter
    uint8_t second = tydl::get(s1.Second);
       
    cout << first << " " << second << endl;
    
    return 0;
  }

Nested Fields
=============

For our second example, let us consider a slightly more complex data
structure: a `record`_ with nested fields.

.. table:: Nested Data Structure
   
   +--------+----------------------------+
   | Field  | Type                       |
   +========+============================+
   | S1     | `Simple Data Structure`_   |
   +--------+----------------------------+
   | S2     | `Simple Data Structure`_   |
   +--------+----------------------------+

This record contains two instances of the ``Simple`` data structure described
in the previous section.  When stored in `byte-addressable`_ memory, the data
structure is layed out like this:

.. table:: Memory Layout of Nested Data Structure

   +-------------+----------------------------+
   | Byte Offset | Content                    |
   +=============+============================+
   | 0           | ``First``  field of ``S1`` |
   +-------------+----------------------------+
   | 1           | ``Second`` field of ``S1`` |
   +-------------+----------------------------+
   | 2           | ``First``  field of ``S2`` |
   +-------------+----------------------------+
   | 3           | ``Second`` field of ``S2`` |
   +-------------+----------------------------+

A Tydl declaration for this data structure can be written as follows:

.. code-block:: none
  :linenos:
  :caption: Nested.td
  
  import
    identifiers: all
    from:
      Tydl
      Tydl.Data

  Nested: Record
    fields:
      S1: Field
        type: Simple
      S2: Field
        type: Simple

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
    n.S1.First(1)
        .Second(2);
    s.First(3)
     .Second(4);
    
    // assignment operators
    n.S2.First = 5;
    n.S2.Second = n.S1.Second;
    n.S1 = s;

    // functional getters
    uint8_t First = n.S1.First();
    s = n.S2();
    
    cout << First << endl;
    return 0;
  }

Multi-Byte Fields
=================

For our next example, let us consider another simple data structure: a
`record`_ with two multi-byte fields.

.. table:: Simple2 Data Structure
   
   +--------+----------------------------+
   | Field  | Type                       |
   +========+============================+
   | First  | `16-Bit Unsigned Integer`_ |
   +--------+----------------------------+
   | Second | `16-Bit Unsigned Integer`_ |
   +--------+----------------------------+

When stored in `byte-addressable`_ memory on a little-`endian`_ machine, the
data structure is layed out like this:

.. table:: Memory Layout of Simple2 Data Structure (Little-Endian)

   +-------------+-------------------------------------------------+
   | Byte Offset | Content                                         |
   +=============+=================================================+
   | 0           | Least-Significant Byte of ``First`` (Bits 7-0)  |
   +-------------+-------------------------------------------------+
   | 1           | Most-Significant Byte of ``First`` (Bits 15-8)  |
   +-------------+-------------------------------------------------+
   | 2           | Least-Significant Byte of ``Second`` (Bits 7-0) |
   +-------------+-------------------------------------------------+
   | 3           | Most-Significant Byte of ``Second`` (Bits 15-8) |
   +-------------+-------------------------------------------------+

Note that when stored in `byte-addressable`_ memory on a big-`endian`_
machine, the same data structure is layed out in a slightly different way:

.. table:: Memory Layout of Simple2 Data Structure (Big-Endian)

   +-------------+-------------------------------------------------+
   | Byte Offset | Content                                         |
   +=============+=================================================+
   | 0           | Most-Significant Byte of ``First`` (Bits 15-8)  |
   +-------------+-------------------------------------------------+
   | 1           | Least-Significant Byte of ``First`` (Bits 7-0)  |
   +-------------+-------------------------------------------------+
   | 2           | Most-Significant Byte of ``Second`` (Bits 15-8) |
   +-------------+-------------------------------------------------+
   | 3           | Least-Significant Byte of ``Second`` (Bits 7-0) |
   +-------------+-------------------------------------------------+

If we want to make sure that the data structure is stored or transmitted in a
consistent way, regardless of the machine architecture, we can make use of
the `scalar_storage_order <scalar_storage_order>` `Record <Record>`
attribute, as shown below:

.. code-block:: none
  :linenos:
  :caption: Simple2.td
  :emphasize-lines: 8
  
  import
    identifiers: all
    from:
      Tydl
      Tydl.Data

  Simple2: Record
    scalar_storage_order: most_significant_first
    fields:
      First: Field
        type: 'Unsigned Integer'
          bit_width: 16
      Second: Field
        type: 'Unsigned Integer'
          bit_width: 16
          
If the `scalar_storage_order <scalar_storage_order>` attribute is not
specified, then the machine's native byte order will be used for efficiency.

Floating-Point Fields
=====================

In this example, let us consider yet another simple data structure: a
`record`_ with two 32-bit floating-point fields, stored in little-`endian`_
format.

.. table:: Coordinates Data Structure
   
   +--------+---------------------------------------------+
   | Field  | Type                                        |
   +========+=============================================+
   | X      | `IEEE 754 Single-Precision Floating-Point`_ |
   +--------+---------------------------------------------+
   | Y      | `IEEE 754 Single-Precision Floating-Point`_ |
   +--------+---------------------------------------------+

The details of the `IEEE 754 Single-Precision Floating-Point`_ format can be
found in the Wikipedia article:

.. image:: ../images/ieee_754_single_float.*
   :width: 100%

When stored in `byte-addressable`_ memory on a little-`endian`_ machine, the
data structure is layed out like this:

.. table:: Memory Layout of Coordinates Data Structure (Little-Endian)

   +-------------+------------------------------------------------------+
   | Byte Offset | Content                                              |
   +=============+======================================================+
   | 0           | Least-Significant Byte of ``X``                      |
   |             | (Fraction Bits 7-0)                                  |
   +-------------+------------------------------------------------------+
   | 1           | 2nd Least-Significant Byte of ``X``                  |
   |             | (Fraction Bits 15-8)                                 |
   +-------------+------------------------------------------------------+
   | 2           | 2nd Most-Significant Byte of ``X``                   |
   |             | (Exponent Bit 0, Fraction Bits 22-16)                |
   +-------------+------------------------------------------------------+
   | 3           | Most-Significant Byte of ``X``                       |
   |             | (Sign Bit, Exponent Bits 7-1)                        |
   +-------------+------------------------------------------------------+
   | 4           | Least-Significant Byte of ``Y``                      |
   |             | (Fraction Bits 7-0)                                  |
   +-------------+------------------------------------------------------+
   | 5           | 2nd Least-Significant Byte of ``Y``                  |
   |             | (Fraction Bits 15-8)                                 |
   +-------------+------------------------------------------------------+
   | 6           | 2nd Most-Significant Byte of ``Y``                   |
   |             | (Exponent Bit 0, Fraction Bits 22-16)                |
   +-------------+------------------------------------------------------+
   | 7           | Most-Significant Byte of ``Y``                       |
   |             | (Sign Bit, Exponent Bits 7-1)                        |
   +-------------+------------------------------------------------------+

Once again, constructing a Tydl declaration with two `Floating Point Values
<Float>` is straight-forward:

.. code-block:: none
  :linenos:
  :caption: Coordinates.td
  
  import
    identifiers: all
    from:
      Tydl
      Tydl.Data

  Coordinates: Record
    scalar_storage_order: least_significant_first
    fields:
      X: Field
        type: 'Floating-Point Value'
          bit_width: 32
      Y: Field
        type: 'Floating-Point Value'
          bit_width: 32

.. _record:
    https://en.wikipedia.org/wiki/Record_(computer_science)

.. _byte:
    https://en.wikipedia.org/wiki/Integer_(computer_science)#Bytes_and_octets

.. _8-Bit Unsigned Integer:
    https://en.wikipedia.org/wiki/Integer_(computer_science)#Bytes_and_octets

.. _byte-addressable:
    https://en.wikipedia.org/wiki/Byte_addressing

.. _template:
    https://en.wikipedia.org/wiki/Template_%28C%2B%2B%29
    
.. _16-Bit Unsigned Integer:
    https://en.wikipedia.org/wiki/Integer_(computer_science)#Short_integer

.. _endian:
    https://en.wikipedia.org/wiki/Endianness

.. _IEEE 754 Single-Precision Floating-Point:
    https://en.wikipedia.org/wiki/Single-precision_floating-point_format
