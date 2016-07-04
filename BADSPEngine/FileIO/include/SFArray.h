//
// Copyright 1997-1999 by Craig Stuart Sapp, All Rights Reserved.
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed Feb  5 19:42:53 PST 1997
// Last Modified: Sun May 11 20:33:13 GMT-0800 1997
// Last Modified: Wed Jul  7 11:44:50 PDT 1999 (added setAll() function)
// Last Modified: Mon Jul 29 22:08:32 PDT 2002 (added operator==) 
// Filename:      ...sig/maint/code/base/Array/Array.h
// Web Address:   http://sig.sapp.org/include/sigBase/Array.h
// Documentation: http://sig.sapp.org/doc/classes/Array
// Syntax:        C++ 
//
// Description:   An array which can grow dynamically.  Array is derived from 
//                the Collection class and adds various mathematical operators
//                to the Collection class.  The Array template class is used for
//                storing numbers of any type which can be added, multiplied
//                and divided into one another.
//

#ifndef _SFARRAY_H_INCLUDED
#define _SFARRAY_H_INCLUDED

#include "Collection.h"


template<class type>
class SFArray : public Collection<type> {
   public:
                     SFArray             (void);
					 SFArray			(int arraySize);
					 SFArray			(SFArray<type>& aArray);
					 SFArray			(int arraySize, type *anArray);
                    ~SFArray			();

      void           setAll            (type aValue);
      type           sum               (void);
      type           sum               (int lowIndex, int hiIndex);
      void           zero              (int minIndex = -1, int maxIndex = -1);

      int            operator==        (const SFArray<type>& aArray);
	  SFArray<type>&   operator=         (const SFArray<type>& aArray);
	  SFArray<type>&   operator+=        (const SFArray<type>& aArray);
	  SFArray<type>&   operator-=        (const SFArray<type>& aArray);
	  SFArray<type>&   operator*=        (const SFArray<type>& aArray);
	  SFArray<type>&   operator/=        (const SFArray<type>& aArray);

	  SFArray<type>    operator+         (const SFArray<type>& aArray) const;
	  SFArray<type>    operator+         (type aNumber) const;
	  SFArray<type>    operator-         (const SFArray<type>& aArray) const;
	  SFArray<type>    operator-         (void) const;

	  SFArray<type>    operator-         (type aNumber) const;
	  SFArray<type>    operator*         (const SFArray<type>& aArray) const;
	  SFArray<type>    operator*         (type aNumber) const;
	  SFArray<type>    operator/         (const SFArray<type>& aArray) const;
};


#include "SFArray.cpp"   /* necessary for templates */



#endif  /* _ARRAY_H_INCLUDED */



// md5sum: 09d1b1f8e70ecde53f484548e48f33c3 Array.h [20030102]
