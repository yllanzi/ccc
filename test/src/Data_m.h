//
// Generated file, do not edit! Created by nedtool 4.6 from Data.msg.
//

#ifndef _DATA_M_H_
#define _DATA_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>Data.msg:1</tt> by nedtool.
 * <pre>
 * packet Data
 * {
 *     int source;
 *     int seq;
 *     double data;
 *     int state;
 * }
 * </pre>
 */
class Data : public ::cPacket
{
  protected:
    int source_var;
    int seq_var;
    double data_var;
    int state_var;

  private:
    void copy(const Data& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Data&);

  public:
    Data(const char *name=NULL, int kind=0);
    Data(const Data& other);
    virtual ~Data();
    Data& operator=(const Data& other);
    virtual Data *dup() const {return new Data(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getSource() const;
    virtual void setSource(int source);
    virtual int getSeq() const;
    virtual void setSeq(int seq);
    virtual double getData() const;
    virtual void setData(double data);
    virtual int getState() const;
    virtual void setState(int state);
};

inline void doPacking(cCommBuffer *b, Data& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Data& obj) {obj.parsimUnpack(b);}


#endif // ifndef _DATA_M_H_

