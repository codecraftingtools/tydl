.. Copyright 2021 NTA, Inc.

.. _data reference:

==========
Data Types
==========

This section documents the data type entities provided by Tydl and describes
the attributes that are applicable to each one.  These entities are defined
in the ``Tydl.Data`` namespace.

.. _Array:

Array
=====

Composite `Type <Type>` representing a `data array`_ of similarly-typed
elements.

The following keyword parameters may be used to specify attributes of this
entity:

element_type
  `Type <Type>` of elements stored in the array.  If this attribute is not
  specified, then any type of element may be stored in the array.
  
first_index
  The index of the first element in the array.  If ``indices`` is specified,
  then the first index will be automatically determined.  The default value
  for this attribute is ``0``.
  
indices
  Range of possible values for the array index (e.g. ``1..10``, ``0..9``,
  ``15..0``).  If present, this attribute determines the number of elements
  in the array as well as the indexing convention (e.g. zero or one-based
  indexing, ascending/descending) used to access the elements.

length
  Indicates the number of elements in the array.  If ``indices`` is
  specified, then the length will be automatically determined.  If no value
  is specified, then the array length is unconstrained.

of
  Alias for ``element_type``.

The following positional parameters are accepted:

.. table::
   
   +-------------------+----------------------------------------------+
   | Argument Position | Parameter                                    |
   +===================+==============================================+
   | 1st               | ``element_type``                             |
   +-------------------+----------------------------------------------+

.. _Bit:

Bit
===

Primitive data `Type <Type>` representing a single bit.  This is equivalent
to an `Unsigned Integer <UInt>` with a ``bit_width`` of ``1``.

.. _Bool:

Boolean Value (Boolean/Bool)
============================

Primitive data `Type <Type>` representing `boolean`_ values that are stored
as integers of a specific size.  A ``true`` value is represented as ``1`` and
a ``false`` value is represented as ``0``.

The following keyword parameters may be used to specify attributes of this
entity:

bit_width
  Alias for `bit_count <bit_count>`.  If specified, this attribute indicates
  the number of bits used for storage, otherwise the size is unconstrained
  and an implementation-dependent number of bits may be used.  The
  ``bit_width`` for boolean values may range from 1 to 64.
  
The following positional parameters are accepted:

.. table::
   
   +-------------------+----------------------------------------------+
   | Argument Position | Parameter                                    |
   +===================+==============================================+
   | 1st               | ``bit_width``                                |
   +-------------------+----------------------------------------------+
   
.. _Enum:

Enumeration (Enumerated/Enum)
=============================

Primitive data `Type <Type>` implementing `enumerations`_.  This data type
provides a way to encode a set of abstract, symbolic identifiers (i.e.
*choices*) as a set of concrete, numeric (typically integer) values.  The
following attributes are supported:

as
  Alias for ``representation``.
  
bit_width
  This attribute determines the number of bits used to store the value
  representing the encoded choice.  In other words, it determines the
  ``bit_count`` of the `Type <Type>` specified via the ``representation``
  attribute.  If not explictly specified, a sufficiently large
  implementation-dependent value may be chosen.

logical_type
  Data `Type <Type>` of the symbolic choices that are represented by the
  enumeration.  This attribute defaults to ``Identifier`` and rarely needs to
  be changed.  In some cases, however, enumerations may be used to represent
  a discrete set of typed values (e.g. `Floats <Float>`).

of
  Alias for ``logical_type``.
  
representation
  Concrete `Type <Type>` used to store the encoded values.  Typically, the
  default value for this attribute (`Unsigned Integer <UInt>`) is sufficient.

reserved
  List of reserved encodings (representation values) that are not explicitly
  defined, but may be used for undocumented purposes.  A *range* of encoding
  values is also acceptable.

spare
  Explicit list of spare encodings (representation values) that are not
  currently being used.  A *range* of encoding values is also acceptable.

choices
  List of enumerated choices.  The data `Type <Type>` of each choice should
  be compatible with the type specified by the ``logical_type`` attribute
  (usually these values are just symbolic ``Identifiers``).  Alternatively, a
  list of key-value pairs may be specified to explicitly specify how each
  value is represented/encoded.  The key identifies the symbolic choice, and
  the corresponding value (in the key-value pair) specifies the concrete
  encoding for that symbolic value.

The following positional parameters are accepted:

.. table::
   
   +-------------------+----------------------------------------------+
   | Argument Position | Parameter                                    |
   +===================+==============================================+
   | 1st               | ``logical_type``                             |
   +-------------------+----------------------------------------------+
   
