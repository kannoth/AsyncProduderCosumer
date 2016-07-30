/*********************************************************************************
 * hpsSM.c
 *
 *  Created on: July 8, 2016
 *      Author: Subash Kannoth
 *      E-mail: s_kannoth14@informatik.uni-kl.de
 *
 *	Description Mealy machine for transition of the Software consumer thread
 * 
 *********************************************************************************/

#include "hpsSM.h"

hpsState_t hpsTxn(hpsStates_t pState, hpsIpVect_t inp, void* buffer){
	hpsState_t nxtState;
	switch(pState){
		case(HPS_IDLE):{
			nxtState.op.dataReadAck = false;
			nxtState.state	= WAIT_FOR_VALID;
			return nxtState;
			break;
		}
		case(WAIT_FOR_VALID):{
			nxtState.op.dataReadAck = false;
			if (inp.dataReady){
				nxtState.state = DATA_READ;
			}else{
				nxtState.state = WAIT_FOR_VALID;
			}
			return nxtState;
			break;
		}
		case(DATA_READ):{
            nxtState.op.dataReadAck = false;

            localreadComplete = inp.readComplete;

            if (localreadComplete){
                nxtState.state = DATA_READ_ACK;
            }else{
                nxtState.state = DATA_READ;
            }
            return nxtState;
			break;
		}
		case(DATA_READ_ACK):{
            if (sh_buffer_rw != DATA_INVALID){
                printf("Data Consumed = %ld \n",sh_buffer_rw);
            }
            nxtState.op.dataReadAck = true;
			nxtState.state = WAIT_FOR_VALID;
			return nxtState;
			break;
		}
		default:
			nxtState.op.dataReadAck = false;
			nxtState.state = HPS_IDLE;
			return nxtState;
			break;
	}
}


void hpsPrintState(hpsState_t s, boolean readComplete ){
	switch (s.state){
		case(HPS_IDLE):{
            printf("@hps    <-  HPS_IDLE , readComplete = %d \n",readComplete);
			break;
		}
		case(WAIT_FOR_VALID):{
            printf("@hps    <-  WAIT_FOR_VALID , readComplete = %d \n",readComplete);
			break;
		}
		case(DATA_READ):{
            printf("@hps    <-  DATA_READ , readComplete = %d \n",readComplete);
			break;
		}
		case(DATA_READ_ACK):{
            printf("@hps    <-  DATA_READ_ACK , readComplete = %d \n",readComplete);
			break;
		}
	}
}
