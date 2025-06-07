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

// CG2022112465杨奎Doc.cpp: CCG2022112465杨奎Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2022112465杨奎.h"
#endif

#include "CG2022112465杨奎Doc.h"

#include <propkey.h>
#include "CG2022112465杨奎View.h"
#include "CGScene.h"
#include "CGCamera.h"
#include "CGTransform.h"
#include "CGGeode.h"
#include "CGLineSegment.h"
#include "CGRenderContext.h"
#include "UIEventHandler.h"
#include "CGDraw2DLineSeg.h"
#include "CGDraw2DBrokenLine.h"

#include "CGSceneGraphView.h"

#include "CGModel2DTransform.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "TessellationHints.h"
#include "CGCube.h"
#include "CGSphere.h"
#include "CInputDialog1.h"
#include "RobotBodyTransform.h"
#include "CGCameraOp.h"
#include "LightTransform.h"
#include "CInputDialog2.h"
// CCG2022112465杨奎Doc

IMPLEMENT_DYNCREATE(CCG2022112465杨奎Doc, CDocument)

BEGIN_MESSAGE_MAP(CCG2022112465杨奎Doc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_Draw2D_LINESEG, &CCG2022112465杨奎Doc::OnUpdateDraw2dLineseg)
	ON_COMMAND(ID_Draw2D_LINESEG, &CCG2022112465杨奎Doc::OnDraw2dLineseg)
	ON_COMMAND(ID_Draw2D_LINESTRIP, &CCG2022112465杨奎Doc::OnDraw2dBrokenline)
	ON_UPDATE_COMMAND_UI(ID_Draw2D_LINESTRIP, &CCG2022112465杨奎Doc::OnUpdateDraw2dBrokenline)
	ON_COMMAND(ID_TranslateLF, &CCG2022112465杨奎Doc::OnTranslatelf)
	ON_COMMAND(ID_TranslateRt, &CCG2022112465杨奎Doc::OnTranslatert)
	ON_COMMAND(ID_TranslateDw, &CCG2022112465杨奎Doc::OnTranslatedw)
	ON_COMMAND(ID_TranslateUp, &CCG2022112465杨奎Doc::OnTranslateup)
	ON_COMMAND(ID_NRotate, &CCG2022112465杨奎Doc::OnNrotate)
	ON_COMMAND(ID_BRotate, &CCG2022112465杨奎Doc::OnBrotate)
	ON_COMMAND(ID_InRotate, &CCG2022112465杨奎Doc::OnInrotate)
	ON_COMMAND(ID_XScale1, &CCG2022112465杨奎Doc::OnXscale)
	ON_COMMAND(ID_YScale1, &CCG2022112465杨奎Doc::OnYscale)
	ON_COMMAND(ID_Scale1, &CCG2022112465杨奎Doc::OnScale)

	ON_COMMAND(ID_Draw3D_Sphere, &CCG2022112465杨奎Doc::OnDraw3dSphere)
	ON_COMMAND(ID_Draw3D_Sphereface, &CCG2022112465杨奎Doc::OnDraw3dSphereface)
	ON_COMMAND(ID_Timer, &CCG2022112465杨奎Doc::OnBtnTimer)
	ON_UPDATE_COMMAND_UI(ID_Timer, &CCG2022112465杨奎Doc::OnUpdateBtnTimer)
	ON_COMMAND(ID_DrawRobot, &CCG2022112465杨奎Doc::OnDrawrobot)
	ON_COMMAND(ID_Camera, &CCG2022112465杨奎Doc::OnCamera)
	ON_COMMAND(ID_LightOpen, &CCG2022112465杨奎Doc::OnLightopen)
	ON_COMMAND(ID_LightClose, &CCG2022112465杨奎Doc::OnLightclose)
	ON_COMMAND(ID_CreateSpotLight, &CCG2022112465杨奎Doc::OnCreatespotlight)
END_MESSAGE_MAP()

