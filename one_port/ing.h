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
 //   sc_in          <int>                clkcnt; 
    sc_in_clk                            clk;

    sc_in<PKT_STR>                      in_port;
 //output
 //   sc_out         <PKT_STR>             out_cell_que;      

    void                                main_process();
    void                                rev_pkt_process();
    void                                port_rr_sch_process();
    void                                lut_process();
    void                                pkt_to_cell_process();

    int                                 que_id   ;
    int                                 flow_id   ;
    int                                 pkt_count_port; 
    int                                 drop_count_port;

    fifo                                fifo_port;
    RR_SCH                              *rr_sch;
    sc_signal     <PKT_STR>             s_port_sch_result;

        
 
   SC_CTOR(ing) 
   {           
      fifo_port.full  = false;    
      fifo_port.empty = true;

      pkt_count_port = 0;
      drop_count_port = 0;

      rr_sch = new RR_SCH(1) ;

//        in_port.resize(g_sport_num);
//        fifo_port.resize(g_sport_num);
//
//        for(int i=0; i < g_sport_num; i++)
//        {
//          fifo_port[i].full  = false;    
//          fifo_port[i].empty = true;
//        }
  
         SC_METHOD(main_process);
 //        sensitive << clk.pos();
        sensitive << in_port;
;
    
 //       for(int i=0; i < g_sport_num; i++)
 //       {
 //        sensitive << in_port[i];
 //       }

    }  
   
};
#endif