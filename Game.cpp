#include <QApplication>
#include <QPainter>
#include <QKeyEvent>
#include <QIcon>
#include <QOpenGLWidget>
#include "Game.h"
#include "Wario.h"
#include "Enemy.h"
#include "Torch.h"
#include "Fireball.h"
#include "Spider.h"
#include "Spark.h"
#include "Sprites.h"
#include "Sounds.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include "DynamicPlatform.h"
#include "GiantCoin.h"
#include "ReturnMenu.h"
#include "SaveMenu.h"
#include "ToMap.h"

using namespace WL3;

// singleton
Game* Game::_uniqueInstance = 0;
Game* Game::instance()
{
    if (_uniqueInstance == 0)
        _uniqueInstance = new Game();
    return _uniqueInstance;
}

Game::Game() : QGraphicsView()
{
    // setup world
    _world = new QGraphicsScene();
    _world->setSceneRect(0, -TILE * 12, TILE * 224, TILE * 15);
    setScene(_world);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // setup game engine
    QObject::connect(&_engine, SIGNAL(timeout()), this, SLOT(nextFrame()));
    _engine.setTimerType(Qt::PreciseTimer);
    _engine.setInterval(1000 / FPS);

    // setup FPS measuring
    QObject::connect(&_FPS_timer, SIGNAL(timeout()), this, SLOT(updateFPS()));
    _FPS_timer.setTimerType(Qt::PreciseTimer);
    _FPS_timer.setInterval(1000);
    _FPS_timer.start();

    // inizializza il level builder
    _builder = new LevelBuilder();

    // abilita il rendering openGL
    QOpenGLWidget* gl = new QOpenGLWidget();
    setViewport(gl);

    _schedule_white = 0;

    // inizializza HUD
    _hud = new HUD(width(), height(), this);

    reset();
}

void Game::reset()
{
    _state = GameState::READY;
    _engine.stop();
    _world->clear();
    _hud->reset();
    _player = 0;
    _frame_count = 0;
    _freezed = false;
    _left_pressed = false;
    _right_pressed = false;
    _crouch_pressed = false;
    _up_pressed = false;
    _run_pressed = false;
    _jump_pressed = false;
    _jump_block = false;
    _coin = 999;
    _schedule_white = 0;


    QGraphicsPixmapItem* title_screen = _world->addPixmap(QPixmap(Sprites::instance()->get("title-screen")));
    title_screen->setY(-TILE * 6);

    setSceneRect(QRectF());
    centerOn(0, 0);

    Sounds::instance()->stop("ost_main");
    Sounds::instance()->stop("ost_fire");
    Sounds::instance()->stop("ost_menu");
    Sounds::instance()->stop("ost_worm");
    Sounds::instance()->stop("run");
    Sounds::instance()->stop("ost_win");
    Sounds::instance()->run();
}

void Game::start()
{
    if (_state == GameState::READY)
    {
        _state = GameState::RUNNING;
        _world->clear();
        _engine.start();

        if (!Sounds::instance()->running())
            Sounds::instance()->play("ost_main", true);

        _player = _builder->load("world-1-1");
    }
}

