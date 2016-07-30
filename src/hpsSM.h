/*********************************************************************************
 * hpsSM.h
 *
 *  Created on: July 8, 2016
 *      Author: Subash Kannoth
 *      E-mail: s_kannoth14@informatik.uni-kl.de
 *
 *	Description Mealy machine for transition of the Software consumer thread
 * 
 *********************************************************************************/

#ifndef _HPS_SM_H 
#define _HPS_SM_H

#include "common.h"
// hps side///////////////////////////////////
typedef enum {	HPS_IDLE = 0,
				WAIT_FOR_VALID = 1,
				DATA_READ = 2,
				DATA_READ_ACK = 3
}hpsStates_t;

typedef struct{
	boolean dataReady;
	boolean readComplete;
}hpsIpVect_t;

typedef struct{
	boolean dataReadAck;	
}hpsOpVect_t;

typedef struct{
	hpsStates_t state;
	hpsOpVect_t op;	
}hpsState_t;

typedef  hpsState_t (*hpsTxCallback)(hpsStates_t pState, hpsIpVect_t inp, void* buffer);

typedef struct{
	hpsState_t state;
	hpsTxCallback txn;	
}hpssm_t;

hpsState_t hpsTxn(hpsStates_t pState, hpsIpVect_t inp, void* buffer);
void hpsPrintState(hpsState_t s, boolean readComplete);

extern long sh_buffer_rw;

boolean localreadComplete;

#endif
