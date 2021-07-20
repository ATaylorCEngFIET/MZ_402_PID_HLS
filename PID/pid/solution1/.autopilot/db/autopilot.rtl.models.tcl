set SynModuleInfo {
  {SRCNAME PID MODELNAME PID RTLNAME PID IS_TOP 1
    SUBMODULES {
      {MODELNAME PID_faddfsub_32ns_32ns_32_5_full_dsp_1 RTLNAME PID_faddfsub_32ns_32ns_32_5_full_dsp_1 BINDTYPE op TYPE fsub IMPL fulldsp LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME PID_fmul_32ns_32ns_32_4_max_dsp_1 RTLNAME PID_fmul_32ns_32ns_32_4_max_dsp_1 BINDTYPE op TYPE fmul IMPL maxdsp LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME PID_fdiv_32ns_32ns_32_16_no_dsp_1 RTLNAME PID_fdiv_32ns_32ns_32_16_no_dsp_1 BINDTYPE op TYPE fdiv IMPL fabric LATENCY 15 ALLOW_PRAGMA 1}
      {MODELNAME PID_fcmp_32ns_32ns_1_2_no_dsp_1 RTLNAME PID_fcmp_32ns_32ns_1_2_no_dsp_1 BINDTYPE op TYPE fcmp IMPL auto LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME PID_control_s_axi RTLNAME PID_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
