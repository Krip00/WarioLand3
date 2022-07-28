#pragma once
#include <QPixmap>

namespace WL3 {	class Sprites; }

class WL3::Sprites
{
    private:
        // sprites
        QPixmap hud;
        QPixmap hud_transparent;
        QPixmap enemies;
        QPixmap wario;
        QPixmap stage_tiles;
        QPixmap stage_tiles_transparent;
        QPixmap title_screen;
        QPixmap spearhead;
        QPixmap frog;
        QPixmap spider;
        QPixmap worm;
        QPixmap torch;

        Sprites();
    public:
        // singleton
        static Sprites* instance();

        QPixmap get(const std::string & id); // prende la sprite dato il suo ID
        void getWario(const std::string& state, QPixmap textures[12]); // stato di wario <-> sprite specifica
        QPixmap number(int n, int fill = 0); // numeri composti da sprite di caratteri
        QPixmap string(std::string text, int fill = 0); // stringhe composte da singoli caratteri
        static QPixmap loadTexture(const std::string& file, QColor mask_color = Qt::magenta);
};
