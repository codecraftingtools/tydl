-- Copyright 2021 Jeffrey A. Webb

import all: from: (Tydl, Tydl.Data.Types)

Child: Record
  fields:
    member1: UInt32
    member2: UInt32

Parent: Record
  fields:
    child1: Child
    child2: Child
