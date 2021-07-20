#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_set_point "../tv/cdatafile/c.PID.autotvin_set_point.dat"
#define AUTOTB_TVOUT_set_point "../tv/cdatafile/c.PID.autotvout_set_point.dat"
// wrapc file define:
#define AUTOTB_TVIN_KP "../tv/cdatafile/c.PID.autotvin_KP.dat"
#define AUTOTB_TVOUT_KP "../tv/cdatafile/c.PID.autotvout_KP.dat"
// wrapc file define:
#define AUTOTB_TVIN_KI "../tv/cdatafile/c.PID.autotvin_KI.dat"
#define AUTOTB_TVOUT_KI "../tv/cdatafile/c.PID.autotvout_KI.dat"
// wrapc file define:
#define AUTOTB_TVIN_KD "../tv/cdatafile/c.PID.autotvin_KD.dat"
#define AUTOTB_TVOUT_KD "../tv/cdatafile/c.PID.autotvout_KD.dat"
// wrapc file define:
#define AUTOTB_TVIN_sample "../tv/cdatafile/c.PID.autotvin_sample.dat"
#define AUTOTB_TVOUT_sample "../tv/cdatafile/c.PID.autotvout_sample.dat"
// wrapc file define:
#define AUTOTB_TVOUT_return "../tv/cdatafile/c.PID.autotvout_ap_return.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_set_point "../tv/rtldatafile/rtl.PID.autotvout_set_point.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_KP "../tv/rtldatafile/rtl.PID.autotvout_KP.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_KI "../tv/rtldatafile/rtl.PID.autotvout_KI.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_KD "../tv/rtldatafile/rtl.PID.autotvout_KD.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_sample "../tv/rtldatafile/rtl.PID.autotvout_sample.dat"
#define AUTOTB_TVOUT_PC_return "../tv/rtldatafile/rtl.PID.autotvout_ap_return.dat"

class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  set_point_depth = 0;
  KP_depth = 0;
  KI_depth = 0;
  KD_depth = 0;
  sample_depth = 0;
  return_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{set_point " << set_point_depth << "}\n";
  total_list << "{KP " << KP_depth << "}\n";
  total_list << "{KI " << KI_depth << "}\n";
  total_list << "{KD " << KD_depth << "}\n";
  total_list << "{sample " << sample_depth << "}\n";
  total_list << "{ap_return " << return_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int set_point_depth;
    int KP_depth;
    int KI_depth;
    int KD_depth;
    int sample_depth;
    int return_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};

static void RTLOutputCheckAndReplacement(std::string &AESL_token, std::string PortName) {
  bool no_x = false;
  bool err = false;

  no_x = false;
  // search and replace 'X' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('X', 0);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
  no_x = false;
  // search and replace 'x' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('x', 2);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
}
extern "C" float PID_hw_stub_wrapper(float, float, float, float, float);

extern "C" float apatb_PID_hw(float __xlx_apatb_param_set_point, float __xlx_apatb_param_KP, float __xlx_apatb_param_KI, float __xlx_apatb_param_KD, float __xlx_apatb_param_sample) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;
    float AESL_return;
    {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_return);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > return_pc_buffer(1);
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "return");
  
            // push token into output port buffer
            if (AESL_token != "") {
              return_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {((char*)&AESL_return)[0*4+0] = return_pc_buffer[0].range(7, 0).to_int64();
((char*)&AESL_return)[0*4+1] = return_pc_buffer[0].range(15, 8).to_int64();
((char*)&AESL_return)[0*4+2] = return_pc_buffer[0].range(23, 16).to_int64();
((char*)&AESL_return)[0*4+3] = return_pc_buffer[0].range(31, 24).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
    AESL_transaction_pc++;
    return  AESL_return;
  }
static unsigned AESL_transaction;
static AESL_FILE_HANDLER aesl_fh;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
//set_point
aesl_fh.touch(AUTOTB_TVIN_set_point);
aesl_fh.touch(AUTOTB_TVOUT_set_point);
//KP
aesl_fh.touch(AUTOTB_TVIN_KP);
aesl_fh.touch(AUTOTB_TVOUT_KP);
//KI
aesl_fh.touch(AUTOTB_TVIN_KI);
aesl_fh.touch(AUTOTB_TVOUT_KI);
//KD
aesl_fh.touch(AUTOTB_TVIN_KD);
aesl_fh.touch(AUTOTB_TVOUT_KD);
//sample
aesl_fh.touch(AUTOTB_TVIN_sample);
aesl_fh.touch(AUTOTB_TVOUT_sample);
CodeState = DUMP_INPUTS;
// print set_point Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_set_point, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_set_point);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_set_point, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.set_point_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_set_point, __xlx_sprintf_buffer.data());
}
// print KP Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_KP, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_KP);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_KP, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.KP_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_KP, __xlx_sprintf_buffer.data());
}
// print KI Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_KI, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_KI);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_KI, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.KI_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_KI, __xlx_sprintf_buffer.data());
}
// print KD Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_KD, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_KD);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_KD, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.KD_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_KD, __xlx_sprintf_buffer.data());
}
// print sample Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_sample, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_sample);

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVIN_sample, s.append("\n")); 
  }
  tcl_file.set_num(1, &tcl_file.sample_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_sample, __xlx_sprintf_buffer.data());
}
CodeState = CALL_C_DUT;
float ap_return = PID_hw_stub_wrapper(__xlx_apatb_param_set_point, __xlx_apatb_param_KP, __xlx_apatb_param_KI, __xlx_apatb_param_KD, __xlx_apatb_param_sample);
CodeState = DUMP_OUTPUTS;
// print return Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_return, __xlx_sprintf_buffer.data());
  sc_bv<32> __xlx_tmp_lv = ((int*)&ap_return)[0];

    std::string s(__xlx_tmp_lv.to_string(SC_HEX));
    aesl_fh.write(AUTOTB_TVOUT_return, s.append("\n")); 
  
  tcl_file.set_num(1, &tcl_file.return_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_return, __xlx_sprintf_buffer.data());
}
CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
return ap_return;
}
