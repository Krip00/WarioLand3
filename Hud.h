#pragma once

#include <QWidget>
#include "Sprites.h"
#include "MenuNumber.h"

namespace WL3
{
	class HUD;
}


class WL3::HUD : public QWidget
{
	Q_OBJECT

	private:
		QPixmap _background;
		int _fps;
		QPixmap _number_menu[10];
        QPixmap _little_keys[4];

		MenuNumber *_menu_num;      // monete giganti
        MenuNumber *_menu_num_1;    // monete totali (centinaia)
        MenuNumber *_menu_num_2;    // monete totali (decine)
        MenuNumber *_menu_num_3;    // monete totali (unita)        
		
    public:

		HUD(int w, int h, QWidget* parent);

        void reset() {_fps = 0;}
        void setFPS(int v)   { _fps= v; update(); }
        void advance() { update(); }
        void menuPause(int c, int tc, int lc);

		virtual void paintEvent(QPaintEvent* event) override;

};