void Game::nextFrame()
{
    if (_state == GameState::MENU) {
        for (auto item : _world->items())
        {
            GiantCoin* giantCoin = dynamic_cast<GiantCoin*>(item);
            ReturnMenu* retMenu = dynamic_cast<ReturnMenu*>(item);
            SaveMenu* save = dynamic_cast<SaveMenu*>(item);
            ToMap* toMap = dynamic_cast<ToMap*>(item);


            if (giantCoin)
                giantCoin->animate();
            if (retMenu)
                retMenu->animate();
            if (save)
                save->animate();
            if (toMap)
                toMap->animate();
        }
    }

    if (_player->end_screen())
        gameover();
    if (_player->white_screen() && _schedule_white == 0)
    {
        _schedule_white++;
        menu();
    }
    else if (_player->white_screen() && _schedule_white < 30)
        _schedule_white++;
    else if (_player->white_screen())
    {
        menu();
        _player->white_screen(false);
        _schedule_white = 0;
    }

    if (_state != GameState::RUNNING)
        return;

    _frame_count++;

    // controlli precisi del giocatore
    if (!_freezed && !_player->is_sliding() && !_player->lock_keys())
    {
        if (_right_pressed)
        {
            _player->move(Direction::RIGHT);

            if (!_player->is_run() && !_player->is_on_pre_fire() && !_player->is_on_fire()
                && !_player->pre_worm() && !_player->worm() && !_player->post_worm() && !_player->pre_rool()
                && !_player->rool() && !_player->thunder() && !_player->bumped())
            {
                if (_player->crouch() && _player->mag() != 0 && Sounds::instance()->isFinished("crouch") && !_player->isInAir())
                    Sounds::instance()->play("crouch");
                else if (!_player->crouch() && _player->mag() != 0 && Sounds::instance()->isFinished("walk") && !_player->isInAir())
                    Sounds::instance()->play("walk");
            }
        }
        else if (_left_pressed)
        {
            _player->move(Direction::LEFT);
            if (!_player->is_run() && !_player->is_on_pre_fire() && !_player->is_on_fire()
                && !_player->pre_worm() && !_player->worm() && !_player->post_worm() && !_player->pre_rool()
                && !_player->rool() && !_player->thunder() && !_player->bumped())
            {
                if (_player->crouch() && _player->mag() != 0 && Sounds::instance()->isFinished("crouch") && !_player->isInAir())
                    Sounds::instance()->play("crouch");
                else if (!_player->crouch() && _player->mag() != 0 && Sounds::instance()->isFinished("walk") && !_player->isInAir())
                    Sounds::instance()->play("walk");
            }
        }
        else
            _player->move(Direction::NONE);

        _player->crouch(_crouch_pressed);
        _player->up_steps(_up_pressed);
        _player->ladder_run(_run_pressed);


        if (_run_pressed && !_run_block)
        {
            _player->initialcrouch(_crouch_pressed);
            _player->run(true);
            _run_block = true;
        }
        if (_up_pressed && !_up_block)
        {
            _up_block = true;
            _player->entrable();
        }
        if (_jump_pressed && !_jump_block)
        {
            _jump_block = true;
            _player->jump_ramp(true);
        }


    }

    // fa partire prima gli oggetti dinamici
    for (auto item : _world->items())
    {
        DynamicPlatform* obj = dynamic_cast<DynamicPlatform*>(item);

        if (obj && obj->isVisible())
        {
            obj->unfreezeWhenVisible();
            if (obj->freezed())
                continue;

            if (!obj->isVisible())
                continue;

            if (!_freezed)
            {
                obj->advance();
                obj->updateSchedulers();
            }
            obj->animate();
        }
    }

    // main game loop
    for (auto item : _world->items())
    {
        Object* obj = dynamic_cast<Object*>(item);
        Fireball* frb = dynamic_cast<Fireball*>(item);
        Spark* srp = dynamic_cast<Spark*>(item);
        Spider* spi = dynamic_cast<Spider*>(item);
        Torch* thc = dynamic_cast<Torch*>(item);

        if (obj && obj->isVisible() && !obj->to<DynamicPlatform*>())
        {
            obj->unfreezeWhenVisible();
            if (obj->freezed() && !frb && !srp && !thc && !spi)
                continue;

            if (!obj->isVisible() && !frb && !srp && !thc && !spi)
                continue;

            if (!_freezed || obj == _player || frb || srp || thc || spi )
                obj->advance();

            if (!_freezed || obj == _player || frb || srp || thc || spi )
                obj->updateSchedulers();

            if (!_freezed || obj == _player || frb || srp || thc || spi )
                obj->animate();
        }
    }


    // camera centrata sul giocatore
    centerOn(_player->x(), 0);

    if (_player->y() < 0 && (!_player->isInAir() || _statecam == CameraState::CAM1))
        _statecam = CameraState::CAM1;

    if (_player->y() < -8 * TILE && (!_player->isInAir() || _statecam == CameraState::CAM2))
        _statecam = CameraState::CAM2;

    if (_player->y() > 0 * TILE && (!_player->isInAir() || _statecam == CameraState::CAM5))
        _statecam = CameraState::CAM5;

    if (_player->y() > 9 * TILE && (!_player->isInAir() || _statecam == CameraState::CAM3))
        _statecam = CameraState::CAM3;

    if (_player->y() > 17 * TILE && (!_player->isInAir() || _statecam == CameraState::CAM4))
        _statecam = CameraState::CAM4;

    setSceneRect((sceneRect().x(), _player->x() - 4 * TILE), static_cast<int>(_statecam), 16 * TILE, 15 * TILE);

    if (_player->x() < TILE * 4)
        setSceneRect(0, static_cast<int>(_statecam), 16 * TILE, 15 * TILE);
    if (_player->x() > TILE * 24 && _player->x() < TILE * 30)
        setSceneRect(TILE * 14, static_cast<int>(_statecam), 16 * TILE, 15 * TILE);
    if (_player->x() > TILE * 30 && _player->x() < TILE * 38)
        setSceneRect(TILE * 32, static_cast<int>(_statecam), 16 * TILE, 15 * TILE);
    if (_player->x() > TILE * 70 && _player->x() < TILE * 76)
        setSceneRect(TILE * 60, static_cast<int>(_statecam), 16 * TILE, 15 * TILE);
    if (_player->x() > TILE * 76 && _player->x() < TILE * 84)
        setSceneRect(TILE * 78, static_cast<int>(_statecam), 16 * TILE, 15 * TILE);


    if (_player->x() > TILE * 118 && _player->x() < TILE * 126)
        setSceneRect(TILE * 108, static_cast<int>(_statecam), 16 * TILE, 15 * TILE);
    if (_player->x() > TILE * 124 && _player->x() < TILE * 130)
        setSceneRect(TILE * 126, static_cast<int>(_statecam), 16 * TILE, 15 * TILE);
    if (_player->x() > TILE * 134 && _player->x() < TILE * 142)
        setSceneRect(TILE * 124, static_cast<int>(_statecam), 16 * TILE, 15 * TILE);
    if (_player->x() > TILE * 142 && _player->x() < TILE * 148)
        setSceneRect(TILE * 142, static_cast<int>(_statecam), 16 * TILE, 15 * TILE);
    if (_player->x() > TILE * 183 && _player->x() < TILE * 189)
        setSceneRect(TILE * 174, static_cast<int>(_statecam), 16 * TILE, 15 * TILE);






    if (_player->x() > TILE * 126 && _player->x() < TILE * 139 && _player->y() <= 0)
    {
        if (_player->y() < (-10 * TILE + 1)) // in alto a tutto
            setSceneRect(TILE * 126, (-20 * TILE + 1), 16 * TILE, 15 * TILE);
        else if (_player->y() >= 1 * TILE) // livello base
            setSceneRect(TILE * 126, _player->y() - TILE * 10 + 1, 16 * TILE, 15 * TILE);
        else if (_player->y() < -3 * TILE)  // livello medio, quando y<-3
            setSceneRect(TILE * 126, _player->y() - TILE * 6 + 1, 16 * TILE, 15 * TILE);
    }


    _hud->advance();
}

