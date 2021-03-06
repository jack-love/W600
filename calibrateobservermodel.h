#ifndef CALIBRATEOBSERVERMODEL_H
#define CALIBRATEOBSERVERMODEL_H

#include <QObject>

class CalibrateObserverModel
{

private:
    int _itemNo;
    QString _itemName;
    int _white;
    int _red;
    int _green;
    int _blue;
    int _calibrateValue;
    QString _resultValue;
    QString _calibrateDate;
public:
    void setItemNo(int);
    void setItemName(QString);
    void setWhite(int);
    void setRed(int);
    void setGreen(int);
    void setBlue(int);
    void setCalibrateValue(int);
    void setResultValue(QString);
    void setCalibrateDate(QString);

    int getItemNo();
    QString getItemName();
    int getWhite();
    int getRed();
    int getGreen();
    int getBlue();
    int getCalibrateValue();
    QString getResultValue();
    QString getCalibrateDate();
};

#endif // CALIBRATEOBSERVERMODEL_H
