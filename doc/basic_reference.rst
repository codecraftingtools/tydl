.. Copyright 2021 NTA, Inc.

.. _basic reference:

===================
Basic Functionality
===================

This section documents the general-purpose entities, directives, and commands
defined in the ``Tydl`` namespace and describes the attributes or parameters
that are applicable to each one.

.. _Alias:

Alias
=====

`Parameterized Entity <Parameterized>` used explictly define an alias
(i.e. an alternate name) for a value.  This is useful in situations where the
usual method of creating an implicit alias (i.e. just assigning multiple
names to the same value) may not be possible, such as in parameter lists.

The following keyword parameters may be used to specify attributes of this
entity:

aliasee
  `Entity <Entity>` to be aliased.

for
  Alias for ``aliasee``.

.. comment
   
   Field Alias
   
   This type of alias also adds the capability of overriding some less
   significant attributes (e.g. visibility or documentation-related items) of
   the aliased entity with alternate values.
    
   Other keyword parameters may be supplied, and their usage may depend on
   what type of alias this is (e.g. a `Field <Field>` alias).

.. _Attribute:

Attribute
=========

Special type of `Parameter <Parameter>` representing an entity attribute
(i.e. an ``Attribute`` is used to specify a property of an ``Entity``).

The following keyword parameters may be used to specify attributes of this
``Attribute`` entity:

type
  Type of `Entity <Entity>` that may be assigned to this ``Attribute``.  If
  no type is specified, then any type of ``Entity`` is acceptable.

positional
  `Boolean Value <Bool>` specifying whether or not values for this
  ``Attribute`` may be passed to an ``Entity`` specialization *call* as a
  positional argument.  The default value for this parameter is ``false``.
  If ``true`` is specified, then the value for this ``Attribute`` may be
  passed as a positional argument following any other positional arguments
  that occur before this one in the attribute list defined by the parent
  ``Entity``.

.. _Command:

Command
=======

Extension of `Callable Entity <Callable>` that serves as a base for custom
instructions that are evaluated as a file is parsed and processed.  One
primary use case is macros.  A *callable* ``Command`` must be instantiated
from a `Macro <Macro>` entity before it can be invoked.

.. _Callable:

Callable Entity (Callable)
==========================

Extension of `Entity <Entity>` that serves as a base for entities that are
*callable*.

.. _Directive:

Directive
=========

Extension of `Callable Entity <Callable>` that serves as a base for built-in
entities that influence how Tydl source files are parsed, processed, and
evaluated.

.. _Entity:

Entity
======

Fundamental entity that serves as a base for all other entities.

All entities have the following attributes:

attributes
  Ordered list of key-value pairs that defines the additional attributes
  associated with this entity, aside from ``attributes`` itself.  The keys in
  the list indicate the names of the attributes, and the values specify the
  types of entities permissible for each attribute and possibly other
  attribute-specific properties, such as extendability, mutability, and
  argument position.  Each value may be either an `Attribute <Attribute>` or
  another type of ``Entity``, depending on whether or not any of the
  optional, attribute-specific properties are required.  If a key with no
  value is specified, then the type of value that can be assigned to an
  attribute is not constrained.  Derived entities (extensions) may append
  attributes to the end of this list.

.. _file:

file
====

`Directive <Directive>` used to specify attributes related to the file
currently being processed.

The following keyword parameters are accepted:

namespace
  Namespace identifier (possibly dotted) specifying the namespace into which
  any named entities declared in the current file will be stored.  If no
  namespace is specified, then the root namespace will be used.

.. _import:

import
======

`Directive <Directive>` used to import entities declared in other namespaces
into the calling one.  Note that this special, fundamental directive is
automatically imported into the namespace of every file to bootstrap the
import process.

The following keyword parameters are accepted:
  
from
  Alias for ``source`` or ``sources`` (if list).
  
identifier
  Singular alias for ``identifiers``
  
identifiers
  List of (possibly dotted) identifiers to be imported into the calling
  namespace, or the single identifier ``all``.

  If this parameter is set to ``all``, everything declared in each of the
  namespaces specified by the ``sources`` parameter will be imported.  Please
  note, however, that this feature should be used with care to avoid
  polluting the calling namespace by unintentionally importing unwanted
  identifiers.  In general, ``all`` should only be specified when importing
  common, well-known definitions, such as the ones found in the ``Tydl`` and
  ``Tydl.Data`` namespaces.

  If the ``sources`` parameter is not specified, ``identifiers`` is expected
  to be a list of namespace identifiers that may be explicitly referenced in
  the calling namespace.
  
source
  Singular alias for ``sources``

sources
  List of (possibly dotted) namespace identifiers that specify the namespaces
  from which the indicated ``identifiers`` will be imported.  Only one
  namespace identifier may be specified unless the ``identifiers`` parameter
  is set to ``all``.

The following positional parameters are accepted:

.. table::
   
   +-------------------+----------------------------------------------+
   | Argument Position | Parameter                                    |
   +===================+==============================================+
   | 1st               | ``identifier`` or ``identifiers`` (if list)  |
   +-------------------+----------------------------------------------+

.. _macro:

macro
=====

`Command <Command>` that, in a single statement, defines a `Macro <Macro
Entity>` entity and instantiates a *callable* ``Command`` instance from that
``Macro``.  Any arguments passed into the the ``macro`` command are simply
passed along to the underlying ``Macro`` entity specialization.

.. _Macro Entity:

Macro
=====

`Parameterized Entity <Parameterized>` representing a parameterized
expression that is to be evaluated in the context of the calling location.
When a `Command <Command>` instance created from a ``Macro`` entity (usually
created via the ``macro`` command) is called, the value of each argument
passed into the *call* will be substituted in place of the associated
parameter name wherever it occurs in the macro body expression, and then the
resulting expression will substituted in place of the call.

