#include "Hud.h"
#include "Game.h"
#include "Sprites.h"
#include "MenuNumber.h"

using namespace WL3;

HUD::HUD(int w, int h, QWidget* parent) : QWidget(parent)
{
    _menu_num = nullptr;
    _menu_num_1 = nullptr;
    _menu_num_2 = nullptr;
    _menu_num_3 = nullptr;

    setFixedSize(w, h);

    reset();
}

void HUD::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.setBackgroundMode(Qt::TransparentMode);
    painter.setWindow(0, 0, TILE * 16, TILE * 15);
    painter.drawPixmap(25, 15, _background);
    painter.drawPixmap(20, 15, Sprites::instance()->string("F"));
    painter.drawPixmap(28, 15, Sprites::instance()->string("X"));
    painter.drawPixmap(37, 15, Sprites::instance()->number(_fps));
}

void HUD::menuPause(int c, int tc, int lc)
{
    if (!_menu_num_1)
        delete _menu_num_1;
    if (!_menu_num_2)
        delete _menu_num_2;
    if (!_menu_num_3)
        delete _menu_num_3;


    if (!_menu_num)
        delete _menu_num;

    _menu_num = new MenuNumber(QPointF(3.5 * TILE, 14.5 * TILE), c, 75); // monete giganti

    // centinaia
    if (tc >= 100)
        _menu_num_1 = new MenuNumber(QPointF(7 * TILE, 14.5 * TILE), 1, 75);
    else if (tc > 200)
        _menu_num_1 = new MenuNumber(QPointF(7 * TILE, 14.5 * TILE), 2, 75);
    else
        _menu_num_1 = new MenuNumber(QPointF(7 * TILE, 14.5 * TILE), 0, 75);

    // decine
    if (tc >= 0 && tc < 10)
        _menu_num_2 = new MenuNumber(QPointF(7.5 * TILE, 14.5 * TILE), 0, 75);
    else if (tc >= 10 && tc < 20)
        _menu_num_2 = new MenuNumber(QPointF(7.5 * TILE, 14.5 * TILE), 1, 75);
    else if (tc >= 20 && tc < 30)
        _menu_num_2 = new MenuNumber(QPointF(7.5 * TILE, 14.5 * TILE), 2, 75);
    else if (tc >= 30 && tc < 40)
        _menu_num_2 = new MenuNumber(QPointF(7.5 * TILE, 14.5 * TILE), 3, 75);
    else if (tc >= 40 && tc < 50)
        _menu_num_2 = new MenuNumber(QPointF(7.5 * TILE, 14.5 * TILE), 4, 75);
    else if (tc >= 50 && tc < 60)
        _menu_num_2 = new MenuNumber(QPointF(7.5 * TILE, 14.5 * TILE), 5, 75);
    else if (tc >= 60 && tc < 70)
        _menu_num_2 = new MenuNumber(QPointF(7.5 * TILE, 14.5 * TILE), 6, 75);
    else if (tc >= 70 && tc < 80)
        _menu_num_2 = new MenuNumber(QPointF(7.5 * TILE, 14.5 * TILE), 7, 75);
    else if (tc >= 80 && tc < 90)
        _menu_num_2 = new MenuNumber(QPointF(7.5 * TILE, 14.5 * TILE), 8, 75);
    else if (tc >= 90 && tc < 100)
        _menu_num_2 = new MenuNumber(QPointF(7.5 * TILE, 14.5 * TILE), 9, 75);

    // unità
    if (lc >= 0 && lc < 10)
        _menu_num_3 = new MenuNumber(QPointF(8 * TILE, 14.5 * TILE), lc, 75);
}



