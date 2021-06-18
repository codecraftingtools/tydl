-- Copyright 2021 Jeffrey A. Webb

import all: from: (Tydl, Tydl.Data.Types)

Struct1: Record
  fields:
    member1: UInt8
    member2: Array
      length: Expression
        value: member1
      max_length: 4
    member3: UInt8

Struct2: Record
  fields:
    child1: Struct1
    child2: Struct1
