// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		drivers.h
//		Purpose:	Hardware interface (Header)
//		Created:	21st September 2015
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#ifndef _DRIVERS_H
#define _DRIVERS_H

#define DRVKEY_RUN 			('R')
#define DRVKEY_STEP			('S')
#define DRVKEY_INTERRUPT	('I')

BYTE8 DRVIsPushButtonPressed(BYTE8 button);
BYTE8 DRVReadToggleSwitches(void);
void DRVReset(void);
void DRVEndFrame(void);
void DRVRefreshPanel(WORD16 address,BYTE8 data,BYTE8 status,BYTE8 intMode,BYTE8 halt,BYTE8 runMode);

#endif