// CCG2022112465杨奎Doc 构造/析构
CCG2022112465杨奎Doc::CCG2022112465杨奎Doc() noexcept
{
	// TODO: 在此添加一次性构造代码
	mScene = std::make_shared<CGScene>();
	//mScene->SetMainCamera(std::make_shared<CGCamera>());
	//取消默认创建的geode
	//auto e = std::make_shared<CGGeode>();
	//auto line = std::make_shared<CGLineSegment>(glm::dvec3(100, 100, 0), glm::dvec3(400, 300, 0));
	//e->AddChild(line);
	//auto g = std::make_shared<CGTransform>();
	//g->AddChild(e);
	//mScene->SetSceneData(g);

	
	//球体模型
	auto c = std::make_shared<CGCube>();
	auto h = std::make_shared<TessellationHints>();
	c->setTessellationHints(h);
	c->setDisplayListEnabled(true);
	//右球体实例节点
	auto t1 = std::make_shared<CGTransform>(); //实列组节点
	auto e1 = std::make_shared<CGGeode>(); //实列叶节点
	auto color1 = std::make_shared<CGColor>(); //属性
	color1->setValue(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)); //黄色
	e1->gocRenderStateSet()->setRenderState(color1, -1); //设置节点属性

	t1->translate(100, 0, 0);
	t1->rotate(45, 1, 1, 1);
	t1->scale(50, 50, 50);
	e1->AddChild(c);
	t1->AddChild(e1);
	
	//添加材质
	auto material1 = std::make_shared<CGMaterial>();
	material1->setDiffuse(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));//物体表面的漫反射颜色（黄色）
	material1->setAmbient(glm::vec4(0.2f, 0.2f, 0.0f, 1.0f));//环境光颜色（稍微偏暗的黄色）
	material1->setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//镜面反射光颜色（白色镜面反射光）
	material1->setShininess(64.0f);//32-64高光系数，越大高光越集中
	//绑定材质回调
	//material1->SetUpdateCallback(std::make_shared<MaterialAnimCallback>());
	e1->gocRenderStateSet()->setRenderState(material1, -1);

	//设置光照模型
	auto L1= std::make_shared<CGLightModel>();
	L1->setLocalViewer(true);// 启用局部观察者，意味着视点位置会影响高光计算（更真实）
	L1->setTwoSide(true);	// 启用双面光照，使物体背面也能被正确照亮（否则背面可能看起来是黑的）。
	L1->setAmbientColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f)); // 更暗的环境光
	e1->gocRenderStateSet()->setRenderState(L1, -1); //设置节点属性

	//设置着色模式
	auto S1 = std::make_shared<CGShadeModel>(SM_SMOOTH);//平滑着色模式，让光照颜色过度更流畅
	e1->gocRenderStateSet()->setRenderState(S1, -1);
	
	mScene->GetSceneData()->asGroup()->AddChild(t1);
	
	//长方体模型
	auto c2 = std::make_shared<CGCube>();
	auto h2 = std::make_shared<TessellationHints>();
	c2->setTessellationHints(h2);
	c2->setDisplayListEnabled(true);
	//左长方体节点
	auto t2 = std::make_shared<CGTransform>(); //实列组节点
	auto e2 = std::make_shared<CGGeode>(); //实列叶节点
	auto color2 = std::make_shared<CGColor>(); //属性
	color2->setValue(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); //蓝色
	e2->gocRenderStateSet()->setRenderState(color2, -1); //设置节点属性
	auto p2 = std::make_shared<CGPolygonMode>(PM_FILL, PM_FILL); //设置填充模式
	e2->gocRenderStateSet()->setRenderState(p2, -1); //设置节点属性

	t2->translate(-100, 0, 0);
	t2->rotate(45, 1, 1, 1);
	t2->scale(50, 50, 50);
	e2->AddChild(c2);
	t2->AddChild(e2);

	//添加材质
	auto material2 = std::make_shared<CGMaterial>();
	material2->setDiffuse(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));//物体表面的漫反射颜色（蓝色）
	material2->setAmbient(glm::vec4(0.0f, 0.0f, 0.2f, 1.0f)); //环境光颜色（稍微偏暗的蓝色）
	material2->setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); //镜面反射光颜色（白色镜面反射光）
	material2->setShininess(64.0f); //32-64高光系数，越大高光越集中
	//绑定材质回调
	//material2->SetUpdateCallback(std::make_shared<MaterialAnimCallback>());
	e2->gocRenderStateSet()->setRenderState(material2, -1);

	//设置光照模型
	auto L2 = std::make_shared<CGLightModel>();
	L2->setLocalViewer(true);// 启用局部观察者，意味着视点位置会影响高光计算（更真实）
	L2->setTwoSide(true);	// 启用双面光照，使物体背面也能被正确照亮（否则背面可能看起来是黑的）。
	L2->setAmbientColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f)); // 更暗的环境光
	e2->gocRenderStateSet()->setRenderState(L2, -1); //设置节点属性

	//设置着色模式
	auto S2 = std::make_shared<CGShadeModel>(SM_SMOOTH);
	e2->gocRenderStateSet()->setRenderState(S2, -1);

	mScene->GetSceneData()->asGroup()->AddChild(t2);
}

