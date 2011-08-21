#pragma once
 #include <QtGui/QStyledItemDelegate>

class CameraPropertyModelDelegate:public QStyledItemDelegate
{
	Q_OBJECT
public:
	CameraPropertyModelDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
		void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
     void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;


	~CameraPropertyModelDelegate(void);

	public slots:
		void onCheckBoxStateChanged(int);
};
