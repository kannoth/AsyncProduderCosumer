/*********************************************************************************
 * fpgaSM.h
 *
 *  Created on: July 8, 2016
 *      Author: Subash Kannoth
 *      E-mail: s_kannoth14@informatik.uni-kl.de
 *
 *	Description Mealy machine for transition of the Hardware producer 
 * thread
 *********************************************************************************/

#ifndef _FPGA_SM_HPS_H 
#define _FPGA_SM_HPS_H

#include "common.h"
// fpga side////////////////////////////////
typedef enum {	FPGA_IDLE = 0,
				DATACREATE = 1,
				DATAREADY = 2,
				END = 3
}fpgaStates_t;

typedef struct{
	boolean cAck;
	boolean dataPrepared;// From some porcess where data is prepared
}fpgaIpVect_t;

typedef struct{
	boolean dataValid;	
}fpgaOpVect_t;

typedef struct{
	fpgaStates_t state;
	fpgaOpVect_t op;	
}fpgaState_t;

typedef  fpgaState_t (*fpgaTxCallback)(fpgaStates_t pState, fpgaIpVect_t inp, void* buffer);

typedef struct{
	fpgaState_t state;
	fpgaTxCallback txn;	
}fpgasm_t;

fpgaState_t fpgaTxn(fpgaStates_t pState, fpgaIpVect_t inp, void* buffer);
void fpgaPrintState(fpgaState_t s, boolean cAck);
long random_at_most(long max);

long local_buffer_32;
extern long sh_buffer_rw;

boolean localcAck;

#endif
