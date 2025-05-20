#include "pch.h"
#include "CGRenderContext.h"
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include <utility>
#include <algorithm>

const GLfloat Pi = 3.1415926536f;
CCGRenderContext::CCGRenderContext()
{
}
//-------------------------------------------------------------------
 void CCGRenderContext::gl_points(int n,int *points)
{
	//以下是绘制代码示例：用于其他算法参考，可根据自己的涉及进行修改 
	glColor3f(1.0f, 0.0f, 0.0f);
	//
	glBegin(GL_POINTS);
	for (int i = 0; i < n; i += 2) {
		glVertex2d(points[i], points[i + 1]); //在(x,y)处，以颜色color绘像素 
	}
	glEnd();
	glFinish();
}


void CCGRenderContext::gl_lines(int xStart, int yStart, int xEnd, int yEnd) {
	glm::vec3 color(1.0f, 0.0f, 0.0f);
	glColor3f(color.r, color.g, color.b);
	//
	glBegin(GL_LINES);
	glVertex2d(xStart, yStart); //在(x,y)处，以颜色color绘像素 
	glVertex2d(xEnd, yEnd);
	glEnd();
	glFinish();
}


void CCGRenderContext::gl_line_strip(int n, int a[]) {
	glm::vec3 color(1.0f, 0.0f, 0.0f);
	glColor3f(color.r, color.g, color.b);
	//
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < n; i += 2) {
		glVertex2d(a[i], a[i + 1]); //在(x,y)处，以颜色color绘像素 
	}
	glEnd();
	glFinish();
}


void CCGRenderContext::gl_line_loop(int n, int a[]) {
	glm::vec3 color(1.0f, 0.0f, 0.0f);
	glColor3f(color.r, color.g, color.b);
	//
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i += 2) {
		glVertex2d(a[i], a[i + 1]); //在(x,y)处，以颜色color绘像素 
	}
	glEnd();
	glFinish();
}


void CCGRenderContext::gl_triangles(int a[6]) {
	glm::vec3 color(1.0f, 0.0f, 0.0f);
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_TRIANGLES);
	glVertex2d(a[0], a[1]); //在(x,y)处，以颜色color绘像素 
	glVertex2d(a[2], a[3]);
	glVertex2d(a[4], a[5]);
	glEnd();
	glFinish();
}


void CCGRenderContext::gl_triangle_strip(int n, int a[]) {
	glColor3f(1.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < n; i += 2) {
		glVertex2d(a[i], a[i + 1]); //在(x,y)处，以颜色color绘像素 
	}
	glEnd();

	glColor3f(0.0f, 1.0f, 0.5f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < n; i += 2) {
		glVertex2d(a[i], a[i + 1]); //在(x,y)处，以颜色color绘像素 
	}
	glEnd();
	glFinish();
}

void CCGRenderContext::gl_triangle_fan(int n, int a[]) {
	glColor3f(1.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < n; i += 2) {
		glVertex2d(a[i], a[i + 1]); //在(x,y)处，以颜色color绘像素 
	}
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < n; i += 2) {
		glVertex2d(a[i], a[i + 1]); //在(x,y)处，以颜色color绘像素 
	}
	glEnd();
	glFinish();
}


void CCGRenderContext::gl_quads(int n, int a[]) {
	glm::vec3 color(1.0f, 0.0f, 0.0f);
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_QUADS);
	for (int i = 0; i < n; i += 2) {
		glVertex2d(a[i], a[i + 1]); //在(x,y)处，以颜色color绘像素 
	}
	glEnd();
	glFinish();
}


void CCGRenderContext::gl_quad_strip(int n, int a[]) {
	glColor3f(1.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < n; i += 2) {
		glVertex2d(a[i], a[i + 1]); //在(x,y)处，以颜色color绘像素 
	}
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < n; i += 2) {
		glVertex2d(a[i], a[i + 1]); //在(x,y)处，以颜色color绘像素 
	}
	glEnd();
	glFinish();
}


void CCGRenderContext::gl_polygon(int n, int a[]) {
	glm::vec3 color(1.0f, 0.0f, 0.0f);
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i += 2) {
		glVertex2d(a[i], a[i + 1]); //在(x,y)处，以颜色color绘像素 
	}
	glEnd();
	glFinish();
}

