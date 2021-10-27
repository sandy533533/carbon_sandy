#ifndef __COMM_DEF_H__
#define __COMM_DEF_H__

#include <stdio.h>
#include <memory>
#include <string.h>
#include <sstream>
#include <array>
#include <vector>
#include <deque>
#include <map>
#include <unordered_map>
#include <assert.h>
#include "systemc.h"
using namespace std;
////////////////////////////////////////////////////////
// Project： SystemC虚拟项目
// Module:   commdef
// Description: 全局定义文件
// Group：预研组
// Author: Newton
// Date: 2021.10.14 第一版
// Hierarchy : 编号，索引公共库
////////////////////////////////////////////////////////

const int G_FREQ = 100; //100M HZ
const int G_INTER_NUM = 4;
const int G_QUE_NUM = 16;
const int G_CELL_LEN = 64;

enum DESC_TYPE
{
    DESC_TYPE_NULL = -1,
    DESC_TYPE_PKT = 0,
    DESC_TYPE_CELL = 1
};

struct s_pkt_desc
{
    int type; // 0 packet 1 cell
    int fid;  // flow id，对应Flow号，和激励对应
    int sid;  // 用于三元组匹配
    int did;  // 用于三元组匹配
    int fsn;
    int len;   // 包长度
    int pri;   // 报文优先级
    int sport; // 源端口号，与ing入口侧端口对应
    int dport; // 目的端口号，与engress出口侧端口对应
    int qid;   // queue 号，队列号，对应ing/sch里的que号
    int vldl;  // 有效报文长度，只有cell状态下有意义
    int csn;   // cell切片号， 只有cell状态下有意义
    int sop;   // 首切片，只有cell状态下有意义
    int eop;   // 尾切片，只有cell状态下有意义

    s_pkt_desc():
        type(DESC_TYPE_NULL),
        fid(-1),
        sid(-1),
        did(-1),
        fsn(-1),
        len(-1),
        pri(-1),
        sport(-1),
        dport(-1),
        qid(-1),
        vldl(-1),
        csn(-1),
        sop(-1),
        eop(-1)
    {
    }

    inline bool operator==(const s_pkt_desc &rhs) const
    {
        return ((rhs.type == type) && (rhs.fid == fid) && (rhs.sid == sid)
                && (rhs.did == did) && (rhs.fsn == fsn) && (rhs.len == len)
                && (rhs.pri == pri) && (rhs.sport == sport) && (rhs.dport == dport)
                && (rhs.qid == qid) && (rhs.vldl == vldl) && (rhs.csn == csn)
                && (rhs.sop == sop) && (rhs.eop == eop));
    }
};

inline ostream &operator<<(ostream &os, const s_pkt_desc &a /* a */)
{
    os << "[type:" << a.type;
    os << ",fid:" << a.fid;
    os << ",sid:" << a.sid;
    os << ",did:" << a.did;
    os << ",fsn:" << a.fsn;
    os << ",len:" << a.len;
    os << ",pri:" << a.pri;
    os << ",sport:" << a.sport;
    os << ",dport:" << a.dport;
    os << ",qid:" << a.qid;
    os << ",vldl:" << a.vldl;
    os << ",csn:" << a.csn;
    os << ",sop:" << a.sop;
    os << ",eop:" << a.eop << "]" << endl;
    return os;
}

//inline void sc_trace(sc_trace_file *tf, const s_pkt_desc &a, const std::string &name)
//{
//    sc_trace(tf, a.sport, name + ".data");
//}
inline void
#if defined(SC_API_VERSION_STRING)
sc_trace(sc_trace_file *tf, const s_pkt_desc &a, const std::string &name)
#else
sc_trace(sc_trace_file *tf, const s_pkt_desc &a, const sc_string &name)
#endif
{
    sc_trace(tf, a.type, name + ".type");
    sc_trace(tf, a.fid, name + ".fid");
    sc_trace(tf, a.sid, name + ".sid");
    sc_trace(tf, a.did, name + ".did");
    sc_trace(tf, a.fsn, name + ".fsn");
    sc_trace(tf, a.len, name + ".len");
    sc_trace(tf, a.pri, name + ".pri");
    sc_trace(tf, a.sport, name + ".sport");
    sc_trace(tf, a.dport, name + ".dport");
    sc_trace(tf, a.qid, name + ".qid");
    sc_trace(tf, a.vldl, name + ".vldl");
    sc_trace(tf, a.csn, name + ".csn");
    sc_trace(tf, a.sop, name + ".sop");
    sc_trace(tf, a.eop, name + ".eop");
}

// fid映射规则表内容
struct s_flow_rule
{
    int sid;
    int did;
    int len;
    int pri;
    int sport;
    int dport;
    int qid;
    int len2add;
    int flow_speed;

