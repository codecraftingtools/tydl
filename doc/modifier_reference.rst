.. Copyright 2021 NTA, Inc.

.. _modifier reference:

===================
Data Type Modifiers
===================

This section describes the data type modifers provided by Tydl.  These
commands are defined in the ``Tydl.Data`` namespace.

quantified
==========

This creates a derived type that adds a ``units`` attribute to the specified
base type.  The following parameters are supported:

base
  The base `Type <Type>` to derive from.  This parameter may be specified as
  a keyword argument or as the first positional argument.
  
units
  The units associated with this data type.  Identifiers corresponding to
  most standard units and some abbreviations may be found in the
  ``Tydl.Units`` namespace.
  
scaled
======

This creates a scaled data type that stores data with a scale factor applied.
The logical type and stored data representation may also be different.  The
following parameters are supported:

as
  The logical data `Type <Type>`.  Usually this parameter may be omitted and
  can be deduced from the other parameters.

lsb
  The scale factor or weighting of the least significant bit of the stored
  data type.  The stored value is multiplied by this value to determine the
  logical value of the data.
  
max_value
  Specifies the maximum possible logical value that can be taken on by an
  instance of this data type.  This may need to be scaled by the ``lsb``
  internally before being passed along to the underlying physical data type.
  
min_value
  Specifies the minimum possible logical value that can be taken on by an
  instance of this data type.  This may need to be scaled by the ``lsb``
  internally before being passed along to the underlying physical data type.

range
  Specifies the range of possible logical values (i.e. ``min_value`` and
  ``max_value``) for instances of this data type. This may need to be scaled
  by the ``lsb`` internally before being passed along to the underlying
  physical data type.
  
representation
  The physical data `Type <Type>` that will be used to store the value.  This
  parameter may be specified as a keyword argument or as the first positional
  argument.

Other keyword parameters related to the physical representation will be
passed along to the underlying ``representation``, and the rest will be
passed to the underlying logical data type (``as``).