void CCGRenderContext::pentagram()
{
	//外顶点计算
	GLfloat a = 1 / (2 - 2 * cos(72 * Pi / 180));
	GLfloat bx = a * cos(18 * Pi / 180);
	GLfloat by = a * sin(18 * Pi / 180);
	GLfloat cy = -a * cos(18 * Pi / 180);
	GLfloat
		PointA[2] = { 0 * 100 + 400, a * 100 + 400 },
		PointB[2] = { bx * 100 + 400, by * 100 + 400 },
		PointC[2] = { 0.5 * 100 + 400, cy * 100 + 400 },
		PointD[2] = { -0.5 * 100 + 400, cy * 100 + 400 },
		PointE[2] = { -bx * 100 + 400, by * 100 + 400 };

	// 计算内顶点坐标（凹点）
	GLfloat innerRadius = a * sin(18 * Pi / 180) / sin(126 * Pi / 180);
	// 内顶点坐标数组
	GLfloat innerPoints[5][2];

	// 计算五个内顶点坐标
	for (int i = 0; i < 5; i++) {
		float angle = (54 - i * 72) * Pi / 180;
		innerPoints[i][0] = innerRadius * cos(angle) * 100 + 400;
		innerPoints[i][1] = innerRadius * sin(angle) * 100 + 400;
	}


	GLfloat PointAB[2] = { innerPoints[0][0], innerPoints[0][1] };
	GLfloat PointBC[2] = { innerPoints[1][0], innerPoints[1][1] };
	GLfloat PointCD[2] = { innerPoints[2][0], innerPoints[2][1] };
	GLfloat PointDE[2] = { innerPoints[3][0], innerPoints[3][1] };
	GLfloat PointEA[2] = { innerPoints[4][0], innerPoints[4][1] };


	glBegin(GL_TRIANGLES);
	// 第一个角区域
	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex2f(400, 400);      // 中心点
	glVertex2fv(PointA);   // 外顶点A
	glVertex2fv(PointAB);  // 内顶点AB

	glColor3f(1.0f, 1.0f, 0.5f);
	glVertex2f(400, 400); 
	glVertex2fv(PointAB); 
	glVertex2fv(PointB);  

	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex2f(400, 400);
	glVertex2fv(PointB); 
	glVertex2fv(PointBC);


	glColor3f(1.0f, 1.0f, 0.5f);
	glVertex2f(400, 400); 
	glVertex2fv(PointBC); 
	glVertex2fv(PointC);  

	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex2f(400, 400); 
	glVertex2fv(PointC);  
	glVertex2fv(PointCD); 

	glColor3f(1.0f, 1.0f, 0.5f);
	glVertex2f(400, 400); 
	glVertex2fv(PointCD); 
	glVertex2fv(PointD);  

	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex2f(400, 400); 
	glVertex2fv(PointD);  
	glVertex2fv(PointDE); 

	glColor3f(1.0f, 1.0f, 0.5f);
	glVertex2f(400, 400);
	glVertex2fv(PointDE);
	glVertex2fv(PointE); 

	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex2f(400, 400);
	glVertex2fv(PointE); 
	glVertex2fv(PointEA);

	glColor3f(1.0f, 1.0f, 0.5f);
	glVertex2f(400, 400);
	glVertex2fv(PointEA);
	glVertex2fv(PointA); 
	glEnd();
	glFinish();
}

