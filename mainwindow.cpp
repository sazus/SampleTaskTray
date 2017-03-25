#include <QSystemTrayIcon>
#include <QCloseEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"

/******************************************************************************/
/*!
 * \brief MainWindow::MainWindow
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	/// widgetを常に手前に表示する
	Qt::WindowFlags flags = windowFlags();
	flags |= Qt::WindowStaysOnTopHint;
	setWindowFlags(flags);

	/// タスクトレイのアイコン設定と動作設定
	createTrayIcon();
}

/******************************************************************************/
/*!
 * \brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
	delete ui;
}

/******************************************************************************/
/*!
 * \brief MainWindow::createActions
 *			タスクトレイのメニューと動作設定
 */
void MainWindow::createActions()
{
	minimizeAction = new QAction(tr("最小化"), this);
	connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

	maximizeAction = new QAction(tr("最大化"), this);
	connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

	restoreAction = new QAction(tr("開く"), this);
	connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

	quitAction = new QAction(tr("&Quit"), this);
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

/******************************************************************************/
/*!
 * \brief MainWindow::createTrayIcon
 */
void MainWindow::createTrayIcon()
{
	createActions();

	/// メニューの登録
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(minimizeAction);
	trayIconMenu->addAction(maximizeAction);
	trayIconMenu->addAction(restoreAction);
	trayIconMenu->addAction(quitAction);

	/// タスクトレイアイコンの設定
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->setIcon(QIcon("://icon.png"));
	trayIcon->show();
}

/******************************************************************************/
/*!
 * \brief MainWindow::closeEvent
 * \param event
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
	/// closeイベントが発生してもquitせずにタスクトレイに常駐するようにする。
	if (trayIcon->isVisible()) {
		hide();
		event->ignore();
	}
}

/******************************************************************************/
/*!
 * \brief MainWindow::on_action_Quit_triggered [slot]
 *			メニューバーのQuitからのtriggered()に対してのslot処理
 */
void MainWindow::on_action_Quit_triggered()
{
	qApp->quit();
}
