#include <systemc>
#include <vector>
#include <iostream>
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_fixed.h"
using namespace std;
using namespace sc_dt;
class AESL_RUNTIME_BC {
  public:
    AESL_RUNTIME_BC(const char* name) {
      file_token.open( name);
      if (!file_token.good()) {
        cout << "Failed to open tv file " << name << endl;
        exit (1);
      }
      file_token >> mName;//[[[runtime]]]
    }
    ~AESL_RUNTIME_BC() {
      file_token.close();
    }
    int read_size () {
      int size = 0;
      file_token >> mName;//[[transaction]]
      file_token >> mName;//transaction number
      file_token >> mName;//pop_size
      size = atoi(mName.c_str());
      file_token >> mName;//[[/transaction]]
      return size;
    }
  public:
    fstream file_token;
    string mName;
};
extern "C" float PID(float, float, float, float, float, float, float);
extern "C" float apatb_PID_hw(float __xlx_apatb_param_set_point, float __xlx_apatb_param_KP, float __xlx_apatb_param_KI, float __xlx_apatb_param_KD, float __xlx_apatb_param_sample, float __xlx_apatb_param_ts, float __xlx_apatb_param_pmax) {
  // DUT call
  float ap_return = PID(__xlx_apatb_param_set_point, __xlx_apatb_param_KP, __xlx_apatb_param_KI, __xlx_apatb_param_KD, __xlx_apatb_param_sample, __xlx_apatb_param_ts, __xlx_apatb_param_pmax);
return ap_return;
}
