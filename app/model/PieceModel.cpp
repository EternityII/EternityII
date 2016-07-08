#include "PieceModel.h"
#include "../constraint/CasePieceConstraint.h"

void PieceModel::initialize(GameImportData &gameImportData)
{
    nbPieces = gameImportData.depth;
    size = gameImportData.size;

    casesQte.resize(nbPieces,
        vector<int>(4, nbPieces));
    casesQteHistory.resize(nbPieces,
        vector<vector<int >>(nbPieces,
            vector<int>(4, 0)));

    isAvailable.resize(nbPieces, true);
    isAvailableHistory.resize(nbPieces,
        vector<bool>(nbPieces, false));

    // [n°piece][rotation][x][y]
    pieceCases.resize(nbPieces,
        vector<vector<vector<bool>>>(4,
            vector<vector<bool>>(size,
                vector<bool>(size, true))));

    pieceCasesHistory.resize(nbPieces,
        vector<vector<vector<vector<bool >> >>(nbPieces,
            vector<vector<vector<bool >>>(4,
                vector<vector<bool >>(size,
                    vector<bool>(size, false)))));

}

void PieceModel::accept(PieceData &pieceData, const int &depth)
{
    if (isAvailable[pieceData.id]) {
        isAvailable[pieceData.id] = false;
        isAvailableHistory[depth][pieceData.id] = true;

        addAcceptedEvent<CasePieceConstraint, PieceData>(
            static_cast<CasePieceConstraint &>(*observers[0]),
            pieceData,
            depth);

        //static_cast<CasePieceConstraint *>(observers[0])->accepted(pieceData, depth);
    }
}

void PieceModel::accepted(CaseData &caseData, const int &depth)
{
    // it's a consequence of the update of caseData, so we do it without checking anything
    for (int nPiece = 0; nPiece < nbPieces; ++nPiece) {
        if (isAvailable[nPiece]) { // if the piece is available
            for (int rotation = 0; rotation < 4; ++rotation) {
                // if the piece has the case in it's domain
                if (pieceCases[nPiece][rotation][caseData.x][caseData.y]) {
                    --casesQte[nPiece][rotation];
                    --casesQteHistory[depth][nPiece][rotation];
                    //not anymore
                    pieceCases[nPiece][rotation][caseData.x][caseData.y] = false;
                    pieceCasesHistory[depth][nPiece][rotation][caseData.x][caseData.y] = true;
                }
            }
        }
    }
}

void PieceModel::discard(CaseData &caseData, PieceData &pieceData, const int &depth)
{
    pieceCases[pieceData.id][pieceData.rotation][caseData.x][caseData.y] = false;
    pieceCasesHistory[depth][pieceData.id][pieceData.rotation][caseData.x][caseData.y] = true;

    --casesQte[pieceData.id][pieceData.rotation];
    --casesQteHistory[depth][pieceData.id][pieceData.rotation];
}

void PieceModel::discarded(CaseData &caseData, const int &depth)
{
    // TODO
}

void PieceModel::rollback(const int &depth)
{
    for (int nPiece = 0; nPiece < nbPieces; ++nPiece) {
        for (int rotation = 0; rotation < 4; ++rotation) {

            if (casesQteHistory[depth][nPiece][rotation] != 0) {
                casesQte[nPiece][rotation] -= casesQteHistory[depth][nPiece][rotation];
                casesQteHistory[depth][nPiece][rotation] = 0;
            }


            for (int x = 0; x < size; ++x) {
                for (int y = 0; y < size; ++y) {
                    if (pieceCasesHistory[depth][nPiece][rotation][x][y]) {
                        pieceCases[nPiece][rotation][x][y] = true;
                        pieceCasesHistory[depth][nPiece][rotation][x][y] = false;
                    }
                }
            }
        }

        if (isAvailableHistory[depth][nPiece]) {
            isAvailable[nPiece] = true;
            isAvailableHistory[depth][nPiece] = false;
        }
    }
}