.. _Float:

Floating Point Value (Float)
============================

Primitive data `Type <Type>` representing binary `IEEE 754`_-formatted
floating-point values of a specific size.

The following keyword parameters may be used to specify attributes of this
entity:

bit_width
  Alias for `bit_count <bit_count>`.  This attribute indicates the number of
  bits used for storage and should be specified for concrete types.  The
  ``bit_width`` for floating point numbers may be ``32`` or ``64``.

The following positional parameters are accepted:

.. table::
   
   +-------------------+----------------------------------------------+
   | Argument Position | Parameter                                    |
   +===================+==============================================+
   | 1st               | ``bit_width``                                |
   +-------------------+----------------------------------------------+
   
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
  Ordered list of key-value pairs that define the fields present in the
  ``Record``, where the key indicates the name of the field and the value
  specifies the data type and optional field-specific attributes, such as the
  field location.  Each value may be either a `Type <Type>` or `Field
  <Field>` instance, depending on whether or not field-specific attributes
  are required.  The order in which the fields are listed determines the
  order they are stored in memory unless a location is explicitly specified.
  This list attribute is considered *appendable* by extensions of this
  entity.

.. comment
    
   .. _Little-Endian Record:
    
   Little-Endian Record
   ====================
    
   Convenience definition, equivalent to a `Record <Record>` with a
   `scalar_storage_order <scalar_storage_order>` of
   ``least_significant_first``.
    
   .. _Big-Endian Record:
    
   Big-Endian Record
   =================
    
   Convenience definition, equivalent to a `Record <Record>` with a
   `scalar_storage_order <scalar_storage_order>` of
   ``most_significant_first``.

.. _Int:

Signed Integer (SInt/Int)
=========================

Primitive data `Type <Type>` representing signed (`two's complement`_)
integer values of a specific size.

The following keyword parameters may be used to specify attributes of this
entity:

bit_width
  Alias for `bit_count <bit_count>`.  This attribute indicates the number of
  bits used for storage and should be specified for concrete types.  The
  ``bit_width`` for signed integers typically ranges from 1 to 64.

The following positional parameters are accepted:

.. table::
   
   +-------------------+----------------------------------------------+
   | Argument Position | Parameter                                    |
   +===================+==============================================+
   | 1st               | ``bit_width``                                |
   +-------------------+----------------------------------------------+

.. _Tagged Union:

Tagged Union
============

Composite `Type <Type>` representing a `tagged data union`_ that can
represent multiple kinds of `Records <Record>`. Unlike a standard `union`_,
the specific subtype of a tagged union can be determined from a field (or
*tag*) embedded in the data structure itself.

The following keyword parameters may be used to specify attributes of this
entity:

kinds
  List of `Record <Record>` subtypes that instances of this tagged union can
  represent.  All of the records listed here should be extensions of a common
  base entity.

of
  Alias for ``kinds``.
  
.. _Type:

Type
====

Extension of `Parameterized Entity <Parameterized>` that serves as a base for
all Tydl data types, including composite (e.g. `Arrays <Array>` and `Records
<Record>`) and primitive types.

The following keyword parameters may be used to specify attributes of this
entity:

.. _bit_count:

bit_count
  An unsigned integer indicating the number of bits used to represent (store)
  the value.

bit_numbering
  Indicates the `bit numbering`_ convention adopted by this data type.  Valid
  values for this attribute are ``least_significant_bit_is_0`` (aka
  ``lsb_0``) and ``most_significant_bit_is_0`` (aka ``msb_0``).  The default
  value is ``least_significant_bit_is_0``.

