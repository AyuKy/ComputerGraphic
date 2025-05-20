#pragma once
#include "glIncludes.h"
#include<iostream>
#include<vector>




class CCGRenderContext
{
	public:

	CCGRenderContext();
	//绘制函数
	//第一次
	void CCGRenderContext::gl_points(int n,int *a);
	void CCGRenderContext::gl_lines(int xStart, int yStart, int xEnd, int yEnd);
	void CCGRenderContext::gl_line_strip(int n,int a[]);
	void CCGRenderContext::gl_line_loop(int n, int a[]);
	void CCGRenderContext::gl_triangles(int a[6]);
	void CCGRenderContext::gl_triangle_strip(int n,int a[]);
	void CCGRenderContext::gl_triangle_fan(int n, int a[]);
	void CCGRenderContext::gl_quads(int n, int a[]);
	void CCGRenderContext::gl_quad_strip(int n, int a[]);
	void CCGRenderContext::gl_polygon(int n, int a[]);
	void CCGRenderContext::pentagram();
	void CCGRenderContext::pentagram2();
	//-----------------
	//第二次
	//-----------------
	void CCGRenderContext::Test2_1(std::vector<std::pair<int, int>> points,glm::vec3 color);
	void CCGRenderContext::Test2_2();
	//-----------------
	//第三次
	virtual ~CCGRenderContext();
};