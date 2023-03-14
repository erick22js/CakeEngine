#include <CakeEngine/math/shape/Geometry2D.hpp>



inline Bool CKGeometry2D::colision_pointToPoint(CKVec2& p1_pos, CKVec2& p2_pos){
	return p1_pos.equal(&p2_pos);
}

inline Bool CKGeometry2D::colision_pointToCircle(CKVec2& p_pos, CKVec2& c_pos, Float c_radius){
	Float dist = p_pos.distance(&c_pos);
	return dist<=c_radius;
}

inline Bool CKGeometry2D::colision_pointToRectangle(CKVec2& p_pos, CKVec2& r_pos, CKVec2& r_size){
	CKVec2 r_edge = r_pos;
	r_edge.add(&r_size);
	Bool chk_x = (p_pos.x>=r_pos.x)&&(p_pos.x<=r_edge.x);
	Bool chk_y = (p_pos.y>=r_pos.y)&&(p_pos.y<=r_edge.y);
	return chk_x&&chk_y;
}

inline Bool CKGeometry2D::colision_pointToLine(CKVec2& p_pos, CKVec2& l_beg, CKVec2& l_end){
	const Float MARGIN = 1;
	Float dist_beg = p_pos.distance(&l_beg);
	Float dist_end = p_pos.distance(&l_end);
	Float size_line = l_beg.distance(&l_end);
	return (dist_beg+dist_end)<=(size_line+MARGIN);
}

inline Bool CKGeometry2D::colision_pointToPolygon(CKVec2& p_pos, std::vector<CKVec2>& s_pos){
	/* TODO */
	return false;
}


inline Bool CKGeometry2D::colision_circleToCircle(CKVec2& c1_pos, Float c1_radius, CKVec2& c2_pos, Float c2_radius){
	Float dist = c1_pos.distance(&c2_pos);
	return dist<=(c1_radius+c2_radius);
}

inline Bool CKGeometry2D::colision_circleToRectangle(CKVec2& c_pos, Float c_radius, CKVec2& r_pos, CKVec2& r_size){
	/* TODO */
	return false;
}

inline Bool CKGeometry2D::colision_circleToLine(CKVec2& c_pos, Float c_radius, CKVec2& l_beg, CKVec2& l_end){
	/* TODO */
	return false;
}

inline Bool CKGeometry2D::colision_circleToPolygon(CKVec2& c_pos, Float c_radius, std::vector<CKVec2>& s_pos){
	/* TODO */
	return false;
}


inline Bool CKGeometry2D::colision_rectangleToRectangle(CKVec2& r1_pos, CKVec2& r1_size, CKVec2& r2_pos, CKVec2& r2_size){
	CKVec2 r1_edge = r1_pos;
	r1_edge.add(&r1_size);
	CKVec2 r2_edge = r2_pos;
	r2_edge.add(&r2_size);
	Float chk_x1 = (r1_pos.x>=r2_pos.x)&&(r1_pos.x<=r2_edge.x);
	Float chk_x2 = (r2_pos.x>=r1_pos.x)&&(r2_pos.x<=r1_edge.x);
	Float chk_y1 = (r1_pos.y>=r2_pos.y)&&(r1_pos.y<=r2_edge.y);
	Float chk_y2 = (r2_pos.y>=r1_pos.y)&&(r2_pos.y<=r1_edge.y);
	return (chk_x1||chk_x2)&&(chk_y1||chk_y2);
}

inline Bool CKGeometry2D::colision_rectangleToLine(CKVec2& r_pos, CKVec2& r_size, CKVec2& l_beg, CKVec2& l_end){
	/* TODO */
	return false;
}

inline Bool CKGeometry2D::colision_rectangleToPolygon(CKVec2& r_pos, CKVec2& r_size, std::vector<CKVec2>& s_pos){
	/* TODO */
	return false;
}


inline Bool CKGeometry2D::colision_lineToLine(CKVec2& l1_beg, CKVec2& l1_end, CKVec2& l2_beg, CKVec2& l2_end, Float &col_x, Float &col_y){
	Float num1 = (l2_end.x-l2_beg.x)*(l1_beg.y-l2_beg.y) - (l2_end.y-l2_beg.y)*(l1_beg.x-l2_beg.x);
	Float num2 = (l1_end.x-l1_beg.x)*(l1_beg.y-l2_beg.y) - (l1_end.y-l1_beg.y)*(l1_beg.x-l2_beg.x);
	Float den = (l2_end.y-l2_beg.y)*(l1_end.x-l1_beg.x) - (l2_end.x-l2_beg.x)*(l1_end.y-l1_beg.y);
	
	if(den==0){
		return (num1==0)&&(num2==0);
	}
	
	Float u1 = num1/den;
	Float u2 = num2/den;
	
	col_x = l1_beg.x + u1*(l1_end.x-l1_beg.x);
	col_y = l1_beg.y + u1*(l1_end.y-l1_beg.y);
	
	return ((u1>=0)&&(u1<=1))&&((u2>=0)&&(u2<=1));
}

inline Bool CKGeometry2D::colision_lineToPolygon(CKVec2& l_beg, CKVec2& l_end, std::vector<CKVec2>& s_pos){
	/* TODO */
	return false;
}


inline Bool CKGeometry2D::colision_polygonToPolygon(std::vector<CKVec2>& s1_pos, std::vector<CKVec2>& s2_pos){
	/* TODO */
	return false;
}



inline Float CKGeometry2D::side_pointToLine(CKVec2& p_pos, CKVec2& l_beg, CKVec2& l_end){
	return (l_end.x-l_beg.x)*(p_pos.y-l_beg.y) - (l_end.y-l_beg.y)*(p_pos.x-l_beg.x);
}


inline Bool direction_polygon(std::vector<CKVec2>& s_pos){
	Float sum = 0;
	Int length = s_pos.size();
	for(Int vi=0; vi<length; vi++){
		CKVec2 v1 = s_pos.at(vi);
		CKVec2 v2;
		if(vi==(length-1)){
			v2 = s_pos.at(0);
		}
		else{
			v2 = s_pos.at(vi+1);
		}
		sum += (v2.x-v1.x)*(v2.y+v1.y);
	}
	return sum>=0;
}