void Game::keyPressEvent(QKeyEvent* e)
{
    if (e->isAutoRepeat())
        return;

    if (_state != GameState::MENU) // comandi di gioco
    {
        if (e->key() == Qt::Key_S)
            start();
        else if (e->key() == Qt::Key_R)
            reset();
        else if (e->key() == Qt::Key_C)
            toggleColliders();
        else if (e->key() == Qt::Key_Minus)
            _engine.setInterval(250);
        else if (e->key() == Qt::Key_Plus)
            _engine.setInterval(1000 / FPS);
        else if (e->key() == Qt::Key_Escape)
            if (_state != GameState::READY)
                menu();

    }
    else if (_state == GameState::MENU) 
        if (e->key() == Qt::Key_Escape)
            menu();

    if (_state == GameState::RUNNING && _player && !_player->lock_keys() && _player->is_on_pre_fire())
    {
        if (e->key() == Qt::Key_Space)
        {
            _player->jump();
            _jump_pressed = true;
        }
    }

    if (_state == GameState::RUNNING && _player && !_player->lock_keys() && !_player->worm() && !_player->pre_worm())
    {
        if (e->key() == Qt::Key_Left)
            _left_pressed = true;
        else if (e->key() == Qt::Key_Right)
            _right_pressed = true;
        else if (e->key() == Qt::Key_Down)
            _crouch_pressed = true;
        else if (e->key() == Qt::Key_Up)
            _up_pressed = true;
        else if (e->key() == Qt::Key_Space && !_player->is_on_fire())
        {
            _player->jump();
            _jump_pressed = true;
        }
        else if (e->key() == Qt::Key_I)
            _player->invincible(true);
        else if (e->key() == Qt::Key_Z && !_player->is_on_fire() && !_player->is_on_pre_fire())
            _run_pressed = true;
    }

}

