


#include "packet_gen.h"
//激励包长应从顶层获取，先配置固定256B，稍后再改
packet_gen_module::packet_gen_module(sc_module_name name, global_config_c *glb_cfg):sc_module(name)
{

    m_cycle_cnt =0;
    m_packet_id =0;
    m_cfg = glb_cfg;
    
 //   output.resize(g_sport_num);
 //   for(int i=0; i < g_sport_num; i++)
 //   {
 //       output[i] = new sc_out<PKT>;
 //   }
    //init shape
 //   packet_shape.resize(g_sport_num);
 //   for(int i=0; i < g_sport_num; i++)
 //   {
// comm_shape_func(int shape_value, int tmp_cbs_value, int add_value, int fill_period);
// shape_value  = 1000
// tmp_cbs_value = 最大筒深9620 
// add_value = 每次添加13个令牌  
// fill_period

        packet_shape = new comm_shape_func(1000, 9620, 13, 10);
 //   }
    
//stat
    string debug_file = string("packet_gen_debug.log");
    m_bw_stat =new comm_stat_bw(m_cfg, debug_file,g_sport_num);


    SC_METHOD(packet_gen_process);
    sensitive << clk.pos();

    

}
//发packet时的令牌目的是制造有带宽意义的packet
//packet_shape[i]->add_token(13);   -> ；指针变量
//vector<comm_shape_func *> packet_shape;  因为packet_shape定义的是指针，所以操作的时候是指针的操作
// 定义用指针，类似于dma，传递的是内存的指针地址，用的地方直接去指针地址取，从而不需要传递真实的数据，减少了内存的访问次数和数据多次在内存中的搬移。

void packet_gen_module::packet_gen_process()
{
   m_cycle_cnt++;  
//stat
    if((m_cycle_cnt !=0) && (m_cycle_cnt % (m_cfg->stat_period *100) ==0))
   {
       m_bw_stat->print_bw_info(m_cycle_cnt);
   }
   

   //填桶
    if((m_cycle_cnt !=0) &&(m_cycle_cnt % 10 ==0))    
    {
  //      for(int i=0; i < g_sport_num; i++)
  //      {
            packet_shape->add_token(13);  //10cc填充13个
   //     }    
    }
    
   //4端口轮询
   //没有 256B的payload，只是传递了len是256的信息，因为不关注payload的内容
 //  for(int i=0; i < g_sport_num; i++)
//   {
        if(packet_shape->shape_status(256)) //包长是否够  packet_shape获取hape_status(256)的指针地址，return是1，还是0 ？
        {
            m_packet_id++;  
            PKT_STR new_trans ;
            new_trans.fsn = m_packet_id;
            new_trans.sid = 1;
            new_trans.did = 2;
            new_trans.pri = 3;                                  
            new_trans.len = 1000;
            new_trans.qid = 0;
            new_trans.fid = 0;
            new_trans.vldl= 0;     
            new_trans.csn = 0;
            new_trans.eop = true;
            output.write(new_trans);

            //stat
            m_bw_stat->record_bw_info(0, new_trans.len, true);
//        }
   }   
}