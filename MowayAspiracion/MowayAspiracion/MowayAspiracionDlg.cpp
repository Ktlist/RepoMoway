
// MowayAspiracionDlg.cpp: archivo de implementaci�n
//

#include "stdafx.h"
#include "MowayAspiracion.h"
#include "MowayAspiracionDlg.h"
#include "afxdialogex.h"
#include "CMoway.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMoway moway;

// Cuadro de di�logo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de di�logo
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementaci�n
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cuadro de di�logo de CMowayAspiracionDlg



CMowayAspiracionDlg::CMowayAspiracionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMowayAspiracionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMowayAspiracionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMowayAspiracionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMowayAspiracionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMowayAspiracionDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Controladores de mensaje de CMowayAspiracionDlg

BOOL CMowayAspiracionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Agregar el elemento de men� "Acerca de..." al men� del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Establecer el icono para este cuadro de di�logo.  El marco de trabajo realiza esta operaci�n
	//  autom�ticamente cuando la ventana principal de la aplicaci�n no es un cuadro de di�logo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono peque�o

	// TODO: agregar aqu� inicializaci�n adicional

	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CMowayAspiracionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Si agrega un bot�n Minimizar al cuadro de di�logo, necesitar� el siguiente c�digo
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operaci�n la realiza autom�ticamente el marco de trabajo.

void CMowayAspiracionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rect�ngulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// El sistema llama a esta funci�n para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CMowayAspiracionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMowayAspiracionDlg::OnBnClickedOk()
{
	// TODO: Agregue aqu� su c�digo de controlador de notificaci�n de control
	moway.ConnectMoway(23);
	//CDialogEx::OnOK();
}


void CMowayAspiracionDlg::OnBnClickedButton1()
{
	int lf = 0, clf = 0, crf = 0, rf = 0;
	moway.ReadProximitySensors(&lf, &clf, &crf, &rf);
	moway.SetSpeed(50, 50, CMoway::FORWARD, CMoway::FORWARD, 0, 0);

	if (clf >= 150){
		moway.SetSpeed(15 - ((crf * 15) / 255), 0, CMoway::FORWARD, CMoway::FORWARD, 0, 0);
	}
	else if (crf >= 150){
		moway.SetSpeed(0, 15 - ((clf * 15) / 255), CMoway::FORWARD, CMoway::FORWARD, 0, 0);
	}
	// TODO: Agregue aqu� su c�digo de controlador de notificaci�n de control
}
