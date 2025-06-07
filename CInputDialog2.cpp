// CInputDialog2.cpp: 实现文件
//

#include "pch.h"
#include "CG2022112465杨奎.h"
#include "afxdialogex.h"
#include "CInputDialog2.h"


// CInputDialog2 对话框

IMPLEMENT_DYNAMIC(CInputDialog2, CDialogEx)

CInputDialog2::CInputDialog2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT_DIALOG2, pParent)
	, pos_x(0.0)
	, pos_y(0.0)
	, pos_z(500.0)
	, dx(0.0)
	, dy(0.0)
	, dz(-1.0)
	, abient1(0.1)
	, abient2(0.1)
	, abient3(0.1)
	, diffuse1(0.7)
	, diffuse2(0.7)
	, diffuse3(0.7)
	, specular1(1.0)
	, specular2(1.0)
	, specular3(1.0)
	, perspectives(10.0)
	, constant(1.0)
	, linear(0.0)
	, quadratic(0.0)
{

}

CInputDialog2::~CInputDialog2()
{
}

void CInputDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1_pos, pos_x);
	DDX_Text(pDX, IDC_EDIT2_pos, pos_y);
	DDX_Text(pDX, IDC_EDIT3_pos, pos_z);
	DDX_Text(pDX, IDC_EDIT4_dir, dx);
	DDX_Text(pDX, IDC_EDIT5_dir, dy);
	DDX_Text(pDX, IDC_EDIT6_dir, dz);
	DDX_Text(pDX, IDC_EDIT7_abient, abient1);
	DDX_Text(pDX, IDC_EDIT8_abient, abient2);
	DDX_Text(pDX, IDC_EDIT9_abient, abient3);
	DDX_Text(pDX, IDC_EDIT10_diffuse, diffuse1);
	DDX_Text(pDX, IDC_EDIT11_diffuse, diffuse2);
	DDX_Text(pDX, IDC_EDIT12_diffuse, diffuse3);
	DDX_Text(pDX, IDC_EDIT13_specular, specular1);
	DDX_Text(pDX, IDC_EDIT14_specular, specular2);
	DDX_Text(pDX, IDC_EDIT15_specular, specular3);
	DDX_Text(pDX, IDC_EDIT16_perspectives, perspectives);
	DDX_Text(pDX, IDC_EDIT17_constant, constant);
	DDX_Text(pDX, IDC_EDIT18_linear, linear);
	DDX_Text(pDX, IDC_EDIT19_quadratic, quadratic);
}


BEGIN_MESSAGE_MAP(CInputDialog2, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputDialog2::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputDialog2 消息处理程序

void CInputDialog2::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true); //取回输入框中数据到成员变量
	CDialogEx::OnOK();
}

BOOL CInputDialog2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
