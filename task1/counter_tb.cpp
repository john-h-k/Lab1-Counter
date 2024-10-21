#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "../vbuddy.cpp"

int main(int argc, char **argv, char **env) {
  int i;
  int clk;

  Verilated::commandArgs(argc, argv);
  // init top verilog instance
  Vcounter *top = new Vcounter;
  // init trace dump
  Verilated::traceEverOn(true);
  VerilatedVcdC *tfp = new VerilatedVcdC;
  top->trace(tfp, 99);
  tfp->open("counter.vcd");

  if (vbdOpen() != 1) {
    return -1;
  }

  vbdHeader("Lab 1: Counter");

  // initialize simulation inputs
  top->clk = 1;
  top->rst = 1;
  top->en = 0;
  // run simulation for many clock cycles
  for (i = 0; i < 300; i++) {
    // dump variables into VCD file and tog
    for (clk = 0; clk < 2; clk++) {
      tfp->dump(2 * i + clk);
      // unit is
      top->clk = !top->clk;
      top->eval();
    }

    // int shifts[4] = { 0, 4, 8, 16 };
    // for (int j = 4; j > 0; j--) {
    //   vbdHex(i, (int(top->count) >> (shifts[j - 1])) & 0xF);
    // }
    vbdPlot(int(top->count), 0, 255);
    vbdCycle(i + 1);

    top->rst = (i < 2) | (i == 15);
    top->en = vbdFlag();
    // top->en = (i > 4);
    if (Verilated::gotFinish()) {
      exit(0);
    }
  }

  vbdClose();
  tfp->close();
  exit(0);
}
