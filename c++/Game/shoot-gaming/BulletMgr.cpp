#include "BulletMgr.h"
#include "Macro.h"

using namespace std;

bool BulletMgr::IsCross(Coor a, Coor b, Coor c, Coor d)
{
	/*
	* For the x coordinate,
	* If they do not intersect obviously.
	*/
	if (a.x >= b.x) {
		if ((a.x < c.x && a.x < d.x) || (b.x > c.x && b.x > d.x)) {
			return false;
		}
	}
	else {
		if ((b.x < c.x && b.x < d.x) || (a.x > c.x && a.x > d.x)) {
			return false;
		}
	}

	/*
	* For the y coordinate,
	* If they do not intersect obviously.
	*/
	if (a.y >= b.y) {
		if ((a.y > c.y && a.y > d.y) || (b.y < c.y && b.y < d.y)) {
			return false;
		}
	}
	else {
		if ((b.x > c.x && b.x > d.x) || (a.x < c.x && a.x < d.x)) {
			return false;
		}
	}

	/*
	* Do line AB and line CD intersect?
	*/
	if (((a.x - b.x) * (c.y - a.y) - (a.y - b.y) * (c.x - a.x)) *
		((a.x - b.x) * (d.y - a.y) - (a.y - b.y) * (d.x - a.x)) > 0) {
		return false;
	}
	if (((c.x - d.x) * (a.y - c.y) - (c.y - d.y) * (a.x - c.x)) *
		((c.x - d.x) * (b.y - c.y) - (c.y - d.y) * (b.x - c.x)) > 0) {
		return false;
	}

	return true;
}

BulletMgr::BulletMgr()
{
}

void BulletMgr::init()
{
	_bullets.clear();
	_ebullets.clear();
}

bool BulletMgr::update()
{
	auto it = _bullets.begin();
	auto eit = _ebullets.begin();

	while (it != _bullets.end())
	{
		if (it[0]->update()) {
			it++;
		}
		else {
			it = _bullets.erase(it);
		}
	}

	while(eit != _ebullets.end())
	{
		if (eit[0]->update()) {
			eit++;
		}
		else {
			eit = _ebullets.erase(eit);
		}
	}
	return true;
}

int BulletMgr::CheckTaken(vector<pair<Coor, Coor>> edge, int flag)
{
	int cnt = 0;
	vector<Bullet *>::iterator itr, end;

	if (flag)
	{
		itr = _bullets.begin();
		end = _bullets.end();
	}
	else
	{
		itr = _ebullets.begin();
		end = _ebullets.end();
	}

	while (itr != end)
	{
		bool is_cross = false;
		auto t = itr[0]->getStatus();
		pair<double, double> p = t.coor;
		pair<double, double> _h_w = t._h_w;
		pair<double, double> off = t.offset;

		Coor v1, v2, v3, v4;

		switch (t.b_type)
		{
		/*
		*  b_type : +
		*/
		case eBalletPattern::EnemyBlt:
			v1 = { p.first, p.second + off.second + _h_w.first / 2.0 };
			v2 = { p.first + _h_w.second, p.second + off.second + _h_w.first / 2.0 };
			v3 = { p.first + _h_w.second / 2.0, p.second + off.second };
			v4 = { p.first + _h_w.second / 2.0, p.second + off.second + _h_w.first };

			for (auto e : edge)
			{
				if (IsCross(e.first, e.second, v1, v2) ||
					IsCross(e.first, e.second, v3, v4) ||
					IsCross(v1, v2, e.first, e.second) ||
					IsCross(v3, v4, e.first, e.second))
				{
					is_cross = true;
					break;
				}
			}

			//DrawPixel(p.first, p.second + off.second + _h_w.second / 2.0, GetColor(255, 0, 255));
			//DrawPixel(p.first + _h_w.first, p.second + off.second + _h_w.second / 2.0, GetColor(255, 0, 255));
			//DrawPixel(p.first + _h_w.first / 2.0, p.second + off.second, GetColor(255, 0, 255));
			//DrawPixel(p.first + _h_w.first / 2.0, p.second + off.second + _h_w.second, GetColor(255, 0, 255));

			if (is_cross)
			{
				cnt++;

				if (flag) {
					itr = _bullets.erase(itr);
					end = _bullets.end();

				}
				else {
					itr = _ebullets.erase(itr);
					end = _ebullets.end();
				}
				continue;
			}
			else
			{
				itr++;
				continue;
			}
			break;
		/*
		*  b_type : |
		*/
		case eBalletPattern::PlayerBlt:
			v1 = { p.first + off.first, p.second };
			v2 = { p.first + off.first, p.second + _h_w.first };

			for (auto e : edge)
			{
				if (IsCross(e.first, e.second, v1, v2) ||
					IsCross(v1, v2, e.first, e.second))
				{
					is_cross = true;
					break;
				}
			}

			//DrawPixel(p.first + off.first, p.second, GetColor(255, 0, 255));
			//DrawPixel(p.first + off.first, p.second + _h_w.first, GetColor(255, 0, 255));

			if (is_cross)
			{
				cnt++;

				if (flag) {
					itr = _bullets.erase(itr);
					end = _bullets.end();
				}
				else {
					itr = _ebullets.erase(itr);
					end = _ebullets.end();
				}
				continue;
			}
			else
			{
				itr++;
				continue;
			}
			break;
		default:
			ERR("ë∂ç›ÇµÇ»Ç¢b_typeÇ™ëIëÇ≥ÇÍÇ‹ÇµÇΩÅI");
			break;
		}
	}
	return cnt;
}

void BulletMgr::Shoot(double x, double y, double ang, double sp, eBalletPattern ptn, int flag)
{
	if(!flag) _bullets.push_back(new Bullet(x, y, ang, sp, ptn));
	else _ebullets.push_back(new Bullet(x, y, ang, sp, ptn));
}

void BulletMgr::draw() const
{
}