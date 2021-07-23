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

Member (`data field`_) of a `Record <Record>`.  The following attributes are
supported:

at
  If this attribute is specified, the associated field will not be appended
  to the end of the parent `Record <Record>`, but will instead overlay
  another existing field (or set of fields) in the parent record.  The value
  of this parameter supplies an ordered list of the existing fields (or
  single field) into which the bytes of the associated field content are to
  be stored.

flat
  Indicates that members of a nested `Record <Record>` field should be
  directly accessible (as if they were children of the parent record).  In
  other words, there is no requirement to mention the name of the
  intermediate field.  This is similar to how `anonymous union`_ fields work
  in C/C++.

hidden
  Indicates that this field should not be shown/printed when the parent
  record is displayed.  The field is still accessible from auto-generated
  *smart structure* classes, however.  This attribute is often used in
  conjunction with field aliases to avoid displaying the same data twice.

if
  If this attribute is specified, then the associated field is conditional.
  In other words, it may or may not be present in the structure, depending on
  the value of some fields that appear before it in the record.  The value of
  this parameter is a boolean expression that determines whether or not this
  field is present.  This expression may include other fields of the parent
  record that appear before this one.
  
reserved
  Indicates that this field is classified as a *reserved* field that is not
  explicitly defined, but may be used for undocumented purposes.

spare
  Indicates that this field is classified as a *spare* field that is not
  currently used.

type
  `Type <Type>` of data stored in this field.  This attribute also
  corresponds to the first positional argument.

.. _Layout:

Layout
======

Specifies the low-level bit/byte layout to be used when storing an instance
of a data `Type <Type>` in `byte-addressable`_ memory.  The following
attributes are supported:

at
  Ordered list of the low-level fields into which the bytes of the associated
  data type instance are to be stored.

of
  `Record <Record>` representing the physical memory area into which a data
  type instance may be stored.

.. _anonymous union:
    https://en.wikipedia.org/wiki/Union_type#Anonymous_union

.. _data field:
    https://en.wikipedia.org/wiki/Field_(computer_science)

.. _byte-addressable:
    https://en.wikipedia.org/wiki/Byte_addressing