void CCGRenderContext::pentagram2()
{
	//外顶点计算
	GLfloat a = 1 / (2 - 2 * cos(72 * Pi / 180));
	GLfloat bx = a * cos(18 * Pi / 180);
	GLfloat by = a * sin(18 * Pi / 180);
	GLfloat cy = -a * cos(18 * Pi / 180);
	GLfloat
		PointA[2] = { 0 * 100 + 700, a * 100 + 400 },
		PointB[2] = { bx * 100 + 700, by * 100 + 400 },
		PointC[2] = { 0.5 * 100 + 700, cy * 100 + 400 },
		PointD[2] = { -0.5 * 100 + 700, cy * 100 + 400 },
		PointE[2] = { -bx * 100 + 700, by * 100 + 400 };

	// 计算内顶点坐标（凹点）
	GLfloat innerRadius = a * sin(18 * Pi / 180) / sin(126 * Pi / 180);
	// 内顶点坐标数组
	GLfloat innerPoints[5][2];

	// 计算五个内顶点坐标
	for (int i = 0; i < 5; i++) {
		float angle = (54 - i * 72) * Pi / 180;
		innerPoints[i][0] = innerRadius * cos(angle) * 100 + 700;
		innerPoints[i][1] = innerRadius * sin(angle) * 100 + 400;
	}


	GLfloat PointAB[2] = { innerPoints[0][0], innerPoints[0][1] };
	GLfloat PointBC[2] = { innerPoints[1][0], innerPoints[1][1] };
	GLfloat PointCD[2] = { innerPoints[2][0], innerPoints[2][1] };
	GLfloat PointDE[2] = { innerPoints[3][0], innerPoints[3][1] };
	GLfloat PointEA[2] = { innerPoints[4][0], innerPoints[4][1] };



	glBegin(GL_TRIANGLES);
	// 第一个角区域
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(700, 400);      // 中心点
	glVertex2fv(PointA);   // 外顶点A
	glVertex2fv(PointAB);  // 内顶点AB

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(700, 400); 
	glVertex2fv(PointAB); 
	glVertex2fv(PointB);  

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(700, 400); 
	glVertex2fv(PointB);  
	glVertex2fv(PointBC); 


	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(700, 400); 
	glVertex2fv(PointBC); 
	glVertex2fv(PointC);  

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(700, 400);
	glVertex2fv(PointC); 
	glVertex2fv(PointCD);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(700, 400);
	glVertex2fv(PointCD);
	glVertex2fv(PointD); 

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(700, 400); 
	glVertex2fv(PointD);  
	glVertex2fv(PointDE); 

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(700, 400);
	glVertex2fv(PointDE);
	glVertex2fv(PointE); 

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(700, 400); 
	glVertex2fv(PointE);  
	glVertex2fv(PointEA); 

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(700, 400);
	glVertex2fv(PointEA);
	glVertex2fv(PointA); 
	glEnd();
	glFinish();
}
//---------------------------------------------------------------------
//实验1测试函数
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// --------------------------------------------------------------------



// 绘制DDA线段算法
void DDALine(std::vector<std::pair<int, int>>& points, glm::vec3 color)
{
	if (points.size() < 2) return;

	glColor3f(color.r,color.g,color.b);
	glBegin(GL_POINTS);

	for (int i = 0; i < points.size(); i++) {
		int xStart = points[i].first;
		int yStart = points[i].second;
		// 使用模运算连接最后一个点和第一个点
		int xEnd = points[(i + 1) % points.size()].first; 
		int yEnd = points[(i + 1) % points.size()].second;

		//确定步数
		int steps;
		int dx = xEnd - xStart;
		int dy = yEnd - yStart;
		if (abs(dx) >= abs(dy))
			steps = abs(dx);
		else
			steps = abs(dy);
		if (steps == 0)
			continue;
		float x = (float)xStart, 
			y = (float)yStart, 
			xincre = (float)dx / steps, 
			yincre = (float)dy / steps;

		for (int j = 0; j <= steps; j++) {
			glVertex2d((int)(x + 0.5), (int)(y + 0.5)); //在(x,y)处，以颜色color绘像素 
			x = x + xincre;
			y = y + yincre;
		}
	}

	glEnd();
	glFinish();
}

