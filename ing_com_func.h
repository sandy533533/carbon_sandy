#ifndef __ING_COM_FUNC_H__
#define __ING_COM_FUNC_H__
#include<vector>
#include "systemc.h"
#include "comm_def.h"

using namespace std;

struct fifo {

   PKT regs[4];
   bool full;
   bool empty;
   sc_uint<3> pntr;
  
   // constructor

   fifo()
    {
      full = false;
      empty = true;
      pntr = 0;
    }

  // methods
   
   void pkt_in(const PKT& data_pkt);
   
   PKT pkt_out();
};

class RR_SCH
{
    public:
        int que_num;
        int sch_pos;
        vector<int> que_status;
    public:
        RR_SCH(int tmp_que_num);
        void set_que_valid(int que_id, bool valid_flag);
        bool  get_sch_result(int &rst_que);

};


#endif