void Game::keyReleaseEvent(QKeyEvent* e)
{
    if (e->isAutoRepeat())
        return;

    if (_state == GameState::RUNNING && _player)
    {
        if (e->key() == Qt::Key_Left)
            _left_pressed = false;
        else if (e->key() == Qt::Key_Right)
            _right_pressed = false;
        else if (e->key() == Qt::Key_Down) {
            _crouch_pressed = false;
            _player->initialcrouch(_crouch_pressed);
        }
        else if (e->key() == Qt::Key_Up)
        {
            _up_pressed = false;
            _up_block = false;
        }
        else if (e->key() == Qt::Key_Space)
        {
            _jump_pressed = false;
            _jump_block = false;
            _player->jump(false);
        }
        else if (e->key() == Qt::Key_Z)
        {
            _run_pressed = false;
            _run_block = false;
        }
    }
}


void Game::wheelEvent(QWheelEvent* e)
{
    if (e->angleDelta().y() > 0)
        scale(1.1, 1.1);
    else
        scale(1 / 1.1, 1 / 1.1);
}

void Game::resizeEvent(QResizeEvent* evt)
{
    fitInView(0, 0, TILE * 10 - 1, TILE * 9 - 1);
    _hud->resize(evt->size());
}

void Game::updateFPS()
{
    _hud->setFPS(_frame_count);
    _frame_count = 0;
}

void Game::toggleColliders()
{
    for (auto item : _world->items())
        if (dynamic_cast<Object*>(item))
            dynamic_cast<Object*>(item)->toggleCollider();
}


void Game::gameover()
{
    _state = GameState::GAME_OVER;
    Sounds::instance()->stop("ost_main");
    Sounds::instance()->stop("ost_fire");
    Sounds::instance()->stop("ost_worm");
    Sounds::instance()->stop("run");
    Sounds::instance()->run();

    _engine.stop();

    if (!Sounds::instance()->running())
        Sounds::instance()->play("ost_win", true);

    QGraphicsPixmapItem* screen = _world->addPixmap(QPixmap(Sprites::instance()->get("win")));

    screen->setY(6 * TILE);
    screen->setZValue(999);
    setSceneRect(QRectF());
    centerOn(5 * TILE, 10 * TILE);
    setSceneRect(screen->x(), screen->y(), 16 * TILE, 15 * TILE);
}

void Game::menu()
{
    screen = _world->addPixmap(QPixmap(Sprites::instance()->get("menu")));
    screen_white = _world->addPixmap(QPixmap(Sprites::instance()->get("white")));

    if (_state == GameState::RUNNING)
    {
        _state = GameState::MENU;


        setSceneRect(QRectF());
        centerOn(5 * TILE, 10 * TILE);
        if (_player->white_screen())
        {
            screen_white->setY(22 * TILE);
            screen_white->setZValue(5);
            setSceneRect(screen_white->x(), screen_white->y(), 16 * TILE, 15 * TILE);
        }
        else
        {
            screen->setY(6 * TILE);
            screen->setZValue(5);
            setSceneRect(screen->x(), screen->y(), 16 * TILE, 15 * TILE);
            _hud->menuPause(_player->getCoins(), _player->getTotal(), _player->getUnit());
            Sounds::instance()->stop("ost_main");
            Sounds::instance()->stop("ost_fire");
            Sounds::instance()->stop("ost_worm");
            Sounds::instance()->stop("run");
            Sounds::instance()->run();
            if (!Sounds::instance()->running())
                Sounds::instance()->play("ost_menu", true);
        }
    }
    else if (_state == GameState::MENU && (!_player->white_screen() || _schedule_white >= 30))
    {
        _freezed = false;
        _left_pressed = false;
        _right_pressed = false;
        _crouch_pressed = false;
        _up_pressed = false;
        _run_pressed = false;
        _engine.start();
        _state = GameState::RUNNING;
        if (!_player->white_screen())
        {
            Sounds::instance()->stop("ost_menu");
            Sounds::instance()->run();

            if (_player->is_on_pre_fire() || _player->is_on_fire())
                Sounds::instance()->play("ost_fire");
            else if (_player->pre_worm() || _player->worm() || _player->post_worm())
                Sounds::instance()->play("ost_worm");
            else if (_player->is_run())
                Sounds::instance()->play("run", true);
            else
                Sounds::instance()->play("ost_main", true);
        }
    }
}
