
#ifndef __CLK_CNT_H__
#define SWITCH_CLK_H_INCLUDED

#include "systemc.h"

struct clk_cnt: sc_module {
      sc_out     <int>   out_clk_cnt;
      sc_in_clk          CLK;

      int                 cnt_clk ;

      SC_CTOR(clk_cnt)
        {
           cnt_clk = 0;
           SC_METHOD(entry);
           dont_initialize();
           sensitive << CLK.pos(); 
         }
     void entry();
};
#endif // SWITCH_CLK_H_INCLUDED
