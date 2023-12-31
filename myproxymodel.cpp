#include "myproxymodel.h"
#include "mytableview.h"
#include <QDebug>

MyProxyModel::MyProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    //    int DataTableSize = dynamic_cast<MyTableView*>(sourceModel())->Data.at(0).FieldData.size();
    //    for (int i = 0; i < DataTableSize; i++) {
    //        columnName.append(dynamic_cast<MyTableView*>(sourceModel())->Data.at(0).FieldData.at(i).name);
    //    }
    for (int i = 0; i < myTableModel.Data.at(0).FieldData.size(); i++) {
        columnName.append(myTableModel.Data.at(0).FieldData.at(i).name);
    }
    //add column Int to columnNameInt
    for (int i = 0; i < myTableModel.Data.at(0).FieldData.size(); ++i) {
        if(myTableModel.Data.at(0).FieldData.at(i).value.type() == QVariant::Int){
            //qDebug()<<myTableModel.Data.at(0).FieldData.at(i).name;
            columnNameInt.append(myTableModel.Data.at(0).FieldData.at(i).name);
        }
    }

    MyTableView *table = new MyTableView;
    setSourceModel(table);

    //    qDebug()<<columnNameInt;
    //    qDebug()<<dynamic_cast<MyTableView *>(sourceModel())->Data.at(0).FieldData.size();
}

bool MyProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);
    return leftData.toString() < rightData.toString();
}

void MyProxyModel::sortTable(int column)
{
    //    qDebug()<<"call sort" << column;
    if(Asc){
        qDebug()<<"Ascending Sort>>>>>";
        sort(column, Qt::AscendingOrder);
        Asc = false;
    }
    else if(!Asc){
        qDebug()<<"Descending Sort>>>>>";
        sort(column, Qt::DescendingOrder);
        Asc = true;
    }
    invalidateFilter();
}

