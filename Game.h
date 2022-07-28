#pragma once
#include <QGraphicsView>
#include <QTimer>
#include <QLabel>
#include <QSound>
#include "LevelBuilder.h"
#include "DynamicObject.h"
#include "Hud.h"

namespace WL3
{
    // parametri globali
	static const int FPS = 60;
	static const int TILE = 16;


	class Game;
    enum class GameState { READY, RUNNING, PAUSED, GAME_OVER, MENU };
    enum class CameraState {CAM1=(-13*TILE - 8), CAM2=(-20*TILE + 1), CAM3=(8*TILE + 8), CAM4=(16*TILE+7), CAM5=(0*TILE + 8)};
}

class WL3::Game : public QGraphicsView
{ 
	Q_OBJECT 

	private:
        // attributi di gioco
		QTimer			_engine;
		GameState		_state;
        CameraState     _statecam;
		QGraphicsScene* _world;
        Wario*			_player;
		LevelBuilder*   _builder;
		HUD*			_hud;
        QGraphicsPixmapItem* screen;
        QGraphicsPixmapItem* screen_white;
		bool			_freezed;

        // controlli precisi
		bool			_left_pressed;
		bool			_right_pressed;
		bool			_crouch_pressed;
        bool			_up_pressed;
        bool            _up_block;
        bool            _jump_pressed;
        bool            _jump_block;
        bool			_run_pressed;
        bool            _run_block;

        // misurazioni di FPS e contatori
		int				_frame_count;
        QTimer			_FPS_timer;
        int             _schedule_white;

        // chiavi per aprire la chest
        int             _coin;

        // singleton
		static Game* _uniqueInstance;
        Game();

	public: 
		static Game* instance();

		// getters / setters
        Wario* wario() { return _player; }
        HUD* hud() { return _hud; }
        GameState state() { return _state; }
		QGraphicsScene* world()  { return _world; }
        double aspectRatio() { return 16 * 1.14 / 15; }
        int chest_coin () {return _coin;}
		void freeze(bool on) { _freezed = on; }
        void chest_coin (int tot) {_coin=tot;}

        // gestori di eventi
		virtual void keyPressEvent(QKeyEvent* e) override;		
		virtual void keyReleaseEvent(QKeyEvent* e) override;
		virtual void wheelEvent(QWheelEvent* e) override;
        virtual void resizeEvent(QResizeEvent* event) override;

	public slots:

		void reset();
		void start();
		void nextFrame();
		void toggleColliders();
		void updateFPS();
		void gameover();
        void menu();
};
