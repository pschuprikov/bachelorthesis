//
// Generated file, do not edit! Created by nedtool 5.7 from inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg.
//

#ifndef __INET__IEEE80211_IEEE80211PRIMITIVES_M_H
#define __INET__IEEE80211_IEEE80211PRIMITIVES_M_H

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
namespace ieee80211 {

class Ieee80211PrimRequest;
class Ieee80211PrimConfirm;
class Ieee80211Prim_ScanRequest;
class Ieee80211Prim_BssDescription;
class Ieee80211Prim_ScanConfirm;
class Ieee80211Prim_AuthenticateRequest;
class Ieee80211Prim_AuthenticateConfirm;
class Ieee80211Prim_DeauthenticateRequest;
class Ieee80211Prim_AssociateRequest;
class Ieee80211Prim_AssociateConfirm;
class Ieee80211Prim_ReassociateRequest;
class Ieee80211Prim_ReassociateConfirm;
class Ieee80211Prim_DisassociateRequest;
} // namespace ieee80211
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/linklayer/ieee80211/mgmt/Ieee80211MgmtFrame_m.h" // import inet.linklayer.ieee80211.mgmt.Ieee80211MgmtFrame

#include "inet/linklayer/common/MacAddress_m.h" // import inet.linklayer.common.MacAddress


namespace inet {
namespace ieee80211 {

/**
 * Enum generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:33</tt> by nedtool.
 * <pre>
 * //
 * // IEEE 802.11 command codes, sent by the agent to the management entity.
 * // These constants should be set as message kind on the messages.
 * //
 * // \@see ~Ieee80211PrimConfirmCode, ~Ieee80211MgmtSta, ~Ieee80211AgentSta
 * //
 * enum Ieee80211PrimRequestCode
 * {
 *     PR_SCAN_REQUEST = 1;
 *     PR_AUTHENTICATE_REQUEST = 2;
 *     PR_DEAUTHENTICATE_REQUEST = 3;
 *     PR_ASSOCIATE_REQUEST = 4;
 *     PR_REASSOCIATE_REQUEST = 5;
 *     PR_DISASSOCIATE_REQUEST = 6;
 * }
 * </pre>
 */
enum Ieee80211PrimRequestCode {
    PR_SCAN_REQUEST = 1,
    PR_AUTHENTICATE_REQUEST = 2,
    PR_DEAUTHENTICATE_REQUEST = 3,
    PR_ASSOCIATE_REQUEST = 4,
    PR_REASSOCIATE_REQUEST = 5,
    PR_DISASSOCIATE_REQUEST = 6
};

/**
 * Enum generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:51</tt> by nedtool.
 * <pre>
 * //
 * // IEEE 802.11 confirm codes, sent by the management entity to the agent,
 * // in response to the agents's requests.
 * // These constants should be set as message kind on the messages.
 * //
 * // \@see ~Ieee80211PrimRequestCode, ~Ieee80211MgmtSta, ~Ieee80211AgentSta
 * //
 * enum Ieee80211PrimConfirmCode
 * {
 *     PR_SCAN_CONFIRM = 1;
 *     PR_AUTHENTICATE_CONFIRM = 2;
 *     PR_DEAUTHENTICATE_CONFIRM = 3;
 *     PR_ASSOCIATE_CONFIRM = 4;
 *     PR_REASSOCIATE_CONFIRM = 5;
 *     PR_DISASSOCIATE_CONFIRM = 6;
 * }
 * </pre>
 */
enum Ieee80211PrimConfirmCode {
    PR_SCAN_CONFIRM = 1,
    PR_AUTHENTICATE_CONFIRM = 2,
    PR_DEAUTHENTICATE_CONFIRM = 3,
    PR_ASSOCIATE_CONFIRM = 4,
    PR_REASSOCIATE_CONFIRM = 5,
    PR_DISASSOCIATE_CONFIRM = 6
};

/**
 * Enum generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:62</tt> by nedtool.
 * <pre>
 * enum Ieee80211BssType
 * {
 *     BSSTYPE_ANY = 0;
 *     BSSTYPE_INFRASTRUCTURE = 1;
 *     BSSTYPE_INDEPENDENT = 2;
 * }
 * </pre>
 */
enum Ieee80211BssType {
    BSSTYPE_ANY = 0,
    BSSTYPE_INFRASTRUCTURE = 1,
    BSSTYPE_INDEPENDENT = 2
};

/**
 * Enum generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:76</tt> by nedtool.
 * <pre>
 * //
 * // Values for the resultCode field in confirm primitives, sent from
 * // the management entity to the agent.
 * //
 * // \@see ~Ieee80211PrimConfirmCode, ~Ieee80211MgmtSta, ~Ieee80211AgentSta
 * //
 * enum Ieee80211PrimResultCode
 * {
 *     PRC_SUCCESS = 0;
 *     PRC_INVALID_PARAMETERS = 1;
 *     PRC_TIMEOUT = 2;
 *     PRC_TOO_MANY_SIMULTANEOUS_REQUESTS = 3;
 *     PRC_REFUSED = 4;
 * }
 * </pre>
 */
enum Ieee80211PrimResultCode {
    PRC_SUCCESS = 0,
    PRC_INVALID_PARAMETERS = 1,
    PRC_TIMEOUT = 2,
    PRC_TOO_MANY_SIMULTANEOUS_REQUESTS = 3,
    PRC_REFUSED = 4
};

/**
 * Class generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:89</tt> by nedtool.
 * <pre>
 * //
 * // Base class for request primitives
 * //
 * class Ieee80211PrimRequest extends cObject
 * {
 * }
 * </pre>
 */
class INET_API Ieee80211PrimRequest : public ::omnetpp::cObject
{
  protected:

