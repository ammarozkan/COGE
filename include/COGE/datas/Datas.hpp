//  COGE DATA STYLE:
/*

COGE can handle the datas from only one data file. Data style shall be:
[DATAHEADER]=[GENERIC_TYPE][GENERIC_DATA_COUNT]
[DATA1_TYPE(ENUM)][DATA1_NAME_SIZE(UNSIGNED LONG)][DATA1_NAME][DATA1_SIZE(UNSIGNED LONG)][DATA1]
[DATA2_TYPE(ENUM)][DATA2_NAME_SIZE(UNSIGNED LONG)][DATA2_NAME][DATA2_SIZE(UNSIGNED LONG)][DATA2]
...


COGE_MODEL
	COGE handles model datas in a byte order. The first 4 bytes of data tells
the size of vertices to the reader. And after the vertices, another 4 bytes
will came out. These 4 bytes shall tell size of the indices to the reader.
So order is always important. Reader shall be capable of handling that.

	For more standart model initializion, define of a vertex buffer
will be: [aPos]vec3(3*float) + [TexCoord]vec2(2*float) + [BoneBind]vec1(1*float)


COGE_SHADER
	COGE handles shader datas as only bunch of texts. Just seperating 
vertex and fragment by #GLSL_Fragment and #GLSL_Vertex lines.

COGE_PROP
	Defines props for COGE_MAPPROP with constant position and scale values. If mass is zero, 
prop will be a constant prop. Cannot move. (Maybe if its lower than zero, only visual apperence?)
	[PROP_NAME_SIZE(unsigned int)][PROP_NAME(char*)][MODEL_NAME_SIZE(unsigned int)][MODEL_NAME(char*)]
		[MASS(unsigned? float)]
		[position_x(float)][position_y(float)][position_z(float)]
		[scale_x(float)][scale_y(float)][scale_z(float)]
		[collider_pos_0_x(float)][collider_pos_0_y(float)][collider_pos_0_z(float)]
		[collider_pos_1_x(float)][collider_pos_1_y(float)][collider_pos_1_z(float)] ???

COGE_MAPPROP
	Just puts props to a position and rotation.

	[PROP_NAME_SIZE(unsigned int)][PROP_NAME(char*)]
		[MATERIAL_NAME_SIZE(unsigned int)][MATERIAL_NAME(char*)]
		[position_x(float)][position_y(float)][position_z(float)]
		[rotation_x(float)][rotation_y(float)][rotation_z(float)]

COGE_VISUAL
	This will be a clasic visual effect for the game. Shader data maybe?

//TODO
COGE_EVENT
	Position. Idle animation.
	Character near animation.
	Character near near animation.
	Character interact(nip to nip close) animation.
	Character near reject animation.
	Character near near reject animation.

	Interaction animation need to provide a camera animation. Maybe switch on controller.

COGE_BONE_ANIMATION
	COGE scans COGE_BONE_ANIMATION and creates an animation for bones.
And creates matrixes for bones. Then uses shaders to move bone binded
vertexes.
*/

#ifndef COGE_DATAS_HPP
#define COGE_DATAS_HPP

typedef long int _FILESIZE;

namespace COGE
{
	enum DATA_TYPE
	{
		COGE_DEFAULT = 0, COGE_MODEL, COGE_SHADER, COGE_TEXTURE, COGE_PROP, COGE_MAPPROP, COGE_EVENT, COGE_ANIMATION
	};
}

#include <COGE/datas/DataLoader.hpp>

#ifdef COGE_EDITOR
#include <COGE/datas/DataPacker.hpp>
#endif

#endif