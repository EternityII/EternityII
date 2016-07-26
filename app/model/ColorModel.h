#ifndef ETERNITYII_COLORMODEL_H
#define ETERNITYII_COLORMODEL_H


#include "../../core/model/ModelInterface.h"
#include "BordureModel.h"
#include "../data/variable/BordureData.h"
#include "../data/value/PieceData.h"

/**
 * ColorModel Class. Responsible of maintaining the Colors disponibility.
 */
class ColorModel: public ModelInterface
{
private:
    //! history of denied colors
    vector<vector<deque<ColorData> > > availableHistory;

    //! history of the quantity of borders by color
    vector<vector<deque<ColorData> > > borduresCountHistory;

    //! history of denied (colors, bordures) pairs
    vector<vector<deque<pair<ColorData, BordureData> > > > colorBorduresHistory;
public:
    //! bordureQte the total number of borders
    int borduresQte;

    //! the total number of colors
    int colorsQte;

    //! if the color is available
    vector<bool> available;

    //! how many borders the color has
    vector<int> borduresCount;

    //! which color has which border
    vector<vector<int>> colorBordures;

    ColorModel(const GameImportData &gameImportData,
        EventManager &eventManager);

    void allow(const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth);

    void denyOne(const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth, const int &persistent);

    void deny(const BordureData &bordureData,
        const int &depth,
        const int &persistent);

    void deny(const ColorData &colorData,
        const int &depth,
        const int &persistent);

    void rollback(const int &depth, const bool total = true);
};


#endif //ETERNITYII_COLORMODEL_H
