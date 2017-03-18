#ifndef __SHAPES_H__
#define __SHAPES_H__

#include <cocos2d.h>


namespace Shapes
{
	class IShapes : public cocos2d::Node
	{
	public:

		IShapes();
		CREATE_FUNC(IShapes);

		virtual ~IShapes();

	protected:

		cocos2d::DrawNode* p_drawNode;
		std::vector<cocos2d::Vec2> m_vertices;
	};

	class Arc : public IShapes
	{
	public:

		CREATE_FUNC(Arc);

	protected:

		virtual bool init();
	};
}




#endif __SHAPES_H__



