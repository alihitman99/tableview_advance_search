#include <QQmlComponent>

#include "list.h"
//#include "myproxymodel.h"

//--------------------------------ListManager-----------------------
ListManager::ListManager(QQmlEngine *engine)
{
    m_proxyModel = new ListProxyModel;
    m_engine = engine;
    createQml();
}

void ListManager::createQml()
{
    QQmlComponent *comp = new QQmlComponent(m_engine);

    connect(comp, &QQmlComponent::statusChanged, [&] {
        if (comp->status() == QQmlComponent::Status::Error) {
            qDebug() << comp->errorString();
        }

        //qDebug() << m_proxyModel << m_newProxyModel;
        m_qmlItem = qobject_cast<QQuickItem *>(comp->create());
        m_qmlItem->setProperty("tableModel", QVariant::fromValue(m_proxyModel));
        
    });

    //qDebug() << "it is what it is";
    comp->loadUrl(QUrl("qrc:/MyTableView.qml"));
}

ListProxyModel *ListManager::proxyModel() const
{
    //qDebug() << "chch";
    return m_proxyModel;
}

void ListManager::setProxyModel(ListProxyModel *newProxyModel)
{
    //qDebug() << "chchch";
    m_proxyModel = newProxyModel;
}

QQuickItem *ListManager::qmlItem() const
{
    return m_qmlItem;
}

void ListManager::setQmlItem(QQuickItem *newQmlItem)
{
    if (m_qmlItem == newQmlItem)
        return;
    m_qmlItem = newQmlItem;
    emit qmlItemChanged();
}

//--------------------------------------ListProxyModel-------------------------------------

ListProxyModel::ListProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    //    int DataTableSize = dynamic_cast<ListModel*>(sourceModel())->Data.at(0).FieldData.size();
    //    for (int i = 0; i < DataTableSize; i++) {
    //        columnName.append(dynamic_cast<ListModel*>(sourceModel())->Data.at(0).FieldData.at(i).name);
    //    }
    ListModel *listModel = new ListModel;
    for (int i = 0; i < listModel->Data.at(0).FieldData.size(); i++) {
        columnName.append(listModel->Data.at(0).FieldData.at(i).name);
    }
    //add column Int to columnNameInt
    for (int i = 0; i < listModel->Data.at(0).FieldData.size(); ++i) {
        if (listModel->Data.at(0).FieldData.at(i).value.type() == QVariant::Int) {
            //qDebug()<<listModel.Data.at(0).FieldData.at(i).name;
            columnNameInt.append(listModel->Data.at(0).FieldData.at(i).name);
        }
    }
    setSourceModel(listModel);

    //    qDebug()<<columnNameInt;
    //    qDebug()<<dynamic_cast<ListModel *>(sourceModel())->Data.at(0).FieldData.size();
}

bool ListProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);

    QVariant rightData = sourceModel()->data(right);
    //qDebug() << leftData << rightData;
    return leftData.toString() < rightData.toString();
}

void ListProxyModel::sortTable(int column)
{
    //qDebug() << "call sort" << column;
    if (Asc) {
        qDebug() << "Ascending Sort>>>>>";
        sort(column, Qt::AscendingOrder);
        Asc = false;
    } else if (!Asc) {
        qDebug() << "Descending Sort>>>>>";
        sort(column, Qt::DescendingOrder);
        Asc = true;
    }
    invalidateFilter();
}

bool ListProxyModel::filterAcceptsColumn(int sourceColumn, const QModelIndex &sourceParent) const
{
    if (m_filterColumn == tabList.at(0)) { //Main
        //        qDebug()<<sourceModel()->headerData(sourceColumn,Qt::Horizontal);
        //        QModelIndex index = sourceModel()->index(0, sourceColumn, sourceParent);
        //        QVariant data = sourceModel()->data(index);
        QVariant data = sourceModel()->headerData(sourceColumn, Qt::Horizontal);
        bool result = false;
        for (int i = 0; i < columnName.size(); ++i) {
            if (i <= Ecolumn::EMaster || i >= Ecolumn::EBattle) {
                //qDebug()<<Ecolumn::EMaster;
                result = result || data.toString().contains(columnName.at(i), Qt::CaseInsensitive);
            }
        }
        return result;
    } else if (m_filterColumn == tabList.at(1)) { //Location
        QVariant data = sourceModel()->headerData(sourceColumn, Qt::Horizontal);
        bool result = false;
        for (int i = 0; i < columnName.size(); ++i) {
            if (i <= Ecolumn::EName || i >= Ecolumn::ELatitude) {
                result = result || data.toString().contains(columnName.at(i), Qt::CaseInsensitive);
            }
        }
        return result;
    }
    return true;
}

