#ifndef EXACTCPUSWITCH_HH
#define EXACTCPUSWITCH_HH
#include <click/batchelement.hh>
#include <click/vector.hh>
CLICK_DECLS

/*
 * =c
 * ExactCPUSwitch()
 * =s threads
 * classifies packets by cpu
 * =d
 * Can have any number of outputs.
 * Chooses the output on which to emit each packet based on the thread's cpu. Contrary to CPUSwitch, the output is choosed using the thread-vector mapping. It means that the outputs will be evenly shared among threads. Eg, if threads 1, 7 and 8 push packets to a CPUSwitch with 3 outputs, the 1 and 7 will push to output 1, and 8 to output 2. Leading to an imbalance. ExactCPUSwitch will use the nown list of possible threads to balance evenly.
 * =a
 * CPUSwitch
 */

class ExactCPUSwitch : public BatchElement {

 public:

  ExactCPUSwitch() CLICK_COLD;
  ~ExactCPUSwitch() CLICK_COLD;

  const char *class_name() const		{ return "ExactCPUSwitch"; }
  const char *port_count() const		{ return "1/1-"; }
  const char *processing() const		{ return PUSH; }

  int initialize(ErrorHandler* errh) override CLICK_COLD;
  int thread_configure(ThreadReconfigurationStage, ErrorHandler*) override CLICK_COLD;
  bool get_spawning_threads(Bitvector& b, bool, int) override;

  void push(int port, Packet *);
#if HAVE_BATCH
  void push_batch(int port, PacketBatch *);
#endif

 private:
  Vector<unsigned> map;
};

CLICK_ENDDECLS
#endif