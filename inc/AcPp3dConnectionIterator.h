//
// (C) Copyright 2008-2009 by Autodesk, Inc.
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

#include "AcPpDb3dPipeNetwork.h"
#include "PnPDllDef.h"

//-----------------------------------------------------------------------------
class AcPp3dImpConnectionIterator;

/// <summary>
/// This class is used to iterate a pipeline. During creation, the iterator 
/// caches a snapshot of the connection model and therefore is not affected by 
/// changes to the model in the drawing or data-cache.
/// </summary>
/// <remarks>
/// Iteration of the pipeline follows a path and queues encountered branches
/// for processing when the current path ends. All objects are therefore visited
/// while it is not guaranteed that the jump from one object to the next implies
/// a connection between the two objects.
/// </remarks>
///
class PNP3DOBJECTS_API AcPp3dConnectionIterator
{
private:

    // Disallow derivation and instance creation
    // outside of the newIterator() factories.
    //
    AcPp3dConnectionIterator();

public:

    // Class factories
    //

    /// <summary>
    /// Creates an instance of AcPp3dConnectionIterator.
    /// </summary>
    /// <param name="pair">Specifies the part and port to start from.</param>
    /// <param name="pIter">Reference variable to assign the new iterator to.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    /// <remarks>
    /// The <paramref cref="pIter"/> parameter must be freed by the caller.
    /// </remarks>
    ///
    static Acad::ErrorStatus newIterator(const AcPp3dPair& pair, 
                                         AcPp3dConnectionIterator*& pIter);

    /// <summary>
    /// Creates an instance of AcPp3dConnectionIterator.
    /// </summary>
    /// <param name="partId">Specifies a part to start from.</param>
    /// <param name="port">Specifies the port to start from.</param>
    /// <param name="pIter">Reference variable to assign the new iterator to.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    /// <remarks>
    /// The <paramref cref="pIter"/> parameter must be freed by the caller.
    /// </remarks>
    ///
    static Acad::ErrorStatus newIterator(const AcDbObjectId& partId, 
                                         const AcPp3dPort& port,
                                         AcPp3dConnectionIterator*& pIter);

    /// <summary>
    /// Creates an instance of AcPp3dConnectionIterator.
    /// </summary>
    /// <param name="partId">Specifies the part from.</param>
    /// <param name="pIter">Reference variable to assign the new iterator to.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    /// <remarks>
    /// The <paramref cref="pIter"/> parameter must be freed by the caller.
    /// </remarks>
    ///
    static Acad::ErrorStatus newIterator(const AcDbObjectId& partId, 
                                         AcPp3dConnectionIterator*& pIter);

    ~AcPp3dConnectionIterator();

    // Implementation
    //

    /// <summary>
    /// This function is used to determine if iteration is complete.
    /// </summary>
    /// <returns>Boolean where true means the iterator has reached the final position.</returns>
    ///
    bool done() const;

    /// <summary>
    /// This function is used to step the iterator to the next piping object.
    /// </summary>
    /// <param name="bValidateConnection">
    /// Optional boolean to indicate whether the connection should be validated.
    /// </param>
    /// <returns>Boolean where true means iterator position was advanced.</returns>
    /// <remarks>
    /// By default, the iterator follows the network topology using port names. If it is
	/// desirable to check port positions, then specify true for <paramref cref="bValidateConnection"/>.
    /// </remarks>
    ///
    bool next(bool bValidateConnection = false);

    /// <summary>
    /// This function is used to reset the iterator to the start position.
    /// </summary>
    /// <returns>Boolean that indicates if the function succeeded or not.</returns>
    ///
    bool start();

    /// <summary>
    /// This function is used to get the AcDbObjectId of the piping object at the
    /// current position of the iterator.
    /// </summary>
    /// <param name="objId">Reference of AcDbObjectId to assign.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    ///
    Acad::ErrorStatus getObjectId(AcDbObjectId& objId) const;

    /// <summary>
    /// This function is used to specify the start position where iteration begins.
    /// </summary>
    /// <param name="pair">Specifies a part and port to use as the starting point.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    /// <remarks>
    /// The <paramref cref="start"/> method is used to start iteration again.
    /// </remarks>
    ///
    Acad::ErrorStatus setStartPosition(const AcPp3dPair& pair);

    /// <summary>
    /// Used to specify the start position where iteration begins.
    /// </summary>
    /// <param name="partId">Specifies the part to start from.</param>
    /// <param name="port">Specifies the port to start from.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    /// <remarks>
    /// The <paramref cref="start"/> method is used to start iteration again.
    /// </remarks>
    ///
    Acad::ErrorStatus setStartPosition(const AcDbObjectId& partId, 
                                       const AcPp3dPort& port);
    
private:
    
    AcPp3dImpConnectionIterator*  m_pImp;
};