CCG2022112465杨奎Doc::~CCG2022112465杨奎Doc()
{
}

BOOL CCG2022112465杨奎Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCG2022112465杨奎Doc 序列化

void CCG2022112465杨奎Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCG2022112465杨奎Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CCG2022112465杨奎Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CCG2022112465杨奎Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCG2022112465杨奎Doc 诊断

#ifdef _DEBUG
void CCG2022112465杨奎Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCG2022112465杨奎Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG




bool CCG2022112465杨奎Doc::RenderScene(CGRenderContext* pRC)
{
	if (pRC == nullptr)
		return false;
	if (mScene == nullptr)
		return false;
	CGCamera* pCamera = mScene->GetMainCamera();
	if (pCamera == nullptr)
		return false;
	return mScene->Render(pRC, pCamera);
}
bool CCG2022112465杨奎Doc::AddRenderable(std::shared_ptr<CGNode> r)
{
	/*if (mScene == nullptr)
		return false;
	CGGroup* g = mScene->GetSceneData()->asGroup();
	if (g) {
		g->AddChild(r);
		return true;
	}	return false;*/

	if (mSelectedGroup) { //需要先选中一各组节点
		//模型加入实例节点后加入场景
		auto ge = std::make_shared<CGGeode>();
		ge->AddChild(r);
		mSelectedGroup->AddChild(ge);
		CTreeCtrl& tree = GetSceneGraphView()->GetTreeCtrl();
		InstToSceneTree(&tree, mSelectedItem, ge.get());
		return true;
	}
	else {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
	}
	return false;

}

// CCG2022112465杨奎Doc 命令

void CCG2022112465杨奎Doc::OnDraw2dLineseg()
{
	if (!mSelectedGroup) {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
		return;
	}
	// TODO: 在此添加命令处理程序代码
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGDraw2DLineSeg(view->glfwWindow())); //创建绘制直线段的命令对象
	}
}

void CCG2022112465杨奎Doc::OnUpdateDraw2dLineseg(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() ==
		EventType::Draw2DLineSeg);
}


void CCG2022112465杨奎Doc::OnDraw2dBrokenline()
{
	if (!mSelectedGroup) {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
		return;
	}
	// TODO: 在此添加命令处理程序代码
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGDraw2DBrokenLine(view->glfwWindow())); //创建绘制折线段段的命令对象
	}
}

void CCG2022112465杨奎Doc::OnUpdateDraw2dBrokenline(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() ==
		EventType::Draw2DLineStrip);
}


CCGSceneGraphView* CCG2022112465杨奎Doc::GetSceneGraphView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCGSceneGraphView))) {
			CCGSceneGraphView* view = dynamic_cast<CCGSceneGraphView*>(pView);
			return view;
		}
	}
	return nullptr;
}
void CCG2022112465杨奎Doc::InstToSceneTree(CTreeCtrl* pTree)
{
	TV_INSERTSTRUCT tvinsert;
	HTREEITEM hInst;
	tvinsert.hParent = NULL;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 40;
	tvinsert.item.cChildren = 0;
	tvinsert.item.lParam = NULL;//
	CString str(_T("场景"));
	tvinsert.item.pszText = str.GetBuffer();
	str.ReleaseBuffer();
	hInst = pTree->InsertItem(&tvinsert);
	pTree->SetItemData(hInst, DWORD_PTR(mScene.get()));
	InstToSceneTree(pTree, hInst, mScene->GetSceneData());
	pTree->Expand(hInst, TVE_EXPAND);
}
void CCG2022112465杨奎Doc::InstToSceneTree(CTreeCtrl* pTree, HTREEITEM hParent, CGNode* node)
{
	TV_INSERTSTRUCT tvinsert;
	HTREEITEM hTree;
	tvinsert.hParent = hParent;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 40;
	tvinsert.item.cChildren = 0;
	tvinsert.item.lParam = LPARAM(&node);//
	if (node->asGeode()) {
		if (node->Name()) {
			tvinsert.item.pszText = node->Name().GetBuffer();
			node->Name().ReleaseBuffer();
		}
		else {
			CString str(_T("Geode"));
			tvinsert.item.pszText = str.GetBuffer();
			str.ReleaseBuffer();
		}
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		//叶子实例节点不再显示模型节点
	}
	else if (node->asTransform()) {
		if (node->Name()){
			tvinsert.item.pszText = node->Name().GetBuffer();
			node->Name().ReleaseBuffer();
		}
		else {
			CString str(_T("Trans"));
			tvinsert.item.pszText = str.GetBuffer();
			str.ReleaseBuffer();
		}
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		unsigned int childs = node->asTransform()->GetNumChildren();
		for (unsigned int i = 0; i < childs; i++) {
			InstToSceneTree(pTree, hTree, node->asTransform()->GetChild(i));
		}
	}
	else if (node->asGroup()) {
		if (node->Name()){
			tvinsert.item.pszText = node->Name().GetBuffer();
			node->Name().ReleaseBuffer();
		}
		else {
			CString str(_T("Group"));
			tvinsert.item.pszText = str.GetBuffer();
			str.ReleaseBuffer();
		}
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		unsigned int childs = node->asGroup()->GetNumChildren();
		for (unsigned int i = 0; i < childs; i++) {
			InstToSceneTree(pTree, hTree, node->asGroup()->GetChild(i));
		}
	}
}
void CCG2022112465杨奎Doc::OnSelectSceneTreeItem(CTreeCtrl* pTree, HTREEITEM hItem)
{
	mSelectedItem = hItem;
	if (!mSelectedItem) {
		mSelectedGroup = nullptr;
		return;
	}
	HTREEITEM hRoot = pTree->GetRootItem();
	if (mSelectedItem == hRoot) {
		mSelectedGroup = nullptr;
	}
	else {
		CGGroup* node = (CGGroup*)(pTree->GetItemData(mSelectedItem));
		if (node && node->asGroup() && !(node->asGeode())) { //不允许叶子节点上再
			mSelectedGroup = dynamic_cast<CGGroup*>(node);
		}
		else {
			mSelectedGroup = nullptr;
		}
	}
}


