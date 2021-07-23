.. Copyright 2021 NTA, Inc.

.. _operation reference:

===============
Data Operations
===============

This section describes the built-in data operations provided by Tydl.  These
macros are defined in the ``Tydl.Operations`` namespace.

sum
===

Returns the sum of the supplied positional arguments.  The following keyword
parameters are accepted:

modulo
  If this parameter is specified, then the sum will be computed using
  `modular arithmetic`_ with the modulus being equal to the value of this
  parameter.

twos_complement
===============

Returns the `two's complement`_ of the first positional argument.

.. _modular arithmetic:
    https://en.wikipedia.org/wiki/Modular_arithmetic

.. _two's complement:
    https://en.wikipedia.org/wiki/Two%27s_complement
