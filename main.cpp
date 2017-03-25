#include "mainwindow.h"
#include <QApplication>

/******************************************************************************/
/*!
 * \brief The HideWidget class (TaskBarにWidgetを表示させない。)
 */
class HideWidget : public QWidget
{
public:
	HideWidget(QWidget *parent) : QWidget(parent, Qt::Dialog) {}
};

/******************************************************************************/
/*!
 * \brief main
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QApplication::setQuitOnLastWindowClosed(false);
	MainWindow w;
	w.show();

	/// タスクバーにWidgetを表示されないようにする。
	HideWidget widget(&w);

	return a.exec();
}