// 绘制中点线段算法
void MIDLine(std::vector<std::pair<int, int>>& points,glm::vec3 color)
{
	if (points.size() < 2) return;


	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);

	for (int i = 0; i < points.size(); i++) {
		int xStart = points[i].first;
		int yStart = points[i].second;
		// 使用模运算连接最后一个点和第一个点
		int xEnd = points[(i + 1) % points.size()].first;
		int yEnd = points[(i + 1) % points.size()].second;
		if (xStart > xEnd)               /* 保证xStart<xEnd,即xStart为xEnd左边的点。*/
		{
			int xtemp, ytemp;
			xtemp = xStart;
			xStart = xEnd;
			xEnd = xtemp;
			ytemp = yStart;
			yStart = yEnd;
			yEnd = ytemp;
		}

		int dx = xEnd - xStart, dy = yEnd - yStart;

		if (dx == 0) {
			// 竖直线段
			if (yStart < yEnd) {
				for (int y = yStart; y <= yEnd; y++)glVertex2d(xStart, y);
			}
			else {
				for (int y = yEnd; y <= yStart; y++)glVertex2d(xStart, y);
			}
		}
		else if (dy == 0) {
			// 水平线段
			if (xStart < xEnd) {
				for (int x = xStart; x <= xEnd; x++)glVertex2d(x, yStart);
			}
			else {
				for (int x = xEnd; x <= xStart; x++)glVertex2d(x, yStart);
			}
		}
		 if ((dx >= dy) && (dy > 0))//0<k<=1
		{

			int a = yStart - yEnd;
			int b = xEnd - xStart;
			int d = 2 * a + b;
			int delta1 = 2 * a;
			int delta2 = 2 * (a + b);
			int x = xStart, y = yStart;
			//在对应的x,y像素点着色
			glVertex2d(x, y);
			while (x < xEnd)
			{
				if (d < 0)
				{
					x++; y++;
					d += delta2;
				}
				else
				{
					x++; d += delta1;
				}
				//在对应的x,y像素点着色
				glVertex2d(x, y);
			}
		}
		else if ((dy > dx) && (dx > 0))//k>1
		{
			int a = yStart - yEnd,
				b = xEnd - xStart,
				d = a + 2 * b,
				delta1 = 2 * (a + b),
				delta2 = 2 * b,
				x = xStart, y = yStart;
			//在对应的x,y像素点着色
			glVertex2d(x, y);
			while (y < yEnd)
			{
				if (d < 0)
				{
					y++;
					d += delta2;
				}
				else
				{
					y++; x++;
					d += delta1;
				}
				//在对应的x,y像素点着色
				glVertex2d(x, y);
			}
		}
		else if ((dx >= abs(dy)) && (dy < 0))//-1<=k<0 
		{
			int a = yStart - yEnd,
				b = xEnd - xStart,
				d = 2 * a - b,
				delta1 = 2 * a - 2 * b,
				delta2 = 2 * a,
				x = xStart,
				y = yStart;
			//在对应的x,y像素点着色
			glVertex2d(x, y);
			while (x < xEnd)
			{
				if (d < 0)
				{
					x++;
					d += delta2;
				}
				else
				{
					x++;
					y--;
					d += delta1;
				}
				//在对应的x,y像素点着色
				glVertex2d(x, y);

			}
		}
		else if ((abs(dy) > dx) && (dx>0&&dy < 0))//k<-1
		{
			int a = yStart - yEnd,
				b = xEnd - xStart,
				d = a - 2 * b,
				delta1 = -2 * b,
				delta2 = 2 * (a - b),
				x = xStart,
				y = yStart;
			//在对应的x,y像素点着色
			glVertex2d(x, y);
			while (y > yEnd)
			{
				if (d < 0)
				{
					x++;
					y--;
					d += delta2;
				}
				else
				{
					y--;
					d += delta1;
				}
				//在对应的x,y像素点着色
				glVertex2d(x, y);
			}
		}
	}
	glEnd();
}


//绘制Bresenham线段算法
void BreSenhamLine(std::vector<std::pair<int, int>>& points,glm::vec3 color) {
	if (points.size() < 2) return;

	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	for (int i = 0; i < points.size(); i++) {

		int xStart = points[i].first;
		int yStart = points[i].second;
		// 使用模运算连接最后一个点和第一个点
		int xEnd = points[(i + 1) % points.size()].first;
		int yEnd = points[(i + 1) % points.size()].second;

		int dx = abs(xEnd - xStart);
		int dy = abs(yEnd - yStart);
		//斜率为负的情况改变步进方向
		int sx = (xStart < xEnd) ? 1 : -1;  // x方向步进
		int sy = (yStart < yEnd) ? 1 : -1;  // y方向步进

		if (dx > dy) {
			// 斜率在 [0, 1) 范围内
			int d = 2 * dy - dx;
			int delta1 = 2 * dy;
			int delta2 = 2 * (dy - dx);
			int x = xStart, y = yStart;
			while (x != xEnd) {
				glVertex2d(x, y);
				x += sx;
				if (d < 0) {
					d += delta1;
				}
				else {
					y += sy;
					d += delta2;
				}
			}
		}
		else {
			// 斜率在 [1, ∞) 范围内
			int d = 2 * dx - dy;
			int delta1 = 2 * dx;
			int delta2 = 2 * (dx - dy);
			int x = xStart, y = yStart;
			while (y != yEnd) {
				glVertex2d(x, y);
				y += sy;
				if (d < 0) {
					d += delta1;
				}
				else {
					x += sx;
					d += delta2;
				}
			}
		}
	}

	glEnd();
	glFinish();
}


