#include "DebugBoxObject.h"

void DebugBoxObject::Update()
{

}

void DebugBoxObject::Draw()
{
	DrawCube3D(position, VGet(position.x + 20, position.y + 20, position.z + 20), color, color, true);
}

