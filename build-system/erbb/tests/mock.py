#!/usr/bin/env python
#
#     mock.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



from .. import adapter


class Input:
   def __init__ (self, input_):
      assert isinstance (input_, list)
      self.content = input_

   def __getitem__ (self, key):
      if isinstance (key, slice):
         start, stop, step = key.indices (len (self.content))
         return ' '.join ([self.content [idx] for idx in range (start, stop, step)])

      if isinstance (key, int):
         return self.content [key]

      assert False   # pragma: no cover



def parser (input_):
   parser_ = lambda: None
   parser_.input = Input (input_)
   parser_.file_name = 'test'
   return parser_



class _Token (adapter.Token):
   @property
   def length (self):
      return 1


def token (TokenCategory, name, parser_, tag):
   node = lambda: None
   node.value = name
   node.position = tag
   if parser_:
      assert tag != 0
      assert parser_.input [tag] == name
   return TokenCategory (parser_, node)


class _Identifier (_Token, adapter.Identifier):
   pass

def identifier (name, parser_ = None, tag = 0):
   return token (_Identifier, name, parser_, tag)


class _Keyword (_Token, adapter.Keyword):
   pass

def keyword (name, parser_ = None, tag = 0):
   return token (_Keyword, name, parser_, tag)


class _Symbol (_Token, adapter.Symbol):
   pass

def symbol (name, parser_ = None, tag = 0):
   return token (_Symbol, name, parser_, tag)


class _Literal (_Token, adapter.Literal):
   pass

def literal (name, parser_ = None, tag = 0):
   return token (_Literal, name, parser_, tag)
