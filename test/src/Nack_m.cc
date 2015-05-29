//
// Generated file, do not edit! Created by nedtool 4.6 from Nack.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Nack_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(Nack);

Nack::Nack(const char *name, int kind) : ::cPacket(name,kind)
{
    this->status_var = 0;
    this->num_var = 0;
    for (unsigned int i=0; i<20; i++)
        this->seq_var[i] = 0;
    this->finalkey_var = 0;
    this->source_var = 0;
    this->dest_var = 0;
}

Nack::Nack(const Nack& other) : ::cPacket(other)
{
    copy(other);
}

Nack::~Nack()
{
}

Nack& Nack::operator=(const Nack& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Nack::copy(const Nack& other)
{
    this->status_var = other.status_var;
    this->num_var = other.num_var;
    for (unsigned int i=0; i<20; i++)
        this->seq_var[i] = other.seq_var[i];
    this->finalkey_var = other.finalkey_var;
    this->source_var = other.source_var;
    this->dest_var = other.dest_var;
}

void Nack::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->status_var);
    doPacking(b,this->num_var);
    doPacking(b,this->seq_var,20);
    doPacking(b,this->finalkey_var);
    doPacking(b,this->source_var);
    doPacking(b,this->dest_var);
}

void Nack::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->status_var);
    doUnpacking(b,this->num_var);
    doUnpacking(b,this->seq_var,20);
    doUnpacking(b,this->finalkey_var);
    doUnpacking(b,this->source_var);
    doUnpacking(b,this->dest_var);
}

int Nack::getStatus() const
{
    return status_var;
}

void Nack::setStatus(int status)
{
    this->status_var = status;
}

int Nack::getNum() const
{
    return num_var;
}

void Nack::setNum(int num)
{
    this->num_var = num;
}

unsigned int Nack::getSeqArraySize() const
{
    return 20;
}

int Nack::getSeq(unsigned int k) const
{
    if (k>=20) throw cRuntimeError("Array of size 20 indexed by %lu", (unsigned long)k);
    return seq_var[k];
}

void Nack::setSeq(unsigned int k, int seq)
{
    if (k>=20) throw cRuntimeError("Array of size 20 indexed by %lu", (unsigned long)k);
    this->seq_var[k] = seq;
}

int Nack::getFinalkey() const
{
    return finalkey_var;
}

void Nack::setFinalkey(int finalkey)
{
    this->finalkey_var = finalkey;
}

int Nack::getSource() const
{
    return source_var;
}

void Nack::setSource(int source)
{
    this->source_var = source;
}

int Nack::getDest() const
{
    return dest_var;
}

void Nack::setDest(int dest)
{
    this->dest_var = dest;
}

class NackDescriptor : public cClassDescriptor
{
  public:
    NackDescriptor();
    virtual ~NackDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(NackDescriptor);

NackDescriptor::NackDescriptor() : cClassDescriptor("Nack", "cPacket")
{
}

NackDescriptor::~NackDescriptor()
{
}

bool NackDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Nack *>(obj)!=NULL;
}

const char *NackDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NackDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int NackDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *NackDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "status",
        "num",
        "seq",
        "finalkey",
        "source",
        "dest",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int NackDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "num")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "seq")==0) return base+2;
    if (fieldName[0]=='f' && strcmp(fieldName, "finalkey")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "dest")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NackDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *NackDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int NackDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Nack *pp = (Nack *)object; (void)pp;
    switch (field) {
        case 2: return 20;
        default: return 0;
    }
}

std::string NackDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Nack *pp = (Nack *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getStatus());
        case 1: return long2string(pp->getNum());
        case 2: return long2string(pp->getSeq(i));
        case 3: return long2string(pp->getFinalkey());
        case 4: return long2string(pp->getSource());
        case 5: return long2string(pp->getDest());
        default: return "";
    }
}

bool NackDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Nack *pp = (Nack *)object; (void)pp;
    switch (field) {
        case 0: pp->setStatus(string2long(value)); return true;
        case 1: pp->setNum(string2long(value)); return true;
        case 2: pp->setSeq(i,string2long(value)); return true;
        case 3: pp->setFinalkey(string2long(value)); return true;
        case 4: pp->setSource(string2long(value)); return true;
        case 5: pp->setDest(string2long(value)); return true;
        default: return false;
    }
}

const char *NackDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *NackDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Nack *pp = (Nack *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