void CCG2022112465杨奎Doc::OnTranslatelf()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		// UIEventHandler::SetCommand(new CGModel2DTransform((CGRenderable*)pTree->GetItemData(mSelectedItem),view->glfwWindow())); 
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		// 直接应用向左平移变换（每次移动10个单位）
		const float translateAmount = -10.0f; // 负值表示向左移动
		child->Translate(translateAmount, 0);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已向左移动");
	}
}

void CCG2022112465杨奎Doc::OnTranslatert()//右移
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		// UIEventHandler::SetCommand(new CGModel2DTransform((CGRenderable*)pTree->GetItemData(mSelectedItem),view->glfwWindow())); 
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		// 直接应用向左平移变换（每次移动10个单位）
		const float translateAmount = 10.0f; // 负值表示向左移动
		child->Translate(translateAmount, 0);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已向右移动");
	}
}

void CCG2022112465杨奎Doc::OnTranslatedw()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		// UIEventHandler::SetCommand(new CGModel2DTransform((CGRenderable*)pTree->GetItemData(mSelectedItem),view->glfwWindow())); 
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		// 直接应用向左平移变换（每次移动10个单位）
		const float translateAmount = -10.0f; // 负值表示向左移动
		child->Translate(0,translateAmount);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已向左移动");
	}
}

void CCG2022112465杨奎Doc::OnTranslateup()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		// UIEventHandler::SetCommand(new CGModel2DTransform((CGRenderable*)pTree->GetItemData(mSelectedItem),view->glfwWindow())); 
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		// 直接应用向左平移变换（每次移动10个单位）
		const float translateAmount = 10.0f; // 负值表示向左移动
		child->Translate(0, translateAmount);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已向左移动");
	}
}

void CCG2022112465杨奎Doc::OnNrotate()	// 逆时针旋转操作
{
	//TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		// UIEventHandler::SetCommand(new CGModel2DTransform((CGRenderable*)pTree->GetItemData(mSelectedItem),view->glfwWindow())); 
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}

		child->Rotate(90, 0, 0);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("旋转完成");
	}
}

void CCG2022112465杨奎Doc::OnBrotate()	// 顺时针旋转操作
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		// UIEventHandler::SetCommand(new CGModel2DTransform((CGRenderable*)pTree->GetItemData(mSelectedItem),view->glfwWindow())); 
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		
		child->Rotate(-90,0,0);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("旋转完成");
	}
}

void CCG2022112465杨奎Doc::OnInrotate()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGModel2DTransform 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow())); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}


void CCG2022112465杨奎Doc::OnXscale()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow(), true, false)); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}



void CCG2022112465杨奎Doc::OnYscale()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow(), false, true)); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}


void CCG2022112465杨奎Doc::OnScale()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow(), true, true)); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}


