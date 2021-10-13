

#ifndef __PACKET_GEN__
#define __PACKET_GEN__

#include "comm_def.h"
#include "comm_func.h"
#include <map>
using namespace std;

class packet_gen_module: public sc_module
{
  public: 
  // 二维数组，多端口的output接口，每个output都是sc_fifo_out类型的，格式是TRANS
    vector<sc_out<PKT>>    output;
    sc_in_clk clk;
    int m_cycle_cnt;
    int m_packet_id;
    SC_HAS_PROCESS(packet_gen_module);
    //SC_HAS_PROCESS提供参数化构造函数，可以带任意参数，但是必须有一个sc_module_name类型的参数，用于指定模块实例的名称
    //类的构造函数是类的一种特殊的成员函数，它会在每次创建类的新对象时执行。
    //构造函数的名称与类的名称是完全相同的，并且不会返回任何类型，也不会返回 void。构造函数可用于为某些成员变量设置初始值。
    
    //~SC_HAS_PROCESS()  : 析构函数，释放构造函数的它会在每次删除所创建的对象时执行。
    //析构函数的名称与类的名称是完全相同的，只是在前面加了个波浪号（~）作为前缀，它不会返回任何值，也不能带有任何参数。
    //析构函数有助于在跳出程序（比如关闭文件、释放内存等）前释放资源。

    global_config_c            *m_cfg;
    comm_stat_bw               *m_bw_stat;
    
  public:
  // 成员函数声明
    packet_gen_module(sc_module_name name, global_config_c *glb_cfg);
    void packet_gen_process();
    vector<comm_shape_func *> packet_shape;
    

};
 

#endif