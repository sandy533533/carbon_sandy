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

     SC_CTOR(ing) 
     {

//      in_port0 = new  sc_in<pkt>() ;
//      in_port1 = new  sc_in<pkt>() ;
//      in_port2 = new  sc_in<pkt>() ;
//      in_port3 = new  sc_in<pkt>() ;
//      in_port_bcpu = new  sc_in<pkt>() ;
//      in_port_mcpu = new  sc_in<pkt>() ;

      out_que.resize(g_que_num);
//      for (int i=0;i<g_que_num;i++)
//      {
//         out_que[i] = new sc_out<pkt>() ;
//      }
   
//      s_port_sch_result = new  sc_signal<pkt>() ;

      SC_METHOD(main_process);
       sensitive << in_port0;
       sensitive << *in_port1;
       sensitive << *in_port2;
       sensitive << *in_port3;
       sensitive << *in_port_bcpu;
       sensitive << *in_port_mcpu;

   }  
   
};
#endif