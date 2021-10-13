#ifndef __COMM_DEF_H__
#define __COMM_DEF_H__

#include "stdio.h"
#include <memory>
#include "systemc.h"
#include "tlm"
#include "tlm_utils/multi_passthrough_initiator_socket.h"
#include "string.h"
#include<vector>
#include <assert.h>

using namespace std;
using namespace tlm_utils;
using namespace tlm;


const int g_m_freq  = 100; //100M HZ
const int g_sport_num =4;
const int g_que_num =256;
const int cell_len  =64;
const int g_m_ipg_len =20;

typedef struct trans_type
{
   int  sid;
   int  did;
   int  pri;

   int  fsn;
   int  len;

   int  sport;
   int  dport;

 
   int  qid;
   int  fid;

   int  csn;
   int  vldl;
   bool eop;
   
    inline bool operator == (const trans_type& rhs) const
   {
     return (rhs.sid == sid && rhs.did == did && rhs.qid == qid && rhs.fsn == fsn && rhs.len == len && rhs.vldl == vldl
           &&rhs.pri == pri && rhs.fid == fid && rhs.eop == eop&& rhs.fsn == fsn && rhs.sport == sport&& rhs.dport == dport);
   }


   trans_type()
   {
      sid    =0;
      did    =0;     
      pri    =0;
      fsn    =0;
      len    =0;
      dport  =0;
      sport  =0;
      csn    =0;
      vldl   =0;  
      eop    =false;
   }
} PKT; 

typedef  std::shared_ptr<PKT>  pkt_ptr;

inline
ostream&
operator << ( ostream& os, const trans_type& /* a */ )
{
    os << "streaming of struct TRANS_STR not implemented";
    return os;
}


inline
void
#if defined(SC_API_VERSION_STRING)
    sc_trace( sc_trace_file* tf, const trans_type& a, const std::string& name )
#else
    sc_trace( sc_trace_file* tf, const trans_type& a, const sc_string& name )
#endif
{
  sc_trace( tf, a.sid, name + ".sport_id" );
  sc_trace( tf, a.did, name + ".dport_id" );
  sc_trace( tf, a.qid, name + ".que_id" );
  sc_trace( tf, a.fsn, name + ".packet_id" );
  sc_trace( tf, a.len, name + ".packet_len" );
  sc_trace( tf, a.vldl, name + ".valid_len" );
  sc_trace( tf, a.pri, name + ".pri_id" );
  sc_trace( tf, a.csn, name + ".csn" );
  sc_trace( tf, a.eop, name + ".eop" );


}



// 全局配置
class global_config_c
{
   public:
      int  m_freq;           //主频,单位MHZ
      int  m_inter_num;      //接口数
      int  m_sch_sel;        //调度器选择 0:SP 1:RR  2:WRR
      int  shape_value;      //限速值 单位Mbps
      int  stat_period;      //统计间隔，以us为单位


   global_config_c()
   {
      m_freq = g_m_freq;
      m_inter_num =g_sport_num; 
      m_sch_sel = 1;
      shape_value = 1000;
      stat_period = 10;        
//      sport_id_que[0][0] = 1;  
   }
}; 

class table_xid_to_qid
{
      public:
      map  <int, int>    Map_xid2qid;

      table_xid_to_qid()
      {
      }


};




#define  ASSERT(A)  (assert(A))



#endif