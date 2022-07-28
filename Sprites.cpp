#include "Sprites.h"
#include <QBitmap>
#include <iostream>
#include <string>
#include <QPainter>
using namespace WL3;

// load texture with transparency using the given color as mask
QPixmap Sprites::loadTexture(const std::string& file, QColor mask_color)
{
    QPixmap pixmap(file.c_str());
    pixmap.setMask(pixmap.createMaskFromColor(mask_color));
    return pixmap;
}

// replace color (useful for palette changes)
QPixmap replaceColor(QPixmap pix, QColor old_color, QColor new_color)
{
    QBitmap mask = pix.createMaskFromColor(old_color, Qt::MaskOutColor);
    QPainter p(&pix);
    p.setPen(new_color);
    p.drawPixmap(pix.rect(), mask, mask.rect());
    p.end();
    return pix;
}

// moving within sprite utility function
QRect moveBy(QRect rect, int x, int y, int dx = 16, int dy = 16, int border_x = 1, int border_y = 1)
{
    rect.moveTo(QPoint(rect.x() + x * dx + x * border_x, rect.y() + y * dy + y * border_y));
    return rect;
}

// main object positions within sprites
static QRect wario_stand(1, 1, 30, 40);
static QRect wario_roll(1, 264, 30, 40);
static QRect wario_pre_roll(1, 305, 35, 45);
static QRect wario_jump(1, 223, 30, 40);
static QRect wario_running(1, 182, 35, 40);
static QRect wario_crouch(1, 124, 30, 40);
static QRect wario_stairs_down(1, 398, 34, 35);
static QRect wario_stairs(1, 398, 30, 35);
static QRect wario_invisible(1, 434, 30, 39);
static QRect wario_fire(1, 470, 35, 34);          
static QRect wario_first_fire(1, 511, 31, 34);    
static QRect wario_second_fire(129, 511, 31, 35);   
static QRect wario_third_fire(257, 511, 31, 35);    
static QRect wario_fourth_fire(385, 511, 31, 35);   
static QRect wario_total_black1(1, 549, 36, 45);   
static QRect wario_total_black2(223, 549, 36, 45);    
static QRect wario_electric(1, 594, 50, 63);
static QRect wario_bump(1, 434, 30, 37);
static QRect wario_worm(191, 629, 36, 32);
static QRect terrain(10, 38, 16, 16);
static QRect terrain_w(302, 38, 16, 16);
static QRect topsoil(594, 38, 16, 16);
static QRect block(781, 1285, 16, 16);
static QRect hud_letter(519, 254, 8, 8);
static QRect hud_number(519, 263, 8, 8);
static QRect big_rect_blues(1, 1, 33, 16);
static QRect frogs(1, 1, 32, 53); 


Sprites* Sprites::instance()
{
    static Sprites uniqueInstance;
    return &uniqueInstance;
}

Sprites::Sprites()
{
    hud = loadTexture(":/sprites/hud.png");
    hud_transparent = loadTexture(":/sprites/hud.png", QColor(147, 187, 236));
    wario = loadTexture(":/sprites/wario.png", QColor(147, 187, 236));
    enemies = loadTexture(":/sprites/enemies.png", QColor(147, 187, 236));
    stage_tiles = loadTexture(":/sprites/stage_tiles.png");
    stage_tiles_transparent = loadTexture(":/sprites/stage_tiles.png", QColor(147, 187, 236));
    spearhead = loadTexture(":/sprites/blu.png", QColor(147, 187, 236));
    frog = loadTexture(":/sprites/frog.png", QColor(147, 187, 236));
    spider = loadTexture(":/sprites/spider.png", QColor(147, 187, 236));
    worm = loadTexture(":/sprites/worm.png", QColor(147, 187, 236));
    torch = loadTexture(":/sprites/torch.png", QColor(147, 187, 236));
}

