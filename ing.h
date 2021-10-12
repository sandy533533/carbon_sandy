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
#include "comm_func.h"

struct ing : sc_module {

 //input
    sc_in       <int>                clkcnt; 
    sc_in       <pkt>               *in_port0;
    sc_in       <pkt>               *in_port1;
    sc_in       <pkt>               *in_port2;
    sc_in       <pkt>               *in_port3;
    sc_in       <pkt>               *in_port_bcpu;
    sc_in       <pkt>               *in_port_mcpu;

 //output
    vector<sc_out<TRANS>*>          out_que;      

    void                            main_process();


     SC_CTOR(ing) 
     {

      in_port0 = new  sc_in<pkt>() ;



      string debug_file = string("ingress_sach_debug.log");
      m_bw_stat =new comm_stat_bw(m_cfg, debug_file,g_m_inter_num);


       SC_METHOD(main_process);
       sensitive << clk.pos();


   }  
   
};
#endif