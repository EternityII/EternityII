#include "BordureCaseConstraint.h"
BordureCaseConstraint::BordureCaseConstraint(BordureModel &bordureModel,
    CaseModel &caseModel,
    EventManager &eventManager)
    : ConstraintInterface(eventManager), _first(bordureModel),
      _second(caseModel)
{
    _first.add(*this);
    _second.add(*this);
}

void BordureCaseConstraint::accept(const BordureData &bordureData,
    const CaseData &caseData,
    const int &depth)
{
//TODO :
}

void BordureCaseConstraint::discard(const BordureData &bordureData,
    const CaseData &caseData,
    const int &depth)
{
//TODO :
}

void BordureCaseConstraint::accepted(const BordureData &bordureData,
    const int &depth)
{
//TODO :
}

void BordureCaseConstraint::accepted(const CaseData &caseData, const int &depth)
{
//TODO :
}

void BordureCaseConstraint::discarded(const CaseData &caseData,
    const int &depth)
{
//TODO :
}

void BordureCaseConstraint::discarded(const BordureData &bordureData,
    const int &depth)
{
//TODO :
}