bit_range_order
  Indicates the order used to specify bit ranges (e.g. ``Bits[0..3]`` or
  ``Bits[3..0]``.  Valid values for this attribute are
  ``least_significant_first`` and ``most_significant_first``.  The default
  value is ``most_significant_first``.

bit_transmission_order
  Indicates the order that the individual bits of a byte are transmitted.
  Valid values for this attribute are ``least_significant_first`` and
  ``most_significant_first``.  The default value is
  ``least_significant_first``.  This attribute only makes sense for serial
  data streams.

default
  The default value to use when initializing instances of this data type.
  Where possible, a *zeroish* value will be used if this attribute is
  unspecified.

layout
  Specifies the low-level bit/byte layout to be used when storing an instance
  of this data type in `byte-addressable`_ memory.  If specified, this
  attribute should be a `Layout <Layout>` instance.

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
        First: Field
          type: 'Unsigned Integer'
            bit_width: 5
        Second: Field
          type: 'Unsigned Integer'
            bit_width: 5
        Third: Field
          type: 'Unsigned Integer'
            bit_width: 6

  If a ``scalar_storage_order`` of ``least_significant_first`` is specified,
  the fields of this record would be stored in `byte-addressable`_ memory
  as shown below:
  
  .. table:: Little-Endian Bit-Field Layout (LSB 0)
             
     +-------------+-------+------------------------------------+--------+
     | Byte Offset | MSb   |                                    | LSb    |
     |             +-------+-----+----+----+----+-------+-------+--------+
     |             | 7     | 6   | 5  | 4  | 3  | 2     | 1     | 0      |
     +=============+=======+=====+====+====+====+=======+=======+========+
     | 0           | Bits 2-0 of      | ``First``                        |
     |             | ``Second``       |                                  |
     +-------------+------------------+-----------------+----------------+
     | 1           | ``Third``                          | Bits 4-3 of    |
     |             |                                    | ``Second``     |
     +-------------+------------------------------------+----------------+
     
  If a ``scalar_storage_order`` of ``most_significant_first`` is specified,
  the fields of this record would be stored in `byte-addressable`_ memory
  as shown below:
  
  .. table:: Big-Endian Bit-Field Layout (LSB 0)
             
     +-------------+-------+------------------------------------+--------+
     | Byte Offset | MSb   |                                    | LSb    |
     |             +-------+-----+----+----+----+-------+-------+--------+
     |             | 7     | 6   | 5  | 4  | 3  | 2     | 1     | 0      |
     +=============+=======+=====+====+====+====+=======+=======+========+
     | 0           | ``First``                  | Bits 4-2 of ``Second`` |
     +-------------+-------------+--------------+------------------------+
     | 1           | Bits 1-0 of | ``Third``                             |
     |             | ``Second``  |                                       |
     +-------------+-------------+---------------------------------------+

stored
  Alias for ``layout``.

text_format
  Desired Python format string to be used when instances of this data type
  are converted to a text string for display purposes.  Note that this does
  not make sense for some data types.

value
  Specifies a fixed value for instances of this data type.  Note that this
  does not make sense for some data types.
  
.. _UInt:

Unsigned Integer (UInt)
=======================

Primitive data `Type <Type>` representing unsigned integer values of a
specific size.

The following keyword parameters may be used to specify attributes of this
entity:

bit_width
  Alias for `bit_count <bit_count>`.  This attribute indicates the number of
  bits used for storage and should be specified for concrete types.  The
  ``bit_width`` for unsigned integers typically ranges from 1 to 64.

The following positional parameters are accepted:

.. table::
   
   +-------------------+----------------------------------------------+
   | Argument Position | Parameter                                    |
   +===================+==============================================+
   | 1st               | ``bit_width``                                |
   +-------------------+----------------------------------------------+
   
.. _data array:
    https://en.wikipedia.org/wiki/Array_data_structure

.. _boolean:
    https://en.wikipedia.org/wiki/Boolean_data_type
    
.. _enumerations:
    https://en.wikipedia.org/wiki/Enumerated_type

.. _IEEE 754:
    https://en.wikipedia.org/wiki/IEEE_754
    
.. _data record:
    https://en.wikipedia.org/wiki/Record_(computer_science)
    
.. _union:
    https://en.wikipedia.org/wiki/Union_type

.. _two's complement:
    https://en.wikipedia.org/wiki/Two%27s_complement
    
.. _tagged data union:
    https://en.wikipedia.org/wiki/Tagged_union

.. _bit numbering:
     https://en.wikipedia.org/wiki/Bit_numbering
     
.. _byte-addressable:
    https://en.wikipedia.org/wiki/Byte_addressing
    
.. _endianness:
    https://en.wikipedia.org/wiki/Endianness
    
.. _scalar:
    https://en.cppreference.com/w/cpp/types/is_scalar

.. _Ada Scalar Storage Order:
    https://gcc.gnu.org/onlinedocs/gcc-4.8.5/gnat_rm/Scalar_005fStorage_005fOrder.html
    
.. _GCC scalar_storage_order type attribute:
    https://gcc.gnu.org/onlinedocs/gcc/Common-Type-Attributes.html

.. _bit fields:
    https://en.wikipedia.org/wiki/Bit_field