.. note::
  In almost all cases, ``Macro`` entities are created and instantiated at the
  same time using the ``macro`` command.

The following keyword parameters may be used to specify attributes of this
entity:

parameters
  Ordered list of key-value pairs specifying the parameters that may be
  passed into a `Command <Command>` instance created from this ``Macro`` when
  the command is called.  The keys in the list indicate the names of the
  parameters, and the values specify the types of entities permissible for
  each parameter and possibly other parameter-specific attributes, such as
  argument position.  Each value may be either a `Parameter <Parameter>` or
  another type of `Entity <Entity>`, depending on whether or not any of the
  optional, parameter-specific attributes are required.  If a key with no
  value is specified, then the type of value that can be passed into the
  associated parameter is not constrained.

body
  Expression that is to be substituted in place of the `Command <Command>`
  instance created from this ``Macro`` when it is called.  Identifiers in the
  parameter list are replaced with the passed-in values wherever they appear
  in the body expression.

is
   Alias for ``body``.

The following positional parameters are accepted:

.. table::
   
   +-------------------+----------------------------------------------+
   | Argument Position | Parameter                                    |
   +===================+==============================================+
   | 1st               | ``parameters``                               |
   +-------------------+----------------------------------------------+
   
.. _Parameter:

Parameter
=========

`Parameterized Entity <Parameterized>` representing a *call* parameter used
to pass data to a *callee*.

The following keyword parameters may be used to specify attributes of this
entity:

type
  Type of `Entity <Entity>` that may be passed to a *callee* through this
  ``Parameter``.  If no type is specified, then any type of value is
  acceptable.

positional
  `Boolean Value <Bool>` specifying whether or not values for this
  ``Parameter`` may be passed to the *callee* as a positional argument.  The
  default value for this parameter is ``false``.  If ``true`` is specified,
  then the value for this ``Parameter`` may be passed as a positional
  argument following any other positional arguments that occur before this
  one in the parameter list defined by the *callee*.

.. _Parameterized:

Parameterized Entity (Parameterized)
====================================

Extension of `Callable Entity <Callable>` that serves as a base for entities,
that when called, return *specialized* versions of themselves.  The arguments
passed when calling a ``Parameterized Entity`` are interpreted as specifiers
for existing ``Entity`` attributes, except in the following two special
cases:

constrains
  Ordered list of key-value pairs specifying *constraints* for existing
  attributes.  The difference between *constraints* and *specifiers* is that
  a *specifier* must fully specify an attribute value, while a *constraint*
  may be used to partially specify an attribute value (i.e. specify
  attributes of attributes).  The keys in the list indicate the names of the
  attributes to be constrained, and the values may be either a fully
  specified value (i.e. the constraint may be a specifier), or a nested list
  of key-value pairs specifying the attributes of the attribute being
  constrained.

appends
  Ordered list of key-value pairs specifying values that should be appended
  to existing list attributes.  The keys in the list indicate names of
  existing list attributes, and the values are expected to be lists
  containing the values to be appended to each of the corresponding lists.
  
.. extended
   ========
    
   Creates a new derived entity that inherits from, or *extends*, an existing
   (base) entity.  Extending means that an instance of the new entity can be
   treated as instance of the base entity, but may have additional properties
   or appended data.  The new entity may define new attributes or append
   additional elements to existing list attributes (if they are
   *extensible*).  The following parameters are accepted:
    
   base
     Base entity to be extended.  This parameter may be specified as a
     keyword argument or as the first positional argument.
    
   Additional keyword arguments are used to append elements to *extensible*
   list attributes that are defined in the base entity or to define new
   attributes that do not exist in the base entity.
    
.. specifier
   =========
    
   Provides a mechanism to essentially create a macro or entity alias that
   also adds additional keyword arguments to any invocation of the alias.
   The following parameters are accepted:
    
   first positional argument
     The macro or entity that is to be "aliased".
    
   Additional keyword arguments passed to ``specifier`` are interpreted as
   additional arguments that are to be passed to the "aliased" macro or
   entity whenever the specifier instance that is being defined is invoked.
    
   function
   ========
    
   Defines a parameterized function that returns a typed value.  The
   following parameters are accepted:
    
   body
     List of statements to be executed during a function call.  When a
     `return <return>` command is encountered, execution of the function
     stops and the result of the `return <return>` call is returned to the
     caller.
    
   is
     Alias for ``body``.
    
   of
     Alias for ``parameters``.
    
   parameters
     List of arguments that are to be passed into the function when it is
     invoked.  If a list of key-value pairs is supplied, the keys represent
     the parameter names and the values represent the data `Types <Type>` for
     the associated parameters.  This parameter may be specified as a keyword
     argument or as the first positional argument.
    
   returns
     Data `Type <Type>` of the value returned by this function.
    
   return
   ======
    
   Command used to return a value from a function to the caller.  The
   following parameters are accepted:
    
   first positional argument
     The value to be returned to the caller.
    
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
    
   Command that conditionally evaluates to one expression or another if
   invoked.  The following parameters are accepted:
    
   condition
     The boolean expression that determines what will be returned.  This
     parameter may be specified as a keyword argument or as the first
     positional argument.
    
   then
     The expression to return if the ``condition`` is true.
    
   else
     The expression to return if the ``condition`` is false.  If this
     parameter is not specified, then an empty list will be returned.
    
   is_specified
   ============
    
   Command that returns ``true`` if the data instance passed in as the first
   positional argument has been assigned a value and ``false`` if it has not.