void CCG2022112465杨奎Doc::OnDraw3dSphere()
{
	// TODO: 在此添加命令处理程序代码
	if (!mSelectedGroup)
	{
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
		return;
	}
	CInputDialog1 dlg;
	dlg.mTitle = _T("请输入球体半径以及三维位置坐标"); //根据需要设置对话框标题
	if (dlg.DoModal() == IDOK) //对话框中点击了【确定】按钮，取回输入的数据
	{ //根据实际需要使用输入的数据
		float R = _ttof(dlg.mValue1);//假如输入的是数值，则将字符串转换为数值
		float X = _ttof(dlg.mValue2);
		float Y = _ttof(dlg.mValue3);
		float Z = _ttof(dlg.mValue4);
		if (R <= 0) {
			AfxMessageBox(_T("请输入大于0的数值！"));
			return;
		}

		//球体模型
		auto c = std::make_shared<CGSphere>(R);
		auto h = std::make_shared<TessellationHints>();
		//设置精度
		//h->setTargetSlices(50);
		//h->setTargetStacks(20);

		c->setTessellationHints(h);
		c->setDisplayListEnabled(true);
		//右球体实例节点
		auto t1 = std::make_shared<CGTransform>(); //实列组节点
		auto e1 = std::make_shared<CGGeode>(); //实列叶节点
		auto color1 = std::make_shared<CGColor>(); //属性
		color1->setValue(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); //红色
		e1->gocRenderStateSet()->setRenderState(color1, -1); //设置节点属性
		auto p1 = std::make_shared<CGPolygonMode>(PM_LINE, PM_LINE); //设置线框模式
		e1->gocRenderStateSet()->setRenderState(p1, -1); //设置节点属性
		t1->translate(X, Y, Z);
		t1->rotate(45, 1, 1, 1);
		//t1->scale(100, 100, 100);
		e1->AddChild(c);
		t1->AddChild(e1);
		//加入场景树
		AddRenderable(t1);
	}
	UpdateAllViews(NULL);
}

void CCG2022112465杨奎Doc::OnDraw3dSphereface()
{
	// TODO: 在此添加命令处理程序代码
	if (!mSelectedGroup)
	{
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
		return;
	}
	CInputDialog1 dlg;
	dlg.mTitle = _T("请输入球体半径以及三维位置坐标"); //根据需要设置对话框标题
	if (dlg.DoModal() == IDOK) //对话框中点击了【确定】按钮，取回输入的数据
	{ //根据实际需要使用输入的数据
		float R = _ttof(dlg.mValue1);//假如输入的是数值，则将字符串转换为数值
		float X = _ttof(dlg.mValue2);
		float Y = _ttof(dlg.mValue3);
		float Z = _ttof(dlg.mValue4);
		if (R <= 0) {
			AfxMessageBox(_T("请输入大于0的数值！"));
			return;
		}

		//球体模型
		auto c = std::make_shared<CGSphere>(R);
		auto h = std::make_shared<TessellationHints>();
		//设置精度
		//h->setTargetSlices(50);
		//h->setTargetStacks(20);

		c->setTessellationHints(h);
		c->setDisplayListEnabled(true);
		//右球体实例节点
		auto t1 = std::make_shared<CGTransform>(); //实列组节点
		auto e1 = std::make_shared<CGGeode>(); //实列叶节点
		auto color1 = std::make_shared<CGColor>(); //属性
		color1->setValue(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); //绿色
		e1->gocRenderStateSet()->setRenderState(color1, -1); //设置节点属性
		//auto p1 = std::make_shared<CGPolygonMode>(PM_LINE, PM_LINE); //设置线框模式
		//e1->gocRenderStateSet()->setRenderState(p1, -1); //设置节点属性
		t1->translate(X, Y, Z);
		t1->rotate(45, 1, 1, 1);

		e1->AddChild(c);
		t1->AddChild(e1);
		//加入场景树
		AddRenderable(t1);
	}
	UpdateAllViews(NULL);
}

std::shared_ptr<CGTransform> createBoxPart(float len, float width, float height, const glm::vec4& color, const  CString name)
{
	using namespace std;
	auto cube = make_shared<CGCube>(len, width, height);
	auto hints = make_shared<TessellationHints>();
	cube->setTessellationHints(hints);
	cube->setDisplayListEnabled(true);

	auto geode = make_shared<CGGeode>();
	geode->AddChild(cube);
	geode->setName(name);

	// 设置颜色
	auto colorState = make_shared<CGColor>();
	colorState->setValue(color);
	geode->gocRenderStateSet()->setRenderState(colorState, -1);

	auto tran = make_shared<CGTransform>();
	tran->AddChild(geode);
	tran->setName(name);
	return tran;
}

void CCG2022112465杨奎Doc::OnBtnTimer()
{
	// TODO: 在此添加命令处理程序代码
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}
	if (view != nullptr) {
		mTimer = view->toggleFrameTimer();// 启动定时器
	}
}

