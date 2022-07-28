#include "LevelBuilder.h"
#include "StaticObject.h"
#include "Lift.h"
#include "Background.h"
#include "Game.h"
#include "Sprites.h"
#include "Block.h"
#include "Ramp.h"
#include "Frog.h"
#include "Torch.h"
#include "ToMap.h"
#include "ReturnMenu.h"
#include "SaveMenu.h"
#include "GiantCoin.h"
#include "Key.h"

using namespace WL3;

Wario* LevelBuilder::load(const QString& level_name)
{
    if (level_name == "world-1-1")
    {
        // background
        Game::instance()->world()->setBackgroundBrush(QBrush(QColor(92, 148, 252)));
        QGraphicsPixmapItem* background = new Background(QPointF(0, 0), ":/levels/1-1.png");
        background->setY(-TILE * 14);
        background->setX(0);


        /* PRIMO STAGE [0,31] */

        // Blocchi non rompibili
        for (int i = 0; i < 15; i++)
            new StaticObject(QPoint(TILE, -TILE * i), Sprites::instance()->get("wood-hard-0"));
        for (int i = 1; i < 11; i++)
            new StaticObject(QPoint(i * TILE, TILE), Sprites::instance()->get("terrain"));

        new StaticObject(QPoint(6 * TILE, 0), Sprites::instance()->get("block"));
        new StaticObject(QPoint(7 * TILE, 0), Sprites::instance()->get("block"));
        new StaticObject(QPoint(7 * TILE, -TILE), Sprites::instance()->get("block"));

        new StaticObject(QPoint(10 * TILE, 0), Sprites::instance()->get("block"));
        new StaticObject(QPoint(11 * TILE, 0), Sprites::instance()->get("block"));
        new StaticObject(QPoint(11 * TILE, -TILE), Sprites::instance()->get("block"));

        new StaticObject(QPoint(12 * TILE, -TILE), Sprites::instance()->get("terrain-1"));
        new StaticObject(QPoint(13 * TILE, -TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(14 * TILE, -TILE), Sprites::instance()->get("terrain-2"));
        new StaticObject(QPoint(14 * TILE, 0), Sprites::instance()->get("terrain-5"));
        new StaticObject(QPoint(14 * TILE, TILE), Sprites::instance()->get("terrain-8"));
        for (int i = 15; i < 20; i++)
            new StaticObject(QPoint(i * TILE, TILE), Sprites::instance()->get("terrain"));

        new StaticObject(QPoint(19 * TILE, 0), Sprites::instance()->get("block"));
        new StaticObject(QPoint(20 * TILE, 0), Sprites::instance()->get("block"));
        new StaticObject(QPoint(20 * TILE, -TILE), Sprites::instance()->get("block"));
        new StaticObject(QPoint(21 * TILE, -TILE), Sprites::instance()->get("terrain-1"));
        new StaticObject(QPoint(22 * TILE, -TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(23 * TILE, -TILE), Sprites::instance()->get("terrain-2"));
        new StaticObject(QPoint(23 * TILE, 0), Sprites::instance()->get("terrain-8"));

        for (int i = 24; i < 32; i++)
            new StaticObject(QPoint(i * TILE, 0), Sprites::instance()->get("terrain"));

        new StaticObject(QPoint(27 * TILE, 3 * -TILE), Sprites::instance()->get("ramp-0")); 
        new StaticObject(QPoint(28 * TILE, 3 * -TILE), Sprites::instance()->get("ramp-1")); 
        new StaticObject(QPoint(29 * TILE, 3 * -TILE), Sprites::instance()->get("ramp-2")); 
        new StaticObject(QPoint(29 * TILE, 4 * -TILE), Sprites::instance()->get("wood-hard-3"));
        for (int i = 5; i < 15; i++)
            new StaticObject(QPoint(29 * TILE, -TILE * i), Sprites::instance()->get("wood-hard-2"));

        new StaticObject(QPoint(30 * TILE, -3 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(31 * TILE, -3 * TILE), Sprites::instance()->get("terrain"));



        // Piattaforme
        new Lift(QPoint(TILE * 17, -9 * TILE));
        new Lift(QPoint(TILE * 21, -7 * TILE));
        new Lift(QPoint(TILE * 24, -5.5 * TILE));



        // Piante
        new Block(QPoint(16 * TILE, 0 * TILE), Sprites::instance()->get("plants-0"), Block::Type::HIDDEN);
        new Block(QPoint(17 * TILE, 0 * TILE), Sprites::instance()->get("plants-2"), Block::Type::HIDDEN);



        // Blocchi rompibili
        new Block(QPoint(8 * TILE, -2 * TILE));
        new Block(QPoint(8 * TILE, -1 * TILE));
        new Block(QPoint(8 * TILE, 0 * TILE));
        new Block(QPoint(8 * TILE, -9 * TILE));
        new Block(QPoint(9 * TILE, -9 * TILE));
        new Block(QPoint(9 * TILE, -2 * TILE), Block::Type::BRICK, Spawnable::Type::COIN);
        new Block(QPoint(9 * TILE, -1 * TILE));
        new Block(QPoint(9 * TILE, 0 * TILE));
        new Block(QPoint(10 * TILE, -1 * TILE));
        new Block(QPoint(12 * TILE, -9 * TILE));
        new Block(QPoint(13 * TILE, -9 * TILE));
        new Block(QPoint(18 * TILE, 0 * TILE));
        new Block(QPoint(19 * TILE, -1 * TILE), Block::Type::BRICK, Spawnable::Type::COIN);
        new Block(QPoint(20 * TILE, -2 * TILE));
        new Block(QPoint(27 * TILE, -2 * TILE));
        new Block(QPoint(27 * TILE, -1 * TILE));
        new Block(QPoint(28 * TILE, -2 * TILE));
        new Block(QPoint(28 * TILE, -1 * TILE));



        // Blocchi teletrasporto
        new Block(QPoint(31 * TILE, -2 * TILE), Sprites::instance()->get("door-0"),
            Block::Type::TELEPORTOUT, Spawnable::Type::NONE, 1, QPoint(31.8 * TILE, 14 * TILE));
        new Block(QPoint(31 * TILE, -1 * TILE), Sprites::instance()->get("door-1"),
            Block::Type::TELEPORTOUT, Spawnable::Type::NONE, 1, QPoint(31.8 * TILE, 14 * TILE));





        /* STAGE 2 [30,77] */

        // Blocchi non rompibili
        new StaticObject(QPoint(30 * TILE, 13 * TILE), Sprites::instance()->get("terrain"));
        for (int i = 30; i < 35; i++)
            new StaticObject(QPoint(i * TILE, 16 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(31 * TILE, 13 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(32 * TILE, 13 * TILE), Sprites::instance()->get("wood-hard-4"));
        for (int i = 0; i < 27; i++)
            new StaticObject(QPoint(32 * TILE, (12 - i) * TILE), Sprites::instance()->get("wood-hard-0"));

        new StaticObject(QPoint(35 * TILE, 25 * TILE), Sprites::instance()->get("terrain-8"));
        new StaticObject(QPoint(35 * TILE, 16 * TILE), Sprites::instance()->get("terrain-2"));
        for (int i = 17; i < 25; i++)
            new StaticObject(QPoint(35 * TILE, i * TILE), Sprites::instance()->get("terrain-5"));
        for (int i = 36; i < 44; i++)
            new StaticObject(QPoint(i * TILE, 25 * TILE), Sprites::instance()->get("terrain"));

        new StaticObject(QPoint(40 * TILE, 16 * TILE), Sprites::instance()->get("terrain-1"));
        new StaticObject(QPoint(40 * TILE, 20 * TILE), Sprites::instance()->get("terrain-7"));
        for (int i = 0; i < 3; i++)
            new StaticObject(QPoint(40 * TILE, (19 - i) * TILE), Sprites::instance()->get("terrain-4"));
        new StaticObject(QPoint(41 * TILE, 20 * TILE), Sprites::instance()->get("terrain-9"));
        new StaticObject(QPoint(41 * TILE, 16 * TILE), Sprites::instance()->get("terrain-2"));
        for (int i = 0; i < 3; i++)
            new StaticObject(QPoint(41 * TILE, (19 - i) * TILE), Sprites::instance()->get("terrain-5"));

        new StaticObject(QPoint(44 * TILE, 16 * TILE), Sprites::instance()->get("terrain-1"));
        new StaticObject(QPoint(44 * TILE, 25 * TILE), Sprites::instance()->get("terrain-6"));
        for (int i = 17; i < 25; i++)
            new StaticObject(QPoint(44 * TILE, i * TILE), Sprites::instance()->get("terrain-4"));
        new StaticObject(QPoint(45 * TILE, 16 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(46 * TILE, 16 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(46 * TILE, 20 * TILE), Sprites::instance()->get("terrain-10"));
        new StaticObject(QPoint(46 * TILE, 25 * TILE), Sprites::instance()->get("terrain-8"));
        for (int i = 0; i < 4; i++)
            new StaticObject(QPoint(46 * TILE, (24 - i) * TILE), Sprites::instance()->get("terrain-5"));

        new StaticObject(QPoint(47 * TILE, 16 * TILE), Sprites::instance()->get("terrain-2"));
        new StaticObject(QPoint(47 * TILE, 20 * TILE), Sprites::instance()->get("terrain-9"));
        for (int i = 0; i < 3; i++)
            new StaticObject(QPoint(47 * TILE, (19 - i) * TILE), Sprites::instance()->get("terrain-5"));
        for (int i = 47; i < 60; i++)
            new StaticObject(QPoint(i * TILE, 25 * TILE), Sprites::instance()->get("terrain"));

        for (int i = 0; i < 2; i++)
            new StaticObject(QPoint(48 * TILE, (17 - i) * TILE), Sprites::instance()->get("block"));

        new StaticObject(QPoint(49 * TILE, 16 * TILE), Sprites::instance()->get("terrain-1"));
        new StaticObject(QPoint(49 * TILE, 20 * TILE), Sprites::instance()->get("terrain-7"));
        for (int i = 0; i < 3; i++)
            new StaticObject(QPoint(49 * TILE, (19 - i) * TILE), Sprites::instance()->get("terrain-4"));
        new StaticObject(QPoint(50 * TILE, 16 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(51 * TILE, 16 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(52 * TILE, 16 * TILE), Sprites::instance()->get("terrain"));

        new StaticObject(QPoint(53 * TILE, 16 * TILE), Sprites::instance()->get("terrain-2"));
        for (int i = 50; i < 53; i++)
            new StaticObject(QPoint(i * TILE, 20 * TILE), Sprites::instance()->get("terrain-11"));
        new StaticObject(QPoint(53 * TILE, 20 * TILE), Sprites::instance()->get("terrain-9"));
        for (int i = 0; i < 3; i++)
            new StaticObject(QPoint(53 * TILE, (19 - i) * TILE), Sprites::instance()->get("terrain-5"));

        new StaticObject(QPoint(57 * TILE, 16 * TILE), Sprites::instance()->get("terrain-1"));
        new StaticObject(QPoint(57 * TILE, 22 * TILE), Sprites::instance()->get("terrain-7"));
        for (int i = 0; i < 5; i++)
            new StaticObject(QPoint(57 * TILE, (21 - i) * TILE), Sprites::instance()->get("terrain-4"));

        new StaticObject(QPoint(58 * TILE, 22 * TILE), Sprites::instance()->get("terrain-9"));
        new StaticObject(QPoint(58 * TILE, 16 * TILE), Sprites::instance()->get("terrain-2"));
        for (int i = 0; i < 5; i++)
            new StaticObject(QPoint(58 * TILE, (21 - i) * TILE), Sprites::instance()->get("terrain-5"));
        new StaticObject(QPoint(60 * TILE, 17 * TILE), Sprites::instance()->get("terrain-1"));
        new StaticObject(QPoint(60 * TILE, 25 * TILE), Sprites::instance()->get("terrain-6"));
        for (int i = 0; i < 7; i++)
            new StaticObject(QPoint(60 * TILE, (24 - i) * TILE), Sprites::instance()->get("terrain-4"));
        for (int i = 61; i < 69; i++)
            new StaticObject(QPoint(i * TILE, 17 * TILE), Sprites::instance()->get("terrain"));

        new StaticObject(QPoint(68 * TILE, 12 * TILE), Sprites::instance()->get("wood-hard-3"));
        for (int i = 0; i < 26; i++)
            new StaticObject(QPoint(68 * TILE, (11 - i) * TILE), Sprites::instance()->get("wood-hard-2"));
        new StaticObject(QPoint(69 * TILE, 12 * TILE), Sprites::instance()->get("wood-hard-4"));
        new StaticObject(QPoint(69 * TILE, 17 * TILE), Sprites::instance()->get("terrain-2"));
        for (int i = 0; i < 26; i++)
            new StaticObject(QPoint(69 * TILE, (11 - i) * TILE), Sprites::instance()->get("wood-hard-0"));

        new StaticObject(QPoint(71 * TILE, 17 * TILE), Sprites::instance()->get("terrain-1"));
        for (int i = 72; i < 78; i++)
            new StaticObject(QPoint(i * TILE, 17 * TILE), Sprites::instance()->get("terrain"));

        new StaticObject(QPoint(75 * TILE, 14 * TILE), Sprites::instance()->get("wood-hard-3"));
        for (int i = 0; i < 27; i++)
            new StaticObject(QPoint(75 * TILE, (13 - i) * TILE), Sprites::instance()->get("wood-hard-2"));

        new StaticObject(QPoint(76 * TILE, 14 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(77 * TILE, 14 * TILE), Sprites::instance()->get("terrain"));



        // Piattaforme
        new Lift(QPoint(TILE * 38, 16 * TILE), false, false, 4, 1, Sprites::instance()->get("static-platform-1"));
        new Lift(QPoint(TILE * 42, 16 * TILE), false, false, 4, 1, Sprites::instance()->get("static-platform-1"));
        new Lift(QPoint(TILE * 42, 18 * TILE), false, false, 4, 1, Sprites::instance()->get("static-platform-1"));
        new Lift(QPoint(TILE * 42, 20 * TILE), false, false, 4, 1, Sprites::instance()->get("static-platform-1"));
        new Lift(QPoint(TILE * 42, 22 * TILE), false, false, 4, 1, Sprites::instance()->get("static-platform-1"));
        new Lift(QPoint(TILE * 42, 24 * TILE), false, false, 4, 1, Sprites::instance()->get("static-platform-1"));

        new Lift(QPoint(TILE * 70, -3 * TILE));
        new Lift(QPoint(TILE * 70, 15 * TILE), false, false, 4, 1, Sprites::instance()->get("static-platform-1"));
        new Lift(QPoint(TILE * 70, 17 * TILE), false, false, 2, 1, Sprites::instance()->get("static-platform-1"));
        new Lift(QPoint(TILE * 71, -1 * TILE));
        new Lift(QPoint(TILE * 71, 3 * TILE));
        new Lift(QPoint(TILE * 71, 7 * TILE));
        new Lift(QPoint(TILE * 71, 11 * TILE));

        new Lift(QPoint(TILE * 73, 1 * TILE));
        new Lift(QPoint(TILE * 73, 5 * TILE));
        new Lift(QPoint(TILE * 73, 9 * TILE));
        new Lift(QPoint(TILE * 73, 13 * TILE));



        // Piante
        new Block(QPoint(64 * TILE, 16 * TILE), Sprites::instance()->get("plants-0"), Block::Type::HIDDEN);
        new Block(QPoint(65 * TILE, 16 * TILE), Sprites::instance()->get("plants-1"), Block::Type::HIDDEN);
        new Block(QPoint(66 * TILE, 16 * TILE), Sprites::instance()->get("plants-1"), Block::Type::HIDDEN);
        new Block(QPoint(67 * TILE, 16 * TILE), Sprites::instance()->get("plants-2"), Block::Type::HIDDEN);
        new Block(QPoint(72 * TILE, 16 * TILE), Sprites::instance()->get("plants-0"), Block::Type::HIDDEN);
        new Block(QPoint(73 * TILE, 16 * TILE), Sprites::instance()->get("plants-2"), Block::Type::HIDDEN);



        // Blocchi fuoco
        new Block(QPoint(54 * TILE, 16 * TILE), Sprites::instance()->get("fire-block"), Block::Type::FIRE);
        new Block(QPoint(55 * TILE, 16 * TILE), Sprites::instance()->get("fire-block"), Block::Type::FIRE);
        new Block(QPoint(56 * TILE, 16 * TILE), Sprites::instance()->get("fire-block"), Block::Type::FIRE);



        // Scala
        new Block(QPoint(59 * TILE, 25 * TILE), Sprites::instance()->get("terrain"), Block::Type::LADDERUP);
        new Lift(QPoint(59 * TILE, 17 * TILE), false, false, 2, 1,
            Sprites::instance()->get("static-platform-1"), false, true);
        new Lift(QPoint(59 * TILE, 19 * TILE), false, false, 2, 1,
            Sprites::instance()->get("ladder-0"), true, false);
        for (int i = (19 * TILE + 8); i < 25 * TILE; i = i + 8)
            new Block(QPoint(59 * TILE, i), Sprites::instance()->get("trasparent"),
                Block::Type::HIDDEN, Spawnable::Type::NONE, 5, QPoint(0, 0), true);



        // Blocchi rompibili
        new Block(QPoint(40 * TILE, 15 * TILE));
        new Block(QPoint(40 * TILE, 14 * TILE));
        new Block(QPoint(41 * TILE, 15 * TILE), Block::Type::BRICK, Spawnable::Type::COIN);

        for (int i = 0; i < 3; i++)
            new Block(QPoint(48 * TILE, (20 - i) * TILE));

        new Block(QPoint(50 * TILE, 24 * TILE));
        for (int i = 0; i < 2; i++)
            new Block(QPoint(51 * TILE, (24 - i) * TILE));
        for (int i = 0; i < 4; i++)
            new Block(QPoint(52 * TILE, (24 - i) * TILE));
        for (int i = 0; i < 4; i++)
            new Block(QPoint(53 * TILE, (24 - i) * TILE));
        for (int i = 0; i < 3; i++)
            new Block(QPoint(54 * TILE, (24 - i) * TILE));



        // Blocchi teletrasporto
        new Block(QPoint(30 * TILE, 15 * TILE), Sprites::instance()->get("door-1"),
            Block::Type::TELEPORTOUT, Spawnable::Type::NONE, 1, QPoint(28.5 * TILE, -2 * TILE));
        new Block(QPoint(30 * TILE, 14 * TILE), Sprites::instance()->get("door-0"),
            Block::Type::TELEPORTOUT, Spawnable::Type::NONE, 1, QPoint(28.5 * TILE, -2 * TILE));
        new Block(QPoint(77 * TILE, 15 * TILE), Sprites::instance()->get("door-0"),
            Block::Type::TELEPORTOUT, Spawnable::Type::NONE, 1, QPoint(77.5 * TILE, -1 * TILE));
        new Block(QPoint(77 * TILE, 16 * TILE), Sprites::instance()->get("door-0"),
            Block::Type::TELEPORTOUT, Spawnable::Type::NONE, 1, QPoint(77.5 * TILE, -1 * TILE));




        /* STAGE 3 [76, 122] */

        // Blocchi non rompibili
        for (int i = 76; i < 83; i++)
            new StaticObject(QPoint(i * TILE, TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(77 * TILE, -2 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(78 * TILE, -2 * TILE), Sprites::instance()->get("wood-hard-4"));
        for (int i = 0; i < 13; i++)
            new StaticObject(QPoint(78 * TILE, (-3 - i) * TILE), Sprites::instance()->get("wood-hard-0"));
        new StaticObject(QPoint(83 * TILE, -1 * TILE), Sprites::instance()->get("terrain-1"));
        new StaticObject(QPoint(83 * TILE, 0 * TILE), Sprites::instance()->get("terrain-4"));
        new StaticObject(QPoint(83 * TILE, 1 * TILE), Sprites::instance()->get("terrain-6"));
        new StaticObject(QPoint(84 * TILE, -1 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(85 * TILE, -1 * TILE), Sprites::instance()->get("terrain-6"));
        new StaticObject(QPoint(85 * TILE, -2 * TILE), Sprites::instance()->get("terrain-4"));
        new StaticObject(QPoint(85 * TILE, -3 * TILE), Sprites::instance()->get("terrain-1"));
        new StaticObject(QPoint(86 * TILE, -3 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(87 * TILE, -3 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(88 * TILE, -2 * TILE), Sprites::instance()->get("terrain-12"));
        new StaticObject(QPoint(89 * TILE, -1 * TILE), Sprites::instance()->get("terrain-12"));
        new StaticObject(QPoint(90 * TILE, 0), Sprites::instance()->get("terrain-12"));
        new StaticObject(QPoint(91 * TILE, TILE), Sprites::instance()->get("terrain-12"));
        for (int i = 0; i < 30; i++)
            new StaticObject(QPoint((92 + i) * TILE, TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(97 * TILE, 0 * TILE), Sprites::instance()->get("block"));
        for (int i = 112; i < 117; i++)
            new StaticObject(QPoint(i * TILE, -3 * TILE), Sprites::instance()->get("trasparent"));
        new StaticObject(QPoint(116 * TILE, -1 * TILE), Sprites::instance()->get("terrain-7"));
        new StaticObject(QPoint(116 * TILE, -2 * TILE), Sprites::instance()->get("trasparent"));
        new StaticObject(QPoint(117 * TILE, -2 * TILE), Sprites::instance()->get("terrain-10"));
        new StaticObject(QPoint(117 * TILE, -1 * TILE), Sprites::instance()->get("terrain-9"));
        for (int i = 0; i < 6; i++)
            new StaticObject(QPoint((117 + i) * TILE, -3 * TILE), Sprites::instance()->get("terrain"));
        for (int i = 0; i < 4; i++)
            new StaticObject(QPoint((118 + i) * TILE, -2 * TILE), Sprites::instance()->get("terrain-11"));

        new StaticObject(QPoint(122 * TILE, 1 * TILE), Sprites::instance()->get("terrain-6"));
        new StaticObject(QPoint(122 * TILE, -2 * TILE), Sprites::instance()->get("terrain-13"));
        for (int i = 0; i < 2; i++)
            new StaticObject(QPoint(122 * TILE, (-i) * TILE), Sprites::instance()->get("terrain-4"));
        for (int i = -14; i < -3; i++)
            new StaticObject(QPoint(122 * TILE, i * TILE), Sprites::instance()->get("wood-hard-2"));



        // Piante
        new Block(QPoint(79 * TILE, 0 * TILE), Sprites::instance()->get("plants-0"),
            Block::Type::HIDDEN, Spawnable::Type::NONE);
        new Block(QPoint(80 * TILE, 0 * TILE), Sprites::instance()->get("plants-2"),
            Block::Type::HIDDEN, Spawnable::Type::NONE);
        new Block(QPoint(92 * TILE, 0 * TILE), Sprites::instance()->get("plants-0"),
            Block::Type::HIDDEN, Spawnable::Type::NONE);
        new Block(QPoint(93 * TILE, 0 * TILE), Sprites::instance()->get("plants-1"),
            Block::Type::HIDDEN, Spawnable::Type::NONE);
        new Block(QPoint(94 * TILE, 0 * TILE), Sprites::instance()->get("plants-2"),
            Block::Type::HIDDEN, Spawnable::Type::NONE);



        // Rampa
        for (int i = 88 * TILE; i < 92 * TILE; i++)
            (new Ramp(QPoint(i, -3 * TILE - 88 * TILE + i), 1));



        // Blocchi rompibili
        new Block(QPoint(81 * TILE, 0 * TILE));
        new Block(QPoint(82 * TILE, 0 * TILE));
        new Block(QPoint(81 * TILE, -1 * TILE));
        new Block(QPoint(82 * TILE, -1 * TILE));
        new Block(QPoint(84 * TILE, -2 * TILE));
        new Block(QPoint(84 * TILE, -3 * TILE), Block::Type::BRICK, Spawnable::Type::COIN);
        new Block(QPoint(95 * TILE, 0 * TILE));
        new Block(QPoint(96 * TILE, 0 * TILE));
        new Block(QPoint(98 * TILE, 0 * TILE));
        new Block(QPoint(116 * TILE, 0 * TILE), Block::Type::BRICK, Spawnable::Type::NONE, true);
        new Block(QPoint(117 * TILE, 0 * TILE), Block::Type::BRICK, Spawnable::Type::NONE, true);



        // Blocchi teletrasporto
        new Block(QPoint(76 * TILE, 0 * TILE), Sprites::instance()->get("door-0"),
            Block::Type::TELEPORTOUT, Spawnable::Type::NONE, 1, QPoint(74.5 * TILE, 15 * TILE));
        new Block(QPoint(76 * TILE, -1 * TILE), Sprites::instance()->get("door-0"),
            Block::Type::TELEPORTOUT, Spawnable::Type::NONE, 1, QPoint(74.5 * TILE, 15 * TILE));
        new Block(QPoint(113 * TILE, 1 * TILE), Sprites::instance()->get("terrain"),
            Block::Type::TELEPORTIN, Spawnable::Type::NONE, 1, QPoint(126.5 * TILE, -1 * TILE));





        /* STAGE 4 [124, 139] */

        // Blocchi non rompibili
        for (int i = 125; i < 133; i++)
            new StaticObject(QPoint(i * TILE, 1 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(125 * TILE, -3 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(125 * TILE, -2 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(126 * TILE, -14 * TILE), Sprites::instance()->get("screw"));
        new StaticObject(QPoint(126 * TILE, -3 * TILE), Sprites::instance()->get("terrain-9"));
        new StaticObject(QPoint(126 * TILE, -4 * TILE), Sprites::instance()->get("terrain-5"));
        new StaticObject(QPoint(126 * TILE, -5 * TILE), Sprites::instance()->get("terrain-2"));
        for (int i = 0; i < 9; i++)
            new StaticObject(QPoint(126 * TILE, (-6 - i) * TILE), Sprites::instance()->get("wood-hard-0"));
        for (int i = 127; i < 139; i++)
            new StaticObject(QPoint(i * TILE, -14 * TILE), Sprites::instance()->get("brown-2"));

        new StaticObject(QPoint(128 * TILE, -9 * TILE), Sprites::instance()->get("brown"));
        new StaticObject(QPoint(128 * TILE, -10 * TILE), Sprites::instance()->get("brown"));
        new StaticObject(QPoint(128 * TILE, -11 * TILE), Sprites::instance()->get("brown"));
        new StaticObject(QPoint(129 * TILE, -10 * TILE), Sprites::instance()->get("brown-1"));
        new StaticObject(QPoint(129 * TILE, -11 * TILE), Sprites::instance()->get("brown-1"));
        for (int i = 129; i < 139; i++)
            new StaticObject(QPoint(i * TILE, -9 * TILE), Sprites::instance()->get("brown-2"));
        new StaticObject(QPoint(133 * TILE, 1 * TILE), Sprites::instance()->get("terrain-6"));
        new StaticObject(QPoint(133 * TILE, 0 * TILE), Sprites::instance()->get("terrain-1"));
        for (int i = 134; i < 140; i++)
            new StaticObject(QPoint(i * TILE, 0 * TILE), Sprites::instance()->get("terrain"));
        new StaticObject(QPoint(139 * TILE, -9 * TILE), Sprites::instance()->get("screw-1"));
        new StaticObject(QPoint(139 * TILE, -14 * TILE), Sprites::instance()->get("screw-1"));
        for (int i = 0; i < 8; i++)
            new StaticObject(QPoint(139 * TILE, (-1 - i) * TILE), Sprites::instance()->get("wood-hard-2"));
        for (int i = 0; i < 4; i++)
            new StaticObject(QPoint(139 * TILE, (-10 - i) * TILE), Sprites::instance()->get("wood-hard-2"));



        // Piattaforme
        new Lift(QPoint(127 * TILE, -4 * TILE));
        new Lift(QPoint(129 * TILE, -4 * TILE));
        new Lift(QPoint(131 * TILE, -4 * TILE));
        new Lift(QPoint(133 * TILE, -4 * TILE));
        new Lift(QPoint(135 * TILE, -2 * TILE), false, false, 4, 1,
            Sprites::instance()->get("static-platform-1"));



        // Scala
        new Block(QPoint(127 * TILE, -4 * TILE),
            Sprites::instance()->get("static-platform"),Block::Type::LADDERUP);
        new Lift(QPoint(127 * TILE, -13 * TILE), false, false, 2, 1,
            Sprites::instance()->get("green"), false, true);
        new Lift(QPoint(127 * TILE, -11 * TILE), false, false, 2, 1,
            Sprites::instance()->get("ladder-1"), true, false);
        for (int i = 4 * TILE; i < 11 * TILE; i = i + 8)
            new Block(QPoint(127 * TILE, -i),Sprites::instance()->get("trasparent"),
                Block::Type::HIDDEN, Spawnable::Type::NONE, 5, QPoint(0, 0), true);



        // Blocchi teletrasporto
        new Block(QPoint(124 * TILE, -1 * TILE), Sprites::instance()->get("door-0"),
            Block::Type::TELEPORTOUT, Spawnable::Type::NONE, 1, QPoint(112.5 * TILE, -1 * TILE));
        new Block(QPoint(124 * TILE, 0 * TILE), Sprites::instance()->get("door-0"),
            Block::Type::TELEPORTOUT, Spawnable::Type::NONE, 1, QPoint(112.5 * TILE, -1 * TILE));







        // Menu
        new GiantCoin(QPoint(1 * TILE, 13.3 * TILE));
        new ReturnMenu(QPoint(1 * TILE, 9.5 * TILE));
        new SaveMenu(QPoint(3 * TILE, 10 * TILE));
        new ToMap(QPoint(7 * TILE, 10 * TILE));



        // Entità
        new Frog(QPoint(36 * TILE, 17 * TILE), Direction::NONE);
        new Torch(QPoint(106.9 * TILE, -3 * TILE), Direction::NONE);



        // Premi
        new Key(QPoint(5 * TILE, -10 * TILE), Key::Color::GREEN); // primo stage
        new GiantCoin(QPoint(49 * TILE, 22.5 * TILE)); // secondo stage
        new Key(QPoint(39 * TILE, 23.5 * TILE), Key::Color::BLUE); // secondo stage
        new Key(QPoint(70 * TILE, -6.5 * TILE), Key::Color::GREY); // secondo stage
        new Key(QPoint(119 * TILE, 0.1 * TILE), Key::Color::RED); // terzo stage
   
        // Numero di monete per finire il livello
        Game::instance()->chest_coin(4);


        return new Wario(QPointF(3 * TILE, -2 * TILE));
    }
    else
    {
        std::cerr << "Cannot load level: level " << level_name.toStdString() << " not found\n";
        return 0;
    }
}