//绘制中点圆算法
void MidPointCircle(int centerX, int centerY, int radius, glm::vec3 color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);

	int x = 0;
	int y = radius;
	int d = 1 - radius;

	auto drawCirclePoints = [&](int cx, int cy, int x, int y) {
		glVertex2d(cx + x, cy + y);
		glVertex2d(cx - x, cy + y);
		glVertex2d(cx + x, cy - y);
		glVertex2d(cx - x, cy - y);
		glVertex2d(cx + y, cy + x);
		glVertex2d(cx - y, cy + x);
		glVertex2d(cx + y, cy - x);
		glVertex2d(cx - y, cy - x);
		};
	drawCirclePoints(centerX, centerY, x, y);
	while (x < y) {
		
		if (d < 0) {
			d += 2 * x + 3;
		}
		else {
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		drawCirclePoints(centerX, centerY, x, y);
	}

	glEnd();
	glFinish();

}

//绘制Bresenham圆算法
void BresenhamCircle(int centerX, int centerY, int radius,glm::vec3 color) {
	glColor3f(color.r,color.g,color.b);
	glBegin(GL_POINTS);

	int x = 0;
	int y = radius;
	int d = 2 * (1 - radius);

	auto drawCirclePoints = [&](int cx, int cy, int x, int y) {
		glVertex2d(cx + x, cy + y);
		glVertex2d(cx - x, cy + y);
		glVertex2d(cx + x, cy - y);
		glVertex2d(cx - x, cy - y);
		glVertex2d(cx + y, cy + x);
		glVertex2d(cx - y, cy + x);
		glVertex2d(cx + y, cy - x);
		glVertex2d(cx - y, cy - x);
		};

	while (x <= y) {
		drawCirclePoints(centerX, centerY, x, y);
		if (d < 0) {
			if (2 * (d + y) - 1 <= 0) {
				d += 2 * x + 3;
			}
			else {
				d += 2 * (x - y + 3);
				y--;
			}
		}
		else if (d == 0) {
			d += 2 * (x - y + 3);
			y--;
		}
		else {
			if (2 * (d - x) - 1 <= 0) {
				d += 2 * (x - y + 3);
				y--;
			}
			else {
				d -= 2 * y - 3;
				y--;
			}
		}
		x++;
	}

	glEnd();
	glFinish();
}




void checkPoint(int px, int py, int dx, int dy, float cos1, float sin1, float cos2, float sin2, bool t1t2) {
	float cross1 = cos1 * dy - sin1 * dx;
	float cross2 = dx * sin2 - dy * cos2;
	bool inArc = t1t2 ? (cross1 >= 0 && cross2 >= 0) : (cross1 >= 0 || cross2 >= 0);
	if (inArc) {
		glBegin(GL_POINTS);
		glVertex2d(px, py);
		glEnd();
	}
}

void drawPoints(int xc, int yc, int x, int y, float cos1, float sin1, float cos2, float sin2, bool t1t2) {
	checkPoint(xc + x, yc + y, x, y, cos1, sin1, cos2, sin2, t1t2);
	checkPoint(xc - x, yc + y, -x, y, cos1, sin1, cos2, sin2, t1t2);
	checkPoint(xc + x, yc - y, x, -y, cos1, sin1, cos2, sin2, t1t2);
	checkPoint(xc - x, yc - y, -x, -y, cos1, sin1, cos2, sin2, t1t2);
	checkPoint(xc + y, yc + x, y, x, cos1, sin1, cos2, sin2, t1t2);
	checkPoint(xc - y, yc + x, -y, x, cos1, sin1, cos2, sin2, t1t2);
	checkPoint(xc + y, yc - x, y, -x, cos1, sin1, cos2, sin2, t1t2);
	checkPoint(xc - y, yc - x, -y, -x, cos1, sin1, cos2, sin2, t1t2);
}

