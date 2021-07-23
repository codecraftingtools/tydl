.. Copyright 2021 NTA, Inc.

.. _data reference:

==========
Data Types
==========

This section documents the data type entities provided by Tydl and describes
the attributes that are applicable to each specific entity.  These entities
are defined in the ``Tydl.Data`` namespace.

.. _Type:

Type
====

Base entity for all Tydl data types, including composite (e.g. `Arrays
<Array>` and `Records <Record>`) and primitive types.  The following
attributes are supported:

abbreviations
  List of text substitutions definitions (e.g. `macros <macro>`, `short
  <short>`) that can be used in the definitions of other attributes in this
  entity.  This list attribute is considered *extensible* by derived classes.
  
bit_numbering
  Indicates the `bit numbering`_ convention adopted by this data type.  Valid
  values for this attribute are ``lsb_0`` and ``msb_0``.  Currently, this
  attribute is only used for documentation purposes, and may not really be
  necessary.

bit_transmission_order
  Indicates the order that the individual bits of a byte are transmitted.
  Valid values for this attribute are ``least_significant_first`` and
  ``most_significant_first``.  This attribute only makes sense for serial
  data streams.  Currently, this attribute is only used for documentation
  purposes, and may not really be necessary.

.. _bit_width:

bit_width
  An unsigned integer indicating the number of bits used to represent (store)
  the value.

default
  The default value to use when initializing instances of this data type.

layout
  Specifies the low-level bit/byte layout to be used when storing an instance
  of this data type in `byte-addressable`_ memory.  This is either a `Layout
  <Layout>` instance or a list of keyword arguments that are to be
  interpreted as Layout attributes.

max_value
  Specifies the maximum possible value that can be taken on by an instance of
  this data type.  Note that this does not make sense for some data types.
  
min_value
  Specifies the minimum possible value that can be taken on by an instance of
  this data type.  Note that this does not make sense for some data types.
  
range
  Specifies the range of possible values (i.e. ``min_value`` and
  ``max_value``) for instances of this data type.  Note that this does not
  make sense for some data types.

.. _scalar_storage_order:

scalar_storage_order
  Specifies the storage order (`endianness`_) for `scalar`_ (e.g. integer and
  floating-point) types.  Valid values for this attribute are
  ``least_significant_first``, ``most_significant_first``, ``parent``, and
  ``native``.  The default value is ``parent``, which means that this
  attribute is inherited from the parent entity (e.g. `Record <Record>` or
  `Array <Array>`), if applicable.  For top-level entities, a value of
  ``parent`` is equivalent to ``native``, which means that the machine's
  native byte order should be used for efficiency.  Specifying a ``native``
  ``scalar_storage_order`` implies that the storage order is not important
  and may not be portable between different computing architectures.  The
  name of this attribute (the `scalar`_ part, in particular) was chosen for
  consistency with the equivalent `Ada Scalar Storage Order`_ and `GCC
  scalar_storage_order type attribute`_ constructs.

  As an example, consider a 16-bit integer value with the following bits (LSB
  0 `bit numbering`_) :
  
  .. commented table

     +-----+------------------------------------------------------------+-----+
     | MSb |                                                            | LSb |
     +-----+----+----+----+----+----+---+---+---+---+---+---+---+---+---+-----+
     | 15  | 14 | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0   |
     +-----+----+----+----+----+----+---+---+---+---+---+---+---+---+---+-----+
     | Most-Significant Byte                | Least-Significant Byte          |
     +--------------------------------------+---------------------------------+
     
  .. image:: images/uint16.*
     :width: 100%

  If a ``scalar_storage_order`` of ``least_significant_first`` is specified,
  this 16-bit value would be stored in `byte-addressable`_ memory (e.g. RAM)
  as shown below:
  
  .. table:: Little-Endian Layout

     +-------------+------------------------------------------------------+
     | Byte Offset | Content                                              |
     +=============+======================================================+
     | 0           | Least-Significant Byte (Bits 7-0)                    |
     +-------------+------------------------------------------------------+
     | 1           | Most-Significant Byte (Bits 15-8)                    |
     +-------------+------------------------------------------------------+

  If a ``scalar_storage_order`` of ``most_significant_first`` is specified,
  this 16-bit value would be stored in `byte-addressable`_ memory as follows:
  
  .. table:: Big-Endian Layout

     +-------------+------------------------------------------------------+
     | Byte Offset | Content                                              |
     +=============+======================================================+
     | 0           | Most-Significant Byte (Bits 15-8)                    |
     +-------------+------------------------------------------------------+
     | 1           | Least-Significant Byte (Bits 7-0)                    |
     +-------------+------------------------------------------------------+

  The ``scalar_storage_order`` attribute also affects how `bit fields`_ are
  packed into bytes. As an example, consider the following record of bit
  fields:

  .. code-block:: none
                  
    Example: Record
      fields:
        first: UInt5
        second: UInt5
        third: UInt6

  If a ``scalar_storage_order`` of ``least_significant_first`` is specified,
  the fields of this record would be stored in `byte-addressable`_ memory
  as shown below:
  
  .. table:: Little-Endian Bit Field Layout (LSB 0)
             
     +-------------+-------+------------------------------------+--------+
     | Byte Offset | MSb   |                                    | LSb    |
     |             +-------+-----+----+----+----+-------+-------+--------+
     |             | 7     | 6   | 5  | 4  | 3  | 2     | 1     | 0      |
     +=============+=======+=====+====+====+====+=======+=======+========+
     | 0           | Bits 2-0 of      | ``first``                        |
     |             | ``second``       |                                  |
     +-------------+------------------+-----------------+----------------+
     | 1           | ``third``                          | Bits 4-3 of    |
     |             |                                    | ``second``     |
     +-------------+------------------------------------+----------------+
     
  If a ``scalar_storage_order`` of ``most_significant_first`` is specified,
  the fields of this record would be stored in `byte-addressable`_ memory
  as shown below:
  
  .. table:: Big-Endian Bit Field Layout (LSB 0)
             
     +-------------+-------+------------------------------------+--------+
     | Byte Offset | MSb   |                                    | LSb    |
     |             +-------+-----+----+----+----+-------+-------+--------+
     |             | 7     | 6   | 5  | 4  | 3  | 2     | 1     | 0      |
     +=============+=======+=====+====+====+====+=======+=======+========+
     | 0           | ``first``                  | Bits 4-2 of ``second`` |
     +-------------+-------------+--------------+------------------------+
     | 1           | Bits 1-0 of | ``third``                             |
     |             | ``second``  |                                       |
     +-------------+-------------+---------------------------------------+

