#!/usr/bin/env python3
#
#     %module.name%.tayda.drill.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



import argparse
import requests
import sys
import time



#-- parse_args ------------------------------------------------------------
#
#  Description:
#  Parse command line arguments

def parse_args ():
   arg_parser = argparse.ArgumentParser ()

   arg_parser.add_argument (
      '--username',
      help = 'The tayda account username'
   )

   arg_parser.add_argument (
      '--password',
      help = 'The tayda account password'
   )

   arg_parser.add_argument (
      '--update-id',
      help = 'The id of the design to update'
   )

   return arg_parser.parse_args (sys.argv[1:])



"""
==============================================================================
Name : get_token
==============================================================================
"""

def get_token (args):
   body = 'client_id=504c414f002c1bac7dca4f32db3706d7b22c25200d7daa878c0ae0be5f0f7222'
   body += '&response_type=token'
   body += '&grant_type=password'
   body += '&username=%s' % args.username
   body += '&password=%s' % args.password
   body += '&owner_type=box_customer'

   headers = {'content-type' : 'application/x-www-form-urlencoded'}
   url = 'https://www.taydaopc.com/oauth/token.json'

   r = requests.post (url, params=body, headers=headers)
   r.raise_for_status ()

   return (r.json () ['access_token'])



"""
==============================================================================
Name : make_box_design
==============================================================================
"""

def make_box_design ():
   return '%body%'



"""
==============================================================================
Name : create_new_box_design
==============================================================================
"""

def create_new_box_design (token):
   url = 'https://www.taydaopc.com/api/v4/box_designs'
   headers = {
      'Authorization': 'Bearer ' + token,
      'Content-Type': 'application/json',
      'Referer': 'https://drill.taydakits.com/',
   }

   body = make_box_design ()

   r = requests.post (url, data=body, headers=headers)
   r.raise_for_status ()

   return r.json ()['box_design']['id']



"""
==============================================================================
Name : update_box_design
==============================================================================
"""

def update_box_design (token, id):
   url = 'https://www.taydaopc.com/api/v4/box_designs/%s' % id
   headers = {
      'Authorization': 'Bearer ' + token,
      'Content-Type': 'application/json',
      'Referer': 'https://drill.taydakits.com/',
   }

   body = make_box_design ()

   r = requests.put (url, data=body, headers=headers)
   r.raise_for_status ()



"""
==============================================================================
Name : main
==============================================================================
"""

def main (args):
   token = get_token (args)
   if args.update_id:
      update_box_design (token, args.update_id)
   else:
      id = create_new_box_design (token)
      print ('Saved to: https://drill.taydakits.com/box-designs/edit?id=%s' % id)



##############################################################################

if __name__ == '__main__':
   sys.exit (main (parse_args ()))
