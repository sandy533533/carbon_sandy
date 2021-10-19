#ifndef __COMM_DEF_H__
#define __COMM_DEF_H__

#include "stdio.h"
#include <memory>
#include <map>

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
const int g_que_num =  4;
const int cell_len  = 64;
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
     return (rhs.sid == sid && rhs.did == did && rhs.pri == pri &&rhs.fsn == fsn && rhs.len == len && rhs.sport == sport&& rhs.dport == dport
            &&rhs.qid == qid && rhs.fid == fid && rhs.csn == csn && rhs.vldl == vldl&&rhs.eop == eop);
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

      qid    =0;
      fid    =0;

      csn    =0;
      vldl   =0;  
      eop    =false;
   }
} PKT_STR; 

typedef  std::shared_ptr<PKT_STR>  pkt_ptr;

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
  sc_trace( tf, a.sid, name + ".sid" );
  sc_trace( tf, a.did, name + ".did" );
  sc_trace( tf, a.pri, name + ".pri" );

  sc_trace( tf, a.fsn, name + ".fsn" );
  sc_trace( tf, a.len, name + ".len" );

  sc_trace( tf, a.dport, name + ".dport" );
  sc_trace( tf, a.sport, name + ".sport" );

  sc_trace( tf, a.qid, name + ".qid" );
  sc_trace( tf, a.fid, name + ".fid" ); 

  sc_trace( tf, a.vldl, name + ".vldl");
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

//extern map<int flow_rule_s> g_flow_rule_tab;

struct  has_rule_key_s
{
   /* data */
   int sid;
   int did;
   int pri;

inline bool operator < (const has_rule_key_s& keys)const{
return !(keys.sid == sid && keys.did == did && keys.pri == pri);
};

   has_rule_key_s()
   {
      sid = -1;
      did = -1;
      pri = -1;
   }

};

extern std::map<has_rule_key_s,int> g_hash_rule_tab;
//typedef  std::map<has_rule_key_s,int> g_hash_rule_tab;
 
#define  ASSERT(A)  (assert(A))



#endif