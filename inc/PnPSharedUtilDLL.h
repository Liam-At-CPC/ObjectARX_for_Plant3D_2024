//
// (C) Copyright 2009 by Autodesk, Inc.
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//


#pragma once

#include "AdAChar.h"



typedef enum _eacppvaluetype
{
    eAcPpNull,
    eAcPpInt32,
    eAcPpInt64,
    eAcPpDouble,
    eAcPpString
} EAcPpValueType;
    


/// <summary>
/// Array of wstrings. This class handles string manipulations. Utility functions are provided
/// </summary>
class AcPpValue
{
public:
                    AcPpValue ();
                    AcPpValue (int val);
                    AcPpValue (__int64 val);
                    AcPpValue (double val);
                    AcPpValue (const ACHAR * val);
                    AcPpValue (const AcPpValue & other);

    virtual         ~AcPpValue ();

    AcPpValue &     operator= (int val);
    AcPpValue &     operator= (__int64 val);
    AcPpValue &     operator= (double val);
    AcPpValue &     operator= (const ACHAR * other);
    AcPpValue &     operator= (const AcPpValue & other);

    void            setNull ();
    bool            isNull () const;

    EAcPpValueType  type () const;

    ACHAR *         toString   (ACHAR * val, int len) const;

    operator        int       () const;
    operator        __int64   () const;
    operator        double    () const;
    operator        const ACHAR * () const;
private:
    void            clear ();
private:
    EAcPpValueType  m_type; 
    union {
        long        i32;
        __int64     i64;
        double      dbl;
        ACHAR  *    str;
    } m_value;
};

/// <summary>
/// Array of wstrings. This class handles string manipulations. Utility functions are provided
/// </summary>
class AcPpStringArray
{
public:
	/// <summary> Constructor with string physical length set to zero and grow length set to 8 as default</summary>
	AcPpStringArray(int initPhysicalLength = 0 , int initGrowLength = 8);

	/// <summary> Copy constructor</summary>
	/// <param name=""> Reference to AcPpStringArray class </param>
	AcPpStringArray(const AcPpStringArray&);

	/// <summary> Destructor </summary>
	~AcPpStringArray  ();

	/// <summary> Assignment operator </summary>    	
	AcPpStringArray&     operator =      (const AcPpStringArray&);

	// Indexes into the array.
	const ACHAR *        operator []     (int);

	// Accesses array elements.
	/// <summary> Accesses array elements at a specified position</summary>
	/// <param name =""> Position </param>
	/// <returns> Array element at the specified position </returns>
	const ACHAR *        At              (int) const;

	/// <summary> Accesses the first array element </summary>
	/// <returns> First array element </returns>
	const ACHAR *        First           () const ;

	/// <summary> Accesses the last array element </summary>
	/// <returns> Last array element </returns>
	const ACHAR *        Last            () const ;

	/// <summary> Sets the array element at the specified position </summary>
	/// <param name =""> Location to set the element at </param>
	/// <param name =""> Element value </param>
	/// <returns> Element array with the position set</returns>
	AcPpStringArray&       SetAt           (int post, const ACHAR *ch);
    
    // Adds array elements.
	/// <summary> Appends the array element</summary>
	/// <param name =""> Value of element to append </param>
	/// <returns> </returns>
    int                    Append          (const ACHAR *);

	/// <summary> Appends the array element </summary>
	/// <param name =""> Element array to append </param>
	/// <returns> New element array with appended elements</returns>
    AcPpStringArray&       Append          (const AcPpStringArray &);

	/// <summary> Inserts the array element at the specified position</summary>
	/// <param name =""> Location to insert the element </param>
	/// <param name =""> Element to insert </param>
	/// <returns> New element array with inserted elements</returns>
    AcPpStringArray&       InsertAt        (int, const ACHAR *);

    // Removes array elements.
    //
	/// <summary> Removes the array element from the spefied position </summary>
	/// <param name =""> Location of the element to be removed </param>
	/// <returns> New element array with removed elements </returns>
    AcPpStringArray&       RemoveAt        (int);

	/// <summary> Removes the first array element </summary>
	/// <returns> New element array with removed elements </returns>
    AcPpStringArray&       RemoveFirst     ();

	/// <summary> Removes the last array element </summary>
	/// <returns> New element array with removed elements</returns>
    AcPpStringArray&       RemoveLast      ();

    // Queries about array elements.
    //
	/// <summary> Queries array elements </summary>
	/// <param name =""> Element to query</param>
	/// <param name =""> Starting position</param>
	/// <param name =""> Boolean to determine case sensitive search. </param>
	/// <returns> Returns true if present</returns>
    bool                   Contains        (const ACHAR *, 
                                            int start = 0,
                                            bool noCase = false) const;

