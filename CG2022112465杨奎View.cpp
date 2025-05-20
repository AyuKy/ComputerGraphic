// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// CG2022112465杨奎View.cpp: CCG2022112465杨奎View 类的实现
//


#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2022112465杨奎.h"
#endif

#include "MainFrm.h"
#include "UIEventHandler.h"

#include "CG2022112465杨奎Doc.h"
#include "CG2022112465杨奎View.h"

#include <utility>
#include<iostream>
#include<vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCG2022112465杨奎View

IMPLEMENT_DYNCREATE(CCG2022112465杨奎View, CView)

BEGIN_MESSAGE_MAP(CCG2022112465杨奎View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CCG2022112465杨奎View 构造/析构

CCG2022112465杨奎View::CCG2022112465杨奎View() noexcept
{
	// TODO: 在此处添加构造代码

}

CCG2022112465杨奎View::~CCG2022112465杨奎View()
{
	if (mTimer) KillTimer(mTimer); //关闭定时器
	if (m_glfwWindow) {
		glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
	}
}

BOOL CCG2022112465杨奎View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCG2022112465杨奎View 绘图

void CCG2022112465杨奎View::OnDraw(CDC* /*pDC*/)
{
	CCG2022112465杨奎Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	RenderScene();//自定义绘制代码调用函数
}

void CCG2022112465杨奎View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCG2022112465杨奎View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCG2022112465杨奎View 诊断

#ifdef _DEBUG
void CCG2022112465杨奎View::AssertValid() const
{
	CView::AssertValid();
}

void CCG2022112465杨奎View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCG2022112465杨奎Doc* CCG2022112465杨奎View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎Doc)));
	return (CCG2022112465杨奎Doc*)m_pDocument;
}
#endif //_DEBUG


// CCG2022112465杨奎View 消息处理程序

void CCG2022112465杨奎View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	if (m_hWndGL) {
		// 调整GLFW子窗口大小与视图客户区匹配
		::SetWindowPos(m_hWndGL, NULL, 0, 0, cx, cy, SWP_NOZORDER);
		glfwMakeContextCurrent(m_glfwWindow);
		glViewport(0, 0, cx, cy);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//基本图形生成算法实验部分，假定观察窗口与视口一致。（左下角为原点，右上角为(cx,cy)）
		//使用正交平行投影
		//glOrtho(0, cx, //x范围
		//	0, cy, //y范围
		//	-10000.0f, 10000.0f); //z范围（深度）

		glOrtho(-cx / 2.0f, cx / 2.0f, //x范围
			-cy / 2.0f, cy / 2.0f, //y范围
			-10000.0f, 10000.0f); //z 范围（深度）
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

void CCG2022112465杨奎View::OnDestroy()
{
	//窗口销毁时的清理操作，释放GLFW窗口资源并执行父类的销毁逻辑
	if (m_glfwWindow) {
		glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
		m_glfwWindow = nullptr;
	}
	CView::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
}

BOOL CCG2022112465杨奎View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return true;
}

int CCG2022112465杨奎View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: 在此添加您专用的创建代码
	if (!InitGLFW())
		return -1;//返回异常，程序结束
	return 0;
}



bool CCG2022112465杨奎View::InitGLFW()
{
	if (!glfwInit()) {
			AfxMessageBox(_T("GLFW初始化失败"));
		return false;
	}
	// 设置GLFW窗口无边框、透明（避免覆盖MFC控件）
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	// 设置OpenGL版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //如果使用OpenGL核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); //如果使用OpenGL兼容模式
	// 创建隐藏的GLFW窗口
	m_glfwWindow = glfwCreateWindow(100, 100, "", NULL, NULL);
	if (!m_glfwWindow) {
		AfxMessageBox(_T("Failed to glfwCreateWindow"));
		glfwTerminate();
		return false;
	}
	// 获取GLFW窗口的HWND并设置为MFC视图的子窗口
	m_hWndGL = glfwGetWin32Window(m_glfwWindow);
	SetWindowLong(m_hWndGL, GWL_STYLE, WS_VISIBLE);
	::SetParent(m_hWndGL, GetSafeHwnd());
	::ShowWindow(m_hWndGL, SW_SHOW);
	// 初始化OpenGL上下文
	glfwMakeContextCurrent(m_glfwWindow);
#if defined(_USE_GLEW)
	glewInit();
#else
	//使用GLAD来加载OpenGL的函数地址
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			AfxMessageBox(_T("Failed to initialize GLAD"));
			return false;
		}
#endif
	// 设置视口
	CRect rect;
	GetClientRect(&rect);
	glViewport(0, 0, rect.Width(), rect.Height());
	m_bGLInitialized = true;


	//设置回调函数用到的指针（this-当前view）
	glfwSetWindowUserPointer(m_glfwWindow, this); //this也是CCGRenderContext*类型
	//设置键盘输入回调
	glfwSetKeyCallback(m_glfwWindow, UIEventHandler::KeyCallback);
	//设置鼠标按键回调
	glfwSetMouseButtonCallback(m_glfwWindow, UIEventHandler::MouseButtonCallback);
	//设置光标移动回调
	glfwSetCursorPosCallback(m_glfwWindow, UIEventHandler::CursorPosCallback);
	//设置鼠标滚轮回调
	glfwSetScrollCallback(m_glfwWindow, UIEventHandler::ScrollCallback);


	return true;
}