void drawArc(int xc, int yc, int r, float theta1, float theta2,glm::vec3 color) {
	float rad1 = theta1 * Pi / 180.0f;
	float rad2 = theta2 * Pi / 180.0f;
	float cos1 = cos(rad1), sin1 = sin(rad1);
	float cos2 = cos(rad2), sin2 = sin(rad2);
	bool t1t2 = theta1 <= theta2;

	int x = 0, y = r;
	int d = 1 - r;
	while (x <= y) {
		glColor3f(color.r, color.g, color.b);
		drawPoints(xc, yc, x, y, cos1, sin1, cos2, sin2, t1t2);
		if (d < 0) {
			d += 2 * x + 3;
		}
		else {
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}
//---------------------------------------------------------------------
//实验2-1测试函数
//---------------------------------------------------------------------
void CCGRenderContext::Test2_1(std::vector<std::pair<int, int>> points, glm::vec3 color) {

	for (int i = 0; i < points.size(); ++i) {
		for (int j = i + 1; j < points.size(); ++j) {
			//获取点对
			std::pair<int, int> point1 = points[i];
			std::pair<int, int> point2 = points[j];
			
			std::vector<std::pair<int, int>> line = { point1, point2 };
			// 调用 画线算法 绘制线段
			//测试哪个就调用哪个
			DDALine(line,color);
			//MIDLine(line,color);
			//BreSenhamLine(line,color);
		}
	}

	MidPointCircle(150, 100, 50, color);
	MidPointCircle(150, 100, 70, color);
	MidPointCircle(150, 100, 90, color);

	BresenhamCircle(310, 100, 30, color);
	BresenhamCircle(310, 100, 40, color);
	BresenhamCircle(310, 100, 50, color);	
	BresenhamCircle(310, 100, 60, color);
	drawArc(400, 100, 50, 0, 60, color);
	drawArc(550, 100, 50, 90, 200, color);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------



//有效边表扫描线算法
// 边结构体
struct Edge {
	int yMax;       // 边的最大 y 值
	float x;        // 当前 x 值
	float dx;       // 斜率倒数 (1/m)

};

// 构建边表
std::vector<std::vector<Edge>> buildET(std::vector<std::pair<int, int>>& point) {
	std::vector<std::vector<Edge>> ET(1000); //设最大y范围为 1000
	int n = point.size();

	for (int i = 0; i < n; ++i) {
		auto v1 = point[i];
		auto v2 = point[(i + 1) % n];

		if (v1.second == v2.second) continue; // 忽略水平边
		if (v1.second > v2.second) std::swap(v1, v2); // 确保 v1 是下端点

		Edge edge;
		edge.yMax = v2.second;
		edge.x = v1.first;
		edge.dx = (float)(v2.first - v1.first) / (v2.second - v1.second);

		ET[v1.second].push_back(edge);//压入边表
	}

	return ET;
}

// 扫描线填充
void scanlineFill(std::vector<std::pair<int, int>>& point, glm::vec3 color) {
	auto edgeTable = buildET(point);//创建边表
	std::vector<Edge> AET;//活动边表

	for (int y = 0; y < edgeTable.size(); ++y) {
		// 添加新边到活动边表
		for (const auto& edge : edgeTable[y]) {
			AET.push_back(edge);
		}

		// 移除 yMax 等于当前 y 的边
		AET.erase(
			std::remove_if(AET.begin(), AET.end(),
				[y](const Edge& e) { return e.yMax == y; }),
			AET.end());

		// 按 x 坐标排序
		std::sort(AET.begin(), AET.end(),
			[](const Edge& e1, const Edge& e2) { return e1.x < e2.x; });
		
		// 成对填充像素
		for (size_t i = 0; i < AET.size(); i += 2) {
			int xStart = (int)AET[i].x;
			int xEnd = (int)AET[i + 1].x;
			glColor3f(color.r, color.g, color.b);
			glBegin(GL_POINTS);
			for (int x = xStart; x <= xEnd; ++x) {
				glVertex2i(x, y);
			}
			glEnd();
		}

		// 更新 x 坐标
		for (auto& edge : AET) {
			edge.x += edge.dx;
		}
	}
}
//---------------

glm::vec3 getPixelColor(int x, int y) {
	GLfloat pixel[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixel);
	// 提取当前像素的颜色
	glm::vec3 currentColor(pixel[0], pixel[1], pixel[2]);
	return currentColor;
}
void setPixelColor(int x, int y, glm::vec3 color) {
	glPointSize(1.0f); // 设置点的大小
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
bool compareColor(glm::vec3 color1, glm::vec3  color2, float epsilon = 0.01f) {
	return (fabs(color1.r- color2.r) < epsilon) &&
			(fabs(color1.g - color2.g) < epsilon) &&
			(fabs(color1.b - color2.b) < epsilon);
}
//边界表示
void BoundFill4(int x, int y, glm::vec3 bColor, glm::vec3 nColor)
{
	std::queue<std::pair<int, int>> pixels;
	pixels.push({ x, y });

	while (!pixels.empty()) {
		std::pair<int, int> currentPixel = pixels.front();
		pixels.pop();
		int px = currentPixel.first;
		int py = currentPixel.second;

		glm::vec3 currentColor = getPixelColor(px, py);

		if (!compareColor(currentColor, bColor) && !compareColor(currentColor, nColor)) {
			setPixelColor(px, py, nColor);
			pixels.push({ px - 1, py }); // 左
			pixels.push({ px, py+1 }); // 上
			pixels.push({ px+1, py }); // 右
			pixels.push({ px, py - 1 }); // 下
		}
	}
}

//内点表示
void floodfill4(int x, int y, glm::vec3 oldColor, glm::vec3 newColor) {
	std::queue<std::pair<int, int>> pixels;
	pixels.push({ x, y });
	while (!pixels.empty()) {
		std::pair<int, int> currentPixel = pixels.front();
		pixels.pop();
		int px = currentPixel.first;
		int py = currentPixel.second;

		glm::vec3 currentColor = getPixelColor(px, py);
		//if(currentColor==oldColor){
		if (compareColor(currentColor, oldColor)){
			setPixelColor(px, py, newColor);
			pixels.push({ px - 1, py }); // 左
			pixels.push({ px, py+1 }); // 上
			pixels.push({ px+1, py }); // 右
			pixels.push({ px, py - 1 }); // 下
		}
	}
}


//---------------------------------------------------------------------
//实验2-2测试函数
//---------------------------------------------------------------------
void CCGRenderContext::Test2_2() {
	std::vector<std::pair<int, int>> concavePolygon = {
	{100, 100}, {200, 20}, {300, 100}, {250, 200}, {150, 150}
	};

	// 凸多边形顶点数组
	std::vector<std::pair<int, int>> convexPolygon = {
		{400, 100}, {500, 100}, {550, 150}, {500, 200}, {450, 200}, {400, 150}
	};

	// 任意多边形顶点数组
	std::vector<std::pair<int, int>> randomPolygon = {
		{600, 100}, {650, 150}, {700, 120}, {720, 200}, {650, 220}, {620, 180}, {600, 150}
	};
	scanlineFill(concavePolygon, glm::vec3(1.0f, 0.0f, 0.0f));
	scanlineFill(convexPolygon, glm::vec3(1.0f, 0.0f, 0.0f));
	scanlineFill(randomPolygon, glm::vec3(1.0f, 0.0f, 0.0f));
	//----------------------------------------------------
	MidPointCircle(150, 300, 30,glm::vec3(1.0f,0.0f,0.0f));
	floodfill4(150, 300, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	BresenhamCircle(400, 300, 50,glm::vec3(1.0f,0.0f,0.0f));
	BoundFill4(400, 300, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}
//----------
CCGRenderContext::~CCGRenderContext()
{
}