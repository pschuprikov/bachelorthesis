//
// Generated file, do not edit! Created by nedtool 5.7 from inet/networklayer/common/EchoPacket.msg.
//

#ifndef __INET_ECHOPACKET_M_H
#define __INET_ECHOPACKET_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0507
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif


namespace inet {

class EchoPacket;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk


namespace inet {

/**
 * Enum generated from <tt>inet/networklayer/common/EchoPacket.msg:27</tt> by nedtool.
 * <pre>
 * //
 * // Determines the packet type.
 * //
 * enum EchoProtocolType
 * {
 *     ECHO_PROTOCOL_REQUEST = 0;
 *     ECHO_PROTOCOL_REPLY = 1;
 * }
 * </pre>
 */
enum EchoProtocolType {
    ECHO_PROTOCOL_REQUEST = 0,
    ECHO_PROTOCOL_REPLY = 1
};

/**
 * Class generated from <tt>inet/networklayer/common/EchoPacket.msg:36</tt> by nedtool.
 * <pre>
 * //
 * // Generic network protocol packet for testing network connectivity.
 * //
 * class EchoPacket extends FieldsChunk
 * {
 *     chunkLength = B(6);
 *     EchoProtocolType type;
 *     int identifier; // identifier to aid in matching Echo replies. May be Zero
 *     int seqNumber; // sequence number to aid in matching Echo replies. May be Zero
 * }
 * </pre>
 */
class INET_API EchoPacket : public ::inet::FieldsChunk
{
  protected:
    inet::EchoProtocolType type = static_cast<inet::EchoProtocolType>(-1);
    int identifier = 0;
    int seqNumber = 0;

  private:
    void copy(const EchoPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const EchoPacket&);

  public:
    EchoPacket();
    EchoPacket(const EchoPacket& other);
    virtual ~EchoPacket();
    EchoPacket& operator=(const EchoPacket& other);
    virtual EchoPacket *dup() const override {return new EchoPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual inet::EchoProtocolType getType() const;
    virtual void setType(inet::EchoProtocolType type);
    virtual int getIdentifier() const;
    virtual void setIdentifier(int identifier);
    virtual int getSeqNumber() const;
    virtual void setSeqNumber(int seqNumber);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EchoPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EchoPacket& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_ECHOPACKET_M_H

