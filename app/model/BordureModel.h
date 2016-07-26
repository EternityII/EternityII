#ifndef ETERNITYII_BORDUREMODEL_H
#define ETERNITYII_BORDUREMODEL_H

#include <vector>
#include "../../core/model/ModelInterface.h"
#include "../data/variable/BordureData.h"
#include "../data/variable/CaseData.h"
#include "../data/value/ColorData.h"

using namespace std;

class BordureModel: public ModelInterface
{
private:
    vector<vector<deque<BordureData> > > availableHistory;

    vector<vector<deque<BordureData> > > colorsCountHistory;

    vector<vector<deque<pair<BordureData, ColorData> > > > bordureColorsHistory;
public:

    int borduresQte;
    int colorsQte;

    vector<bool> available;

    vector<int> colorsCount;

    vector<vector<int>> bordureColors;

    BordureModel(
        const GameImportData &gameImportData, EventManager &eventManager);

    void allow(const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth);

    void denyOne(const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth, const int &persistent);

    void deny(const ColorData &colorData,
        const int &depth,
        const int &persistent);

    void deny(const BordureData &bordureData,
        const int &depth,
        const int &persistent);

    void rollback(const int &depth, const bool total = true);
};


#endif //ETERNITYII_BORDUREMODEL_H
