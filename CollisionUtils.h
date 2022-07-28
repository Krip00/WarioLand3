#pragma once
#include "Vec2D.h"
#include "Direction.h"
#include <QRectF>

namespace WL3
{
	struct RectF
	{
		Vec2Df pos;
		Vec2Df size;
	};

    bool RayVsRect(const Vec2Df& ray_origin, const Vec2Df& ray_dir,	const RectF* target, Vec2Df& contact_point,
        Vec2Df& contact_normal,	double& t_hit_near)
	{
		contact_normal = { 0,0 };
		contact_point = { 0,0 };

        // divisione delle cache
        // ray_dir.x (velocity.x) = 0 ==> +infinito, il che va bene <==> non ci sono intersezioni sull'asse x.
        // Lo stesso si applica alla y
		Vec2Df invdir = 1.0 / ray_dir;

        // calcola le intersezioni tra i rettangoli
		Vec2Df t_near = (target->pos - ray_origin) * invdir;
		Vec2Df t_far = (target->pos + target->size - ray_origin) * invdir;

        // le righe sopra possono produrre 0 * infinito = NaN, che NON va bene
        // <=> uno dei lati di destinazione tocca la direzione del raggio
        // <=> la collisione NON sta avvenendo
		if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
		if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

        // scambia le distanze se necessario
		if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
		if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

        // reiezione prima collisione
		if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

        // Il tempo di contatto sarà il secondo punto t_near lungo il raggio
		t_hit_near = std::max(t_near.x, t_near.y);

        // il tempo di contatto di uscita è il primo punto t_far lungo il raggio
		double t_hit_far = std::min(t_far.x, t_far.y);

        // rifiuta se la direzione del raggio punta lontano dall'oggetto
		if (t_hit_far < 0)
			return false;

        // punto di contatto di collisione dall'equazione della retta parametrica
		contact_point = ray_origin + t_hit_near * ray_dir;

        // contatto normale
		if (t_near.x > t_near.y)
			if (invdir.x < 0)
				contact_normal = { 1,  0 };
			else
				contact_normal = { -1,  0 };
		else
			if (invdir.y < 0)
				contact_normal = { 0,  1 };
			else
				contact_normal = { 0, -1 };

        // Nota se t_near == t_far, la collisione è in diagonale
        // consideriamo questo caso nel ramo "else" che è
        // equivalente a supporre che le collisioni diagonali
        // vengono risolte lungo l'asse verticale
		return true;
	}

    bool DynamicRectVsRect(RectF source, Vec2Df source_vel, RectF target, Vec2Df& contact_point, Vec2Df& contact_normal,
		double& contact_time)
	{
        // espandi il rettangolo di destinazione in base alle dimensioni di origine
		RectF expanded_target;
		expanded_target.pos = target.pos - source.size / 2;
		expanded_target.size = target.size + source.size;

        // esegue l'intersezione tra raggio e retto
		if (RayVsRect(source.pos + source.size / 2, source_vel, &expanded_target, contact_point, contact_normal, contact_time))
			return (contact_time >= -0.0001 && contact_time <= 1.0);
		else
			return false;
	}
}
