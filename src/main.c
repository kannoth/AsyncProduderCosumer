/*********************************************************************************
 * main.c
 *
 *  Created on: July 8, 2016
 *      Author: Subash Kannoth
 *      E-mail: s_kannoth14@informatik.uni-kl.de
 *
 *	Description Mealy machine for transition of the Software consumer thread
 * 
 *********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>
#include "fpgaSM.h"
#include "hpsSM.h"


#define NUM_THREADS     2

long random_at_most(long max);
void *Consumer(void *threadid);
void *Producer(void *threadid);

int fpga_o_dataValid_sh;
int fpga_in_cAck_sh;
int hps_o_dataReadAck_sh;
int hps_in_readComplete;

int sh_dataReadAck;
long sh_buffer_rw;

int main (int argc, char *argv[])
{
    USEVAR(fpga_o_dataValid_sh);
    USEVAR(fpga_in_cAck_sh);
    USEVAR(hps_o_dataReadAck_sh);
    USEVAR(hps_in_readComplete);

    pthread_t producer_thread,consumer_thread;
    int rc;
    long t = 0;

    rc = pthread_create(&producer_thread, NULL, &Consumer, (void*)t);
    if (rc){
    	printf("ERROR; return code from pthread_create() is %d\n", rc);
    	exit(-1);
    }
    t = 1;
    rc = pthread_create(&consumer_thread, NULL, &Producer, (void*)t);
    if (rc){
    	printf("ERROR; return code from pthread_create() is %d\n", rc);
    	exit(-1);
    }
	 /////////////////////////////////////////////////////////////
	 /////////////////////////////////////////////////////////////
    /* Last thing that main() should do */
    pthread_exit(NULL);
 	// Thread  ////////////////////////////////////////////////
	return 0;
}


void *Producer(void *threadid){
	 printf("PRODUCER ..\n");
    long tid;
    //long ldata =0;
    tid = (long)threadid; if (tid){;}
	////////////////////////////////////
	fpgasm_t* sm = (fpgasm_t*) malloc( sizeof(fpgasm_t));
    fpgaState_t nextStates;
    fpgaIpVect_t ip;
	sm->txn = fpgaTxn;
    ip.dataPrepared = true;
    nextStates.state = FPGA_IDLE;
	do{

        //fpgaPrintState(nextStates, hps_o_dataReadAck_sh);
        nextStates = sm->txn(nextStates.state,ip,NULL);

        fpga_o_dataValid_sh = nextStates.op.dataValid;
        ip.cAck = hps_o_dataReadAck_sh;

        usleep(10);
	}while(1);
	free (sm);
	////////////////////////////////////
    pthread_exit(NULL);
}

void *Consumer(void *threadid){
    printf("CONSUMER ..\n");
    long tid;
    tid = (long)threadid; if (tid){;}
	////////////////////////////////////
 	hpssm_t* hpssm = (hpssm_t*) malloc( sizeof(hpssm_t));
    hpsState_t hpsnextStates;
    hpsIpVect_t hpsip;
	hpssm->txn = hpsTxn;
    hpsip.readComplete = true;
    hpsnextStates.state = HPS_IDLE;
	do{
        //hpsPrintState(hpsnextStates, fpga_o_dataValid_sh);
        hpsnextStates = hpssm->txn(hpsnextStates.state,hpsip, NULL);

        hps_o_dataReadAck_sh = hpsnextStates.op.dataReadAck;
        hpsip.dataReady = fpga_o_dataValid_sh;


        usleep(100000);
	}while(1);
	free(hpssm);
	////////////////////////////////////
    pthread_exit(NULL);
}

