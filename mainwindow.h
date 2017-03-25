#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSystemTrayIcon;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void on_action_Quit_triggered();

private:
	Ui::MainWindow *ui;

	QSystemTrayIcon* trayIcon;
	QMenu* trayIconMenu;
	QAction *minimizeAction;
	QAction *maximizeAction;
	QAction *restoreAction;
	QAction *quitAction;

	void createActions();
	void createTrayIcon();
};

#endif // MAINWINDOW_H