void CCG2022112465杨奎Doc::OnUpdateBtnTimer(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mTimer != 0);
}
void CCG2022112465杨奎Doc::OnDrawrobot()
{
	// TODO: 在此添加命令处理程序代码
	//创建根节点机器人
	auto Robot = std::make_shared<CGTransform>();
	Robot->setName("Robot");
	//创建躯干
	auto Trunk = std::make_shared<CGTransform>();
	Trunk->setName("Trunk");
	auto trunk1 = createBoxPart(80, 40, 50, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), "Trunk1");
	trunk1->translate(0, 35, 0);
	auto trunk2 = createBoxPart(60, 25, 40, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), "Trunk2");
	trunk2->translate(0, 0, 0);
	auto trunk3 = createBoxPart(30, 10, 30, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), "Trunk3");
	trunk3->translate(0, -18, 0);
	auto trunk4 = createBoxPart(40, 20, 35, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), "Trunk4");
	trunk4->translate(0, -30, 0);
	Trunk->AddChild(trunk1);
	Trunk->AddChild(trunk2);
	Trunk->AddChild(trunk3);
	Trunk->AddChild(trunk4);
	Robot->AddChild(Trunk);

	//创建头部
	auto Head = createBoxPart(40, 40, 40, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), "Head");
	Head->translate(0, 70, 0);
	Head->rotate(20,0,1,0);
	Head->rotate(15,1,0,0);
	Robot->AddChild(Head);

	//创建右上臂
	auto RighUpperArm = createBoxPart(20, 50, 20, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "RighUpperArm");
	RighUpperArm->translate(50, 40, 0);
	RighUpperArm->rotate(-45, 0, 0, -1);

	//创建右下臂
	auto RightLowerArm = createBoxPart(18, 40, 18, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "RightLowerArm");
	RightLowerArm->translate(0, -30, 10);
	RightLowerArm->rotate(-60, 1, 0, 0); // 旋转下臂
	RighUpperArm->AddChild(RightLowerArm);

	//创建右手掌
	auto RightHand = createBoxPart(16, 16, 16, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "RightHand");
	RightHand->translate(0, -30, 0);
	RightLowerArm->AddChild(RightHand);

	//创建右手指（示例：2根）
	auto finger1 = createBoxPart(4, 12, 4, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "finger");
	finger1->translate(-6, -12, 0);
	RightHand->AddChild(finger1);
	auto finger2 = createBoxPart(4, 12, 4, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "finger");
	finger2->translate(6, -12, 0);
	RightHand->AddChild(finger2);
	//右臂组装到机器人
	Robot->AddChild(RighUpperArm);

	//创建左上臂
	auto LeftUpperArm = createBoxPart(20, 50, 20, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "RighUpperArm");
	LeftUpperArm->translate(-50, 40, 0);
	LeftUpperArm->rotate(-60, 0, 0, 1);
	LeftUpperArm->rotate(-30, 1, 0, 0);

	//创建左下臂
	auto LeftLowerArm = createBoxPart(18, 40, 18, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "RightLowerArm");
	LeftLowerArm->translate(0, -30, 15);
	LeftLowerArm->rotate(-90, 1, 0, 0); // 旋转下臂
	LeftUpperArm->AddChild(LeftLowerArm);

	//创建左手掌
	auto LeftHand = createBoxPart(16, 16, 16, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "RightHand");
	LeftHand->translate(0, -30, 0);
	LeftLowerArm->AddChild(LeftHand);

	//创建左手指（示例：2根）
	auto finger3 = createBoxPart(4, 12, 4, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "finger");
	finger3->translate(-6, -12, 0);
	LeftHand->AddChild(finger3);
	auto finger4 = createBoxPart(4, 12, 4, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "finger");
	finger4->translate(6, -12, 0);
	LeftHand->AddChild(finger4);
	//左臂组装到机器人
	Robot->AddChild(LeftUpperArm);

	//创建两条腿
	auto Leg = std::make_shared<CGTransform>();
	Leg->setName("Leg");
	//左大腿
	auto leftUpperLeg = createBoxPart(20, 50, 20, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "leftUpperLeg");
	leftUpperLeg->translate(-25, -55, 10);
	leftUpperLeg->rotate(45, -1, -1, -1);
	//左小腿
	auto leftLowerLeg = createBoxPart(22, 55, 22, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "leftLowerLeg");
	leftLowerLeg->translate(0, -50, -15);
	leftLowerLeg->rotate(30, 1, 0, 0);
	leftUpperLeg->AddChild(leftLowerLeg);
	Leg->AddChild(leftUpperLeg);
	//右大腿
	auto rightUpperLeg = createBoxPart(20, 50, 20, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "rightUpperLeg");
	rightUpperLeg->translate(25, -55, 10);
	rightUpperLeg->rotate(45, -1, 1, 1);
	//右小腿
	auto rightLowerLeg = createBoxPart(22, 55, 22, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), "rightLowerLeg");
	rightLowerLeg->translate(0, -50, -10);
	rightLowerLeg->rotate(20, 1, 0, 0);
	rightUpperLeg->AddChild(rightLowerLeg);
	Leg->AddChild(rightUpperLeg);

	Robot->AddChild(Leg);
	//加入场景
	mScene->GetSceneData()->asGroup()->AddChild(Robot);
	UpdateAllViews(NULL);

