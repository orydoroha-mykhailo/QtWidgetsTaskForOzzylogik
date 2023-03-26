#pragma once

#include <QMainWindow>

class QTreeView;
class QStatusBar;
class QPushButton;
class DataModel;
class IconDelegate;
class OperatorEditorDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPushButton *m_newItem = nullptr;
    QTreeView *m_treeView = nullptr;
    QStatusBar *m_statusBar = nullptr;
    DataModel *m_itemModel = nullptr;
    IconDelegate *m_itemDelegate = nullptr;
    OperatorEditorDialog *m_editorDialog = nullptr;
};