bool ListProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    //search Tag all of them
    bool resultName = m_filterName.isEmpty();
    bool result1 = Tags.isEmpty();
    bool result2 = TagFilter1.isEmpty();
    bool result3 = TagFilter2.isEmpty();
    bool result4 = TagFilter3.isEmpty();
    //    if(!Tags.isEmpty())
    //        result1 = false;
    //    if(!TagFilter1.isEmpty())
    //        result2 = false;
    //    if(!TagFilter2.isEmpty())
    //        result3 = false;
    //    if(!TagFilter3.isEmpty())
    //        result4 = false;
    if (m_search == "filter") {
        for (int iter = 0; iter < columnName.size(); ++iter) {
            QModelIndex index = sourceModel()->index(sourceRow, iter, sourceParent);
            QVariant data = sourceModel()->data(index);
            for (int i = 0; i < Tags.size(); ++i) {
                if (columnName.at(iter) == Tags.at(i).name) {
                    result1 = result1
                              || data.toString().contains(Tags.at(i).value, Qt::CaseInsensitive);
                }
            }
            for (int j = 0; j < TagFilter1.size(); ++j) {
                if (columnName.at(iter) == TagFilter1.at(j).name) {
                    //qDebug()<<TagFilter1.at(j).name;
                    result2 = result2
                              || data.toString().contains(TagFilter1.at(j).value,
                                                          Qt::CaseInsensitive);
                }
            }
            for (int i = 0; i < TagFilter2.size(); ++i) {
                if (columnName.at(iter) == TagFilter2.at(i).name) {
                    //qDebug()<< Tags.at(i).valueFrom << Tags.at(i).valueTo;
                    result3 = result3
                              || (data.toInt() >= TagFilter2.at(i).valueFrom
                                  && data.toInt() <= TagFilter2.at(i).valueTo);
                }
            }
            for (int i = 0; i < TagFilter3.size(); ++i) {
                if (columnName.at(iter) == TagFilter3.at(i).name) {
                    //qDebug()<<TagFilter3.at(i).mark ;
                    if (TagFilter3.at(i).mark == "<")
                        result4 = result4 || data.toInt() < TagFilter3.at(i).value;
                    else if (TagFilter3.at(i).mark == "<=")
                        result4 = result4 || data.toInt() <= TagFilter3.at(i).value;
                    else if (TagFilter3.at(i).mark == "=")
                        result4 = result4 || data.toInt() == TagFilter3.at(i).value;
                    else if (TagFilter3.at(i).mark == ">")
                        result4 = result4 || data.toInt() > TagFilter3.at(i).value;
                    else if (TagFilter3.at(i).mark == ">=")
                        result4 = result4 || data.toInt() >= TagFilter3.at(i).value;
                    //else return true;
                }
            }
            if (data.toString().contains(m_filterName, Qt::CaseInsensitive)) {
                resultName = resultName
                             || data.toString().contains(m_filterName, Qt::CaseInsensitive);
            }
        }
        return result1 && result2 && result3 && result4 && resultName;
    }

    if (m_search == "type") {
        QModelIndex index = sourceModel()->index(sourceRow, Ecolumn::EType, sourceParent);
        QVariant data = sourceModel()->data(index);
        if (m_filterType == "All")
            return true;
        else
            return data.toString().contains(m_filterType, Qt::CaseInsensitive);
    }

    //    if (m_search == "attack") {
    //        //qDebug() << attakerList.at(0);
    //        QModelIndex index = sourceModel()->index(sourceRow, Ecolumn::EName, sourceParent);
    //        QVariant data = sourceModel()->data(index);

    //        for (int i = 0; i < attakerList.size(); ++i) {
    //            if (data.toString() == attakerList.at(i)) {
    //                return true;
    //            }
    //        }
    //        return false;
    //    }

    //    if(m_search == "filterAllTable"){
    //        bool resultName = false;
    //        //qDebug()<<m_filterName;
    //        int itrator = listModel->Data.at(0).FieldData.size();
    //        for (int i = 0; i < itrator; ++i) {
    //            QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);
    //            QVariant data = sourceModel()->data(index);
    //            //qDebug()<<data;
    //            if(data.toString().contains(m_filterName, Qt::CaseInsensitive))
    //                resultName = resultName || data.toString().contains(m_filterName, Qt::CaseInsensitive);
    //        }
    //        return resultName;
    //    }
    //qDebug()<<"cx";
    return true;
}

void ListProxyModel::nodeTypeFilter(QString type)
{
    m_filterType = type;
    m_search = "type";
    invalidateFilter();
}

void ListProxyModel::filterString(QString search, QString value)
{
    m_filterName = value;
    //m_search = search;
    m_search = "filter";
    //qDebug() << value;
    invalidateFilter();
}

