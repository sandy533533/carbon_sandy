////////////////////////////////////////////////////////
// Project： SystemC carbon
// Module:   ing.cpp
// Description: Pkt to cell, look up table then enter the queue (Pkt转Cell，查表入队列)
// Group：
// Author: Sandy
// Date: 2021.10.11  new
// Hierarchy : --top
//             --|--ing.cpp
//    pktgen------>|ing-->sch-->pe-->eng|----->stat
////////////////////////////////////////////////////////

#include "ing.h"

void ing::main_process()
{
    rev_pkt_process();
    port_rr_sch_process();
    lut_process();
    pkt_to_cell_process();
}

void ing::rev_pkt_process()
{
    for(int i=0; i < g_sport_num; i++)
    {
        if (in_port[i]->event()) 
        {
	        pkt_count_port[i]++;
	        if (fifo_port[i].full == true) 
            {
                drop_count_port[i]++;
            }   
            else
            {
                fifo_port[i].pkt_in(in_port[i]->read());
                infifo_count_port[i]++;

            }
            cout << "rev_pkt_process..." <<  "port id: " << i << " pkts received: " <<  pkt_count_port[i]
                 << " pkts infifo: " <<  infifo_count_port[i] << " pkts dropped: " <<  drop_count_port[i]  << endl;       
        };  
                 
    }
}

void ing::port_rr_sch_process()
{

    for(int i=0; i < g_sport_num; i++)
    {
        if(fifo_port[i].empty == false)
        {
            rr_sch->set_que_valid(i ,true);    // que非空的时候才参与sch          
        }
        else
        {
            rr_sch->set_que_valid(i ,false);
        }
    } 

    int  rst_que = 0;
    bool rst_flag = rr_sch->get_sch_result(rst_que);

    if((rst_flag ==true)and (pkt_out_flag == 0))
    {   
        s_port_sch_result = fifo_port[rst_que].pkt_out();

        pkt_tmp_len = s_port_sch_result.len;

        pkt_out_flag = 1;

        cout << "port_rr_sch_process..."<< "sch rslt flag: " <<  rst_flag << " sch rslt que id : " <<  rst_que << endl;
    }   

}    


void ing::lut_process()
{
    int s_sid ;
    int s_did ;
    int s_pri ;
    s_sid = s_port_sch_result.sid;
    s_did = s_port_sch_result.did;
    s_pri = s_port_sch_result.pri ;

    has_rule_key_s hash_pkt_lut_key;

    hash_pkt_lut_key.sid= s_sid;
    hash_pkt_lut_key.did= s_did;
    hash_pkt_lut_key.pri= s_pri;

    if (pkt_out_flag == 1)
    {
        std::unordered_map<has_rule_key_s,int>::iterator iter= g_hash_rule_tab.find(hash_pkt_lut_key); 
      
        if(iter != g_hash_rule_tab.end())   
        {
           cout<<"Find, the value is "<<iter->second<<endl;  
           flow_id = iter->second;
           cout<<"Fid "<< flow_id <<endl;            
        } 

        flow_rule = g_flow_rule_tab[flow_id];  
        que_id = flow_rule.qid;        
        cout<<"que_id "<< que_id <<endl;
    }
}



void ing::pkt_to_cell_process()
{
  int  cell_sn ;
  PKT_STR  cell_trans ;
  cell_sn = 0;

  if(pkt_tmp_len >0)
    {
        while (pkt_tmp_len >=cell_len)
        {
            cell_trans = s_port_sch_result;
            cell_trans.qid = que_id;
            cell_trans.fid =flow_id;
            cell_trans.vldl =cell_len;            
            cell_trans.csn = cell_sn;
            cell_trans.eop = false;

 //           out_cell_que.write(cell_trans);
            pkt_tmp_len-=cell_len;
            cell_sn++;

            cout << "pkt_to_cell_process..." << "cell_trans  : fsn: " <<  cell_trans.fsn <<" sid: "<<cell_trans.sid <<" did: "<<cell_trans.did
                 <<" pri:"<<cell_trans.pri<<" qid: " <<  cell_trans.qid  << " fid: " <<  cell_trans.fid 
                 <<" vldl: " <<  cell_trans.vldl << " csn: " <<  cell_trans.csn<< " eop: " <<  cell_trans.eop << endl;

        }
        
        cell_trans = s_port_sch_result;
        cell_trans.qid = que_id;
        cell_trans.fid =flow_id;
        cell_trans.vldl =pkt_tmp_len;            
        cell_trans.csn = cell_sn;
        cell_trans.eop = true;
//      out_cell_que.write(cell_trans);

        pkt_tmp_len = 0;
        pkt_out_flag = 0;
        
        cout << "pkt_to_cell_process..." << "cell_trans  : fsn: " <<  cell_trans.fsn <<" sid: "<<cell_trans.sid <<" did: "<<cell_trans.did
                 <<" pri:"<<cell_trans.pri<<" qid: " <<  cell_trans.qid  << " fid: " <<  cell_trans.fid 
                 <<" vldl: " <<  cell_trans.vldl << " csn: " <<  cell_trans.csn<< " eop: " <<  cell_trans.eop << endl;

    }


}
