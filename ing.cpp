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
 
}

void ing::rev_pkt_process()
{

  int pkt_count_port0; 
  int pkt_count_port1;

  int drop_count_port0;
  int drop_count_port1;

   pkt_count_port0  = 0;
   pkt_count_port1  = 0;

   drop_count_port0 = 0;
   drop_count_port1 = 0;

    if (in_port0.event()) 
    {
	    pkt_count_port0++;
	    if (fifo_port0.full == true) 
        {
            drop_count_port0++;
        }   
        else
        {
            fifo_port0.pkt_in(in_port0.read());
        }
    };  

    if (in_port1.event()) 
    {
	    pkt_count_port1++;
	    if (fifo_port1.full == true) 
            drop_count_port1++;
        else 
            fifo_port1.pkt_in(in_port1.read());
    };  


   cout << endl << endl << "-------------------------------------------------------------------------------" << endl;
   cout << "End of rev_pkt_process..." << endl;
   cout << "Total number of port0 packets received: " <<  pkt_count_port0 << endl;
   cout << "Total number of port1 packets received: " <<  pkt_count_port0 << endl;
   cout << "Total number of packets dropped: " <<  drop_count_port0 << endl;
   cout << "Total number of packets dropped: " <<  drop_count_port1 << endl;
   cout << "-------------------------------------------------------------------------------" << endl;
  
}

void ing::port_rr_sch_process()
{

    if(fifo_port0.empty == false)
    {
        rr_sch->set_que_valid(0 ,true);    // que非空的时候才参与sch
    }
    else
    {
        rr_sch->set_que_valid(0 ,false);
    }

        if(fifo_port1.empty == false)
    {
        rr_sch->set_que_valid(1 ,true);    // que非空的时候才参与sch
    }
    else
    {
        rr_sch->set_que_valid(1 ,false);
    }


    int  rst_que =-1;
    bool rst_flag = rr_sch->get_sch_result(rst_que);

    if(rst_flag ==true)
    {   if (rst_que== 0) 
        {
   //         s_port_sch_result->write(fifo_port0..pkt_out()); 
            s_port_sch_result = fifo_port0.pkt_out();

        }
        else if (rst_que== 1) 
        {
//            s_port_sch_result->write(fifo_port1.pkt_out()); 
            s_port_sch_result = fifo_port1.pkt_out();

        }

    }
}    


void ing::lut_process()
{
  int sid ;
  sid = s_port_sch_result->sport.id;



}
