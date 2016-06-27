#include "CaseModel.h"

void CaseModel::initialize(GameImportData &gameImportData)
{
    //TODO
}

void CaseModel::accept(DataInterface &dataInterface, const int &depth)
{
    //TODO
    this->isAvailable;
    this->isAvailableHistory;
    this->piecesPossible;
    this->piecesPossibleHistory;
    this->piecesQte;
    this->piecesQteHistory;

    CaseData &caseData = dynamic_cast<CaseData &> (dataInterface);

    cout << "yolo" << endl;
    // verifier le type
}

void CaseModel::discard(DataInterface &dataInterface, const int &depth)
{
    //TODO
}

void CaseModel::rollback(const int &depth)
{
    //TODO
}