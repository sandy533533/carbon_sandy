
#include "ing_com_func.h"

RR_SCH::RR_SCH(int tmp_que_num)
{
    que_num = tmp_que_num;
    que_status.resize(que_num,0);   //que-status is a vector ,size = que_num ,value = 0
    sch_pos = 0;
}

void RR_SCH::set_que_valid(int que_id, bool valid_flag)
{
    if(que_id >= que_num)
    {
        cout << "error rr que_id" << que_id <<endl;
    }
    else
    {
        que_status[que_id] = valid_flag;
    }
}

bool  RR_SCH::get_sch_result(int &rst_que)
{
    int tmp_pos = sch_pos;
    for (int i=0; i< que_num; i++)
    {
        tmp_pos = (sch_pos +i) % que_num;

        if(que_status[tmp_pos] == 1)
        {
            sch_pos =(tmp_pos +1) % que_num;
            rst_que = tmp_pos;
            return true;
        }
    }
    
    return false;
}


/*

cell_shape_func::cell_shape_func(int max_pkt_len)
{
    
    s_max_pkt_len = max_pkt_len;  //初始包长
}


void cell_shape_func::sub_len(int cell_len)
{

    pkt_tmp_len -=cell_len;
}

bool cell_shape_func::shape_status(int packet_len,int cell_len)
{
    if(pkt_tmp_len >=0)
    {
        if (pkt_tmp_len >=cell_len)
        {
            sub_len(cell_len);
            return cell_len;
        }
        else
        {
            sub_len(pkt_tmp_len);
            return pkt_tmp_len;

        }
    }
    else
    {
        return false;
    }
  
}
*/

void fifo::pkt_in(const PKT& data_pkt)
    {
      regs[pntr++] = data_pkt; empty = false;
      if (pntr == 4) full = true;      
    }

    PKT fifo::pkt_out()
    {
       PKT temp;
       temp = regs[0];
       if (--pntr == 0) empty = true;
       else 
	{ 
            regs[0] = regs[1];
	    regs[1] = regs[2];
	    regs[2] = regs[3];
        } 
      return(temp);  
    }