//更新回调测试
	//机器人旋转
	std::shared_ptr<RobotBodyTransformParam> data1 = std::make_shared<RobotBodyTransformParam>();
	std::shared_ptr<RobotBodyRotate> rc1 = std::make_shared<RobotBodyRotate>();
	Robot->setUserData(data1); //设置节点更新参数
	Robot->SetUpdateCallback(rc1); //设置节点更新回调
	//机器人腿部运动
	std::shared_ptr<RotateParam> data2 = std::make_shared<RotateParam>();
	data2->setAxis(glm::vec3(1.0f, 0.0f, 0.0f));
	std::shared_ptr<RotateCallback> rc2 = std::make_shared<RotateCallback>();
	rightUpperLeg->setUserData(data2); //设置节点更新参数
	rightUpperLeg->SetUpdateCallback(rc2); //设置节点更新回调

	std::shared_ptr<RotateParam> data3 = std::make_shared<RotateParam>();
	data3->setAxis(glm::vec3(1.0f, 0.0f, 0.0f));
	data3->setAngle(0.0f);
	data3->setMaxAngle(60.0f);
	std::shared_ptr<RotateCallback> rc3 = std::make_shared<RotateCallback>();
	leftUpperLeg->setUserData(data3); //设置节点更新参数
	leftUpperLeg->SetUpdateCallback(rc3); //设置节点更新回调
	//机器人手臂运动
	std::shared_ptr<RotateParam> data4 = std::make_shared<RotateParam>();
	data4->setAxis(glm::vec3(1.0f, 1.0f, 0.0f));
	data4->setStep(6.0f);
	std::shared_ptr<RotateCallback> rc4 = std::make_shared<RotateCallback>();
	LeftUpperArm->setUserData(data4); //设置节点更新参数
	LeftUpperArm->SetUpdateCallback(rc4); //设置节点更新回调

	std::shared_ptr<RotateParam> data5 = std::make_shared<RotateParam>();
	data5->setAxis(glm::vec3(-1.0f, 0.0f, 0.0f));
	data5->setStep(6.0f);
	std::shared_ptr<RotateCallback> rc5 = std::make_shared<RotateCallback>();
	RighUpperArm->setUserData(data5); //设置节点更新参数
	RighUpperArm->SetUpdateCallback(rc5); //设置节点更新回调
	
	//添加光源
	auto light = std::make_shared<CGLight>();
	light->setPosition(glm::vec4(0.0f, 0.0f, 500.0f, 1.0f));//点光源，位置（200，200，200）
	light->setAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 0.2f));//白色环境光
	light->setDiffuse(glm::vec4(0.7f, 0.7f, 0.7f, 0.7f)); //白色漫反射光
	light->setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); //白色镜面反射光
	light->SetUpdateCallback(std::make_shared<HeadLightCallback>());//头灯回调
	Robot->gocRenderStateSet()->setRenderState(light, 0); //添加到场景根节点


	//添加材质
	auto material = std::make_shared<CGMaterial>();
	material->setDiffuse(glm::vec4(0.0f, 1.0f, 0.5f, 1.0f));
	material->setAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	material->setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	material->setShininess(64.0f);
	//绑定材质回调
	material->SetUpdateCallback(std::make_shared<MaterialAnimCallback>()); 
	Robot->gocRenderStateSet()->setRenderState(material, -1);
	//设置光照模型
	auto L = std::make_shared<CGLightModel>();
	L->setLocalViewer(true);// 启用局部观察者，意味着视点位置会影响高光计算（更真实）
	L->setTwoSide(true);	// 启用双面光照，使物体背面也能被正确照亮（否则背面可能看起来是黑的）。
	L->setAmbientColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f)); // 更暗的环境光
	Robot->gocRenderStateSet()->setRenderState(L, -1); //设置节点属性
	//设置着色模式
	auto S = std::make_shared<CGShadeModel>(SM_SMOOTH);
	Robot->gocRenderStateSet()->setRenderState(S, -1);
}