stored
  Alias for ``layout``.

text_format
  Python format string suitable for use when instances of this data type are
  converted to a text string for display purposes.

value
  Specify a fixed value for instances of this data type.  Note that this does
  not make sense for some data types.
  
.. _Record:

Record
======

Composite `Type <Type>` representing a `data record`_ (i.e. C/C++ structure
or `union`_) with named `Fields <Field>`.  The following attributes are
supported:

default_for_reserved_bit
  Default value (i.e. ``0`` or ``1``) to use for reserved bits of this record.

default_for_spare_bit
  Default value (i.e. ``0`` or ``1``) to use for spare bits of this record.

.. _fields:

fields
  Ordered list of key-value pairs, where the key indicates the name of the
  field and the value specifies the data type and optional field-specific
  attributes.  The value is usually either a `Type <Type>` or `Field <Field>`
  instance, depending on whether or not field-specific attributes are
  required.  Alternatively, the value may be a list of positional/keyword
  arguments that are to be interpreted as Field attributes.  The order in
  which the fields are listed determines the order they are stored in memory
  unless a location is explicitly specified. This list attribute is
  considered *extensible* by derived classes.

.. comment
   
  .. _Little-Endian Record:
   
  Little-Endian Record
  ====================
   
  Convenience definition, equivalent to a `Record <Record>` with a
  `scalar_storage_order <scalar_storage_order>` of ``least_significant_first``.
   
  .. _Big-Endian Record:
   
  Big-Endian Record
  =================
   
  Convenience definition, equivalent to a `Record <Record>` with a
  `scalar_storage_order <scalar_storage_order>` of ``most_significant_first``.

.. _Array:

Array
=====

Composite `Type <Type>` representing a `data array`_ of similarly-typed
elements.  The following attributes are supported:

element_type
  `Type <Type>` of elements stored in the array. This attribute may be
  specified as a keyword argument or as the first positional argument.

first_index
  The index of the first element in the array.  If ``indices`` is specified,
  then the first index will be automatically determined.
  
indices
  Range of possible values for the array index (e.g. ``1..10``, ``0..9``,
  ``15..0``).  This attribute determines the number of elements in the array
  as well as the indexing convention (e.g. zero or one-based indexing,
  ascending/descending) used to access the elements.

length
  Indicates the number of elements in the array.  If ``indices`` is
  specified, then the length will be automatically determined.