bool MyProxyModel::filterAcceptsColumn(int sourceColumn, const QModelIndex &sourceParent) const
{
    if(m_filterColumn == tabList.at(0)){ //Main
        //        qDebug()<<sourceModel()->headerData(sourceColumn,Qt::Horizontal);
        //        QModelIndex index = sourceModel()->index(0, sourceColumn, sourceParent);
        //        QVariant data = sourceModel()->data(index);
        QVariant data = sourceModel()->headerData(sourceColumn,Qt::Horizontal);
        bool result = false;
        for (int i = 0; i < columnName.size(); ++i) {
            if (i <= Ecolumn::EMaster || i >= Ecolumn::EBattle) {
                //qDebug()<<Ecolumn::EMaster;
                result = result || data.toString().contains(columnName.at(i), Qt::CaseInsensitive);
            }
        }
        return result;
    }
    else if(m_filterColumn == tabList.at(1)){ //Location
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


bool MyProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    //search Tag all of them
    bool res = m_filterName.isEmpty();
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
    if(m_search == "filter"){
        for (int iter = 0; iter < columnName.size(); ++iter) {
            QModelIndex index = sourceModel()->index(sourceRow, iter, sourceParent);
            QVariant data = sourceModel()->data(index);                
            for (int i = 0; i < Tags.size(); ++i) {
                if(columnName.at(iter) == Tags.at(i).name){
                    result1 = result1 || data.toString().contains(Tags.at(i).value, Qt::CaseInsensitive);
                }
            }
            for (int j = 0; j < TagFilter1.size(); ++j) {
                if(columnName.at(iter) == TagFilter1.at(j).name){
                    //qDebug()<<TagFilter1.at(j).name;
                    result2 = result2 || data.toString().contains(TagFilter1.at(j).value, Qt::CaseInsensitive);
                }

            }
            for (int i = 0; i < TagFilter2.size(); ++i) {
                if(columnName.at(iter) == TagFilter2.at(i).name){
                    //qDebug()<< Tags.at(i).valueFrom << Tags.at(i).valueTo;
                    result3 = result3 || (data.toInt() >= TagFilter2.at(i).valueFrom && data.toInt() <= TagFilter2.at(i).valueTo);
                }
            }
            for (int i = 0; i < TagFilter3.size(); ++i) {
                if(columnName.at(iter) == TagFilter3.at(i).name){
                    //qDebug()<<TagFilter3.at(i).mark ;
                    if(TagFilter3.at(i).mark == "<") result4 = result4 || data.toInt() < TagFilter3.at(i).value;
                    else if(TagFilter3.at(i).mark == "<=") result4 = result4 || data.toInt() <= TagFilter3.at(i).value;
                    else if(TagFilter3.at(i).mark == "=") result4 = result4 || data.toInt() == TagFilter3.at(i).value;
                    else if(TagFilter3.at(i).mark == ">") result4 = result4 || data.toInt() > TagFilter3.at(i).value;
                    else if(TagFilter3.at(i).mark == ">=") result4 = result4 || data.toInt() >= TagFilter3.at(i).value;
                    //else return true;
                }
            }
            if(data.toString().contains(m_filterName, Qt::CaseInsensitive)){
                res = res || data.toString().contains(m_filterName, Qt::CaseInsensitive);
            }
        }
        return result1 && result2 && result3 && result4 && res;
    }

    if (m_search == "attack") {
        bool resultAttaker = attakerList.isEmpty();
        //qDebug() << attakerList.at(0);
        for (int iter = 0; iter < columnName.size(); ++iter) {
            QModelIndex index = sourceModel()->index(sourceRow, Ecolumn::EName, sourceParent);
            QVariant data = sourceModel()->data(index);
            for (int i = 0; i < attakerList.size(); ++i) {
                if (data.toString() == attakerList.at(i)) {
                    resultAttaker = resultAttaker || true;
                }
            }
        }
        return resultAttaker;
    }

    //    if(m_search == "filterAllTable"){
    //        bool res = false;
    //        //qDebug()<<m_filterName;
    //        int itrator = myTableModel.Data.at(0).FieldData.size();
    //        for (int i = 0; i < itrator; ++i) {
    //            QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);
    //            QVariant data = sourceModel()->data(index);
    //            //qDebug()<<data;
    //            if(data.toString().contains(m_filterName, Qt::CaseInsensitive))
    //                res = res || data.toString().contains(m_filterName, Qt::CaseInsensitive);
    //        }
    //        return res;
    //    }
    //qDebug()<<"cx";
    return true;
}

void MyProxyModel::filterString(QString search, QString value)
{
    m_filterName = value;
    //m_search = search;
    m_search = "filter";
    qDebug()<<value;
    invalidateFilter();
}


void MyProxyModel::filterStringColumn(QString tabName)
{
    m_filterColumn = tabName;
    invalidateFilter();
}


int MyProxyModel::getColumnCount()
{
    return dynamic_cast<MyTableView*>(sourceModel())->getColumnCount();
}

QList<QString> MyProxyModel::getDataComboBox()
{
    //    for (int i = 0; i < myTableModel.Data.at(0).FieldData.size(); ++i) {
    //        //appendItem(sourceModel()->headerData(i, Qt::Horizontal).toString());
    //        //columnName.append(sourceModel()->headerData(i, Qt::Horizontal).toString());
    //    }

    //    for (const QString &option : model.stringList()) {
    //        if (option.contains(searchText, Qt::CaseInsensitive)) {
    //            filteredOptions.append(option);
    //        }
    //    }

    return columnName;
    //    QStringList filteredOptions;
    //    qDebug() << m_searchTextCombo;
    //    for (const QString &option : columnName) {
    //        //qDebug() << option;
    //        if (option.contains(m_searchTextCombo, Qt::CaseInsensitive) && m_searchTextCombo != "") {
    //            qDebug() << option;
    //            filteredOptions.append({option});
    //        }
    //    }
    //    return filteredOptions;
}

QList<QString> MyProxyModel::getDataComboBoxInt()
{
    return columnNameInt;
}

QList<QString> MyProxyModel::getColorFilter()
{
    int iter = dynamic_cast<MyTableView*>(sourceModel())->Data.size();
    for (int i = 0; i < iter; ++i) {
        QString color = dynamic_cast<MyTableView*>(sourceModel())->Data.at(i).FieldData.at(0).value.toString();
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

void MyProxyModel::addTag(QString name, QString value)
{
    //qDebug()<<name << value;
    //Tags.clear();
    Tags.append({name, value});
    m_search = "filter";
    invalidateFilter();
}

void MyProxyModel::addTag1(QString name, QString value)
{
    //Tags.clear();
    //Tags.append({name, value});
    TagFilter1.append({name, value});
    m_search = "filter";
    invalidateFilter();
}

void MyProxyModel::addTag2(QString name, int value1, int value2)
{
    //qDebug()<<search << name << value1 << value2;
    //Tags.clear();
    //Tags.append({name,"", value1, value2});
    TagFilter2.append({name, value1, value2});
    m_search = "filter";
    invalidateFilter();
}

void MyProxyModel::addTag3(QString name, int value, QString mark)
{
    //Tags.clear();
    //Tags.append({name, "", value ,0 , mark});
    TagFilter3.append({name, value, mark});
    m_search = "filter";
    invalidateFilter();
}


void MyProxyModel::removeTag(QString filterSearch, QString name, QString value1)
{
    //qDebug()<<filterSearch<<name<<value1;
    if(filterSearch == "colorFilter"){
        //qDebug()<<"ssss";
        Tags.removeIf( [ valueToRemove = value1 ] (const FilterTag &s) {
            return s.value == valueToRemove;
        });
//        Tags.removeAll([valueToRemove = value1](const FilterTag& s) {
//            return s.name == nameToRemove;
//        });
    }
    if(filterSearch == "filter1"){
        TagFilter1.removeIf( [ valueToRemove = value1, nameToRemove = name ] (const FilterTag1 &s) {
            return s.value == valueToRemove && s.name == nameToRemove;
        });
    }
    if(filterSearch == "filter2"){
        TagFilter2.removeIf( [ valueToRemove = value1, nameToRemove = name ] (const FilterTag2 &s) {
            return s.valueFrom == valueToRemove.toInt() && s.name == nameToRemove;
        });
    }
    if(filterSearch == "filter3"){
        TagFilter3.removeIf( [ valueToRemove = value1, nameToRemove = name ] (const FilterTag3 &s) {
            return s.value == valueToRemove.toInt() && s.name == nameToRemove;
        });
    }

    if(Tags.empty() && TagFilter1.empty() && TagFilter2.empty() && TagFilter3.empty())
        m_search = "";
//    qDebug()<<Tags.empty();
    invalidateFilter();
}

void MyProxyModel::selectionRow(int Row, int Column)
{
   dynamic_cast<MyTableView*>(sourceModel())->selectionRow(Row, Column);
}

QItemSelectionModel *MyProxyModel::selectRowModel()
{
    return dynamic_cast<MyTableView*>(sourceModel())->selectRowModel();
}

QList<QString> MyProxyModel::getTabBarName()
{
    tabList.append({"Main", "Location", "Assignment", "Detection", "Sends"});

    return tabList;
}

QStringList MyProxyModel::filterCombo(QString text, QString nameFilter)
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

void MyProxyModel::attacker(QString name)
{
    attakerList.append({name, "mamad", "ahmad", "farhad"});
    m_search = "attack";
    invalidateFilter();
}
