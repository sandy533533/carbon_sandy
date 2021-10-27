
#include "clk_cnt.h"

void clk_cnt::entry()
 {
// 
 //    cout << "switch-clk start" << endl; 
      cnt_clk++;
      out_clk_cnt =cnt_clk;
 }

