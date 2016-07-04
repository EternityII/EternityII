#ifndef ETERNITYII_OBSERVERINTERFACE_H
#define ETERNITYII_OBSERVERINTERFACE_H

template<class VarD, class ValD>
class ObserverInterface
{
public:
    virtual void accept(VarD &caseData, ValD &pieceData, const int &depth) = 0;

    virtual void discard(VarD &caseData, ValD &pieceData, const int &depth) = 0;

    virtual void accepted(ValD &pieceData, const int &depth) = 0;

    virtual void accepted(VarD &pieceData, const int &depth) = 0;

    virtual void discarded(VarD &caseData, const int &depth) = 0;

    virtual void discarded(ValD &caseData, const int &depth) = 0;

    virtual ~ObserverInterface()
    { }
};

#endif //ETERNITYII_OBSERVERINTERFACE_H
