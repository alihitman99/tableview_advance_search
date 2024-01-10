#include "mytableview.h"
#include <QColor>
#include <QDebug>
#include <QPixmap>

MyTableView::MyTableView(QObject *parent)
    : QAbstractTableModel(parent)
{
    // TEST
    Data.append({{{"color", "green", "Main"},
                  {"icon", "qrc:/icons/system-icon.jpg", "Main"},
                  {"Name", "reza", "Main"},
                  {"TN", 121, "Main"},
                  {"Callsing", "Cls", "Main"},
                  {"IFFcode", "A12345", "Main"},
                  {"Identification", "z", "Main"},
                  {"Type", "System", "Main"},
                  {"Master", "radar2", "Main"},
                  {"Latitude", 10, "Location"},
                  {"Longitude", 5, "Location"},
                  {"Altitude", 5, "Location"},
                  {"Pos", "Pos2", "Location"},
                  {"Heading", 46, "Location"},
                  {"Speed", "m/s", "Location"},
                  {"Battle", "qrc:/icons/battle-icon.jpg", "Main"},
                  {"Target", "qrc:/icons/target-icon.jpg", "Main"},
                  {"More", "qrc:/icons/more-icon.jpg", "Main"}}});
    Data.append({{{"color", "red", "Main"},
                  {"icon", "qrc:/icons/aircraft-icon.jpg", "Main"},
                  {"Name", "NFT2425", "Main"},
                  {"TN", 0, "Main"},
                  {"Callsing", "Cls", "Main"},
                  {"IFFcode", "A12345", "Main"},
                  {"Identification", "z", "Main"},
                  {"Type", "Aircraft", "Main"},
                  {"Master", "radar2", "Main"},
                  {"Latitude", 36, "Location"},
                  {"Longitude", 8, "Location"},
                  {"Altitude", 7, "Location"},
                  {"Pos", "Pos1", "Location"},
                  {"Heading", 46, "Location"},
                  {"Speed", "m/s", "Location"},
                  {"Battle", "qrc:/icons/battle-icon.jpg", "Main"},
                  {"Target", "qrc:/icons/target-icon.jpg", "Main"},
                  {"More", "qrc:/icons/more-icon.jpg", "Main"}}});
    Data.append({{{"color", "royalblue", "Main"},
                  {"icon", "qrc:/icons/station-icon.jpg", "Main"},
                  {"Name", "mamad", "Main"},
                  {"TN", 30, "Main"},
                  {"Callsing", "-", "Main"},
                  {"IFFcode", "A12345", "Main"},
                  {"Identification", "z", "Main"},
                  {"Type", "Station", "Main"},
                  {"Master", "radar2", "Main"},
                  {"Latitude", 60, "Location"},
                  {"Longitude", 3, "Location"},
                  {"Altitude", 59, "Location"},
                  {"Pos", "Pos3", "Location"},
                  {"Heading", 46, "Location"},
                  {"Speed", "m/s", "Location"},
                  {"Battle", "qrc:/icons/battle-icon.jpg", "Main"},
                  {"Target", "qrc:/icons/target-icon.jpg", "Main"},
                  {"More", "qrc:/icons/more-icon.jpg", "Main"}}});
    Data.append({{{"color", "pink", "Main"},
                  {"icon", "qrc:/icons/station-icon.jpg", "Main"},
                  {"Name", "ahmad", "Main"},
                  {"TN", 40, "Main"},
                  {"Callsing", "-", "Main"},
                  {"IFFcode", "A12345", "Main"},
                  {"Identification", "z", "Main"},
                  {"Type", "Station", "Main"},
                  {"Master", "radar2", "Main"},
                  {"Latitude", 50, "Location"},
                  {"Longitude", 5, "Location"},
                  {"Altitude", 53, "Location"},
                  {"Pos", "Pos4", "Location"},
                  {"Heading", 46, "Location"},
                  {"Speed", "m/s", "Location"},
                  {"Battle", "qrc:/icons/battle-icon.jpg", "Main"},
                  {"Target", "qrc:/icons/target-icon.jpg", "Main"},
                  {"More", "qrc:/icons/more-icon.jpg", "Main"}}});
    Data.append({{{"color", "yellow", "Main"},
                  {"icon", "qrc:/icons/system-icon.jpg", "Main"},
                  {"Name", "sina", "Main"},
                  {"TN", 21, "Main"},
                  {"Callsing", "-", "Main"},
                  {"IFFcode", "A12345", "Main"},
                  {"Identification", "z", "Main"},
                  {"Type", "System", "Main"},
                  {"Master", "radar2", "Main"},
                  {"Latitude", 15, "Location"},
                  {"Longitude", 8, "Location"},
                  {"Altitude", 12, "Location"},
                  {"Pos", "Pos5", "Location"},
                  {"Heading", 46, "Location"},
                  {"Speed", "m/s", "Location"},
                  {"Battle", "qrc:/icons/battle-icon.jpg", "Main"},
                  {"Target", "qrc:/icons/target-icon.jpg", "Main"},
                  {"More", "qrc:/icons/more-icon.jpg", "Main"}}});
    Data.append({{{"color", "orange", "Main"},
                  {"icon", "qrc:/icons/station-icon.jpg", "Main"},
                  {"Name", "farhad", "Main"},
                  {"TN", 15, "Main"},
                  {"Callsing", "-", "Main"},
                  {"IFFcode", "A12345", "Main"},
                  {"Identification", "z", "Main"},
                  {"Type", "Station", "Main"},
                  {"Master", "radar2", "Main"},
                  {"Latitude", 71, "Location"},
                  {"Longitude", 1, "Location"},
                  {"Altitude", 1, "Location"},
                  {"Pos", "Pos6", "Location"},
                  {"Heading", 46, "Location"},
                  {"Speed", "m/s", "Location"},
                  {"Battle", "qrc:/icons/battle-icon.jpg", "Main"},
                  {"Target", "qrc:/icons/target-icon.jpg", "Main"},
                  {"More", "qrc:/icons/more-icon.jpg", "Main"}}});
    Data.append({{{"color", "red", "Main"},
                  {"icon", "qrc:/icons/aircraft-icon.jpg", "Main"},
                  {"Name", "shahab", "Main"},
                  {"TN", 0, "Main"},
                  {"Callsing", "Cls", "Main"},
                  {"IFFcode", "A12345", "Main"},
                  {"Identification", "z", "Main"},
                  {"Type", "Aircraft", "Main"},
                  {"Master", "radar2", "Main"},
                  {"Latitude", 41, "Location"},
                  {"Longitude", 9, "Location"},
                  {"Altitude", 90, "Location"},
                  {"Pos", "Pos7", "Location"},
                  {"Heading", 46, "Location"},
                  {"Speed", "m/s", "Location"},
                  {"Battle", "qrc:/icons/battle-icon.jpg", "Main"},
                  {"Target", "qrc:/icons/target-icon.jpg", "Main"},
                  {"More", "qrc:/icons/more-icon.jpg", "Main"}}});
    Data.append({{{"color", "pink", "Main"},
                  {"icon", "qrc:/icons/system-icon.jpg", "Main"},
                  {"Name", "alireza", "Main"},
                  {"TN", 4, "Main"},
                  {"Callsing", "-", "Main"},
                  {"IFFcode", "A12345", "Main"},
                  {"Identification", "z", "Main"},
                  {"Type", "System", "Main"},
                  {"Master", "radar2", "Main"},
                  {"Latitude", 12, "Location"},
                  {"Longitude", 9, "Location"},
                  {"Altitude", 10, "Location"},
                  {"Pos", "Pos8", "Location"},
                  {"Heading", 46, "Location"},
                  {"Speed", "m/s", "Location"},
                  {"Battle", "qrc:/icons/battle-icon.jpg", "Main"},
                  {"Target", "qrc:/icons/target-icon.jpg", "Main"},
                  {"More", "qrc:/icons/more-icon.jpg", "Main"}}});
    Data.append({{{"color", "brown", "Main"},
                  {"icon", "qrc:/icons/station-icon.jpg", "Main"},
                  {"Name", "mehrdad", "Main"},
                  {"TN", 5, "Main"},
                  {"Callsing", "-", "Main"},
                  {"IFFcode", "A12345", "Main"},
                  {"Identification", "z", "Main"},
                  {"Type", "Station", "Main"},
                  {"Master", "radar2", "Main"},
                  {"Latitude", 120, "Location"},
                  {"Longitude", 2, "Location"},
                  {"Altitude", 2, "Location"},
                  {"Pos", "Pos9", "Location"},
                  {"Heading", 46, "Location"},
                  {"Speed", "m/s", "Location"},
                  {"Battle", "qrc:/icons/battle-icon.jpg", "Main"},
                  {"Target", "qrc:/icons/target-icon.jpg", "Main"},
                  {"More", "qrc:/icons/more-icon.jpg", "Main"}}});
    Data.append({{{"color", "yellow", "Main"},
                  {"icon", "qrc:/icons/aircraft-icon.jpg", "Main"},
                  {"Name", "hossein", "Main"},
                  {"TN", 32, "Main"},
                  {"Callsing", "Cls", "Main"},
                  {"IFFcode", "A12345", "Main"},
                  {"Identification", "z", "Main"},
                  {"Type", "Aircraft", "Main"},
                  {"Master", "radar2", "Main"},
                  {"Latitude", 100, "Location"},
                  {"Longitude", 3, "Location"},
                  {"Altitude", 20, "Location"},
                  {"Pos", "Pos1", "Location"},
                  {"Heading", 46, "Location"},
                  {"Speed", "m/s", "Location"},
                  {"Battle", "qrc:/icons/battle-icon.jpg", "Main"},
                  {"Target", "qrc:/icons/target-icon.jpg", "Main"},
                  {"More", "qrc:/icons/more-icon.jpg", "Main"}}});
    Data.append({{{"color", "green", "Main"},
                  {"icon", "qrc:/icons/system-icon.jpg", "Main"},
                  {"Name", "hassan", "Main"},
                  {"TN", 100, "Main"},
                  {"Callsing", "-", "Main"},
                  {"IFFcode", "A12345", "Main"},
                  {"Identification", "z", "Main"},
                  {"Type", "System", "Main"},
                  {"Master", "radar2", "Main"},
                  {"Latitude", 13, "Location"},
                  {"Longitude", 5, "Location"},
                  {"Altitude", 79, "Location"},
                  {"Pos", "Pos2", "Location"},
                  {"Heading", 46, "Location"},
                  {"Speed", "m/s", "Location"},
                  {"Battle", "qrc:/icons/battle-icon.jpg", "Main"},
                  {"Target", "qrc:/icons/target-icon.jpg", "Main"},
                  {"More", "qrc:/icons/more-icon.jpg", "Main"}}});

    //    Data.append({{"color", "green","Main"},{"Name", "ahmad","Main"},{"type","train","Main"},{"latitude",10,"Location"}});
    //    Data.append({"Name", "train", "Main", {{"train", "green","iconSource"}}});
    //    Data.append({"Name", "taxi", "Main", {{"train", "green","iconSource"}}});
    //    Data.append({"Name", "rocket", "Main", {{"train", "green","iconSource"}}});
    //    Data.append({"Name", "motor", "Main", {{"train", "green","iconSource"}}});
    //    for (auto &dataFor : Data) {
    //        qDebug()<<dataFor.FieldData.at(0).value;
    //    }
    // ENDTEST

    selectionModel = new QItemSelectionModel();
}

