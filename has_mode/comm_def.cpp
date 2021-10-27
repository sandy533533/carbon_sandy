////////////////////////////////////////////////////////
// Project： SystemC虚拟项目
// Module:   commdef
// Description: 全局定义文件
// Group：预研组
// Author: Newton
// Date: 2021.10.14 第一版
// Hierarchy : 编号，索引公共库
////////////////////////////////////////////////////////

#include "comm_def.h"

// 用于实现全局cycle_cnt计数

std::vector<s_flow_rule> g_flow_rule_tab;
std::unordered_map<s_hash_rule_key, int, has_rule_key_hash> g_hash_rule_tab;
std::vector<s_tab_que> g_que_rule_tab;
std::vector<s_tab_port> g_port_rule_tab;

bool TAB_CONFIG::InitMap(int tab_sid, int tab_did, int tab_pri, int tab_len, int tab_sport, int tab_dport,
                         int tab_fspeed, int tab_len2add, int tab_fid, int tab_qid) {
    s_hash_rule_key hash_rule_key_0;

    hash_rule_key_0.did = tab_did;
    hash_rule_key_0.sid = tab_sid;
    hash_rule_key_0.pri = tab_pri;

    int fid0 = tab_fid;
//数组方式：
#if 0 
    g_hash_rule_tab[hash_rule_key_0]= fid0;
    g_hash_rule_tab[hash_rule_key_1]= 16;
#endif
    // insert
    g_hash_rule_tab.insert(make_pair(hash_rule_key_0, fid0));
    int a = g_hash_rule_tab.size();
    (void)a;

    for (auto iter = g_hash_rule_tab.begin(); iter != g_hash_rule_tab.end(); ++iter) {
    }
    //调用 reserve() 成员函数来增加容器的容量
    s_flow_rule init_flow_rule_value;

    s_flow_rule flow_rule_value;
    flow_rule_value.sid = tab_sid;
    flow_rule_value.did = tab_did;
    flow_rule_value.len = tab_len;
    flow_rule_value.pri = tab_pri;
    flow_rule_value.sport = tab_sport;
    flow_rule_value.dport = tab_dport;
    flow_rule_value.qid = tab_qid;
    flow_rule_value.len2add = tab_len2add;
    flow_rule_value.flow_speed = tab_fspeed;

    //只对新增的size部分赋值
    g_flow_rule_tab.resize(fid0, init_flow_rule_value);
    g_flow_rule_tab.resize(fid0 + 1, flow_rule_value);

    return true;
}

