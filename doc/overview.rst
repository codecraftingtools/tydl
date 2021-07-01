.. Copyright 2021 Jeffrey A. Webb
   Copyright 2021 NTA, Inc.

========
Overview
========

Motivation
==========

Almost all computer programs, to one degree or another, rely on `data
structures`_ to organize and store the data manipulated by the program.
Within a program, it is often desirable to interact with data structures in
an abstract way, without concern for the underlying physical representation
or layout.  When data is transmitted between programs, however, these details
become important.  This is true whether the data is transmitted via a network
connection, serial data stream, or data file.  Every program that directly
interacts with this data must understand underlying physical representation.
Unfortunately, if programs that interact with a common data structure are
written in different programming languages, or even simply compiled for
different computing architectures, the low-level representation of the data
structure may need to be specified in a different way.  Tydl was conceived as
a way to address this issue by providing a powerful language for
unambiguously describing data structures and an accompanying toolchain that,
when combined, greatly reduce the need for duplicated information and
hand-written boilerplate code.

Project Scope
=============

Language
--------

The first goal of the Tydl project is to implement a language that allows
*all* information about a data structure to be encoded in `one format
<cc:file-format-considerations>` and accessed in one place, from high-level
semantic information to low-level details regarding the physical
representation.  This may include information like field names, measurement
units, numeric bounds (min/max), reference frame, default value, description,
title, scale factor, `endianness`_, `bit numbering`_, custom attributes, etc.
Having all of this information in one place eases the software /
documentation maintenence burden and reduces errors that stem from
`duplicated information`_ not being kept in sync.

In addition to providing a standardized and unified way of describing typical
`data structures`_ (e.g. `arrays`_, `records`_, `bit fields`_ and `unions`_),
Tydl also aspires to support the definition of more sophisticated types than
are available in most mainstream programming languages.  This includes items
like `tagged unions`_, discontiguous (pieced-together) fields,
variable-length arrays, "sliding" fields whose location may move (i.e. they
follow variable-length fields), fields with derived values (e.g. checksums),
conditional fields (may or may not appear), transformed fields (e.g. scaled
integers), etc.

Front End
---------

The second goal of this project is to implement a `Python-based <cc:python>`
front end that parses Tydl-formatted type descriptions (that are easy to
write and maintain) and converts them into a standardized internal
representation that is easy for back-end code to process.  Code and
documentation generators can then leverage a common parsing engine instead of
having to implement this functionality independently.

Back Ends
---------

The Tydl project also aims to provide a set of Python-based back ends for
generating code and documentation from the standardized internal
representation produced by the parsing engine.  Back ends could be used to
generate:

- C++ message class wrappers (i.e. *smart structures*)
- Python bindings for *smart structures*
- API documentation
- Interface control documents
- Graphical data visualizers
- Graphical control applications
- Binary data post-processing tools

Some of these back ends may be provided as part of the Tydl project, while
others will be provided through external plug-ins.

`Automatic generation of code <cc:automatic-code-generation>` and
documentation from a single source specification has many advantages.  Once
the required tools are established, this approach improves the consistency of
class wrappers, eliminates hand-written boilerplate code, minimizes the
duplication of information, reduces the maintenence burden, and maximizes
productivity.

Command-Line Tool
-----------------

The final piece of the Tydl project is a Python-based command-line tool for
invoking the front-end parser and passing information to the back-end
generators.

.. image:: images/data_flow.*
   :width: 100%

.. _endianness:
     https://en.wikipedia.org/wiki/Endianness

.. _bit numbering:
     https://en.wikipedia.org/wiki/Bit_numbering

.. _duplicated information:
     https://en.wikipedia.org/wiki/Don%27t_repeat_yourself
     
.. _data structures:
     https://en.wikipedia.org/wiki/Data_structure

.. _arrays:
     https://en.wikipedia.org/wiki/Array_data_structure

.. _records:
    https://en.wikipedia.org/wiki/Record_(computer_science)

.. _bit fields:
    https://en.wikipedia.org/wiki/Bit_field

.. _unions:
    https://en.wikipedia.org/wiki/Union_type

.. _tagged unions:
    https://en.wikipedia.org/wiki/Tagged_union
