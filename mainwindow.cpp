#include <QTreeView>
#include <QPushButton>
#include <QStatusBar>
#include <QDebug>

#include "mainwindow.h"
#include "data_model.h"
#include "icon_delegate.h"
#include "operator_editor_dialog.h"

static constexpr int SCREEN_WIDTH = 600;
static constexpr int SCREEN_HEIGHT = 800;
static constexpr int MARGIN = 6;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    m_treeView = new QTreeView(this);
    m_statusBar = new QStatusBar(this);
    setStatusBar(m_statusBar);

    m_itemModel = new DataModel(m_treeView);
    m_itemDelegate = new IconDelegate(m_treeView);
    m_treeView->setItemDelegate(m_itemDelegate);
    m_treeView->setModel(m_itemModel);

    m_treeView->viewport()->setAttribute(Qt::WA_Hover);

    m_newItem = new QPushButton("+", m_treeView);
    m_newItem->setFixedSize(64, 64);
    m_newItem->setStyleSheet("font-size: 20px; border: 0px");
    m_newItem->move(this->width() - m_newItem->width() - MARGIN * 3,
        this->height() - m_newItem->height() - MARGIN);

    connect(m_newItem, &QPushButton::clicked, [this]
    {
        m_editorDialog = new OperatorEditorDialog({}, m_itemModel);
        m_editorDialog->exec();
    });

    connect(m_itemDelegate, &IconDelegate::closeButtonClick,
            [](int /*mcc*/, int /*mnc*/)
    {

    });

    connect(m_itemDelegate, &IconDelegate::itemDoubleClick,
            [this](const QModelIndex& index)
    {
        m_editorDialog = new OperatorEditorDialog(index, m_itemModel);
        m_editorDialog->exec();
    });

    setCentralWidget(m_treeView);
}

MainWindow::~MainWindow()
{

}