  private:
    void copy(const Ieee80211PrimRequest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211PrimRequest&);

  public:
    Ieee80211PrimRequest();
    Ieee80211PrimRequest(const Ieee80211PrimRequest& other);
    virtual ~Ieee80211PrimRequest();
    Ieee80211PrimRequest& operator=(const Ieee80211PrimRequest& other);
    virtual Ieee80211PrimRequest *dup() const override {return new Ieee80211PrimRequest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211PrimRequest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211PrimRequest& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:96</tt> by nedtool.
 * <pre>
 * //
 * // Base class for confirm primitives
 * //
 * class Ieee80211PrimConfirm extends cObject
 * {
 *     Ieee80211PrimResultCode resultCode;
 * }
 * </pre>
 */
class INET_API Ieee80211PrimConfirm : public ::omnetpp::cObject
{
  protected:
    inet::ieee80211::Ieee80211PrimResultCode resultCode = static_cast<inet::ieee80211::Ieee80211PrimResultCode>(-1);

  private:
    void copy(const Ieee80211PrimConfirm& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211PrimConfirm&);

  public:
    Ieee80211PrimConfirm();
    Ieee80211PrimConfirm(const Ieee80211PrimConfirm& other);
    virtual ~Ieee80211PrimConfirm();
    Ieee80211PrimConfirm& operator=(const Ieee80211PrimConfirm& other);
    virtual Ieee80211PrimConfirm *dup() const override {return new Ieee80211PrimConfirm(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual inet::ieee80211::Ieee80211PrimResultCode getResultCode() const;
    virtual void setResultCode(inet::ieee80211::Ieee80211PrimResultCode resultCode);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211PrimConfirm& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211PrimConfirm& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:104</tt> by nedtool.
 * <pre>
 * //
 * // Losely based on MLME-SCAN.request.
 * //
 * class Ieee80211Prim_ScanRequest extends Ieee80211PrimRequest
 * {
 *     Ieee80211BssType BSSType; // determines type of BSS's to include in the scan
 *     MacAddress BSSID; // specific BSSID to scan for (default: any)
 *     string SSID;      // SSID to scan for SSID (default: any)
 *     bool activeScan;  // whether to perform active or passive scanning
 *     simtime_t probeDelay; // delay (in �s) to be used prior to transmitting a Probe frame during active scanning
 *     int channelList[]; // list of channels to scan (default: all channels)
 *     simtime_t minChannelTime; // minimum time to spend on each channel when scanning
 *     simtime_t maxChannelTime; // maximum time to spend on each channel when scanning
 * }
 * </pre>
 */
class INET_API Ieee80211Prim_ScanRequest : public ::inet::ieee80211::Ieee80211PrimRequest
{
  protected:
    inet::ieee80211::Ieee80211BssType BSSType = static_cast<inet::ieee80211::Ieee80211BssType>(-1);
    MacAddress BSSID;
    omnetpp::opp_string SSID;
    bool activeScan = false;
    omnetpp::simtime_t probeDelay = SIMTIME_ZERO;
    int *channelList = nullptr;
    size_t channelList_arraysize = 0;
    omnetpp::simtime_t minChannelTime = SIMTIME_ZERO;
    omnetpp::simtime_t maxChannelTime = SIMTIME_ZERO;

  private:
    void copy(const Ieee80211Prim_ScanRequest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211Prim_ScanRequest&);

  public:
    Ieee80211Prim_ScanRequest();
    Ieee80211Prim_ScanRequest(const Ieee80211Prim_ScanRequest& other);
    virtual ~Ieee80211Prim_ScanRequest();
    Ieee80211Prim_ScanRequest& operator=(const Ieee80211Prim_ScanRequest& other);
    virtual Ieee80211Prim_ScanRequest *dup() const override {return new Ieee80211Prim_ScanRequest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual inet::ieee80211::Ieee80211BssType getBSSType() const;
    virtual void setBSSType(inet::ieee80211::Ieee80211BssType BSSType);
    virtual const MacAddress& getBSSID() const;
    virtual MacAddress& getBSSIDForUpdate() { return const_cast<MacAddress&>(const_cast<Ieee80211Prim_ScanRequest*>(this)->getBSSID());}
    virtual void setBSSID(const MacAddress& BSSID);
    virtual const char * getSSID() const;
    virtual void setSSID(const char * SSID);
    virtual bool getActiveScan() const;
    virtual void setActiveScan(bool activeScan);
    virtual omnetpp::simtime_t getProbeDelay() const;
    virtual void setProbeDelay(omnetpp::simtime_t probeDelay);
    virtual void setChannelListArraySize(size_t size);
    virtual size_t getChannelListArraySize() const;
    virtual int getChannelList(size_t k) const;
    virtual void setChannelList(size_t k, int channelList);
    virtual void insertChannelList(int channelList);
    virtual void insertChannelList(size_t k, int channelList);
    virtual void eraseChannelList(size_t k);
    virtual omnetpp::simtime_t getMinChannelTime() const;
    virtual void setMinChannelTime(omnetpp::simtime_t minChannelTime);
    virtual omnetpp::simtime_t getMaxChannelTime() const;
    virtual void setMaxChannelTime(omnetpp::simtime_t maxChannelTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211Prim_ScanRequest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211Prim_ScanRequest& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:116</tt> by nedtool.
 * <pre>
 * class Ieee80211Prim_BssDescription extends cObject
 * {
 *     int channelNumber;
 *     MacAddress BSSID;
 *     string SSID;
 *     Ieee80211SupportedRatesElement supportedRates;
 *     simtime_t beaconInterval;
 * 
 *     double rxPower; // received power from AP; not part of the standard
 * }
 * </pre>
 */
class INET_API Ieee80211Prim_BssDescription : public ::omnetpp::cObject
{
  protected:
    int channelNumber = 0;
    MacAddress BSSID;
    omnetpp::opp_string SSID;
    Ieee80211SupportedRatesElement supportedRates;
    omnetpp::simtime_t beaconInterval = SIMTIME_ZERO;
    double rxPower = 0;

  private:
    void copy(const Ieee80211Prim_BssDescription& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211Prim_BssDescription&);

  public:
    Ieee80211Prim_BssDescription();
    Ieee80211Prim_BssDescription(const Ieee80211Prim_BssDescription& other);
    virtual ~Ieee80211Prim_BssDescription();
    Ieee80211Prim_BssDescription& operator=(const Ieee80211Prim_BssDescription& other);
    virtual Ieee80211Prim_BssDescription *dup() const override {return new Ieee80211Prim_BssDescription(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getChannelNumber() const;
    virtual void setChannelNumber(int channelNumber);
    virtual const MacAddress& getBSSID() const;
    virtual MacAddress& getBSSIDForUpdate() { return const_cast<MacAddress&>(const_cast<Ieee80211Prim_BssDescription*>(this)->getBSSID());}
    virtual void setBSSID(const MacAddress& BSSID);
    virtual const char * getSSID() const;
    virtual void setSSID(const char * SSID);
    virtual const Ieee80211SupportedRatesElement& getSupportedRates() const;
    virtual Ieee80211SupportedRatesElement& getSupportedRatesForUpdate() { return const_cast<Ieee80211SupportedRatesElement&>(const_cast<Ieee80211Prim_BssDescription*>(this)->getSupportedRates());}
    virtual void setSupportedRates(const Ieee80211SupportedRatesElement& supportedRates);
    virtual omnetpp::simtime_t getBeaconInterval() const;
    virtual void setBeaconInterval(omnetpp::simtime_t beaconInterval);
    virtual double getRxPower() const;
    virtual void setRxPower(double rxPower);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211Prim_BssDescription& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211Prim_BssDescription& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:131</tt> by nedtool.
 * <pre>
 * //
 * // Losely based on MLME-SCAN.confirm
 * // Possible result codes: SUCCESS, INVALID_PARAMETERS
 * //
 * class Ieee80211Prim_ScanConfirm extends Ieee80211PrimConfirm
 * {
 *     Ieee80211Prim_BssDescription bssList[];
 * }
 * </pre>
 */
class INET_API Ieee80211Prim_ScanConfirm : public ::inet::ieee80211::Ieee80211PrimConfirm
{
  protected:
    Ieee80211Prim_BssDescription *bssList = nullptr;
    size_t bssList_arraysize = 0;

  private:
    void copy(const Ieee80211Prim_ScanConfirm& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211Prim_ScanConfirm&);

  public:
    Ieee80211Prim_ScanConfirm();
    Ieee80211Prim_ScanConfirm(const Ieee80211Prim_ScanConfirm& other);
    virtual ~Ieee80211Prim_ScanConfirm();
    Ieee80211Prim_ScanConfirm& operator=(const Ieee80211Prim_ScanConfirm& other);
    virtual Ieee80211Prim_ScanConfirm *dup() const override {return new Ieee80211Prim_ScanConfirm(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual void setBssListArraySize(size_t size);
    virtual size_t getBssListArraySize() const;
    virtual const Ieee80211Prim_BssDescription& getBssList(size_t k) const;
    virtual Ieee80211Prim_BssDescription& getBssListForUpdate(size_t k) { return const_cast<Ieee80211Prim_BssDescription&>(const_cast<Ieee80211Prim_ScanConfirm*>(this)->getBssList(k));}
    virtual void setBssList(size_t k, const Ieee80211Prim_BssDescription& bssList);
    virtual void insertBssList(const Ieee80211Prim_BssDescription& bssList);
    virtual void insertBssList(size_t k, const Ieee80211Prim_BssDescription& bssList);
    virtual void eraseBssList(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211Prim_ScanConfirm& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211Prim_ScanConfirm& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:144</tt> by nedtool.
 * <pre>
 * //
 * // Losely based on MLME-AUTHENTICATE.request.
 * //
 * // Note: the "authType" parameter (Open System, Shared Key, etc) is omitted.
 * // The authentication procedure is simulated by this model by exchanging
 * // a number of "dummy" authentication frames without real contents,
 * // and it is configured in the AP how many authentication steps it requires.
 * //
 * class Ieee80211Prim_AuthenticateRequest extends Ieee80211PrimRequest
 * {
 *     MacAddress address;
 *     simtime_t timeout;
 * }
 * </pre>
 */
class INET_API Ieee80211Prim_AuthenticateRequest : public ::inet::ieee80211::Ieee80211PrimRequest
{
  protected:
    MacAddress address;
    omnetpp::simtime_t timeout = SIMTIME_ZERO;

  private:
    void copy(const Ieee80211Prim_AuthenticateRequest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211Prim_AuthenticateRequest&);

  public:
    Ieee80211Prim_AuthenticateRequest();
    Ieee80211Prim_AuthenticateRequest(const Ieee80211Prim_AuthenticateRequest& other);
    virtual ~Ieee80211Prim_AuthenticateRequest();
    Ieee80211Prim_AuthenticateRequest& operator=(const Ieee80211Prim_AuthenticateRequest& other);
    virtual Ieee80211Prim_AuthenticateRequest *dup() const override {return new Ieee80211Prim_AuthenticateRequest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const MacAddress& getAddress() const;
    virtual MacAddress& getAddressForUpdate() { return const_cast<MacAddress&>(const_cast<Ieee80211Prim_AuthenticateRequest*>(this)->getAddress());}
    virtual void setAddress(const MacAddress& address);
    virtual omnetpp::simtime_t getTimeout() const;
    virtual void setTimeout(omnetpp::simtime_t timeout);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211Prim_AuthenticateRequest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211Prim_AuthenticateRequest& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:154</tt> by nedtool.
 * <pre>
 * //
 * // Losely based on MLME-AUTHENTICATE.confirm.
 * // Possible result codes: SUCCESS, INVALID_PARAMETERS, TIMEOUT, TOO_MANY_SIMULTANEOUS_REQUESTS, REFUSED
 * //
 * class Ieee80211Prim_AuthenticateConfirm extends Ieee80211PrimConfirm
 * {
 *     MacAddress address;
 * }
 * </pre>
 */
class INET_API Ieee80211Prim_AuthenticateConfirm : public ::inet::ieee80211::Ieee80211PrimConfirm
{
  protected:
    MacAddress address;

  private:
    void copy(const Ieee80211Prim_AuthenticateConfirm& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211Prim_AuthenticateConfirm&);

  public:
    Ieee80211Prim_AuthenticateConfirm();
    Ieee80211Prim_AuthenticateConfirm(const Ieee80211Prim_AuthenticateConfirm& other);
    virtual ~Ieee80211Prim_AuthenticateConfirm();
    Ieee80211Prim_AuthenticateConfirm& operator=(const Ieee80211Prim_AuthenticateConfirm& other);
    virtual Ieee80211Prim_AuthenticateConfirm *dup() const override {return new Ieee80211Prim_AuthenticateConfirm(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const MacAddress& getAddress() const;
    virtual MacAddress& getAddressForUpdate() { return const_cast<MacAddress&>(const_cast<Ieee80211Prim_AuthenticateConfirm*>(this)->getAddress());}
    virtual void setAddress(const MacAddress& address);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211Prim_AuthenticateConfirm& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211Prim_AuthenticateConfirm& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:166</tt> by nedtool.
 * <pre>
 * //
 * // Losely based on MLME-DEAUTHENTICATE.request
 * //
 * // NOTE: there is no Deauthenticate Confirm, because Deauthenticate Request
 * // takes place immediately, and nothing can go wrong (there is no reply
 * // from the AP to wait for)
 * //
 * class Ieee80211Prim_DeauthenticateRequest extends Ieee80211PrimRequest
 * {
 *     MacAddress address;
 *     Ieee80211ReasonCode reasonCode;
 * }
 * </pre>
 */
class INET_API Ieee80211Prim_DeauthenticateRequest : public ::inet::ieee80211::Ieee80211PrimRequest
{
  protected:
    MacAddress address;
    inet::ieee80211::Ieee80211ReasonCode reasonCode = static_cast<inet::ieee80211::Ieee80211ReasonCode>(-1);

  private:
    void copy(const Ieee80211Prim_DeauthenticateRequest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211Prim_DeauthenticateRequest&);

  public:
    Ieee80211Prim_DeauthenticateRequest();
    Ieee80211Prim_DeauthenticateRequest(const Ieee80211Prim_DeauthenticateRequest& other);
    virtual ~Ieee80211Prim_DeauthenticateRequest();
    Ieee80211Prim_DeauthenticateRequest& operator=(const Ieee80211Prim_DeauthenticateRequest& other);
    virtual Ieee80211Prim_DeauthenticateRequest *dup() const override {return new Ieee80211Prim_DeauthenticateRequest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const MacAddress& getAddress() const;
    virtual MacAddress& getAddressForUpdate() { return const_cast<MacAddress&>(const_cast<Ieee80211Prim_DeauthenticateRequest*>(this)->getAddress());}
    virtual void setAddress(const MacAddress& address);
    virtual inet::ieee80211::Ieee80211ReasonCode getReasonCode() const;
    virtual void setReasonCode(inet::ieee80211::Ieee80211ReasonCode reasonCode);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211Prim_DeauthenticateRequest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211Prim_DeauthenticateRequest& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:175</tt> by nedtool.
 * <pre>
 * //
 * // Losely based on MLME-ASSOCIATE.request
 * //
 * class Ieee80211Prim_AssociateRequest extends Ieee80211PrimRequest
 * {
 *     MacAddress address;
 *     simtime_t timeout;
 * }
 * </pre>
 */
class INET_API Ieee80211Prim_AssociateRequest : public ::inet::ieee80211::Ieee80211PrimRequest
{
  protected:
    MacAddress address;
    omnetpp::simtime_t timeout = SIMTIME_ZERO;

  private:
    void copy(const Ieee80211Prim_AssociateRequest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211Prim_AssociateRequest&);

  public:
    Ieee80211Prim_AssociateRequest();
    Ieee80211Prim_AssociateRequest(const Ieee80211Prim_AssociateRequest& other);
    virtual ~Ieee80211Prim_AssociateRequest();
    Ieee80211Prim_AssociateRequest& operator=(const Ieee80211Prim_AssociateRequest& other);
    virtual Ieee80211Prim_AssociateRequest *dup() const override {return new Ieee80211Prim_AssociateRequest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const MacAddress& getAddress() const;
    virtual MacAddress& getAddressForUpdate() { return const_cast<MacAddress&>(const_cast<Ieee80211Prim_AssociateRequest*>(this)->getAddress());}
    virtual void setAddress(const MacAddress& address);
    virtual omnetpp::simtime_t getTimeout() const;
    virtual void setTimeout(omnetpp::simtime_t timeout);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211Prim_AssociateRequest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211Prim_AssociateRequest& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:185</tt> by nedtool.
 * <pre>
 * //
 * // Losely based on MLME-ASSOCIATE.confirm
 * // Possible result codes: SUCCESS, INVALID_PARAMETERS, TIMEOUT, REFUSED
 * //
 * class Ieee80211Prim_AssociateConfirm extends Ieee80211PrimConfirm
 * {
 *     MacAddress address;
 * }
 * </pre>
 */
class INET_API Ieee80211Prim_AssociateConfirm : public ::inet::ieee80211::Ieee80211PrimConfirm
{
  protected:
    MacAddress address;

  private:
    void copy(const Ieee80211Prim_AssociateConfirm& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211Prim_AssociateConfirm&);

  public:
    Ieee80211Prim_AssociateConfirm();
    Ieee80211Prim_AssociateConfirm(const Ieee80211Prim_AssociateConfirm& other);
    virtual ~Ieee80211Prim_AssociateConfirm();
    Ieee80211Prim_AssociateConfirm& operator=(const Ieee80211Prim_AssociateConfirm& other);
    virtual Ieee80211Prim_AssociateConfirm *dup() const override {return new Ieee80211Prim_AssociateConfirm(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const MacAddress& getAddress() const;
    virtual MacAddress& getAddressForUpdate() { return const_cast<MacAddress&>(const_cast<Ieee80211Prim_AssociateConfirm*>(this)->getAddress());}
    virtual void setAddress(const MacAddress& address);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211Prim_AssociateConfirm& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211Prim_AssociateConfirm& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:193</tt> by nedtool.
 * <pre>
 * //
 * // MLME-REASSOCIATE.request is very similar to MLME-ASSOCIATE.request
 * //
 * class Ieee80211Prim_ReassociateRequest extends Ieee80211Prim_AssociateRequest
 * {
 * }
 * </pre>
 */
class INET_API Ieee80211Prim_ReassociateRequest : public ::inet::ieee80211::Ieee80211Prim_AssociateRequest
{
  protected:

  private:
    void copy(const Ieee80211Prim_ReassociateRequest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211Prim_ReassociateRequest&);

  public:
    Ieee80211Prim_ReassociateRequest();
    Ieee80211Prim_ReassociateRequest(const Ieee80211Prim_ReassociateRequest& other);
    virtual ~Ieee80211Prim_ReassociateRequest();
    Ieee80211Prim_ReassociateRequest& operator=(const Ieee80211Prim_ReassociateRequest& other);
    virtual Ieee80211Prim_ReassociateRequest *dup() const override {return new Ieee80211Prim_ReassociateRequest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211Prim_ReassociateRequest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211Prim_ReassociateRequest& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:200</tt> by nedtool.
 * <pre>
 * //
 * // MLME-REASSOCIATE.confirm is very similar to MLME-ASSOCIATE.confirm
 * //
 * class Ieee80211Prim_ReassociateConfirm extends Ieee80211Prim_AssociateConfirm
 * {
 * }
 * </pre>
 */
class INET_API Ieee80211Prim_ReassociateConfirm : public ::inet::ieee80211::Ieee80211Prim_AssociateConfirm
{
  protected:

  private:
    void copy(const Ieee80211Prim_ReassociateConfirm& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211Prim_ReassociateConfirm&);

  public:
    Ieee80211Prim_ReassociateConfirm();
    Ieee80211Prim_ReassociateConfirm(const Ieee80211Prim_ReassociateConfirm& other);
    virtual ~Ieee80211Prim_ReassociateConfirm();
    Ieee80211Prim_ReassociateConfirm& operator=(const Ieee80211Prim_ReassociateConfirm& other);
    virtual Ieee80211Prim_ReassociateConfirm *dup() const override {return new Ieee80211Prim_ReassociateConfirm(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211Prim_ReassociateConfirm& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211Prim_ReassociateConfirm& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg:211</tt> by nedtool.
 * <pre>
 * //
 * // Losely based on MLME-DISASSOCIATE.request.
 * //
 * // NOTE: there is no Disassociate Confirm, because Disassociate Request
 * // takes place immediately, and nothing can go wrong (there is no reply
 * // from the AP to wait for)
 * //
 * class Ieee80211Prim_DisassociateRequest extends Ieee80211PrimRequest
 * {
 *     MacAddress address;
 *     Ieee80211ReasonCode reasonCode;
 * }
 * </pre>
 */
class INET_API Ieee80211Prim_DisassociateRequest : public ::inet::ieee80211::Ieee80211PrimRequest
{
  protected:
    MacAddress address;
    inet::ieee80211::Ieee80211ReasonCode reasonCode = static_cast<inet::ieee80211::Ieee80211ReasonCode>(-1);

  private:
    void copy(const Ieee80211Prim_DisassociateRequest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211Prim_DisassociateRequest&);

  public:
    Ieee80211Prim_DisassociateRequest();
    Ieee80211Prim_DisassociateRequest(const Ieee80211Prim_DisassociateRequest& other);
    virtual ~Ieee80211Prim_DisassociateRequest();
    Ieee80211Prim_DisassociateRequest& operator=(const Ieee80211Prim_DisassociateRequest& other);
    virtual Ieee80211Prim_DisassociateRequest *dup() const override {return new Ieee80211Prim_DisassociateRequest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const MacAddress& getAddress() const;
    virtual MacAddress& getAddressForUpdate() { return const_cast<MacAddress&>(const_cast<Ieee80211Prim_DisassociateRequest*>(this)->getAddress());}
    virtual void setAddress(const MacAddress& address);
    virtual inet::ieee80211::Ieee80211ReasonCode getReasonCode() const;
    virtual void setReasonCode(inet::ieee80211::Ieee80211ReasonCode reasonCode);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211Prim_DisassociateRequest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211Prim_DisassociateRequest& obj) {obj.parsimUnpack(b);}

} // namespace ieee80211
} // namespace inet

#endif // ifndef __INET__IEEE80211_IEEE80211PRIMITIVES_M_H