int MyTableView::rowCount(const QModelIndex &) const
{
    //    qDebug() <<Data.at(0).FieldData.size();
    //        qDebug() <<Data.size();
    return Data.size();
}

int MyTableView::columnCount(const QModelIndex &) const
{
    //qDebug()<<Data.at(0).FieldData.size();
    return Data.at(0).FieldData.size();
}

QVariant MyTableView::data(const QModelIndex &index, int role) const
{
    if(role == Qt::BackgroundRole)
    {
        // color of first column
        if (index.column() == 0) {
            //            for (int i = 0; i < Data.size(); i++) {
            ////                qDebug()<<Data.at(i).FieldData.at(0).value;
            //                QVariant colorFirsColumn = Data.at(i).FieldData.at(0).value;
            //                if(index.row() == i){
            //                    QColor Background(colorFirsColumn.toString());
            //                    return Background;
            //                }
            //            }
            return QColor(Data.at(index.row()).FieldData.at(index.column()).value.toString());
        }
        //        if (index.row())   //change background only for cell(1,2)
        //        {
        QColor Background("#DEE3E6"); //#bac4f5
        return Background;
        //        }
        //        else{
        //            QColor Background("#DEE3E6"); //#e1e5fc
        //            return Background;
        //        }
        //        if(index.row()){
        //            QColor Background("#bac4f5");
        //            return Background;
        //        }
    }

    if (role == Qt::DecorationRole && index.column() == 1 || index.column() == 15
        || index.column() == 16 || index.column() == 17) {
        return Data.at(index.row()).FieldData.at(index.column()).value.toString();
        //QPixmap pixmap(Data.at(index.row()).FieldData.at(index.column()).value);
    }

    if (role == Qt::DisplayRole) {
        //        for (int i = 0; i < Data.size(); i++) {
        //            if(index.column() == i){
        //                return Data.at(index.row()).FieldData.at(index.column()).value;}
        //        }
        return Data.at(index.row()).FieldData.at(index.column()).value;
    } else {
        return QVariant("defualt");
    }
}

QVariant MyTableView::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return Data.at(0).FieldData.at(section).name;
    //    else if (role == Qt::DisplayRole && orientation == Qt::Vertical)
    //        return section + 1;
    else
        return QVariant("defualt");
}

int MyTableView::getColumnCount()
{
    return Data.at(0).FieldData.size();
}

void MyTableView::selectionRow(int Row, int Column)
{
    //qDebug()<<"Row: "<<Row <<"Column: "<< Column;
    selectionModel->clear();
    for (int i = 0; i < Row; i++) {
        selectionModel->select(index(Column, i), QItemSelectionModel::Select);
    }
}

QItemSelectionModel *MyTableView::selectRowModel()
{
    return selectionModel;
}


QHash<int, QByteArray> MyTableView::roleNames() const
{
    return {
            {Qt::DisplayRole, "display"},
            {Qt::BackgroundRole, "background"},
            {Qt::DecorationRole, "decorate"}
            //             {Qt::EditRole, "edit"},
            };
}
