#ifndef cakengine_math_shape_geometry2d_h
#define cakengine_math_shape_geometry2d_h

#include <iostream>
#include <vector>
#include <CakeEngine/math/util.hpp>
#include <CakeEngine/math/vector/Vector2.hpp>


class CKGeometry2D{
	
private:
	
	
public:
	inline static Bool colision_pointToPoint(CKVec2& p1_pos, CKVec2& p2_pos);
	inline static Bool colision_pointToCircle(CKVec2& p_pos, CKVec2& c_pos, Float c_radius);
	inline static Bool colision_pointToRectangle(CKVec2& p_pos, CKVec2& r_pos, CKVec2& r_size);
	inline static Bool colision_pointToLine(CKVec2& p_pos, CKVec2& l_beg, CKVec2& l_end);
	inline static Bool colision_pointToPolygon(CKVec2& p_pos, std::vector<CKVec2>& s_pos);
	
	inline static Bool colision_circleToCircle(CKVec2& c1_pos, Float c1_radius, CKVec2& c2_pos, Float c2_radius);
	inline static Bool colision_circleToRectangle(CKVec2& c_pos, Float c_radius, CKVec2& r_pos, CKVec2& r_size);
	inline static Bool colision_circleToLine(CKVec2& c_pos, Float c_radius, CKVec2& l_beg, CKVec2& l_end);
	inline static Bool colision_circleToPolygon(CKVec2& c_pos, Float c_radius, std::vector<CKVec2>& s_pos);
	
	inline static Bool colision_rectangleToRectangle(CKVec2& r1_pos, CKVec2& r1_size, CKVec2& r2_pos, CKVec2& r2_size);
	inline static Bool colision_rectangleToLine(CKVec2& r_pos, CKVec2& r_size, CKVec2& l_beg, CKVec2& l_end);
	inline static Bool colision_rectangleToPolygon(CKVec2& r_pos, CKVec2& r_size, std::vector<CKVec2>& s_pos);
	
	inline static Bool colision_lineToLine(CKVec2& l1_beg, CKVec2& l1_end, CKVec2& l2_beg, CKVec2& l2_end, Float &col_x, Float &col_y);
	inline static Bool colision_lineToPolygon(CKVec2& l_beg, CKVec2& l_end, std::vector<CKVec2>& s_pos);
	
	inline static Bool colision_polygonToPolygon(std::vector<CKVec2>& s1_pos, std::vector<CKVec2>& s2_pos);
	
	/*
		Function: Retrieves wich side of the line a point is
		Return: <0 is at right; >0 is at left; =0 is colinear
	*/
	inline static Float side_pointToLine(CKVec2& p_pos, CKVec2& l_beg, CKVec2& l_end);
	
	
	/*
		Function: Retrieves if polygon is clockwise or counter-clockwise
		Return: true if is clockwise, false if counter-clockwise
	*/
	inline static Bool direction_polygon(std::vector<CKVec2>& s_pos);
	
};


#endif // cakengine_math_shape_collision2d_h
