#include <QWidget>
#include <QBoxLayout>
#include "Game.h"

namespace WL3
{
	class MainWindow;
}

class WL3::MainWindow : public QWidget
{
	private:

		Game* _game;
		QBoxLayout* _layout;

	public:

		MainWindow();

		virtual void resizeEvent(QResizeEvent* event) override;
};
