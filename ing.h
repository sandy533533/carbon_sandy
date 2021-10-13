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
#include "ing_com_func.h"

struct ing : sc_module {

 //input
    sc_in          <int>                clkcnt; 
    vector<sc_in   <PKT>>               in_port;
 //output
    sc_out         <PKT>                out_cell_que;      

    void                                main_process();
    void                                rev_pkt_process();
    void                                port_rr_sch_process();
    void                                lut_process();
    void                                pkt_to_cell_process();

    sc_signal     <PKT>                 s_port_sch_result;
    int                                 que_id   ;
    int                                 flow_id   ;

    vector        <fifo>                fifo_port;
 
 //   cell_shape_func                     *packet_to_cell_shape;
    RR_SCH                              *rr_sch;

 
    SC_CTOR(ing) 
    {
        in_port.resize(g_sport_num);
  
        for(int i=0; i < g_sport_num; i++)
        {
          fifo_port[i].full  = false;    
          fifo_port[i].empty = true;
        }
  
         SC_METHOD(main_process);
        
        for(int i=0; i < g_sport_num; i++)
        {
         sensitive << in_port[i];
        }

    }  
   
};
#endif