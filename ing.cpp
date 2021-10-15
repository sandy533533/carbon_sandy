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
        };  
       

        cout << endl << endl << "-------------------------------------------------------------------------------" << endl;
        cout << "End of rev_pkt_process..." << endl;
        cout << "port id ..." << i<< endl;       
        cout << "number of port" << i << " packets received: " <<  pkt_count_port[i] << endl;
        cout << "number of port" << i << " packets info: " <<  infifo_count_port[i] << endl;
        cout << "number of port" << i << " packets dropped: " <<  drop_count_port[i] << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
    }
}

void ing::port_rr_sch_process()
{
    for(int i=0; i < g_sport_num; i++)
    {
        if(fifo_port[i].empty == false)
        {
            rr_sch->set_que_valid(i ,true);    // que非空的时候才参与sch
            cout << "fifo_port"<< i <<" empty:" << fifo_port[i].empty << endl;
           
        }
        else
        {
            rr_sch->set_que_valid(i ,false);
        }
    } 

    int  rst_que = 0;
    bool rst_flag = rr_sch->get_sch_result(rst_que);

    if(rst_flag ==true)
    {   
        s_port_sch_result = fifo_port[rst_que].pkt_out();

    }

     cout << endl << endl << "-------------------------------------------------------------------------------" << endl;
     cout << "End of port_rr_sch_process..." << endl;
     cout << "rr sch result flag: " <<  rst_flag << endl;
     cout << "rr sch result que id : " <<  rst_que << endl;
     cout << endl << endl << "-------------------------------------------------------------------------------" << endl;

}    


void ing::lut_process()
{
    int sid ;
    int did ;
    int pri ;
    int lut_key ;
    sid = s_port_sch_result.read().sid;
    did = s_port_sch_result.read().did;
    pri = s_port_sch_result.read().pri ;

    lut_key = sid + did ;

    que_id = lut_key ;
    flow_id = lut_key*2 ; 
}



void ing::pkt_to_cell_process()
{
  int  pkt_tmp_len ;
  int  cell_sn ;
  PKT_STR  cell_trans ;

 
  cell_sn = 0;
  pkt_tmp_len = s_port_sch_result.read().len;

  if(pkt_tmp_len >=0)
    {
        while (pkt_tmp_len >=cell_len)
        {
            cell_trans = s_port_sch_result.read();
            cell_trans.qid = que_id;
            cell_trans.fid =flow_id;
            cell_trans.vldl =cell_len;            
            cell_trans.csn = cell_sn;
            cell_trans.eop = false;

 //           out_cell_que.write(cell_trans);
            pkt_tmp_len-=cell_len;
            cell_sn++;

        }
        
        cell_trans = s_port_sch_result.read();
        cell_trans.qid = que_id;
        cell_trans.fid =flow_id;
        cell_trans.vldl =pkt_tmp_len;            
        cell_trans.csn = cell_sn;
        cell_trans.eop = true;
//      out_cell_que.write(cell_trans);
        pkt_tmp_len = 0;
    }


}
