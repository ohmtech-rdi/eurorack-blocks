/*****************************************************************************

      TestSdramPtr.h
      Copyright (c) 2020 Raphael DINGE

*Tab=3***********************************************************************/



#pragma once



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



class TestSdramPtr
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:
                  TestSdramPtr () = default;
   virtual        ~TestSdramPtr () = default;

   void           run ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

   void           run_000 ();
   void           run_000b ();
   void           run_001 ();



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:
                  TestSdramPtr (const TestSdramPtr & rhs) = delete;
                  TestSdramPtr (TestSdramPtr && rhs) = delete;
   TestSdramPtr & operator = (const TestSdramPtr & rhs) = delete;
   TestSdramPtr & operator = (TestSdramPtr && rhs) = delete;
   bool           operator == (const TestSdramPtr & rhs) const = delete;
   bool           operator != (const TestSdramPtr & rhs) const = delete;



}; // class TestSdramPtr



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