void Sprites::getWario(const std::string& state, QPixmap textures[12])
{
    if (state == "sleep-0")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 3, 0, 30, 40));
        textures[4] = wario.copy(wario_stand);
    }
    else if (state == "sleep-1")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 4, 0, 30, 40));
        textures[4] = wario.copy(wario_stand);
    }
    else if (state == "sleep-2")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 5, 0, 30, 40));
        textures[4] = wario.copy(wario_stand);
    }
    else if (state == "sleep-3")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 6, 0, 30, 40));
        textures[4] = wario.copy(wario_stand);
    }
    if (state == "stand-0")
    {
        textures[0] = wario.copy(wario_stand);
        textures[4] = wario.copy(wario_stand);
    }
    else if (state == "stand-1")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 1, 0, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 4, 0));
    }
    else if (state == "stand-2")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 2, 0, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 4, 0));
    }
    else if (state == "crouch")
    {
        textures[0] = wario.copy(wario_crouch);
        textures[4] = wario.copy(wario_crouch);
    }
    else if (state == "walk-0")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 0, 2, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 2, 0));
    }
    else if (state == "walk-1")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 1, 2, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 3, 0));
    }
    else if (state == "walk-2")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 2, 2, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 4, 0));
    }
    else if (state == "walk-3")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 3, 2, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 4, 0));
    }
    if (state == "skid-0")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 4, 1, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "skid-1")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 3, 1, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "skid-2")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 2, 1, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "skid-3")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 1, 1, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "skid-4")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 0, 1, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "crouch-walk-0")
    {
        textures[0] = wario.copy(moveBy(wario_crouch, 1, 0, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "crouch-walk-1")
    {
        textures[0] = wario.copy(moveBy(wario_crouch, 2, 0, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "run-0")
    {
        textures[0] = wario.copy(wario_running);
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "run-1")
    {
        textures[0] = wario.copy(moveBy(wario_running, 1, 0, 35, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "run-2")
    {
        textures[0] = wario.copy(moveBy(wario_running, 2, 0, 35, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "run-3")
    {
        textures[0] = wario.copy(moveBy(wario_running, 3, 0, 35, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "run-4")
    {
        textures[0] = wario.copy(moveBy(wario_running, 4, 0, 35, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "run-5")
    {
        textures[0] = wario.copy(moveBy(wario_running, 5, 0, 35, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "run-6")
    {
        textures[0] = wario.copy(moveBy(wario_running, 6, 0, 35, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "run-7")
    {
        textures[0] = wario.copy(moveBy(wario_running, 7, 0, 35, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 5, 0));
    }
    else if (state == "air")
    {
        textures[0] = wario.copy(wario_jump);
        textures[4] = wario.copy(moveBy(wario_stand, 6, 0));
    }
    else if (state == "pre_roll-0")
    {
        textures[0] = wario.copy(wario_pre_roll);
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "pre_roll-1")
    {
        textures[0] = wario.copy(moveBy(wario_pre_roll, 1, 0, 35, 45));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "pre_roll-2")
    {
        textures[0] = wario.copy(moveBy(wario_pre_roll, 2, 0, 35, 45));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "pre_roll-3")
    {
        textures[0] = wario.copy(moveBy(wario_pre_roll, 3, 0, 35, 45));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "pre_roll-4")
    {
        textures[0] = wario.copy(moveBy(wario_pre_roll, 4, 0, 35, 45));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "pre_roll_noscript-0")
    {
        textures[0] = wario.copy(moveBy(wario_pre_roll, 0, 1, 35, 45));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "pre_roll_noscript-1")
    {
        textures[0] = wario.copy(moveBy(wario_pre_roll, 1, 1, 35, 45));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "pre_roll_noscript-2")
    {
        textures[0] = wario.copy(moveBy(wario_pre_roll, 2, 1, 35, 45));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "pre_roll_noscript-3")
    {
        textures[0] = wario.copy(moveBy(wario_pre_roll, 3, 1, 35, 45));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "pre_roll_noscript-4")
    {
        textures[0] = wario.copy(moveBy(wario_pre_roll, 4, 1, 35, 45));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "roll-0")
    {
        textures[0] = wario.copy(wario_roll);
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "roll-1")
    {
        textures[0] = wario.copy(moveBy(wario_roll, 1, 0, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "roll-2")
    {
        textures[0] = wario.copy(moveBy(wario_roll, 2, 0, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "roll-3")
    {
        textures[0] = wario.copy(moveBy(wario_roll, 3, 0, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "roll-4")
    {
        textures[0] = wario.copy(moveBy(wario_roll, 4, 0, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "roll-5")
    {
        textures[0] = wario.copy(moveBy(wario_roll, 5, 0, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "roll-6")
    {
        textures[0] = wario.copy(moveBy(wario_roll, 6, 0, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "roll-7")
    {
        textures[0] = wario.copy(moveBy(wario_roll, 7, 0, 30, 40));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    if (state == "stairs-0")
    {
        textures[0] = wario.copy(wario_stairs);
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "stairs-1")
    {
        textures[0] = wario.copy(moveBy(wario_stairs, 1, 0, 35, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "stairs-2")
    {
        textures[0] = wario.copy(moveBy(wario_stairs, 2, 0, 35, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "stairs-3")
    {
        textures[0] = wario.copy(moveBy(wario_stairs, 3, 0, 35, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "stairs-4")
    {
        textures[0] = wario.copy(moveBy(wario_stairs, 4, 0, 35, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "stairs-5")
    {
        textures[0] = wario.copy(moveBy(wario_stairs, 5, 0, 35, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "stairs-down")
    {
        textures[0] = wario.copy(moveBy(wario_stairs_down, 6, 0, 35, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "invisible-0")
    {
        textures[0] = wario.copy(wario_invisible);
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));

    }
    else if (state == "invisible-1")
    {
        textures[0] = wario.copy(moveBy(wario_invisible, 1, 0, 30, 39));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "invisible-2")
    {
        textures[0] = wario.copy(moveBy(wario_invisible, 2, 0, 30, 39));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "invisible-3")
    {
        textures[0] = wario.copy(moveBy(wario_invisible, 3, 0, 30, 39));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "invisible-4")
    {
        textures[0] = wario.copy(moveBy(wario_invisible, 4, 0, 30, 39));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "invisible-5")
    {
        textures[0] = wario.copy(moveBy(wario_invisible, 5, 0, 30, 39));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "invisible-6")
    {
        textures[0] = wario.copy(moveBy(wario_invisible, 6, 0, 30, 39));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "invisible-7")
    {
        textures[0] = wario.copy(moveBy(wario_invisible, 7, 0, 30, 39));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "fire-0")
    {
        textures[0] = wario.copy(QRect(1, 473, 35, 33));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "fire-1")
    {
        textures[0] = wario.copy(QRect(37, 473, 35, 33));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "fire-2")
    {
        textures[0] = wario.copy(QRect(73, 473, 35, 33));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "fire-3")
    {
        textures[0] = wario.copy(QRect(109, 473, 35, 33));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "fire-4")
    {
        textures[0] = wario.copy(QRect(145, 473, 35, 33));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "fire-5")
    {
        textures[0] = wario.copy(QRect(181, 473, 35, 33));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "fire-6")
    {
        textures[0] = wario.copy(QRect(217, 473, 35, 33));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "fire-7")
    {
        textures[0] = wario.copy(QRect(253, 473, 35, 33));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }

    else if (state == "first_fire-0")
    {
        textures[0] = wario.copy(moveBy(wario_first_fire, 0, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "first_fire-1")
    {
        textures[0] = wario.copy(moveBy(wario_first_fire, 1, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "first_fire-2")
    {
        textures[0] = wario.copy(moveBy(wario_first_fire, 2, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "first_fire-3")
    {
        textures[0] = wario.copy(moveBy(wario_first_fire, 3, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "second_fire-0")
    {
        textures[0] = wario.copy(moveBy(wario_second_fire, 0, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "second_fire-1")
    {
        textures[0] = wario.copy(moveBy(wario_second_fire, 1, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "second_fire-2")
    {
        textures[0] = wario.copy(moveBy(wario_second_fire, 2, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "second_fire-3")
    {
        textures[0] = wario.copy(moveBy(wario_second_fire, 3, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "third_fire-0")
    {
        textures[0] = wario.copy(moveBy(wario_third_fire, 0, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "third_fire-1")
    {
        textures[0] = wario.copy(moveBy(wario_third_fire, 1, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "third_fire-2")
    {
        textures[0] = wario.copy(moveBy(wario_third_fire, 2, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "third_fire-3")
    {
        textures[0] = wario.copy(moveBy(wario_third_fire, 3, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "fourth_fire-0")
    {
        textures[0] = wario.copy(moveBy(wario_fourth_fire, 0, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "fourth_fire-1")
    {
        textures[0] = wario.copy(moveBy(wario_fourth_fire, 1, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "fourth_fire-2")
    {
        textures[0] = wario.copy(moveBy(wario_fourth_fire, 2, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "fourth_fire-3")
    {
        textures[0] = wario.copy(moveBy(wario_fourth_fire, 3, 0, 31, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }

    else if (state == "total_black1-0")
    {
        textures[0] = wario.copy(QRect(1, 549, 36, 43));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "total_black1-1")
    {
        textures[0] = wario.copy(QRect(1 + 37, 549, 36, 43));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "total_black1-2")
    {
        textures[0] = wario.copy(QRect(1 + 37 * 2, 549, 36, 43));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "total_black1-3")
    {
        textures[0] = wario.copy(QRect(1 + 37 * 3, 549, 36, 43));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "total_black1-4")
    {
        textures[0] = wario.copy(QRect(1 + 37 * 4, 549, 36, 43));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "total_black1-5")
    {
        textures[0] = wario.copy(QRect(1 + 37 * 5, 549, 36, 43));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "total_black2-0")
    {
        textures[0] = wario.copy(QRect(223, 549, 45, 43));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "total_black2-1")
    {
        textures[0] = wario.copy(QRect(223 + 46, 549, 45, 43));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "total_black2-2")
    {
        textures[0] = wario.copy(QRect(223 + 46 * 2, 549, 45, 43));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "total_black2-3")
    {
        textures[0] = wario.copy(QRect(223 + 46 * 3, 549, 45, 43));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "total_black2-4")
    {
        textures[0] = wario.copy(QRect(223 + 46 * 4, 549, 45, 43));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "total_black2-5")
    {
        textures[0] = wario.copy(QRect(223 + 46 * 5, 549, 45, 43));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "total_black2-6")
    {
        textures[0] = wario.copy(QRect(223 + 46 * 6, 549, 45, 43));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }

    if (state == "electric-0")
    {
        textures[0] = wario.copy(QRect(1, 594, 38, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "electric-1")
    {
        textures[0] = wario.copy(QRect(40, 594, 41, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "electric-2")
    {
        textures[0] = wario.copy(QRect(82, 594, 37, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "electric-3")
    {
        textures[0] = wario.copy(QRect(120, 594, 39, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "electric-4")
    {
        textures[0] = wario.copy(QRect(160, 594, 41, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "electric-5")
    {
        textures[0] = wario.copy(QRect(202, 594, 38, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "electric-6")
    {
        textures[0] = wario.copy(QRect(241, 594, 38, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "electric-7")
    {
        textures[0] = wario.copy(QRect(280, 594, 34, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "electric-8")
    {
        textures[0] = wario.copy(QRect(315, 594, 34, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "electric-9")
    {
        textures[0] = wario.copy(QRect(350, 594, 34, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "electric-10")
    {
        textures[0] = wario.copy(QRect(385, 594, 34, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "electric-11")
    {
        textures[0] = wario.copy(QRect(420, 594, 34, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "electric-12")
    {
        textures[0] = wario.copy(QRect(455, 594, 34, 34));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "bump-0")
    {
        textures[0] = wario.copy(moveBy(wario_bump, 0, 0, 30, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "bump-1")
    {
        textures[0] = wario.copy(moveBy(wario_bump, 1, 0, 30, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "bump-2")
    {
        textures[0] = wario.copy(moveBy(wario_bump, 2, 0, 30, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "bump-3")
    {
        textures[0] = wario.copy(moveBy(wario_bump, 3, 0, 30, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "bump-4")
    {
        textures[0] = wario.copy(moveBy(wario_bump, 4, 0, 30, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "bump-5")
    {
        textures[0] = wario.copy(moveBy(wario_bump, 5, 0, 30, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "bump-6")
    {
        textures[0] = wario.copy(moveBy(wario_bump, 6, 0, 30, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "bump-7")
    {
        textures[0] = wario.copy(moveBy(wario_bump, 7, 0, 30, 35));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    if (state == "pre_worm_roll-0")
    {
        textures[0] = wario.copy(QRect(1, 629, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "pre_worm_roll-1")
    {
        textures[0] = wario.copy(QRect(38, 629, 37, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "pre_worm_roll-2")
    {
        textures[0] = wario.copy(QRect(76, 629, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "pre_worm_roll-3")
    {
        textures[0] = wario.copy(QRect(113, 629, 37, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "pre_worm_roll-4")
    {
        textures[0] = wario.copy(QRect(151, 629, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }

    else if (state == "worm_roll-0")
    {
        textures[0] = wario.copy(moveBy(wario_worm, 0, 0, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "worm_roll-1")
    {
        textures[0] = wario.copy(moveBy(wario_worm, 1, 0, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "worm_roll-2")
    {
        textures[0] = wario.copy(moveBy(wario_worm, 2, 0, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "worm_roll-3")
    {
        textures[0] = wario.copy(moveBy(wario_worm, 3, 0, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-0")
    {
        textures[0] = wario.copy(QRect(339, 629, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-1")
    {
        textures[0] = wario.copy(QRect(376, 629, 37, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-2")
    {
        textures[0] = wario.copy(QRect(414, 629, 38, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-3")
    {
        textures[0] = wario.copy(QRect(453, 629, 38, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-4")
    {
        textures[0] = wario.copy(QRect(492, 629, 37, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-5")
    {
        textures[0] = wario.copy(QRect(530, 629, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-6")
    {
        textures[0] = wario.copy(QRect(567, 629, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-7")
    {
        textures[0] = wario.copy(QRect(604, 629, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-8")
    {
        textures[0] = wario.copy(QRect(641, 629, 37, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-9")
    {
        textures[0] = wario.copy(QRect(679, 629, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-10")
    {
        textures[0] = wario.copy(QRect(716, 629, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-11")
    {
        textures[0] = wario.copy(QRect(753, 629, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-12")
    {
        textures[0] = wario.copy(QRect(790, 629, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-13")
    {
        textures[0] = wario.copy(QRect(827, 629, 37, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "post_worm_roll-14")
    {
        textures[0] = wario.copy(QRect(865, 629, 36, 32));
        textures[4] = wario.copy(moveBy(wario_stand, 7, 0));
    }
    else if (state == "empty")
    {
        textures[0] = wario.copy(moveBy(wario_stand, 23, 0));
        textures[4] = wario.copy(moveBy(wario_stand, 23, 0));
    }
}

QPixmap Sprites::get(const std::string& id)
{
    if (id == "terrain")
        return stage_tiles.copy(moveBy(terrain, 1, 0));
    else if (id == "terrain-1")
        return stage_tiles.copy(terrain);
    else if (id == "terrain-2")
        return stage_tiles.copy(moveBy(terrain, 2, 0));
    else if (id == "terrain-3")
        return stage_tiles.copy(moveBy(terrain, 1, 1));
    else if (id == "terrain-4")
        return stage_tiles.copy(moveBy(terrain, 0, 1));
    else if (id == "terrain-5")
        return stage_tiles.copy(moveBy(terrain, 2, 1));
    else if (id == "terrain-6")
        return stage_tiles.copy(moveBy(terrain, 3, 0));
    else if (id == "terrain-7")
        return stage_tiles.copy(moveBy(terrain, 0, 2));
    else if (id == "terrain-8")
        return stage_tiles.copy(moveBy(terrain, 4, 0));
    else if (id == "terrain-9")
        return stage_tiles.copy(moveBy(terrain, 2, 2));
    else if (id == "terrain-10")
        return stage_tiles.copy(moveBy(terrain, 4, 1));
    else if (id == "terrain-11")
        return stage_tiles.copy(moveBy(terrain, 1, 2));
    else if (id == "terrain-12")
        return stage_tiles.copy(moveBy(terrain, 4, 4));
    else if (id == "terrain-13")
        return stage_tiles.copy(moveBy(terrain, 3, 1));


    else if (id == "terrain-r")
        return stage_tiles_transparent.copy(moveBy(terrain, 4, 3));

    if (id == "static-platform-w")
        return stage_tiles.copy(moveBy(terrain_w, 4, 3));
    else if (id == "static-platform")
        return stage_tiles.copy(moveBy(terrain, 4, 6));
    else if (id == "static-platform-0")
        return stage_tiles.copy(moveBy(terrain, 4, 5));
    else if (id == "static-platform-1")
        return stage_tiles.copy(moveBy(terrain, 5, 8));
    else if (id == "wood-hard-0")
        return stage_tiles.copy(moveBy(terrain, 3, 5));
    else if (id == "wood-hard-1")
        return stage_tiles.copy(moveBy(terrain, 2, 5));
    else if (id == "wood-hard-2")
        return stage_tiles.copy(moveBy(terrain, 0, 5));
    else if (id == "wood-hard-3")
        return stage_tiles.copy(moveBy(terrain, 0, 6));
    else if (id == "wood-hard-4")
        return stage_tiles.copy(moveBy(terrain, 3, 6));
    else if (id == "wood-hard-5")
        return stage_tiles.copy(moveBy(terrain, 3, 6));

    else if (id == "full")
        return stage_tiles.copy(moveBy(topsoil, 6, 2));
    else if (id == "full-angular")
        return stage_tiles.copy(moveBy(topsoil, 5, 5));
    if (id == "trasparent")
        return stage_tiles_transparent.copy(moveBy(terrain, 2, -2));
    else if (id == "green")
        return stage_tiles_transparent.copy(moveBy(terrain, 3, 11));

    if (id == "ramp-0")
        return stage_tiles.copy(moveBy(terrain, 0, 3));
    else if (id == "ramp-1")
        return stage_tiles.copy(moveBy(terrain, 1, 3));
    else if (id == "ramp-2")
        return stage_tiles.copy(moveBy(terrain, 4, 2));
    else if (id == "plants-0")
        return stage_tiles_transparent.copy(moveBy(terrain, 5, 6));
    else if (id == "plants-1")
        return stage_tiles_transparent.copy(moveBy(terrain, 6, 6));
    else if (id == "plants-2")
        return stage_tiles_transparent.copy(moveBy(terrain, 7, 6));
    else if (id == "brown")
        return stage_tiles_transparent.copy(moveBy(terrain, 0, 3));
    else if (id == "brown-1")
        return stage_tiles_transparent.copy(moveBy(terrain, 2, 3));
    else if (id == "brown-2")
        return stage_tiles_transparent.copy(moveBy(terrain, 1, 3));
    else if (id == "screw")
        return stage_tiles_transparent.copy(moveBy(terrain, 3, 2));
    else if (id == "screw-1")
        return stage_tiles_transparent.copy(moveBy(terrain, 4, 2));
    else if (id == "brick")
        return stage_tiles.copy(moveBy(block, 0, -1));
    else if (id == "dark_brick")
        return stage_tiles.copy(moveBy(block, 1, -1));
    else if (id == "fire-block")
        return stage_tiles.copy(moveBy(block, 1, 0));
    else if (id == "block")
        return stage_tiles.copy(block);
    else if (id == "brokenbrick")
        return stage_tiles_transparent.copy(QRect(886, 293, 8, 10));
    else if (id == "door-0")
        return stage_tiles.copy(moveBy(terrain, 4, 7));
    else if (id == "door-1")
        return stage_tiles.copy(moveBy(terrain, 4, 8));
    else if (id == "door-2")
        return stage_tiles.copy(moveBy(terrain, 4, 7));
    else if (id == "door-3")
        return stage_tiles.copy(moveBy(terrain, 4, 8));
    else if (id == "door-4")
        return stage_tiles.copy(moveBy(terrain, 4, 7));
    else if (id == "door-5")
        return stage_tiles.copy(moveBy(terrain, 4, 8));
    else if (id == "earth-0")
        return stage_tiles.copy(moveBy(terrain, 0, 11));
    else if (id == "earth-1")
        return stage_tiles.copy(moveBy(terrain, 1, 11));

    if (id == "face_wood_top_left")
        return stage_tiles_transparent.copy(moveBy(terrain, 5, 7));
    else if (id == "face_wood_top_center")
        return stage_tiles_transparent.copy(moveBy(terrain, 6, 7));
    else if (id == "face_wood_top_right")
        return stage_tiles_transparent.copy(moveBy(terrain, 7, 7));
    else if (id == "face_wood_mid_center")
        return stage_tiles_transparent.copy(moveBy(terrain, 6, 8));
    else if (id == "face_wood_bottom_left")
        return stage_tiles_transparent.copy(moveBy(terrain, 5, 9));
    else if (id == "face_wood_bottom_center")
        return stage_tiles_transparent.copy(moveBy(terrain, 6, 9));
    else if (id == "face_wood_bottom_right")
        return stage_tiles_transparent.copy(moveBy(terrain, 7, 9));
    else if (id == "bright_arrows_dark_body")
        return stage_tiles_transparent.copy(moveBy(terrain, 4, 10));
    else if (id == "darker_arrows_dark_body")
        return stage_tiles_transparent.copy(moveBy(terrain, 5, 10));
    else if (id == "dark_arrows_dark_body")
        return stage_tiles_transparent.copy(moveBy(terrain, 6, 10));

    // TORCH + FIREBALL
    if (id == "torch-0")
        return torch.copy(QRect(1, 1, 20, 33));
    else if (id == "torch-1")
        return torch.copy(QRect(23, 1, 20, 33));
    else if (id == "torch-2")
        return torch.copy(QRect(45, 1, 20, 33));
    else if (id == "torch-3")
        return torch.copy(QRect(67, 1, 21, 33));

    if (id == "fireball-0")
        return torch.copy(QRect(1, 35, 15, 16));
    else if (id == "fireball-1")
        return torch.copy(QRect(17, 35, 15, 16));
    else if (id == "fireball-2")
        return torch.copy(QRect(33, 35, 16, 16));
    else if (id == "fireball-3")
        return torch.copy(QRect(50, 35, 16, 16));

    // FROG
    if (id == "frog-0")
        return frog.copy(frogs);
    else if (id == "frog-1")
        return frog.copy(moveBy(frogs, 1, 0, 32, 53));
    else if (id == "frog-2")
        return frog.copy(moveBy(frogs, 2, 0, 32, 53));
    else if (id == "frog-3")
        return frog.copy(moveBy(frogs, 3, 0, 32, 53));
    else if (id == "frog-4")
        return frog.copy(moveBy(frogs, 4, 0, 32, 53));
    else if (id == "frog-5")
        return frog.copy(moveBy(frogs, 5, 0, 32, 53));
    else if (id == "frog-6")
        return frog.copy(moveBy(frogs, 6, 0, 32, 53));
    else if (id == "frog-7")
        return frog.copy(moveBy(frogs, 7, 0, 32, 53));
    else if (id == "frog-8")
        return frog.copy(moveBy(frogs, 8, 0, 32, 53));
    else if (id == "frog-9")
        return frog.copy(moveBy(frogs, 9, 0, 32, 53));

    if (id == "frog_angry-0")
        return frog.copy(moveBy(frogs, 0, 1, 32, 53));
    else if (id == "frog_angry-1")
        return frog.copy(moveBy(frogs, 1, 1, 32, 53));
    else if (id == "frog_angry-2")
        return frog.copy(moveBy(frogs, 2, 1, 32, 53));
    else if (id == "frog_angry-3")
        return frog.copy(moveBy(frogs, 3, 1, 32, 53));
    else if (id == "frog_angry-4")
        return frog.copy(moveBy(frogs, 4, 1, 32, 53));
    else if (id == "frog_angry-5")
        return frog.copy(moveBy(frogs, 5, 1, 32, 53));
    else if (id == "frog_angry-6")
        return frog.copy(moveBy(frogs, 6, 1, 32, 53));
    else if (id == "frog_angry-7")
        return frog.copy(moveBy(frogs, 0, 2, 32, 53));
    else if (id == "frog_angry-8")
        return frog.copy(moveBy(frogs, 1, 2, 32, 53));
    else if (id == "frog_angry-9")
        return frog.copy(moveBy(frogs, 2, 2, 32, 53));
    else if (id == "frog_angry-10")
        return frog.copy(moveBy(frogs, 3, 2, 32, 53));
    else if (id == "frog_angry-11")
        return frog.copy(moveBy(frogs, 4, 2, 32, 53));
    else if (id == "frog_angry-12")
        return frog.copy(moveBy(frogs, 5, 2, 32, 53));
    else if (id == "frog_angry-13")
        return frog.copy(moveBy(frogs, 6, 2, 32, 53));
    else if (id == "frog_angry-14")
        return frog.copy(moveBy(frogs, 0, 3, 32, 53));
    else if (id == "frog_angry-15")
        return frog.copy(moveBy(frogs, 1, 3, 32, 53));
    else if (id == "frog_angry-16")
        return frog.copy(moveBy(frogs, 2, 3, 32, 53));
    else if (id == "frog_angry-17")
        return frog.copy(moveBy(frogs, 3, 3, 32, 53));
    else if (id == "frog_angry-18")
        return frog.copy(moveBy(frogs, 4, 3, 32, 53));
    else if (id == "frog_angry-19")
        return frog.copy(moveBy(frogs, 5, 3, 32, 53));
    else if (id == "frog_angry-20")
        return frog.copy(moveBy(frogs, 6, 3, 32, 53));
    else if (id == "frog_angry-21")
        return frog.copy(moveBy(frogs, 0, 4, 32, 53));
    else if (id == "frog_angry-22")
        return frog.copy(moveBy(frogs, 1, 4, 32, 53));
    else if (id == "frog_angry-23")
        return frog.copy(moveBy(frogs, 2, 4, 32, 53));
    else if (id == "frog_angry-24")
        return frog.copy(moveBy(frogs, 3, 4, 32, 53));
    else if (id == "frog_angry-25")
        return frog.copy(moveBy(frogs, 4, 4, 32, 53));
    else if (id == "frog_angry-26")
        return frog.copy(moveBy(frogs, 5, 4, 32, 53));
    else if (id == "frog_angry-27")
        return frog.copy(moveBy(frogs, 6, 4, 32, 53));

    // SPIDER + SPARK
    if (id == "spider-0")
        return spider.copy(QRect(1, 1, 23, 16));
    else if (id == "spider-1")
        return spider.copy(QRect(25, 1, 23, 16));
    else if (id == "spider-2")
        return spider.copy(QRect(49, 1, 23, 16));
    else if (id == "spider-3")
        return spider.copy(QRect(73, 1, 23, 16));
    else if (id == "spider-4")
        return spider.copy(QRect(97, 1, 23, 16));
    else if (id == "spider-5")
        return spider.copy(QRect(121, 1, 23, 16));
    else if (id == "spider-6")
        return spider.copy(QRect(145, 1, 23, 16));
    else if (id == "spider-7")
        return spider.copy(QRect(169, 1, 23, 16));
    else if (id == "spider-8")
        return spider.copy(QRect(193, 1, 23, 16));
    else if (id == "spider-9")
        return spider.copy(QRect(217, 1, 23, 16));
    else if (id == "spider-10")
        return spider.copy(QRect(241, 1, 23, 16));

    if (id == "mini_spider-0")
        return spider.copy(QRect(1, 19, 23, 24));
    else if (id == "mini_spider-1")
        return spider.copy(QRect(1 + 24, 19, 23, 24));
    else if (id == "mini_spider-2")
        return spider.copy(QRect(1 + 24 * 2, 19, 23, 24));
    else if (id == "mini_spider-3")
        return spider.copy(QRect(1 + 24 * 3, 19, 23, 24));
    else if (id == "mini_spider-4")
        return spider.copy(QRect(1 + 24 * 4, 19, 23, 24));
    else if (id == "mini_spider-5")
        return spider.copy(QRect(1 + 24 * 5, 19, 23, 24));
    else if (id == "mini_spider-6")
        return spider.copy(QRect(1 + 24 * 6, 19, 23, 24));
    else if (id == "mini_spider-7")
        return spider.copy(QRect(1 + 24 * 7, 19, 23, 24));
    else if (id == "mini_spider-8")
        return spider.copy(QRect(1 + 24 * 8, 19, 23, 24));
    else if (id == "mini_spider-9")
        return spider.copy(QRect(1 + 24 * 9, 19, 23, 24));
    else if (id == "mini_spider-10")
        return spider.copy(QRect(1 + 24 * 10, 19, 23, 24));
    else if (id == "mini_spider-11")
        return spider.copy(QRect(1 + 24 * 11, 19, 23, 24));
    else if (id == "mini_spider-12")
        return spider.copy(QRect(1 + 24 * 12, 19, 23, 24));
    else if (id == "mini_spider-13")
        return spider.copy(QRect(1 + 24 * 13, 19, 23, 24));
    else if (id == "mini_spider-14")
        return spider.copy(QRect(1 + 24 * 14, 19, 23, 24));
    else if (id == "mini_spider-15")
        return spider.copy(QRect(1 + 24 * 15, 19, 23, 24));
    else if (id == "mini_spider-16")
        return spider.copy(QRect(1 + 24 * 16, 19, 23, 24));
    else if (id == "mini_spider-17")
        return spider.copy(QRect(1 + 24 * 17, 19, 23, 24));
    else if (id == "mini_spider-18")
        return spider.copy(QRect(1 + 24 * 18, 19, 23, 24));
    else if (id == "mini_spider-19")
        return spider.copy(QRect(1 + 24 * 19, 19, 23, 24));
    else if (id == "mini_spider-20")
        return spider.copy(QRect(1 + 24 * 20, 19, 23, 24));
    else if (id == "mini_spider-21")
        return spider.copy(QRect(1 + 24 * 21, 19, 23, 24));
    else if (id == "mini_spider-22")
        return spider.copy(QRect(1 + 24 * 22, 19, 23, 24));

    if (id == "spark-0")
        return spider.copy(QRect(1, 45, 16, 16));
    else if (id == "spark-1")
        return spider.copy(QRect(1 + 17 * 1, 45, 16, 16));
    else if (id == "spark-2")
        return spider.copy(QRect(1 + 17 * 2, 45, 16, 16));
    else if (id == "spark-3")
        return spider.copy(QRect(1 + 17 * 3, 45, 16, 16));
    else if (id == "spark-4")
        return spider.copy(QRect(1 + 17 * 4, 45, 16, 16));
    else if (id == "spark-5")
        return spider.copy(QRect(1 + 17 * 5, 45, 16, 16));
    else if (id == "spark-6")
        return spider.copy(QRect(1 + 17 * 6, 45, 16, 16));

    // WORM
    if (id == "worm_walk-0")
        return worm.copy(QRect(1, 1, 31, 24));
    else if (id == "worm_walk-1")
        return worm.copy(QRect(33, 1, 31, 24));
    else if (id == "worm_walk-2")
        return worm.copy(QRect(65, 1, 31, 24));

    else if (id == "worm_attack-0")
        return worm.copy(QRect(97, 1, 30, 24));
    else if (id == "worm_attack-1")
        return worm.copy(QRect(129, 1, 31, 24));
    else if (id == "worm_attack-2")
        return worm.copy(QRect(162, 1, 29, 24));

    else if (id == "worm_roll-0")
        return worm.copy(QRect(1, 26, 31, 24));
    else if (id == "worm_roll-1")
        return worm.copy(QRect(33, 26, 31, 24));
    else if (id == "worm_roll-2")
        return worm.copy(QRect(65, 26, 31, 24));

    else if (id == "worm_smashed")
        return worm.copy(QRect(250, 1, 20, 37));

    if (id == "ladder-0")
        return stage_tiles.copy(moveBy(terrain, 2, 4));
    else if (id == "ladder-1")
        return stage_tiles.copy(moveBy(terrain, 5, 0));

    // HUD + MENU
    else if (id == "title-screen")
        return hud.copy(QRect(1, 0, 10 * 16, 9 * 16));
    else if (id == "menu")
        return hud.copy(QRect(164, 0, 10 * 16, 9 * 16));
    else if (id == "white")
        return hud.copy(QRect(332, 221, 10 * 16, 9 * 16));
    else if (id == "win")
        return hud.copy(QRect(483, 0, 160, 152));
    else if (id == "return-0")
        return hud.copy(QRect(327, 0, 32, 16));
    else if (id == "return-1")
        return hud.copy(QRect(327, 17, 32, 16));
    else if (id == "return-2")
        return hud.copy(QRect(327, 17 * 2, 32, 16));
    else if (id == "return-3")
        return hud.copy(QRect(327, 17 * 3, 32, 16));
    else if (id == "return-4")
        return hud.copy(QRect(327, 17 * 4, 32, 16));
    else if (id == "return-5")
        return hud.copy(QRect(327, 17 * 5, 32, 16));
    else if (id == "return-6")
        return hud.copy(QRect(327, 17 * 6, 32, 16));

    else if (id == "save-0")
        return hud.copy(QRect(360, 0, 32, 16));
    else if (id == "save-1")
        return hud.copy(QRect(360, 17, 32, 16));
    else if (id == "save-2")
        return hud.copy(QRect(360, 17 * 2, 32, 16));
    else if (id == "save-3")
        return hud.copy(QRect(360, 17 * 3, 32, 16));
    else if (id == "save-4")
        return hud.copy(QRect(360, 17 * 4, 32, 16));

    else if (id == "to_map-0")
        return hud.copy(QRect(393, 0, 32, 16));
    else if (id == "to_map-1")
        return hud.copy(QRect(393, 17, 32, 16));
    else if (id == "to_map-2")
        return hud.copy(QRect(393, 17 * 2, 32, 16));
    else if (id == "to_map-3")
        return hud.copy(QRect(393, 17 * 3, 32, 16));
    else if (id == "to_map-4")
        return hud.copy(QRect(393, 17 * 4, 32, 16));
    else if (id == "to_map-5")
        return hud.copy(QRect(393, 17 * 5, 32, 16));
    else if (id == "to_map-6")
        return hud.copy(QRect(393, 17 * 6, 32, 16));

    if (id == "menu_number-0")
        return hud_transparent.copy(QRect(1, 188, 8, 16));
    else if (id == "menu_number-1")
        return hud_transparent.copy(QRect(10, 188, 8, 16));
    else if (id == "menu_number-2")
        return hud_transparent.copy(QRect(19, 188, 8, 16));
    else if (id == "menu_number-3")
        return hud_transparent.copy(QRect(28, 188, 8, 16));
    else if (id == "menu_number-4")
        return hud_transparent.copy(QRect(37, 188, 8, 16));
    else if (id == "menu_number-5")
        return hud_transparent.copy(QRect(46, 188, 8, 16));
    else if (id == "menu_number-6")
        return hud_transparent.copy(QRect(55, 188, 8, 16));
    else if (id == "menu_number-7")
        return hud_transparent.copy(QRect(64, 188, 8, 16));
    else if (id == "menu_number-8")
        return hud_transparent.copy(QRect(73, 188, 8, 16));
    else if (id == "menu_number-9")
        return hud_transparent.copy(QRect(82, 188, 8, 16));

    if (id == "coin-0")
        return hud_transparent.copy(QRect(1 + 34 * 0, 145, 33, 41));
    else if (id == "coin-1")
        return hud_transparent.copy(QRect(1 + 34 * 1, 145, 33, 41));
    else if (id == "coin-2")
        return hud_transparent.copy(QRect(35 + 34, 145, 33, 41));
    else if (id == "coin-3")
        return hud_transparent.copy(QRect(35 + 34 * 2, 145, 33, 41));
    else if (id == "coin-4")
        return hud_transparent.copy(QRect(35 + 34 * 3, 145, 33, 41));
    else if (id == "coin-5")
        return hud_transparent.copy(QRect(35 + 34 * 4, 145, 33, 41));
    else if (id == "coin-6")
        return hud_transparent.copy(QRect(35 + 34 * 5, 145, 33, 41));
    else if (id == "coin-7")
        return hud_transparent.copy(QRect(35 + 34 * 6, 145, 33, 41));
    else if (id == "coin-8")
        return hud_transparent.copy(QRect(35 + 34 * 7, 145, 33, 41));
    else if (id == "coin-9")
        return hud_transparent.copy(QRect(35 + 34 * 8, 145, 33, 41));
    else if (id == "coin-10")
        return hud_transparent.copy(QRect(35 + 34 * 9, 145, 33, 41));
    else if (id == "coin-11")
        return hud_transparent.copy(QRect(35 + 34 * 10, 145, 33, 41));

    if (id == "lil_coin-0")
        return hud_transparent.copy(QRect(1, 205, 14, 14));
    else if (id == "lil_coin-1")
        return hud_transparent.copy(QRect(16, 205, 14, 14));
    else if (id == "lil_coin-2")
        return hud_transparent.copy(QRect(31, 205, 14, 14));
    else if (id == "lil_coin-3")
        return hud_transparent.copy(QRect(46, 205, 14, 14));
    else if (id == "lil_coin-4")
        return hud_transparent.copy(QRect(61, 205, 14, 14));
    else if (id == "lil_coin-5")
        return hud_transparent.copy(QRect(76, 205, 14, 14));
    else if (id.rfind("number-", 0) == 0)
        return hud.copy(moveBy(hud_number, id[7] - '0', 0, 8, 8));
    else if (id.rfind("char-", 0) == 0)
        return hud.copy(moveBy(hud_letter, id[5] - 'A', 0, 8, 8));

    else if (id == "key_grey-0")
        return hud_transparent.copy(QRect(1, 221, 20, 30));
    else if (id == "key_grey-1")
        return hud_transparent.copy(QRect(25, 221, 18, 30));
    else if (id == "key_grey-2")
        return hud_transparent.copy(QRect(44, 221, 18, 30));
    else if (id == "key_grey-3")
        return hud_transparent.copy(QRect(63, 221, 18, 30));
    else if (id == "key_grey-4")
        return hud_transparent.copy(QRect(83, 221, 28, 30));
    else if (id == "key_grey-5")
        return hud_transparent.copy(QRect(113, 221, 26, 30));
    else if (id == "key_grey-6")
        return hud_transparent.copy(QRect(141, 221, 18, 30));
    else if (id == "key_grey-7")
        return hud_transparent.copy(QRect(160, 221, 18, 30));

    else if (id == "key_green-0")
        return hud_transparent.copy(QRect(1, 270, 20, 30));
    else if (id == "key_green-1")
        return hud_transparent.copy(QRect(25, 270, 18, 30));
    else if (id == "key_green-2")
        return hud_transparent.copy(QRect(44, 270, 18, 30));
    else if (id == "key_green-3")
        return hud_transparent.copy(QRect(63, 270, 18, 30));
    else if (id == "key_green-4")
        return hud_transparent.copy(QRect(83, 270, 28, 30));
    else if (id == "key_green-5")
        return hud_transparent.copy(QRect(113, 270, 26, 30));
    else if (id == "key_green-6")
        return hud_transparent.copy(QRect(141, 270, 18, 30));
    else if (id == "key_green-7")
        return hud_transparent.copy(QRect(160, 270, 18, 30));

    else if (id == "key_red-0")
        return hud_transparent.copy(QRect(1, 319, 20, 30));
    else if (id == "key_red-1")
        return hud_transparent.copy(QRect(25, 319, 18, 30));
    else if (id == "key_red-2")
        return hud_transparent.copy(QRect(44, 319, 18, 30));
    else if (id == "key_red-3")
        return hud_transparent.copy(QRect(63, 319, 18, 30));
    else if (id == "key_red-4")
        return hud_transparent.copy(QRect(83, 319, 28, 30));
    else if (id == "key_red-5")
        return hud_transparent.copy(QRect(113, 319, 26, 30));
    else if (id == "key_red-6")
        return hud_transparent.copy(QRect(141, 319, 18, 30));
    else if (id == "key_red-7")
        return hud_transparent.copy(QRect(160, 319, 18, 30));

    else if (id == "key_blue-0")
        return hud_transparent.copy(QRect(1, 368, 20, 30));
    else if (id == "key_blue-1")
        return hud_transparent.copy(QRect(25, 368, 18, 30));
    else if (id == "key_blue-2")
        return hud_transparent.copy(QRect(44, 368, 18, 30));
    else if (id == "key_blue-3")
        return hud_transparent.copy(QRect(63, 368, 18, 30));
    else if (id == "key_blue-4")
        return hud_transparent.copy(QRect(83, 368, 28, 30));
    else if (id == "key_blue-5")
        return hud_transparent.copy(QRect(113, 368, 26, 30));
    else if (id == "key_blue-6")
        return hud_transparent.copy(QRect(141, 368, 18, 30));
    else if (id == "key_blue-7")
        return hud_transparent.copy(QRect(160, 368, 18, 30));

    else if (id == "chest-0")
        return hud.copy(QRect(183, 221, 48, 48));
    else if (id == "chest-1")
        return hud.copy(QRect(233, 221, 48, 48));
    else if (id == "chest-2")
        return hud.copy(QRect(283, 221, 48, 48));

    else if (id == "lil_key-grey")
        return hud_transparent.copy(QRect(1, 421, 12, 16));
    else if (id == "lil_key-green")
        return hud_transparent.copy(QRect(14, 421, 12, 16));
    else if (id == "lil_key-red")
        return hud_transparent.copy(QRect(27, 421, 12, 16));
    else if (id == "lil_key-blue")
        return hud_transparent.copy(QRect(40, 421, 12, 16));

    else if (id == "blue_walk-0")
        return spearhead.copy(moveBy(big_rect_blues, 0, 1, 24, 16));
    else if (id == "blue_walk-1")
        return spearhead.copy(moveBy(big_rect_blues, 2, 1, 24, 16));
    else if (id == "blue_walk-2")
        return spearhead.copy(moveBy(big_rect_blues, 1, 2, 24, 16));

    if (id == "blue_up-0")
        return spearhead.copy(moveBy(big_rect_blues, 0, 3, 24, 16));
    else if (id == "blue_up-1")
        return spearhead.copy(moveBy(big_rect_blues, 2, 3, 24, 16));
    else if (id == "blue_up-2")
        return spearhead.copy(moveBy(big_rect_blues, 1, 4, 24, 16));
    else if (id == "blue_smashed")
        return spearhead.copy(QRect(127, 1, 21, 16));
    else if (id == "blue_roll-0")
        return spearhead.copy(QRect(149, 1, 16, 16));
    else if (id == "blue_roll-1")
        return spearhead.copy(QRect(166, 1, 16, 16));
    else if (id == "blue_roll-2")
        return spearhead.copy(QRect(183, 1, 16, 16));
    else if (id == "blue_roll-3")
        return spearhead.copy(QRect(200, 1, 16, 16));

    else
    {
        std::cerr << "Cannot find sprite texture with id \"" << id << "\"\n";
        return QPixmap();
    }
}

QPixmap Sprites::number(int n, int fill)
{
    std::string text = std::to_string(n);

    // fill with 0s on the left
    if (fill)
        while (text.size() != fill)
            text = '0' + text;

    // create collage texture
    QPixmap collage(8 * int(text.size()), 8);
    QPainter painter(&collage);

    // add numbers
    for (int i = 0; i < text.size(); i++)
        painter.drawPixmap(8 * i, 0, Sprites::instance()->get(std::string("number-") + text[i]));

    // end painting (necessary for setMask)
    painter.end();

    // make background transparent
    collage.setMask(collage.createMaskFromColor(QColor(147, 187, 236)));

    return collage;
}

QPixmap Sprites::string(std::string text, int fill)
{
    // fill with 0s on the left
    if (fill)
        while (text.size() != fill)
            text = ' ' + text;

    // create collage texture
    QPixmap collage(8 * int(text.size()), 8);
    QPainter painter(&collage);

    // add letters
    for (int i = 0; i < text.size(); i++)
        if (text[i] != ' ')
            painter.drawPixmap(8 * i, 0, Sprites::instance()->get(std::string("char-") + text[i]));

    // end painting (necessary for setMask)
    painter.end();

    // make background transparent
    collage.setMask(collage.createMaskFromColor(QColor(147, 187, 236)));

    return collage;
}
