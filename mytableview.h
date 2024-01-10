#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QAbstractTableModel>
#include <QItemSelectionModel>

class MyTableView : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyTableView(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    int getColumnCount();
    void selectionRow(int rowCount, int idxRow);
    QItemSelectionModel *selectRowModel();



    struct NodeFieldData
    {
        QString name;
        QVariant value;
        QString category;
    };

    struct NodeData
    {
        QVector<NodeFieldData> FieldData;
    };


    QVector<NodeData> Data;
private:
    QItemSelectionModel *selectionModel;
};

#endif // MYTABLEVIEW_H
