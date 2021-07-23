.. Copyright 2021 NTA, Inc.

.. _basic reference:

===================
Basic Functionality
===================

This section documents the general-purpose commands defined in the ``Tydl``
namespace and describes the parameters that are applicable to each one.

import
======

Imports entities from a specified namespace into the current one.  Note that
this special, fundamental command is automatically imported into every
namespace to bootstrap the import process.  The following parameters are
accepted:

all
  If this parameter is specified with no value (or is explicitly set to
  ``true``), all entities from the specified namespace will be imported into
  the current one.  This option should be used with care.  In general, it
  should only be used with common, well-known definitions.  If ``all`` is
  specified, then a specific ``entity`` or list of ``entities`` should not be
  specified.

entities
  This parameter specifies the entity name (or list of names) to import into
  the current namespace.  This parameter may be specified as a keyword
  argument, or as the first positional argument if ``from`` is explicitly
  specified.

entity
  Alias for ``entities``.

from
  Specifies the namespace that the entities will be imported from.  If a
  specific ``entity`` or list of ``entities`` is not specified, then a list
  of namespaces is also acceptable.  If ``all`` and ``entities`` are both
  omitted, then the specified fully qualified (dotted) namespace itself is
  imported for use in the current namespace.  In this case, ``from`` may be
  specified using the first positional argument.

file
====

Specifies properties related to the current file being processed.  The
following parameters are accepted:

namespace
  Namespace in which any named entities declared in the current file will be
  stored.  If no namespace is specified, then the top-level (root) namespace
  will be used.

extended
========

Creates a new derived entity that inherits from, or *extends*, an existing
(base) entity.  Extending means that an instance of the new entity can be
treated as instance of the base entity, but may have additional properties or
appended data.  The new entity may define new attributes or append additional
elements to existing list attributes (if they are *extensible*).  The
following parameters are accepted:

base
  Base entity to be extended.  This parameter may be specified as a keyword
  argument or as the first positional argument.

Additional keyword arguments are used to append elements to *extensible* list
attributes that are defined in the base entity or to define new attributes
that do not exist in the base entity.

.. _macro:

macro
=====

Defines a parameterized expression that is to be substituted wherever it is
invoked.  The following parameters are accepted:

parameters
  List of arguments that are to be passed into the macro when it is invoked
  and substituted into the macro body expression.  This parameter may be
  specified as a keyword argument or as the first positional argument.

body
  Expression to be substituted in place of the macro wherever it is invoked.
  Identifiers in the parameter list are replaced with the passed-in values
  wherever they appear in the body expression.

is
   Alias for ``body``.

.. _specifier:

specifier
=========

Provides a mechanism to essentially create a macro or entity alias that also
adds additional keyword arguments to any invocation of the alias.  The
following parameters are accepted:

first positional argument
  The macro or entity that is to be "aliased".

Additional keyword arguments passed to ``specifier`` are interpreted as
additional arguments that are to be passed to the "aliased" macro or entity
whenever the specifier instance that is being defined is invoked.

.. _function:

function
========

Defines a parameterized function that returns a typed value.  The following
parameters are accepted:

body
  List of statements to be executed during a function call.  When a `return
  <return>` command is encountered, execution of the function stops and the
  result of the `return <return>` call is returned to the caller.

is
  Alias for ``body``.

of
  Alias for ``parameters``.

parameters
  List of arguments that are to be passed into the function when it is
  invoked.  If a list of key-value pairs is supplied, the keys represent the
  parameter names and the values represent the data `Types <Type>` for the
  associated parameters.  This parameter may be specified as a keyword
  argument or as the first positional argument.

returns
  Data `Type <Type>` of the value returned by this function.

.. _return:

return
======

Command used to return a value from a function to the caller.  The following
parameters are accepted:

first positional argument
  The value to be returned to the caller.

.. _short:

short
=====

Command used to define a shorthand notation for an expression.  This is a
simpler version of a `macro <macro>` that is not parameterized.  The
following parameters are accepted:

for
  Expression to be substituted in place of the ``short`` wherever it is
  invoked.

if
==

Command that conditionally evaluates to one expression or another if invoked.
The following parameters are accepted:

condition
  The boolean expression that determines what will be returned.  This
  parameter may be specified as a keyword argument or as the first positional
  argument.

then
  The expression to return if the ``condition`` is true.

else
  The expression to return if the ``condition`` is false.  If this parameter
  is not specified, then an empty list will be returned.

is_specified
============

Command that returns ``true`` if the data instance passed in as the first
positional argument has been assigned a value and ``false`` if it has not.


.. _alias:

alias
=====

Command that may be used to define an alias in places where the normal method
of just assigning another name to a value is not supported (e.g. parameter
lists).  This type of alias also has the capability of overriding some less
significant attributes of the aliased entity with fixed values.  This
functionality is similar to the functionality provided by the `specifier
<specifier>` command, and maybe these could be combined somehow in the
future.  The following parameters are accepted:

for
  The entity to be aliased.

Other keyword parameters may be supplied, and their usage may depend on what
type of alias this is (e.g. a `Field <Field>` alias).
