/*********************************************************************************
 * fpgaSM.c
 *
 *  Created on: July 8, 2016
 *      Author: Subash Kannoth
 *      E-mail: s_kannoth14@informatik.uni-kl.de
 *
 *	Description Mealy machine for transition of the Hardware producer 
 * thread
 *********************************************************************************/

#include "fpgaSM.h"

fpgaState_t fpgaTxn(fpgaStates_t pState, fpgaIpVect_t inp, void* buffer){
    fpgaState_t nxtState;
	switch(pState){
		case(FPGA_IDLE):{
			nxtState.op.dataValid = false;
			nxtState.state	= DATACREATE;
            local_buffer_32 = DATA_INVALID;
			return nxtState;
			break;
		}
        case(DATACREATE):{
			nxtState.op.dataValid = false;
            if (!(inp.cAck)){
                local_buffer_32 = random_at_most(10000000);// Generate randomn data
                printf("Data Produced = %ld \n",local_buffer_32);
            }
            nxtState.state = DATAREADY;
			return nxtState;
			break;
		}
		case(DATAREADY):{
			nxtState.op.dataValid = true;
            sh_buffer_rw = local_buffer_32; // Write data to shared buffer
            localcAck = inp.cAck;
            
            if (localcAck){
                nxtState.state = END;
            }else{
                nxtState.state = DATAREADY;
            }
			return nxtState;
			break;
		}
		case(END):{
			nxtState.op.dataValid = false;
            //local_buffer_32 = random_at_most(100);// Generate local data
            local_buffer_32 = DATA_INVALID; // Clears local buffer
			nxtState.state = DATACREATE;
			return nxtState;
			break;
		}
		default:{
			nxtState.op.dataValid = false;
            local_buffer_32 = DATA_INVALID; // Clears local buffer
			nxtState.state = FPGA_IDLE;
			return nxtState;
			break;
		}
	}
}



void fpgaPrintState(fpgaState_t s, boolean cAck){
	switch (s.state){
		case(FPGA_IDLE):{
            printf("@fpga -> IDLE , cAck = %d \n",cAck);
			break;
		}
		case(DATACREATE):{
            printf("@fpga -> DATACREATE , cAck = %d \n",cAck);
			break;
		}
		case(DATAREADY):{
            printf("@fpga -> DATAREADY , cAck = %d \n",cAck);
			break;
		}
		case(END):{
            printf("@fpga -> END , cAck = %d \n",cAck);
			break;
		}
	}
}


long random_at_most(long max) {
  unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

  long x;
  do {
   x = random();
  }
  // This is carefully written not to overflow
  while (num_rand - defect <= (unsigned long)x);

  // Truncated division is intentional
  return x/bin_size;
}