	/// <summary> Queries array elements </summary>
	/// <param name =""> Element to Find</param>
	/// <param name =""> Position of the element in the array if found</param>
	/// <param name =""> Starting position</param>
	/// <param name =""> Boolean to determine case sensitive search.</param>	
	/// <returns> </returns>
    bool                   Find            (const ACHAR *, int& foundAt,
                                            int start = 0,
                                            bool noCase = false) const;

    // Array length operations.
    //
	/// <summary> Finds the length of the array </summary>
	/// <returns> Array length </returns>
    int                    Length          () const; // Logical length.

	/// <summary> Determines if the array is empty </summary>
 	/// <returns> Depends upon the array being empty or not</returns>
    bool                   IsEmpty         () const;

	/// <summary> </summary>
	/// <param name =""> </param>
	/// <returns> </returns>
    int                    LogicalLength   () const;

	/// <summary> </summary>
	/// <param name =""> </param>
	/// <returns> </returns>
    AcPpStringArray&       SetLogicalLength(int);

	/// <summary> </summary>
	/// <param name =""> </param>
	/// <returns> </returns>
    int                    PhysicalLength  () const;

	/// <summary> </summary>
	/// <param name =""> </param>
	/// <returns> </returns>
    AcPpStringArray&       SetPhysicalLength (int);

    // Automatic resizing.
    //
	/// <summary> Increases the array length </summary>
	/// <returns> </returns>
    int                    GrowLength      () const;

	/// <summary> Sets the increment of array length</summary>
	/// <param name =""> Increment by which the array should grow. </param>
	/// <returns> Incremented element array </returns>
    AcPpStringArray&       SetGrowLength   (int);

    // Utility.
    //
	/// <summary> Reverses the array </summary>
	/// <returns> Reversed array</returns>
    AcPpStringArray&       Reverse         ();

	/// <summary> Sorts the array </summary>
	/// <returns> Sorted array </returns>
    AcPpStringArray&       Sort            ();

	/// <summary> Treat array as simple array of const ACHAR** </summary>
	/// <returns> </returns>
    const ACHAR         **AsArrayPtr    () const;

protected:
    ACHAR           **mpArray;
    int                 mPhysicalLen;   // Actual buffer length.
    int                 mLogicalLen;    // Number of items in the array.
    int                 mGrowLen;       // Buffer grows by this value.

    bool                IsValid         (int) const;

	/// <summary> Sets element value at the specified position </summary>
	/// <param name ="iPosition"> Position in the array where the element value is to be set</param>
	/// <param name =""> Element value to be set</param>	
    void                SetItem         (int iPosition, const ACHAR * ch) ;

	/// <summary> </summary>
	/// <param name =""> </param>
	/// <returns> </returns>
    int                 FindPos         (const ACHAR * pStr, 
                                         int left, 
                                         int right) const;
};


// Inline methods.

inline bool
AcPpStringArray::Contains(const ACHAR *value, 
                           int start, 
                           bool noCase) const
{ int dummy; return Find(value, dummy, start, noCase); }

inline int
AcPpStringArray::Length() const
{ return mLogicalLen; }

inline bool
AcPpStringArray::IsEmpty() const
{ return mLogicalLen == 0; }

inline int
AcPpStringArray::LogicalLength() const
{ return mLogicalLen; }

inline int
AcPpStringArray::PhysicalLength() const
{ return mPhysicalLen; }

inline int
AcPpStringArray::GrowLength() const
{ return mGrowLen; }

inline const ACHAR **
AcPpStringArray::AsArrayPtr() const
{ return (const ACHAR **)mpArray; }

inline bool
AcPpStringArray::IsValid(int i) const
{ 
    if (i < 0 || i >= mLogicalLen)
    {
        throw 0 ;
    }
    else
    {
        return true ;
    }
}

inline const ACHAR *
AcPpStringArray::operator [] (int i)
{ IsValid(i); return mpArray[i]; }

inline const ACHAR *
AcPpStringArray::At(int i) const
{ IsValid(i); return mpArray[i]; }

inline const ACHAR *
AcPpStringArray::First() const
{ IsValid(0); return mpArray[0]; }

inline const ACHAR *
AcPpStringArray::Last() const
{ IsValid(mLogicalLen-1); return mpArray[mLogicalLen-1]; }

inline int
AcPpStringArray::Append(const ACHAR * str)
{ InsertAt(mLogicalLen, str); return mLogicalLen-1; }

inline AcPpStringArray&
AcPpStringArray::RemoveFirst()
{ IsValid(0) ; return RemoveAt(0); }

inline AcPpStringArray&
AcPpStringArray::SetGrowLength(int glen)
{ if (glen > 0)  mGrowLen = glen; return *this; }
