#pragma once
#include "afxdialogex.h"


// CInputDialog2 对话框

class CInputDialog2 : public CDialogEx
{
	DECLARE_DYNAMIC(CInputDialog2)

public:
	CInputDialog2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInputDialog2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

	float pos_x;
	float pos_y;
	float pos_z;
	float dx;
	float dy;
	float dz;
	float abient1;
	float abient2;
	float abient3;
	float diffuse1;
	float diffuse2;
	float diffuse3;
	float specular1;
	float specular2;
	float specular3;
	float perspectives;
	float constant;
	float linear;
	float quadratic;
};
