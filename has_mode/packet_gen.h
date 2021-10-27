

#ifndef __PACKET_GEN__
#define __PACKET_GEN__

#include "comm_def.h"
#include <map>
using namespace std;

class packet_gen_module : public sc_module {
public:
    // 二维数组，多端口的output接口，每个output都是sc_fifo_out类型的，格式是TRANS
    array<sc_out<s_pkt_desc> *, G_INTER_NUM> output;
    sc_in_clk clk;
    int m_cycle_cnt;
    int m_packet_id;
    SC_HAS_PROCESS(packet_gen_module);

    global_config_c *m_cfg;
//    comm_stat_bw *m_bw_stat;
    TAB_CONFIG *hash_tab_config;

public:
    // 成员函数声明
    packet_gen_module(sc_module_name name, global_config_c *glb_cfg);
    void packet_gen_process();
    vector<comm_shape_func *> packet_shape;
};

#endif