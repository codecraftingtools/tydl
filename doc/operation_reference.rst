.. Copyright 2021 NTA, Inc.

.. _operation reference:

===============
Data Operations
===============

This section describes the built-in data operations provided by Tydl.  These
operations are defined in the ``Tydl.Operations`` namespace.

sum
===

`Parameterized Entity <Parameterized>` representing the sum of a set of data
values.

The following keyword parameters may be used to specify attributes of this
entity:

modulo
  Alias for ``modulus``.
  
modulus
  If this `Unsigned Integer <UInt>` attribute is specified, then the sum will
  be computed using `modular arithmetic`_ with the modulus being equal to the
  specified value.

of
  Alias for ``values``.

values
  List of values to sum.

The following positional parameters are accepted:

.. table::
   
   +-------------------+----------------------------------------------+
   | Argument Position | Parameter                                    |
   +===================+==============================================+
   | 1st               | ``values``                                   |
   +-------------------+----------------------------------------------+

twos_complement
===============

`Parameterized Entity <Parameterized>` representing the `two's complement`_
of a specified value.

The following keyword parameters may be used to specify attributes of this
entity:

of
  Alias for ``value``.

value
  Value to complement.
  
The following positional parameters are accepted:

.. table::
   
   +-------------------+----------------------------------------------+
   | Argument Position | Parameter                                    |
   +===================+==============================================+
   | 1st               | ``value``                                    |
   +-------------------+----------------------------------------------+
   
.. _modular arithmetic:
    https://en.wikipedia.org/wiki/Modular_arithmetic

.. _two's complement:
    https://en.wikipedia.org/wiki/Two%27s_complement