////////////////////////////////////////////////////////
// Project： SystemC虚拟项目
// Module:   glb_cfg_c
// Description: glb_cfg_c 生成配置表格
// Group：预研组
// Author: Newton
// Date: 2021.10.14 第一版
// Hierarchy : 编号，索引公共库
////////////////////////////////////////////////////////
//glb_cfg_c::glb_cfg_c(std::string file_name)
//{
//    read_cfg_file(file_name);
//    gen_cfg_table();
//}
//
////////////////////////////////////////////////////////
// Project： SystemC虚拟项目
// Module:   mod_ing
// Description: read_cfg_file
// Group：预研组
// Author: Newton
// Date: 2021.10.14 第一版
// Hierarchy : 编号，索引公共库
////////////////////////////////////////////////////////
//void glb_cfg_c::read_cfg_file(std::string file_name)
//{
//    ifstream in_file(file_name.c_str());
//    if (!in_file.is_open()) {
//        cout << "cfg file error" << endl;
//        return;
//    }
//    std::string read_line;
//    int file_pos_status = -255; // 如果status =1,读取流表 status =2,读取HASH表  status =3,读取队列权重表  status =4,读取Port端口表
//    while (getline(in_file, read_line)) {
//        if (read_line.find("g_flow_rule_tab") != read_line.npos) // 标识符不写入
//        {
//            file_pos_status = 1;
//            continue;
//        } else if (read_line.find("g_hash_rule_tab") != read_line.npos) {
//            file_pos_status = 2;
//            continue;
//        } else if (read_line.find("g_que_rule_tab") != read_line.npos) {
//            file_pos_status = 3;
//            continue;
//        } else if (read_line.find("g_port_rule_tab") != read_line.npos) {
//            file_pos_status = 4;
//            continue;
//        }
//        // 根据状态填充表格
//        std::string tmp_value;
//        int index = 0;
//        char *split_char;
//        std::vector<int> tmp_value_vc;
//        const char *sep = " ";
//        char *line_str = new char[read_line.size() + 1];
//        strcpy(line_str, read_line.c_str());
//        // 获取第一个子字符串
//        split_char = strtok(line_str, sep);
//        while (split_char != NULL) {
//            //cout << split_char <<endl;
//            if ((index != 0) && (*split_char != '\r')) // 全面的标识符sid /did 等不写入
//            {
//                std::string tmp_str = std::string(split_char);
//                tmp_value_vc.push_back(stoi(tmp_str));
//            }
//            index++;
//            split_char = strtok(NULL, sep);
//        }
//        delete[] line_str;
//        if (file_pos_status == 1) {
//            g_flow_tab_relate.push_back(tmp_value_vc);
//        }
//        if (file_pos_status == 2) {
//            g_hash_tab_relate.push_back(tmp_value_vc);
//        }
//        if (file_pos_status == 3) {
//            g_que_tab_relate.push_back(tmp_value_vc);
//        }
//        if (file_pos_status == 4) {
//            g_port_tab_relate.push_back(tmp_value_vc);
//        }
//    }
//}
//
//////////////////////////////////////////////////////////
//// Project： SystemC虚拟项目
//// Module:   mod_ing
//// Description: gen_cfg_table
//// Group：预研组
//// Author: Newton
//// Date: 2021.10.14 第一版
//// Hierarchy : 编号，索引公共库
//////////////////////////////////////////////////////////
//void glb_cfg_c::gen_cfg_table()
//{
//    // 填充flow表格
//    if (g_flow_tab_relate.size() != 0) {
//        int flow_num = g_flow_tab_relate[0].size(); // index0对应fid号
//        // 填充真实flow表
//        for (int i = 0; i < flow_num; i++) {
//            s_flow_rule fill_flow_rule;
//            fill_flow_rule.sid = g_flow_tab_relate[1][i];        // index1对应sid号
//            fill_flow_rule.did = g_flow_tab_relate[2][i];        // index2对应did号
//            fill_flow_rule.pri = g_flow_tab_relate[3][i];        // index3对应pri
//            fill_flow_rule.len = g_flow_tab_relate[4][i];        // index4对应len
//            fill_flow_rule.sport = g_flow_tab_relate[5][i];      // index5对应sport号
//            fill_flow_rule.dport = g_flow_tab_relate[6][i];      // index6对应dport号
//            fill_flow_rule.qid = g_flow_tab_relate[7][i];        // index7对应qid号
//            fill_flow_rule.len2add = g_flow_tab_relate[8][i];    // index8对应len2add
//            fill_flow_rule.flow_speed = g_flow_tab_relate[9][i]; // index9对应flow_speed
//            g_flow_rule_tab.push_back(fill_flow_rule);
//        }
//    }
//
//    // 填充HASH表格
//    if (g_hash_tab_relate.size() != 0) {
//        int hash_rule_num = g_hash_tab_relate[0].size(); // index0对应key_sid
//        // 填充真实HASH表
//        for (int i = 0; i < hash_rule_num; i++) {
//            s_hash_rule_key fill_hash_key;
//            fill_hash_key.sid = g_hash_tab_relate[0][i]; // index0对应key_sid
//            fill_hash_key.did = g_hash_tab_relate[1][i]; // index0对应key_sid
//            fill_hash_key.pri = g_hash_tab_relate[2][i]; // index0对应key_sid
//            int fill_fid = g_hash_tab_relate[3][i];
//            g_hash_rule_tab.insert({fill_hash_key, fill_fid});
//        }
//    }
//
//    // 填充que表格
//    if (g_que_tab_relate.size() != 0) {
//        int que_num = g_que_tab_relate[0].size(); // index0对应que_id
//        // 填充真实que表
//        for (int i = 0; i < que_num; i++) {
//            int fill_weight = g_que_tab_relate[2][i]; // index2对应weight
//            g_que_rule_tab.push_back(fill_weight);
//        }
//    }
//
//    // 填充port表格
//    if (g_port_tab_relate.size() != 0) {
//        int port_num = g_port_tab_relate[0].size(); // index0对应port_id
//        // 填充真实port表
//        for (int i = 0; i < port_num; i++) {
//            int fill_speed = g_port_tab_relate[1][i]; // index1对应port speed
//            g_port_rule_tab.push_back(fill_speed);
//        }
//    }
//}

////////////////////////////////////////////////////////
// Project： SystemC虚拟项目
// Module:   comm_def
// Description: RR_SCH调度算法
// Group：预研组
// Author: Newton
// Date: 2021.10.14 第一版
// Hierarchy : 编号，索引公共库
////////////////////////////////////////////////////////
RR_SCH::RR_SCH(int tmp_que_num)
{
    que_num = tmp_que_num;
    que_status.resize(que_num, 0);
    sch_pos = 0;
}