void CCG2022112465杨奎View::RenderScene()
{
	if (!m_bGLInitialized)
		return;
	//启用渲染环境
	glfwMakeContextCurrent(m_glfwWindow);
	//此处添加自定义OpenGL渲染代码...
	//清除颜色缓冲区和深度缓冲区
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//---------------------------------------------------------
	// 以下是作业部分
	//---------------------------------------------------------
	//1.
	//int points[] = { 10,30,20,20,40,20,50,30,60,40 };
	//gl_points(2*5,points);
	////2.
	//gl_lines(70, 40, 120, 60);
	//gl_lines(120, 56, 180, 36);
	//gl_lines(70, 10, 140, 30);
	//gl_lines(80, 30, 130, 22);
	////3.
	//int n3 = 5;
	//int a[] = {180, 45, 240, 10, 230, 40, 190, 30, 185, 15};
	//gl_line_strip(2*n3,a);
	////4.
	//int n4 = 6;
	//int b[] = {260,30,270,5,310,5,300,28,285,10,272,40 };
	//gl_line_loop(2*n4, b);
	////5.
	//int A[6] = { 330,10,340,10,330,20 };
	//int B[6] = { 335,30,350,30,350,15 };
	//gl_triangles(A);
	//gl_triangles(B);
	////6.
	//int n6 = 6;
	//int triangles1[] = { 370,40,370,20,390,40,400,20,408,40,410,14 };
	//gl_triangle_strip(2*n6,triangles1);
	////7.
	//int n7 = 5;
	//int triangles2[] = { 420,20,420,60,450,56,456,22,452,4};
	//gl_triangle_fan(2 * n7, triangles2);
	////8.
	//int n8 = 8;
	//int quads1[] = { 20,100,30,116,60,120,60,98,80,90,82,116,120,140,100,90};
	//gl_quads(2 * n8, quads1);
	//// 
	////9.
	//int n9 = 8;
	//int quads2[] = { 150,100,148,120,170,100,170,122,190,110,182,126,196,112,186,130};
	//gl_quad_strip(2 * n9, quads2);
	////10.
	//int n10 = 5;
	//int polygon[] = {250,150,300,160,295,125,240,100,235,125 };
	//gl_polygon(2 * n10, polygon);
	//// 11.
	//pentagram();
	//// 12.
	//pentagram2();
	//---------------------------------------------------------
	 //创建一组测试坐标
	//std::vector<std::pair<int, int>> points1 = {
	//{ 400, 300 }, { 375, 350 }, { 325, 375 }, { 275, 375 },
	//{ 225, 350 }, { 200, 300 }, { 200, 250 }, { 225, 200 },
	//{ 275, 175 }, { 325, 175 }, { 375, 200 }, { 400, 250 }
	//};
	//Test2_1(points1,glm::vec3(1.0,1.0,1.0));
	//
	//Test2_2();
	//---------------------------------------------------------
	// 第三次实验
	//---------------------------------------------------------
	// 	
	CCG2022112465杨奎Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc) {
		pDoc->RenderScene((CGRenderContext*)this);
	}
	////绘制完毕，交换缓存
	
	glfwSwapBuffers(m_glfwWindow);
}

//状态栏上显示提示信息
void CCG2022112465杨奎View::ShowPrompt(const std::string& str)
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		pMainWnd->ShowPrompt(CString(str.c_str()));
	}
}
//状态栏上显示坐标信息
void CCG2022112465杨奎View::ShowCoord(double x, double y)
{
	CString str;
	glm::dvec3 v = DCS2WCS(glm::dvec3(x, y, 0.0));
	str.Format(_T("视口坐标 (%.0f, %.0f) : 世界坐标 (%.2f, %.2f) "), x, y, v.x, v.y);
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		pMainWnd->ShowCoord(str); //显示到状态栏
	}
}
glm::dvec3 CCG2022112465杨奎View::DCS2WCS(const glm::dvec3& p)
{
	//暂时使用屏幕设备坐标
	int w, h;
	glfwGetWindowSize(m_glfwWindow, &w, &h);
	//return glm::dvec3(p.x, double(h) - p.y, 0.0);
	return glm::dvec3(p.x - double(w) / 2, double(h) / 2 - p.y, 0.0);
}
glm::dvec3 CCG2022112465杨奎View::WCS2DCS(const glm::dvec3& p)
{
	//待实现
	return glm::dvec3();
}
bool CCG2022112465杨奎View::AddRenderable(std::shared_ptr<CGNode> r) const
{
	CCG2022112465杨奎Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return false;
	return pDoc->AddRenderable(r);
}


UINT CCG2022112465杨奎View::toggleFrameTimer()
{
	if (!mTimer) {
		mTimer = SetTimer(1, 20, NULL);// 启动50FPS定时器（20毫秒间隔）
	}
	else {
		KillTimer(mTimer);
		mTimer = 0;
	}
	return mTimer;
}

void CCG2022112465杨奎View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == mTimer) {
		RenderScene();
	}
	__super::OnTimer(nIDEvent);
}
