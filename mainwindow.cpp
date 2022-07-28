#include "mainwindow.h"
#include <QIcon>
#include <QResizeEvent>
#include <QVBoxLayout>

using namespace WL3;

MainWindow::MainWindow() : QWidget(0)
{
	_game = Game::instance();

	_layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	_layout->setSpacing(0);
	_layout->setContentsMargins(0, 0, 0, 0);
	_layout->addItem(new QSpacerItem(0, 0));
	_layout->addWidget(_game);
	_layout->addItem(new QSpacerItem(0, 0));
	setLayout(_layout);

	setStyleSheet("background-color: black;");

	resize(_game->aspectRatio() * 480, 480);

	setWindowIcon(QIcon(":/icons/wario.ico"));
	setWindowTitle("WarioLand3 [GBC]");
}

void MainWindow::resizeEvent(QResizeEvent* evt)
{
	double thisAspectRatio = (double)evt->size().width() / evt->size().height();
	int widgetStretch, outerStretch;

	if (thisAspectRatio > _game->aspectRatio()) // too wide
	{
		_layout->setDirection(QBoxLayout::LeftToRight);
		widgetStretch = height() * _game->aspectRatio(); // i.e., my width
		outerStretch = (width() - widgetStretch) / 2 + 0.5;
	}
	else // too tall
	{
		_layout->setDirection(QBoxLayout::TopToBottom);
		widgetStretch = width() * (1 / _game->aspectRatio()); // i.e., my height
		outerStretch = (height() - widgetStretch) / 2 + 0.5;
	}

	_layout->setStretch(0, outerStretch);
	_layout->setStretch(1, widgetStretch);
	_layout->setStretch(2, outerStretch);
}