void CCG2022112465杨奎Doc::OnViewResize(int cx, int cy){
	mScene->GetMainCamera()->viewport()->set(0, 0, cx, cy); 
}


void CCG2022112465杨奎Doc::OnCamera()
{
	// TODO: 在此添加命令处理程序代码
	CCG2022112465杨奎View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112465杨奎View))) {
			view = dynamic_cast<CCG2022112465杨奎View*>(pView);
			break;
		}
	}

	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	UIEventHandler::SetCommand(new CGCameraOp(view->glfwWindow(), mScene));
	UpdateAllViews(NULL);
}

void CCG2022112465杨奎Doc::OnLightopen()
{
	////添加光源
	//auto light = std::make_shared<CGLight>();
	//light->setPosition(glm::vec4(0.0f, 0.0f, 500.0f, 1.0f));//点光源，位置（200，200，200）
	//light->setAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 0.2f));//白色环境光
	//light->setDiffuse(glm::vec4(0.7f, 0.7f, 0.7f, 0.7f)); //白色漫反射光
	//light->setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); //白色镜面反射光
	//light->SetUpdateCallback(std::make_shared<HeadLightCallback>());//头灯回调
	//mScene->GetSceneData()->asGroup()->gocRenderStateSet()->setRenderState(light, 0); //添加到场景根节点
	
	glDisable(GL_LIGHTING);
	glEnable(GL_NORMALIZE); // 确保法线正确
	// 启用光照与深度测试（必须）
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST); //启用深度测试，确保物体前后关系正确显示。
	// 更新所有视图
	UpdateAllViews(NULL);
}

void CCG2022112465杨奎Doc::OnLightclose()
{
	// TODO: 在此添加命令处理程序代码
	// 禁用光照和光源
	glDisable(GL_LIGHTING);
	// 禁用颜色材质和深度测试
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);
	//恢复背景色为默认（如白色）
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 更新所有视图
	UpdateAllViews(NULL);
}

void CCG2022112465杨奎Doc::OnCreatespotlight()
{
	// TODO: 在此添加命令处理程序代码
	CInputDialog2 dlg;
	//添加光源
	auto light = std::make_shared<CGLight>();
	float X, Y, Z, dx, dy, dz, abient1, abient2, abient3, diffuse1, diffuse2, diffuse3,
		specular1, specular2, specular3,perspective,constant,linear,quadratic;
	if (dlg.DoModal() == IDOK) //对话框中点击了【确定】按钮，取回输入的数据
	{ //根据实际需要使用输入的数据
		X = dlg.pos_x;
		Y = dlg.pos_y;
		Z = dlg.pos_z;

		dx = dlg.dx;
		dy = dlg.dy;
		dz = dlg.dz;

		abient1 = dlg.abient1;
		abient2 = dlg.abient2;
		abient3 = dlg.abient3;

		diffuse1 = dlg.diffuse1;
		diffuse2 = dlg.diffuse2;
		diffuse3 = dlg.diffuse3;

		specular1 = dlg.specular1;
		specular2 = dlg.specular2;
		specular3 = dlg.specular3;

		perspective = dlg.perspectives;

		constant = dlg.constant;
		linear = dlg.linear;
		quadratic = dlg.quadratic;

		light->setPosition(glm::vec4(X, Y, Z, 1.0f));//点光源
		light->setDirection(glm::vec3(dx, dy, dz)); // 设置光源方向
		light->setAmbient(glm::vec4(abient1, abient2, abient3, 0.2f));
		light->setDiffuse(glm::vec4(diffuse1, diffuse2, diffuse3, 0.f));
		light->setSpecular(glm::vec4(specular1, specular2, specular3, 1.0f));
		light->setSpotCutoff(perspective); // 聚光灯角度
		light->setSpotExponent(10.0f);  // 指数越大，光斑越集中
		light->setAttenuation(constant,linear,quadratic); // 衰减参数
		//添加到场景根节点
		mScene->GetSceneData()->asGroup()->gocRenderStateSet()->setRenderState(light, 0);
	
		glEnable(GL_NORMALIZE); // 确保法线正确
		glEnable(GL_LIGHTING);
		// 启用深度测试（必须）
		glEnable(GL_DEPTH_TEST); //启用深度测试，确保物体前后关系正确显示。
		UpdateAllViews(NULL);
	}
}
