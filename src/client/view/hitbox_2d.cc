#include "client/view/hitbox_2d.h"

bool Hitbox2D::mouseOver(float x, float y)
{
	return (x >= left) && (x <= right) && (y <= top) && (y >= bot);
}