    s_flow_rule():
        sid(-1),
        did(-1),
        len(-1),
        pri(-1),
        sport(-1),
        dport(-1),
        qid(-1),
        len2add(-1),
        flow_speed(-1)
    {
    }
};

//hash规则表KEY值
struct s_hash_rule_key
{
    int sid;
    int did;
    int pri;

    s_hash_rule_key():
        sid(-1),
        did(-1),
        pri(-1)
    {
    }

    inline bool operator==(const s_hash_rule_key &rhs) const
    {
        return (rhs.sid == sid && rhs.did == did && rhs.pri == pri);
    }

    inline bool operator<(const s_hash_rule_key &rhs) const
    {
        return !(rhs.sid == sid && rhs.did == did && rhs.pri == pri);
    }
};

struct has_rule_key_hash
{
    std::size_t operator()(const s_hash_rule_key &key) const
    {
        return key.sid ^ key.did ^ key.pri;
    }
};

// 定义两个别名，用于que队列表和port端口表
typedef int s_tab_que;
typedef int s_tab_port;

// fid映射规则表项,key fid,查表得到映射表
extern std::vector<s_flow_rule> g_flow_rule_tab;
// Hash规则表项，查表得到fid号
extern std::unordered_map<s_hash_rule_key, int, has_rule_key_hash> g_hash_rule_tab;

// que_rule规则表项，查表得到rr_weight权重,key为qid号
extern std::vector<s_tab_que> g_que_rule_tab;

// port_rule规则表项，查表得到port_speed号,key为port号
extern std::vector<s_tab_port> g_port_rule_tab;

//产生全局时钟计数器
extern int g_cycle_cnt;

//产生全局配置
//class glb_cfg_c
//{
//public:
//    glb_cfg_c(std::string file_name);
//    void read_cfg_file(std::string file_name);
//    void gen_cfg_table();
//
//public:
//    std::vector<std::vector<int>> g_flow_tab_relate; //两维度；其中第一维是表项深度（包括key和value项），二维是index及value的横向展开
//    std::vector<std::vector<int>> g_hash_tab_relate; //两维度；其中第一维是表项深度（包括key和value项），二维是index及value的横向展开
//    std::vector<std::vector<int>> g_que_tab_relate;  //两维度；其中第一维是表项深度（包括key和value项），二维是index及value的横向展开
//    std::vector<std::vector<int>> g_port_tab_relate; //两维度；其中第一维是表项深度（包括key和value项），二维是index及value的横向展开
//};

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
      m_freq = G_FREQ;
      m_inter_num =G_INTER_NUM; 
      m_sch_sel = 1;
      shape_value = 1000;
      stat_period = 10;        
//      sport_id_que[0][0] = 1;  
   }
}; 


//公共调度器函数
class WRR_SCH
{
public:
    int que_num;
    int sch_pos;
    std::vector<int> que_status;
    std::vector<int> init_weight;
    std::vector<int> cur_weight;

public:
    WRR_SCH(int tmp_que_num, std::vector<int> tmp_weight);
    void set_que_valid(int que_id, bool valid_flag);
    bool get_sch_result(int &rst_que);
    void reload_weight_value();
};
class RR_SCH
{
public:
    int que_num;
    int sch_pos;
    std::vector<int> que_status;

public:
    RR_SCH(int tmp_que_num);
    void set_que_valid(int que_id, bool valid_flag);
    bool get_sch_result(int &rst_que);
};

class SP_SCH
{
public:
    int que_num;
    int sch_pos;
    std::vector<int> que_status;

public:
    SP_SCH(int tmp_que_num);
    void set_que_valid(int que_id, bool valid_flag);
    void set_que_hpri(int que_id);
    bool get_sch_result(int &rst_que);
};


class TAB_CONFIG 
{
    public:
	bool InitMap(int tab_sid, int tab_did, int tab_pri, int tab_len,int tab_sport,int tab_dport,int tab_fspeed,int tab_len2add,int tab_fid,int tab_qid);
};



class comm_shape_func
{
    //令牌填充10CC填充13个Byte，这算速率13*8*100M=1.04G,如果当前桶内令牌数>=包长,则允许报文发出，同时扣除相应令牌数，
    //如果令牌小于包长,则不允许发出，令牌周期性的填充，最大填充桶深为CBS
    public:
       int cbs_value;
       int token_value;
       int fill_period;
    
    public:
       comm_shape_func(int shape_value, int tmp_cbs_value, int add_value, int fill_period);
       void add_token(int add_value);     //单位Byte
       void sub_token(int sub_value);     //单位Byte
       bool shape_status(int packet_len); //单位Byte


};

#define ASSERT(A) (assert(A))

#endif //__COMM_DEF_H__
