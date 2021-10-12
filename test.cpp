

#include "stdio.h"
#include <iostream>
#include "packet_gen.h"
#include "systemc.h"
#include "comm_def.h"
#include "switch_top.h"

using namespace std;


int sc_main(int argc, char *argv[])


{

   sc_clock                             clk        ("clk",100,SC_NS);  //100ns 对应10MHZ 

   sc_signal<TRANS_STR>                 tmp_singal;  

    
   global_config_c *glb_cfg = new global_config_c();


   packet_gen_module pkt_gen_mod("packet_gen", glb_cfg);
   pkt_gen_mod.clk(clk);
   pkt_gen_mod.output(tmp_singal);

   switch_top switch_top_mod("u_switch_top");
   switch_top_mod.clk(clk);
   switch_top_mod.input(tmp_singal);

  
  
   sc_start(100,SC_MS);

   return 0;
}