

#include "stdio.h"
#include <iostream>
#include "packet_gen.h"
#include "systemc.h"
#include "comm_def.h"
//#include "comm_func.h"
//#include "ing_com_func.h"

#include "ing.h"

using namespace std;


int sc_main(int argc, char *argv[])


{

   sc_clock                               clk        ("clk",100,SC_NS);  //100ns 对应10MHZ 

   sc_signal<PKT_STR>                     tmp_singal;  
   sc_signal          <int>               clkcnt; 

    
   global_config_c *glb_cfg = new global_config_c();


   packet_gen_module pkt_gen_mod("packet_gen", glb_cfg);
   pkt_gen_mod.clk(clk);

   ing ing_mod("u_ing");
   ing_mod.clkcnt(clkcnt);

     pkt_gen_mod.output(tmp_singal);
     ing_mod.in_port(tmp_singal);

  
   sc_start(1,SC_MS);

   return 0;
}