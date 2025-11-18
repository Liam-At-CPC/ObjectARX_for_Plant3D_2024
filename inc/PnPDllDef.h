// $Header$
//  Copyright 2021 by Autodesk, Inc.  All rights reserved.
//
//  This computer source code and related instructions and comments 
//  are the unpublished confidential and proprietary information of 
//  Autodesk, Inc. and are protected under applicable copyright and 
//  trade secret law.  They may not be disclosed to, copied or used
//  by any third party without the prior written consent of Autodesk, Inc.
//

#pragma once

#ifdef PNIDOBJECTS_EXPORTS
#define PNIDOBJECTS_API __declspec(dllexport)
#else
#define PNIDOBJECTS_API __declspec(dllimport)
#endif

#ifdef PNPDATALINKS_EXPORTS
#define PNPDATALINKS_API __declspec(dllexport)
#else
#define PNPDATALINKS_API __declspec(dllimport)
#endif

#ifdef PNPCOMMONDBX_EXPORTS
#define PNPCOMMONDBX_API __declspec(dllexport)
#else
	#ifdef PNIDASSETTOOL_MODULE
		#define PNPCOMMONDBX_API
	#else
		#define PNPCOMMONDBX_API __declspec(dllimport)
	#endif // PNIDASSETTOOL_MODULE
#endif

#ifdef PNP3DOBJECTS_EXPORTS
	#define PNP3DOBJECTS_API __declspec(dllexport)
#else
	#ifdef PNP3DPARTTOOL_MODULE
		#define PNP3DOBJECTS_API
	#else
		#define PNP3DOBJECTS_API __declspec(dllimport)
	#endif // PNP3DPARTTOOL_MODULE
#endif

#ifdef PNP3DDATALINKS_EXPORTS
#define PNP3DDATALINKS_API __declspec(dllexport)
#else
#define PNP3DDATALINKS_API __declspec(dllimport)
#endif

#ifdef PNPDWG2DANNO_EXPORTS
#define PNPDWG2DANNO_API __declspec(dllexport)
#else
#define PNPDWG2DANNO_API __declspec(dllimport)
#endif