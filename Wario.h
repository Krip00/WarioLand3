#pragma once

#include "DynamicObject.h"
#include "Enemy.h"

namespace WL3
{
    class Wario;
}

class WL3::Wario : public DynamicObject
{
protected:

    // state flags
    bool _white_screen;
    bool _end_screen;
    bool _scripted;
    bool _rool;
    bool _pre_rool;
    bool _run;
    bool _nextstop;
    bool _sleep;
    bool _stopimpact;
    bool _checksleep;
    bool _sliding;
    bool _black_fire;
    bool _pre_fire;
    bool _thunder;
    bool _post_thunder;
    bool _pre_worm;
    bool _worm;
    bool _post_worm;
    bool _invincible;
    bool _crouch;
    bool _initialcrouch;
    bool _bouncing;
    bool _fire;
    bool _gliding;
    bool _entrable;
    bool _scripted_ladder;
    bool _up_steps;
    bool _ladder_run;
    bool _fire_run;
    bool _burn_red;
    bool _burn_black;
    bool _burn_normal;
    bool _ground_bounce;
    bool _bumped;
    bool _jump_ramp;
    bool _script_animation;
    bool _lock_keys;
    int _can_crouch;    

    // sprites
    QPixmap _texture_stand[8][12];
    QPixmap _texture_crouch[1][12];
    QPixmap _texture_walk[4][12];
    QPixmap _texture_skid[5][12];
    QPixmap _texture_air[1][12];
    QPixmap _texture_running[8][12];
    QPixmap _texture_sleep[4][12];
    QPixmap _texture_crouch_walk[2][12];
    QPixmap _texture_roll[8][12];
    QPixmap _texture_pre_roll[5][12];
    QPixmap _texture_pre_roll_noscript[5][12];
    QPixmap _texture_stairs[11][12];
    QPixmap _texture_invisible[8][12];
    QPixmap _texture_fire_run[8][12];   
    QPixmap _texture_burn_red[16][12];  
    QPixmap _texture_burn_black[13][12]; 
    QPixmap _texture_electric[13][12];
    QPixmap _texture_bump[8][12];
    QPixmap _texture_pre_worm[5][12];
    QPixmap _texture_worm[4][12];
    QPixmap _texture_post_worm[16][12];


    // contatori
    int _coins;           // monete giganti
    int _total_coins;     // monete totali da vedere nel menu
    int _little_coins;    // monetine dai blocchi
    int _unit;            // rappresentazione delle unita' nel menu' per le monete
    int _key;             // chiavi prese
    int _sleepcount = 0;
    int _runcount = 0;
    double _bouncecount = 0;

public:
    Wario(QPointF pos);
    std::vector<Enemy*> enemyStage;

    // getters
    bool jump_ramp() { return _jump_ramp; }
    bool scripted() { return _scripted; }
    bool white_screen() { return _white_screen; }
    bool end_screen() { return _end_screen; }
    bool scripted_ladder() { return _scripted_ladder; }
    bool ground_bounce() { return _ground_bounce; }
    bool bumped() { return _bumped; }
    bool rool() { return _rool; }
    bool thunder() { return _thunder; }
    bool worm() { return _worm; }
    bool pre_worm() { return _pre_worm; }
    bool post_worm() { return _post_worm; }
    bool pre_rool() { return _pre_rool; }
    bool ladder_run() { return _ladder_run; }
    bool up_steps() { return _up_steps; }
    bool is_run() { return _run; }
    bool is_on_fire() { return _fire; }
    bool is_on_pre_fire() { return _pre_fire; }
    bool stopimpact() { return _stopimpact; }
    bool is_sleep() { return _sleep; }
    bool bouncing() { return _bouncing; }
    bool lock_keys() {return _lock_keys;}
    bool is_sliding() { return _sliding; }
    bool invincible() { return _invincible; }
    bool checksleep() { return _checksleep; }
    bool crouch() { return _crouch; }
    bool initialcrouch() { return _initialcrouch; }
    bool nextstop() { return _nextstop; }
    bool is_entrable() { return _entrable; }
    int getCoins() { return _coins; }
    int getLittleCoins() { return _little_coins; }
    int getTotal() { return _total_coins; }
    int getUnit() { return _unit; }
    double mag() const { return double(std::sqrt(_vel.x * _vel.x + _vel.y * _vel.y)); }

    void setCoins() { _coins++; }
    void setLittleCoins() { _little_coins++; }
    void setUnit() { _unit++; }
    void increase_total(bool special = false) { if (special) _total_coins += 20; else _total_coins++; } 
    void lock_keys(bool on) {_lock_keys = on;}

    // setters
    virtual void ground_bounce(bool on) { _ground_bounce = on; }
    virtual void thunder(bool on) { _thunder = on; }           
    virtual void post_thunder(bool on);
    virtual void crouch(bool on) { _crouch = on; }
    virtual void white_screen(bool on) { _white_screen = on; }
    virtual void stopimpact(bool on) { _stopimpact = on; }
    virtual void up_steps(bool on) { _up_steps = on; }
    virtual void ladder_run(bool on) { _ladder_run = on; }
    virtual void bouncing(bool on) { _bouncing = on; }
    virtual void initialcrouch(bool on = true) { _initialcrouch = on; }
    virtual void can_crouch(bool on) { if (on) _can_crouch++; }
    virtual void scripted(bool on) { _scripted = on; }
    virtual void jump_ramp(bool on);
    virtual void blackFire(bool on);

    virtual void advance() override;
    virtual bool animate() override;
    virtual bool hit(Object* what, Direction fromDir) override;
    virtual std::string name() override { return "Wario"; }
    QPainterPath shape() const override;

    // azioni
    virtual void move(Direction dir) override;
    virtual void jump(bool on = true) override;
    virtual void invincible(bool on);
    virtual void sliding(bool on = true);
    virtual void entrable(bool on = true);
    virtual void check_sleep();
    virtual void check_run();
    virtual void check_roll();
    virtual void check_bounce();
    virtual void check_fire();
    virtual void check_worm();
    virtual void check_script();
    virtual void add_key();


    // cambiamenti di stato
    virtual void bumped(bool on) { _bumped = on; _animation_counter = 0; }
    virtual void powerdown(Direction fromDir, double xy = 1.566); 
    virtual void sleep(bool on);
    virtual void run(bool on);
    virtual void rool(bool on);
    virtual void pre_rool(bool on);
    virtual void scripted_ladder(bool on);
    virtual void pre_fire(bool on);
    virtual void fire(bool on);
    virtual void worm(bool on);
    virtual void pre_worm(bool on);
    virtual void stage1();
    virtual void stage2();
    virtual void stage3();
    virtual void stage4();
};
