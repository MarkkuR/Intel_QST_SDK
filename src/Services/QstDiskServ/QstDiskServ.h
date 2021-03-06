/****************************************************************************/
/*                                                                          */
/*  Module:         QstDiskServ.h                                           */
/*                                                                          */
/*  Description:    Provides  the  necessary  definitions  for  a  Windows  */
/*                  service  that  regularly  obtains temperature readings  */
/*                  from Hard Drives that  expose  their  temperature  via  */
/*                  S.M.A.R.T.  technology  and delivers these readings to  */
/*                  the Intel(R) Quiet System Technology  (QST)  Subsystem  */
/*                  for processing.                                         */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/*     Copyright (c) 2005-2009, Intel Corporation. All Rights Reserved.     */
/*                                                                          */
/*  Redistribution and use in source and binary  forms,  with  or  without  */
/*  modification, are permitted provided that the following conditions are  */
/*  met:                                                                    */
/*                                                                          */
/*    - Redistributions of source code must  retain  the  above  copyright  */
/*      notice, this list of conditions and the following disclaimer.       */
/*                                                                          */
/*    - Redistributions  in binary form must reproduce the above copyright  */
/*      notice, this list of conditions and the  following  disclaimer  in  */
/*      the   documentation  and/or  other  materials  provided  with  the  */
/*      distribution.                                                       */
/*                                                                          */
/*    - Neither the name  of  Intel  Corporation  nor  the  names  of  its  */
/*      contributors  may  be  used to endorse or promote products derived  */
/*      from this software without specific prior written permission.       */
/*                                                                          */
/*  DISCLAIMER: THIS SOFTWARE IS PROVIDED BY  THE  COPYRIGHT  HOLDERS  AND  */
/*  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  */
/*  BUT  NOT  LIMITED  TO,  THE  IMPLIED WARRANTIES OF MERCHANTABILITY AND  */
/*  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN  NO  EVENT  SHALL  */
/*  INTEL  CORPORATION  OR  THE  CONTRIBUTORS  BE  LIABLE  FOR ANY DIRECT,  */
/*  INDIRECT, INCIDENTAL, SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL  DAMAGES  */
/*  (INCLUDING,  BUT  NOT  LIMITED  TO, PROCUREMENT OF SUBSTITUTE GOODS OR  */
/*  SERVICES; LOSS OF USE, DATA, OR  PROFITS;  OR  BUSINESS  INTERRUPTION)  */
/*  HOWEVER  CAUSED  AND  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,  */
/*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING  */
/*  IN  ANY  WAY  OUT  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  */
/*  POSSIBILITY OF SUCH DAMAGE.                                             */
/*                                                                          */
/****************************************************************************/

#ifndef _QSTDISKSERV_H
#define _QSTDISKSERV_H

#include "../../Include/Build.h"

/****************************************************************************/
/* Version Definitions                                                      */
/****************************************************************************/

// Component Version and definitions

#define VER_MAJOR                    1
#define VER_MAJOR_STR               "1"
#define VER_MINOR                    0
#define VER_MINOR_STR               "0"
#define VER_HOTFIX                   0
#define VER_HOTFIX_STR              "0"

#define PROGRAM_VERSION             VER_MAJOR, VER_MINOR, VER_HOTFIX, VER_BUILD

#ifdef _DEBUG
#define PROGRAM_VERSION_STR         VER_MAJOR_STR "." VER_MINOR_STR "." VER_HOTFIX_STR "." VER_BUILD_STR " (DBG)"
#else
#define PROGRAM_VERSION_STR         VER_MAJOR_STR "." VER_MINOR_STR "." VER_HOTFIX_STR "." VER_BUILD_STR
#endif

/****************************************************************************/
/* Configuration Definitions                                                */
/****************************************************************************/

#undef  BREAK_ON_SERVICE_INITIATE               // We're not debugging
#undef  BREAK_ON_UTILITY_INITIATE               // We're not debugging

/****************************************************************************/
/* Miscellaneous Definitions                                                */
/****************************************************************************/

#define NO_RESULT_AVAIL             -1          // Indicates function failure
#define NO_TEMP_AVAIL               -1000       // Indicates GetSmartTemp() failed

/****************************************************************************/
/* Prototypes for Functions in Support Modules                              */
/****************************************************************************/

// Module SmartTemp.c

int     InitSmartTemp( void );                  // Returns # HDs exposing temps
void    DoneSmartTemp( void );                  // Cleans up facility
int     GetSmartTemp( int iIndex );             // Returns HD's temp reading
int     GetSmartIndex( int iIndex );            // Returns HD's physical index
BOOL    GetSmartModel( int iIndex, char *pszModel ); // Returns HD's model string

// Module VtmUpdate.c

int     InitVtmUpdate( void );                  // Returns # VTMs for HD monitoring
void    DoneVtmUpdate( void );                  // Cleans up facility
int     GetVtmIndex( int iIndex );              // Returns QST TM index for VTM
BOOL    PutVtmTemp( int iIndex, int iTemp );    // Sends temp reading to a VTM
BOOL    PutVtmStop( int iIndex );               // Sends no-readings msg to VTM

#endif // ndef _QSTDISKSERV_H

