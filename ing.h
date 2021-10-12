////////////////////////////////////////////////////////
// Project： SystemC carbon
// Module:   ing.h
// Description: Pkt to cell, look up table then enter the queue (Pkt转Cell，查表入队列)
// Group：
// Author: Sandy
// Date: 2021.10.11  new
// Hierarchy : --top
//             --|--ing.h
//    pktgen------>|ing-->sch-->pe-->eng|----->stat
////////////////////////////////////////////////////////

#ifndef __ING_H__
#define __ING_H__

#include "comm_def.h"
//#include "comm_func.h"
#include "fifo.h"


struct ing : sc_module {

 //input
   sc_in       <int>                clkcnt; 
   sc_in       <pkt>                in_port0;
   sc_in       <pkt>                in_port1;
   sc_in       <pkt>                in_port2;
   sc_in       <pkt>                in_port3;
   sc_in       <pkt>                in_port_bcpu;
   sc_in       <pkt>                in_port_mcpu;

 //output
    vector<sc_out<pkt>>              out_cell_que;      

   void                            main_process();
   void                            rev_pkt_process();
   void                            port_rr_sch_process();
   void                            lut_process();
   void                            inque_process();

   sc_signal     <pkt>             s_port_sch_result;
 
   fifo                            fifo_port0;
   fifo                            fifo_port1;
   fifo                            fifo_port2;
   fifo                            fifo_port3;

 
   SC_CTOR(ing) 
   {
      out_cell_que.resize(g_que_num);
      fifo_port0.full  = false;
      fifo_port1.full  = false;
      fifo_port2.full  = false;
      fifo_port3.full  = false;
      fifo_port0.empty = true;
      fifo_port1.empty = true;
      fifo_port2.empty = true;
      fifo_port3.empty = true;

       SC_METHOD(main_process);
       sensitive << in_port0;
       sensitive << in_port1;
       sensitive << in_port2;
       sensitive << in_port3;
       sensitive << in_port_bcpu;
       sensitive << in_port_mcpu;

   }  
   
};
#endif