void ListProxyModel::filterStringColumn(QString tabName)
{
    m_filterColumn = tabName;
    invalidateFilter();
}

QList<QString> ListProxyModel::getDataComboBox()
{

    return columnName;
}

QList<QString> ListProxyModel::getDataComboBoxInt()
{
    return columnNameInt;
}

QList<QString> ListProxyModel::getColorFilter()
{
    int iter = dynamic_cast<ListModel *>(sourceModel())->Data.size();
    for (int i = 0; i < iter; ++i) {
        QString color
            = dynamic_cast<ListModel *>(sourceModel())->Data.at(i).FieldData.at(0).value.toString();
        colorList.append({color});
        std::sort(colorList.begin(), colorList.end());
        auto last = std::unique(colorList.begin(), colorList.end());
        colorList.erase(last, colorList.end());
        //qDebug() << "Original List:" << colorList;

        //        QSet<QString>colorListS(colorList.begin(), colorList.end());
        //        colorList = colorListS;
        //        QSet<QString> colorListSet(colorList.begin(), colorList.end());
        //        qDebug()<<colorListSet;
        //        QSet<QString> colorListSet = colorList.to();
        //        qDebug()<<colorListSet;
        //        QList<QString> colorList = colorListSet.toList();
    }

    return colorList;
}

void ListProxyModel::addTag(QString name, QString value)
{
    Tags.append({name, value});
    m_search = "filter";
    invalidateFilter();
}

void ListProxyModel::addTag1(QString name, QString value)
{
    TagFilter1.append({name, value});
    m_search = "filter";
    invalidateFilter();
}

void ListProxyModel::addTag2(QString name, int value1, int value2)
{
    TagFilter2.append({name, value1, value2});
    m_search = "filter";
    invalidateFilter();
}

void ListProxyModel::addTag3(QString name, int value, QString mark)
{
    TagFilter3.append({name, value, mark});
    m_search = "filter";
    invalidateFilter();
}

void ListProxyModel::removeTag(QString filterSearch, QString name, QString value1)
{
    //qDebug()<<filterSearch<<name<<value1;
    if (filterSearch == "colorFilter") {
        //qDebug()<<"ssss";
        Tags.removeIf(
            [valueToRemove = value1](const FilterTag &s) { return s.value == valueToRemove; });
        //        Tags.removeAll([valueToRemove = value1](const FilterTag& s) {
        //            return s.name == nameToRemove;
        //        });
    }
    if (filterSearch == "filter1") {
        TagFilter1.removeIf([valueToRemove = value1, nameToRemove = name](const FilterTag1 &s) {
            return s.value == valueToRemove && s.name == nameToRemove;
        });
    }
    if (filterSearch == "filter2") {
        TagFilter2.removeIf([valueToRemove = value1, nameToRemove = name](const FilterTag2 &s) {
            return s.valueFrom == valueToRemove.toInt() && s.name == nameToRemove;
        });
    }
    if (filterSearch == "filter3") {
        TagFilter3.removeIf([valueToRemove = value1, nameToRemove = name](const FilterTag3 &s) {
            return s.value == valueToRemove.toInt() && s.name == nameToRemove;
        });
    }

    if (Tags.empty() && TagFilter1.empty() && TagFilter2.empty() && TagFilter3.empty())
        m_search = "";
    //    qDebug()<<Tags.empty();
    invalidateFilter();
}

void ListProxyModel::selectionRow(int Row, int Column)
{
    dynamic_cast<ListModel *>(sourceModel())->selectionRow(Row, Column);
}

QItemSelectionModel *ListProxyModel::selectRowModel()
{
    return dynamic_cast<ListModel *>(sourceModel())->selectRowModel();
}

QList<QString> ListProxyModel::getTabBarName()
{
    tabList.append({"Main", "Location", "Assignment", "Detection", "Sends"});

    return tabList;
}

QList<QString> ListProxyModel::getFilterData()
{
    FilterDataList.append({"All", "Aircraft", "System", "Station"});
    return FilterDataList;
}

QStringList ListProxyModel::filterCombo(QString text, QString nameFilter)
{
    QStringList filteredList;
    if (nameFilter == "String") {
        for (const QString &item : columnName) {
            if (item.contains(text, Qt::CaseInsensitive)) {
                filteredList.append(item);
            }
        }
    } else if (nameFilter == "Int") {
        for (const QString &item : columnNameInt) {
            if (item.contains(text, Qt::CaseInsensitive)) {
                filteredList.append(item);
            }
        }
    }
    return filteredList;
}

void ListProxyModel::attacker(QString name)
{
    dynamic_cast<ListModel *>(sourceModel())->attacker(name);
}

