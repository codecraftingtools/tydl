.. Copyright 2021 NTA, Inc.

.. _supp data reference:

==================================
Supplemental Data-Related Entities
==================================

This section documents the supplemental data-related entities provided by
Tydl and describes the attributes that are applicable to each specific
entity.  These entities are defined in the ``Tydl.Data`` namespace.

.. _Field:

Field
=====

`Parameterized Entity <Parameterized>` representing a member (`data field`_)
of a `Record <Record>`.

The following keyword parameters may be used to specify attributes of this
entity:

at
  Alias for ``location`` or ``locations`` (if list).

flat
  `Boolean Value <Bool>` indicating whether or not members of a nested
  `Record <Record>` field should be directly accessible (as if they were
  immediate children of the parent record).  In other words, if ``flat`` is
  specified, there is no requirement to mention the name of the intermediate
  field.  This is similar to how `anonymous union`_ fields work in C/C++.
  The default value is ``false``.

hidden
  `Boolean Value <Bool>` indicating whether or not this field should be
  shown/printed when the parent `Record <Record>` is displayed.  Fields
  marked as ``hidden`` are still accessible from auto-generated *smart
  structure* classes, however.  This attribute is often used in conjunction
  with field aliases or unions to avoid displaying the same data twice.  The
  default value is ``false``.

.. if
   
    If this attribute is specified, then the associated field is conditional.
    In other words, it may or may not be present in the structure, depending
    on the value of some fields that appear before it in the record.  The
    value of this parameter is a boolean expression that determines whether
    or not this field is present.  This expression may include other fields
    of the parent record that appear before this one.
  
location
  Singular alias for ``locations``.

locations
  If this attribute is specified, the associated field will not be appended
  to the end of the parent `Record <Record>`, but will instead overlay one or
  more fields in the parent record.  The value of this attribute is expected
  to be an ordered list of `Field <Field>` names from the parent ``Record``
  into which the bytes of the associated field content are to be stored.

reserved
  `Boolean Value <Bool>` indicating whether or not this field should be
  classified as a *reserved* field that is not explicitly defined, but may be
  used for undocumented purposes.  The default value for this field is
  ``false``.

spare
  `Boolean Value <Bool>` indicating whether or not this field should be
  classified as a *spare* field that is not currently used.  The default
  value for this field is ``false``.

type
  `Type <Type>` of data stored in this field.

The following positional parameters are accepted:

.. table::
   
   +-------------------+----------------------------------------------+
   | Argument Position | Parameter                                    |
   +===================+==============================================+
   | 1st               | ``type``                                     |
   +-------------------+----------------------------------------------+

.. _Bit Fields:

Bit Fields
==========

Extension of `Field <Field>`, where the ``type`` attribute is a custom
`Bit-Field Word <Bit-Field Word>` extension that contains additional fields.

The following keyword parameters may be used to specify attributes of this
entity:

fields
  Ordered list of key-value pairs that define the additional fields to be
  appended to the ``Bit-Field Word``.

bit_width
  This attribute indicates the ``bit_width`` of the underlying ``Bit-Field
  Word``.
  
.. _Layout:

Layout
======

`Parameterized Entity <Parameterized>` for specifying the low-level bit/byte
layout to be used when storing an instance of a data `Type <Type>` in
`byte-addressable`_ memory.  This functionality is useful for changing the
order that bytes or words in a data value are stored in memory.

The following keyword parameters may be used to specify attributes of this
entity:

at
  Alias for ``location`` or ``locations`` (if list).

location
  Singular alias for ``locations``.
  
locations
  Ordered list of low-level fields (from ``representation``) into which the
  bytes of the associated data type instance are to be stored.

of
  Alias for ``representation``.

representation
  `Record <Record>` representing the physical memory area into which a data
  type instance may be stored.

.. _Reserved Field:

Reserved Field
==============

Extension of `Field <Field>` with ``reserved`` set to ``true`` and a ``type``
of `Bit-Field Word <Bit-Field Word>`.

The following keyword parameters may be used to specify attributes of this
entity:

bit_width
  This attribute indicates the ``bit_width`` of the underlying ``Bit-Field
  Word``.
  
.. _Spare Field:

Spare Field
===========

Extension of `Field <Field>` with ``spare`` set to ``true`` and a ``type`` of
`Bit-Field Word <Bit-Field Word>`.

The following keyword parameters may be used to specify attributes of this
entity:

bit_width
  This attribute indicates the ``bit_width`` of the underlying ``Bit-Field
  Word``.
  
.. _anonymous union:
    https://en.wikipedia.org/wiki/Union_type#Anonymous_union

.. _data field:
    https://en.wikipedia.org/wiki/Field_(computer_science)

.. _byte-addressable:
    https://en.wikipedia.org/wiki/Byte_addressing
