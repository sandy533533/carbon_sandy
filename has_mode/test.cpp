

#include "stdio.h"
#include <iostream>
#include "packet_gen.h"
#include "systemc.h"
#include "comm_def.h"
#include "comm_func.h"
//#include "ing_com_func.h"
#include "clk_cnt.h"

#include "mod_ing.h"

using namespace std;

int sc_main(int argc, char *argv[])
{

    sc_clock clk("clk", 100, SC_NS); // 100ns 对应10MHZ
    sc_signal<int> clkcnt;

    array<sc_signal<s_pkt_desc> *, g_inter_num> tmp_singal;
    sc_signal<s_pkt_desc> tmp_singal1;

    global_config_c *glb_cfg = new global_config_c();

    packet_gen_module pkt_gen_mod("packet_gen", glb_cfg);
    pkt_gen_mod.clk(clk);

    mod_ing ing_mod("u_ing");
    ing_mod.clkcnt(clkcnt);

    clk_cnt clk_cnt_mode("clk_cnt");
    clk_cnt_mode.CLK(clk);
    clk_cnt_mode.out_clk_cnt(clkcnt);

    for (int i = 0; i < g_inter_num; i++)
    {
        tmp_singal[i] = new sc_signal<s_pkt_desc>;

        pkt_gen_mod.output[i]->bind(*tmp_singal[i]);
        ing_mod.in_port[i]->bind(*tmp_singal[i]);
    }

    ing_mod.out_cell_que(tmp_singal1);

    sc_start(40, SC_US);

    return 0;
}