void RR_SCH::set_que_valid(int que_id, bool valid_flag)
{
    if (que_id >= que_num) {
        cout << "error que_id" << que_id << endl;
    } else {
        que_status[que_id] = valid_flag;
    }
}

bool RR_SCH::get_sch_result(int &rst_que)
{
    int tmp_pos = sch_pos;
    for (int i = 0; i < que_num; i++) {
        tmp_pos = (sch_pos + i) % que_num;
        if (que_status[tmp_pos] == 1) {
            sch_pos = (tmp_pos + 1) % que_num;
            rst_que = tmp_pos;
            return true;
        }
    }
    return false;
}

///////////////////////////////////////////////////////
// Project： SystemC虚拟项目
// Module:   comm_def
// Description: WRR_SCH调度算法
// Group：预研组
// Author: Newton
// Date: 2021.10.14 第一版
// Hierarchy : 编号，索引公共库
////////////////////////////////////////////////////////
WRR_SCH::WRR_SCH(int tmp_que_num, vector<int> tmp_weight)
{
    assert(tmp_que_num > 0);

    que_num = tmp_que_num;
    if (tmp_weight.size() != (unsigned int)que_num) {
        cout << "cfg a wrong weight value" << endl;
        return;
    }
    que_status.resize(que_num, 0);
    init_weight = tmp_weight;
    cur_weight = tmp_weight;
    sch_pos = 0;
}

void WRR_SCH::set_que_valid(int que_id, bool valid_flag)
{
    if (que_id >= que_num) {
        cout << "error que_id" << que_id << endl;
    } else {
        que_status[que_id] = valid_flag;
    }
}

bool WRR_SCH::get_sch_result(int &rst_que)
{
    //如果所有队列weight 减为0，统一刷新
    bool update_weight_flag = true;
    for (int index = 0; index < que_num; index++) {
        if (cur_weight[index] > 0) {
            update_weight_flag = false;
            break;
        }
    }
    //如果全为0，reload value
    if (update_weight_flag == true) {
        reload_weight_value();
    }

    int tmp_pos = sch_pos;
    for (int i = 0; i < que_num; i++) {
        tmp_pos = (sch_pos + i) % que_num;
        if ((que_status[tmp_pos] == 1) && (cur_weight[tmp_pos] > 0)) {
            sch_pos = (tmp_pos + 1) % que_num;
            rst_que = tmp_pos;
            cur_weight[tmp_pos] -= 1; //扣权重
            return true;
        }
    }
    return false;
}

void WRR_SCH::reload_weight_value()
{
    cur_weight = init_weight;
}

////////////////////////////////////////////////////////
// Project： SystemC虚拟项目
// Module:   comm_def
// Description: SP调度算法
// Group：预研组
// Author: Newton
// Date: 2021.10.14 第一版
// Hierarchy : 编号，索引公共库
////////////////////////////////////////////////////////
SP_SCH::SP_SCH(int tmp_que_num)
{
    que_num = tmp_que_num;
    que_status.resize(que_num, 0);
    sch_pos = 0;
}

void SP_SCH::set_que_valid(int que_id, bool valid_flag)
{
    if (que_id >= que_num) {
        cout << "error que_id" << que_id << endl;
    } else {
        que_status[que_id] = valid_flag;
    }
}

void SP_SCH::set_que_hpri(int que_id)
{
    if (que_id >= que_num) {
        cout << "error que_id" << que_id << endl;
    } else {
        sch_pos = que_id;
    }
}

bool SP_SCH::get_sch_result(int &rst_que)
{
    int tmp_pos = sch_pos;
    if (que_status[tmp_pos] == 1) {
        rst_que = tmp_pos;
        return true;
    } else {
        for (int i = 0; i < que_num; i++) {
            tmp_pos = (sch_pos + i) % que_num;
            if (que_status[tmp_pos] == 1) {
                rst_que = tmp_pos;
                return true;
            }
        }
    }

    return false;
}




comm_shape_func::comm_shape_func(int shape_value, int tmp_cbs_value, int add_value, int fill_period) {
    cbs_value = tmp_cbs_value;
    token_value = add_value; //初始令牌
    fill_period = fill_period;
}

void comm_shape_func::add_token(int add_value) {
    token_value += add_value;
    if (token_value >= cbs_value) {
        token_value = cbs_value;
    }
}
void comm_shape_func::sub_token(int sub_value) {
    token_value -= sub_value;
}

bool comm_shape_func::shape_status(int packet_len) {
    if (token_value >= packet_len) {
        sub_token(packet_len);
        return true;
    } else {
        return false;
    }
}