of
  Alias for ``element_type``.

.. _Enum:

Enumeration (Enum)
==================

Primitive data `Type <Type>` for implementing `enumerations`_.  This data
type provides a way to encode a set of abstract, symbolic identifiers as a
set of concrete, numeric (typically integer) values.  The following
attributes are supported:

of
  Data type for the symbolic values that are represented by the enumeration.
  This attribute defaults to ``Identifier`` and rarely needs to be changed.
  In some cases, however, enumerations may be used to represent a discrete
  set of typed values (e.g. `Floats <Float>`).  This attribute may be
  specified as a keyword argument or as the first positional argument.

values
  List of enumerated values.  The data type of each value should be
  compatible with the type specified by the ``of`` attribute (usually these
  values are just a symbolic ``Identifiers``).  Alternatively, a list of
  key-value pairs may be specified to explicitly specify how each value is
  represented/encoded.  The key identifies the symbolic value, and the
  corresponding value (in the key-value pair) specifies the concrete encoding
  for that symbolic value.

as
  Concrete type used to represent the encoded values.  Typically, the default
  value for this attribute (`UInt <UInt>`) is sufficient.

bit_width
  This attribute determines the number of bits used in the representation of
  the encoded values.  In other words, it determines the `bit_width
  <bit_width>` of the representation specified via the ``as`` attribute.  If
  not explictly specified, as suitable implementation-dependent value will be
  chosen.

reserved
  List of reserved encodings that are not explicitly defined, but may be used
  for undocumented purposes.

spare
  Explicit list of spare encodings that are not currently being used.

.. _UInt:

Unsigned Integer (UInt)
=======================

Primitive data `Type <Type>` representing unsigned integer values of a
specific size.  For concrete types, the `bit_width <bit_width>` attribute
should be specified via a keyword argument or as the first positional
argument.  The ``bit_width`` for unsigned integers typically ranges from 1
to 64.

.. _Int:

Signed Integer (Int)
====================

Primitive data `Type <Type>` representing signed (two's complement) integer
values of a specific size.  For concrete types, the `bit_width <bit_width>`
attribute should be specified via a keyword argument or as the first
positional argument.  The ``bit_width`` for signed integers typically ranges
from 1 to 64.

.. _Float:

Floating Point (Float)
======================

Primitive data `Type <Type>` representing binary `IEEE 754`_-formatted
floating-point values of a specific size.  For concrete types, the `bit_width
<bit_width>` attribute should be specified via a keyword argument or as the
first positional argument.  The ``bit_width`` for floating point numbers may
be ``32`` or ``64``.

.. _Bit:

Boolean (Bool)
==============

Primitive data `Type <Type>` representing `boolean`_ values that are stored
as integers of a specific size.  A *true* value is represented as ``1`` and a
*false* value is represented as ``0``.  If specified via a keyword argument
or as the first positional argument, the `bit_width <bit_width>` attribute
indicates the number of bits used for storage, otherwise an
implementation-dependent number of bits may be used.  The ``bit_width`` for
boolean values may range from 1 to 64.

Bit
===

Primitive data `Type <Type>` representing a single bit.  This is equivalent
to a `UInt <UInt>` with a `bit_width <bit_width>` of ``1``.

.. _data array:
    https://en.wikipedia.org/wiki/Array_data_structure

.. _data record:
    https://en.wikipedia.org/wiki/Record_(computer_science)
    
.. _union:
    https://en.wikipedia.org/wiki/Union_type

.. _endianness:
    https://en.wikipedia.org/wiki/Endianness
    
.. _scalar:
    https://en.cppreference.com/w/cpp/types/is_scalar

.. _Ada Scalar Storage Order:
    https://gcc.gnu.org/onlinedocs/gcc-4.8.5/gnat_rm/Scalar_005fStorage_005fOrder.html
    
.. _GCC scalar_storage_order type attribute:
    https://gcc.gnu.org/onlinedocs/gcc/Common-Type-Attributes.html

.. _bit numbering:
     https://en.wikipedia.org/wiki/Bit_numbering
     
.. _byte-addressable:
    https://en.wikipedia.org/wiki/Byte_addressing
    
.. _bit fields:
    https://en.wikipedia.org/wiki/Bit_field
    
.. _enumerations:
    https://en.wikipedia.org/wiki/Enumerated_type

.. _IEEE 754:
    https://en.wikipedia.org/wiki/IEEE_754

.. _boolean:
    https://en.wikipedia.org/wiki/Boolean_data_type
