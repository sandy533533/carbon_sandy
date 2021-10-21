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

#ifndef __MOD_ING_H__
#define __MOD_ING_H__

#include "comm_def.h"
#include "comm_func.h"

struct mod_ing : sc_module {

    public:

        sc_in          <int>                     clkcnt; 
        array <sc_in<s_pkt_desc>*,g_inter_num>   in_port;
 //output
        sc_out         <s_pkt_desc>              out_cell_que;     
        
    public:    

        mod_ing(sc_module_name name);
        SC_HAS_PROCESS(mod_ing);
   
        void                                     main_process();
        void                                     rev_pkt_process();
        void                                     port_rr_sch_process();
        void                                     lut_process();
        void                                     pkt_to_cell_process();
        RR_SCH                                   *rr_sch;

    private :    

        s_pkt_desc                               s_port_sch_result;
        int                                      que_id   ;
        int                                      flow_id   ;
        int                                      pkt_tmp_len = 0 ;
        int                                      pkt_out_flag = 0 ;
        s_flow_rule                              flow_rule;

       
 //       array <fifo,g_inter_num>                 fifo_port;
        array <deque<s_pkt_desc>,g_inter_num>    fifo_port;

        array <int,g_inter_num>                  pkt_count_port; 
        array <int,g_inter_num>                  infifo_count_port; 
        array <int,g_inter_num>                  drop_count_port;
   

};
   
#endif