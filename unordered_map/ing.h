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
    sc_in          <int>                  clkcnt; 
    array <sc_in<PKT_STR>*,g_sport_num>   in_port;
 //output
//    sc_out         <PKT_STR>             out_cell_que;      

    void                                  main_process();
    void                                  rev_pkt_process();
    void                                  port_rr_sch_process();
    void                                  lut_process();
    void                                  pkt_to_cell_process();

    sc_signal     <PKT_STR>               s_port_sch_result;
    int                                   que_id   ;
    int                                   flow_id   ;
    int                                   pkt_tmp_len = 0 ;

    array <fifo,g_sport_num>              fifo_port;
    array <int,g_sport_num>               pkt_count_port; 
    array <int,g_sport_num>               infifo_count_port; 
    array <int,g_sport_num>               drop_count_port;

    RR_SCH                                *rr_sch;

    SC_CTOR(ing) 
    {
        rr_sch = new RR_SCH(g_sport_num) ;

        for(int i=0; i < g_sport_num; i++)
        {
            in_port[i] = new sc_in<PKT_STR>;

            pkt_count_port[i]     = 0;
            infifo_count_port[i]  = 0;
            drop_count_port[i]    = 0;
            fifo_port[i].full     = false;    
            fifo_port[i].empty    = true;
        }
  
        SC_METHOD(main_process);
        sensitive <<clkcnt;
     
 //       for(int i=0; i < g_sport_num; i++)
 //       {
 //         sensitive << *in_port[i];
 //       }

    }  
   
};
#endif