void ListProxyModel::setChangeModel(QString checkModel)
{
    dynamic_cast<ListModel *>(sourceModel())->setChangeModel(checkModel);
}

//-----------------------------------------ListModel------------------------------------

#include <QColor>
#include <QDebug>
#include <QPixmap>

ListModel::ListModel(QObject *parent)
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

int ListModel::rowCount(const QModelIndex &) const
{
    //    qDebug() <<Data.at(0).FieldData.size();
    //        qDebug() <<Data.size();
    if (modelType == "attackerModel")
        return DataAttacker->size();
    return Data.size();
}

int ListModel::columnCount(const QModelIndex &) const
{
    //qDebug()<<Data.at(0).FieldData.size();
    if (modelType == "attackerModel")
        return DataAttacker->at(0).FieldData.size();
    return Data.at(0).FieldData.size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    //qDebug() << "changeModel: " << modelType;
    if (role == Qt::BackgroundRole) {
        // color of first column
        if (index.column() == 0) {
            if (modelType == "attackerModel") {
                return QColor(
                    DataAttacker->at(index.row()).FieldData.at(index.column()).value.toString());
            }
            return QColor(Data.at(index.row()).FieldData.at(index.column()).value.toString());
        }
        //        if (index.row())   //change background only for cell(1,2)
        //        {
        QColor Background("#DEE3E6"); //#bac4f5 //#DEE3E6
        return Background;
    }

    if (role == Qt::DecorationRole && index.column() == 1 || index.column() == 15
        || index.column() == 16 || index.column() == 17) {
        if (modelType == "attackerModel") {
            return DataAttacker->at(index.row()).FieldData.at(index.column()).value.toString();
        }
        return Data.at(index.row()).FieldData.at(index.column()).value.toString();
    }

    if (role == Qt::DisplayRole) {
        //        for (int i = 0; i < Data.size(); i++) {
        //            if(index.column() == i){
        //                return Data.at(index.row()).FieldData.at(index.column()).value;}
        //        }

        if (modelType == "attackerModel") {
            //qDebug() << "change Model!!!!!";
            return DataAttacker->at(index.row()).FieldData.at(index.column()).value;
        }
        return Data.at(index.row()).FieldData.at(index.column()).value;
    } else {
        return QVariant("defualt");
    }
}

QVariant ListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return Data.at(0).FieldData.at(section).name;
    //    else if (role == Qt::DisplayRole && orientation == Qt::Vertical)
    //        return section + 1;
    else
        return QVariant("defualt");
}

void ListModel::selectionRow(int Row, int Column)
{
    qDebug() << "Row: " << Row << "Column: " << Column;
    selectionModel->clear();
    //selectionModel->select(index(0, 2), QItemSelectionModel::Select);
    for (int i = 0; i < Column; i++) {
        selectionModel->select(index(1, i), QItemSelectionModel::Select);
    }
}

QItemSelectionModel *ListModel::selectRowModel()
{
    return selectionModel;
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    return {
        {Qt::DisplayRole, "display"},
        {Qt::BackgroundRole, "background"},
        {Qt::DecorationRole, "decorate"},
        {Qt::EditRole, "editRole"}
        //             {Qt::EditRole, "edit"},
    };
}

void ListModel::attacker(QString name)
{
    //qDebug() << "input" << name;
    DataAttacker->clear();

    int bound = Data.size();
    for (int i = 0; i < bound; ++i) {
        if (Data.at(i).FieldData.at(2).value.toString() == name) {
            //qDebug() << "what is name: " << Data.at(i).FieldData.at(2).value;
            DataAttacker->append(Data.at(i));
            //qDebug() << "Data Attacker: " << DataAttacker->at(0).FieldData.at(2).value.toString();
        }
    }
    int randNum1 = QRandomGenerator::global()->bounded(1, bound);
    int randNum2 = QRandomGenerator::global()->bounded(1, bound);
    DataAttacker->append(Data.at(randNum1));
    DataAttacker->append(Data.at(randNum2));
    //    int total = QRandomGenerator::global()->bounded(1, bound); //number of random row
    //    //qDebug() << "totalRand: " << total;
    //    for (int i = 0; i < total; ++i) {
    //        int randomValue = QRandomGenerator::global()->bounded(0, bound); //which one row
    //        //QString value = Data.at(randomValue).FieldData.at(2).value.toString();
    //        DataAttacker->append(Data.at(randomValue));
    //        qDebug() << DataAttacker->at(i).FieldData.at(2).value.toString();
    //    }
}

void ListModel::setChangeModel(QString checkModel)
{
    beginResetModel();
    modelType = checkModel;
    qDebug() << "Set Model: " << modelType;
    endResetModel();
}
