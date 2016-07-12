#ifndef MIDDLEBOX_HTTPOUT_HH
#define MIDDLEBOX_HTTPOUT_HH
#include <click/element.hh>
#include "stackelement.hh"
#include "memorypool.hh"
#include "flowbuffer.hh"
#include "flowbufferentry.hh"

CLICK_DECLS

#define POOL_BUFFER_ENTRIES_SIZE 300

class HTTPOut : public StackElement
{
public:
    HTTPOut() CLICK_COLD;

    const char *class_name() const        { return "HTTPOut"; }
    const char *port_count() const        { return PORTS_1_1; }
    const char *processing() const        { return PROCESSING_A_AH; }

    bool isOutElement()                   { return true; }

    int configure(Vector<String> &, ErrorHandler *) CLICK_COLD;

protected:
    Packet* processPacket(struct fcb*, Packet*);
    void setHeaderContent(struct fcb *fcb, WritablePacket* packet, const char* headerName, const char* content);

    MemoryPool<struct flowBufferEntry> poolBufferEntries;
};

CLICK_ENDDECLS
#endif
