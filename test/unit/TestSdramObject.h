/*****************************************************************************

      TestSdramObject.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



class TestSdramObject
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  TestSdramObject () = default;
   virtual        ~TestSdramObject () = default;

   void           run ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   struct A
   {
      int         a;
   };

   void           run_001 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestSdramObject (const TestSdramObject & rhs) = delete;
                  TestSdramObject (TestSdramObject && rhs) = delete;
   TestSdramObject &
                  operator = (const TestSdramObject & rhs) = delete;
   TestSdramObject &
                  operator = (TestSdramObject && rhs) = delete;
   bool           operator == (const TestSdramObject & rhs) const = delete;
   bool           operator != (const TestSdramObject & rhs) const = delete;



}; // class TestSdramObject



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
