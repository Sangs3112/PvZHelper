// PVZ_Helper.cpp : ����Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "PVZ_Helper.h"
#include "PVZ_1_0.h"
#include "PVZ_1_2_EN_1073.h"
#include "PVZ_1_2_CN_REPAIR.h"
#include "PVZ_1_2_CN_ENDLESS.h"
#include "stdio.h"
#include "commctrl.h"
#include "DllFromMem.h"


#define WM_INIT		WM_USER + 1

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

PVZ* pvz = NULL;

#define INIT_LIST(hwnd,IDC,_List) \
for (int i = 0; i < sizeof(_List) / sizeof(*_List); ++i)\
{\
	SendDlgItemMessage(hwnd, IDC, CB_ADDSTRING, 0, LPARAM(_List[i])); \
}\
	SendDlgItemMessage(hwnd, IDC, CB_SETCURSEL, 0, 0)


const char* pList[] = { "�㶹����", "���տ�", "ӣ��ը��", "���ǽ", "������",
"��������", "���컨", "˫������", "С�繽", "���⹽", "���繽", "Ĺ��������",
"�Ȼ�", "��С��", "������", "����", "˯��", "�ѹ�", "��������", "���ƺ���",
"������", "�ش�", "�����׮", "�߼��", "��Ģ��", "·�ƻ�", "������",
"��Ҷ��", "�Ѽ�����", "����", "�Ϲ�ͷ", "������", "���Ĳ�Ͷ��", "����",
"����Ͷ��", "���ȶ�", "����", "Ҷ�ӱ���ɡ", "��յ��", "����Ͷ��", "��ǹ����",
"˫�����տ�", "������", "����", "����", "�����", "�ش���", "���׼�ũ��",
"����˫������", "��ը���", "�޴���" };

const char* zList[] = { "��ͨ", "����", "·��", "�Ÿ�", "��Ͱ", "����",
"��դ��", "�����", "����", "����", "Ѽ��", "Ǳˮ", "����", "ѩ��", "����",
"С��", "����", "��", "����", "ѩ��", "�ļ�", "����", "����", "����", "С��",
"����", "�㶹", "���", "����", "��ǹ", "�ѹ�", "�߼��", "����" };

const char* bList[] = { "�ݵ�", "���", "ˮ��" };

const char* nList[] = { "1", "2", "3", "4", "5", "6" };

const char* rList[] = { "������", "½·", "ˮ·" };

const char* mList[] = { "ð��ģʽ", "�����", "ҹ���", "Ӿ�ؼ�",
"Ũ���", "�ݶ���", "��������", "ҹ������", "Ӿ������", "Ũ������",
"�ݶ�����", "�����޾�", "ҹ���޾�", "Ӿ���޾�", "Ũ���޾�", "�ݶ��޾�",
"ֲ�ｩʬ", "���������", "�ϻ���", "������ֲ��", "��ʯ����", "����ʳ����",
"������", "��ʬˮ���", "��ʯתת��", "С��ʬ���鷳", "����������", "����һ��",
"ѩ����", "��ʬ����", "����ʬ", "˭Ц�����", "ֲ�ｩʬ2", "���������2",
"�������", "��������", "�������", "����", "�޲�Ƥ֮��", "��Ҫʱ��",
"��̫����", "��Ϯ", "�����ؿ�", "����Ѱ��ѹ��", "��Ĺģʽ", "�����ڳ���",
"������֮ҹ", "�ļ�����ս", "����", "��ƿ�޾�", "���ǽ�ʬ�޾�" };

const char* izeList[] = { "�㶹��", "���������", "�ش�������", "���������", "��С��",
"���ӻ���1", "���ӻ���2", "���ӻ���3" };

const char* cnList[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

const char* czList[] = { "��ͨ", "·��", "�Ÿ�", "��Ͱ", "����", "��", "�ļ�", "�����", "����", "��դ��", "����", "����", "����", "����", "С��" };

const char* fList[] = { "�㶹����", "���տ�", "ӣ��ը��", "���ǽ", "������",
"��������", "���컨", "˫������", "С�繽", "���⹽", "���繽", "Ĺ��������",
"�Ȼ�", "��С��", "������", "����", "˯��", "�ѹ�", "��������", "���ƺ���",
"������", "�ش�", "�����׮", "�߼��", "��Ģ��", "·�ƻ�", "������",
"��Ҷ��", "�Ѽ�����", "����", "�Ϲ�ͷ", "������", "���Ĳ�Ͷ��", "����",
"����Ͷ��", "���ȶ�", "����", "Ҷ�ӱ���ɡ", "��յ��", "����Ͷ��", "��ǹ����",
"˫�����տ�", "������", "����", "����", "�����", "�ش���", "���׼�ũ��", "ģ����",
"��ը���", "�޴���" };

const char* fsList[] = { "����", "С��", "�л�", "��" };

const char* fpList[] = { "��԰", "Ģ��԰", "С��", "ˮ���" };

enum{
	Tab_General,
	Tab_Pass,
	Tab_Plants,
	Tab_Zombies,
	Tab_Card,
	Tab_Seed,
	Tab_FullScreen,
	Tab_Garden,

	Tab_Num
};

class Tabs
{
public:
	void init(HWND hWnd
		, const int ID[]
		, const DLGPROC Procs[]
		, const char* Name[]
		, const int count)
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		TCITEM tie;
		tie.mask = TCIF_TEXT | TCIF_IMAGE;
		tie.iImage = -1;
		for (int i = 0; i < count; ++i)
		{
			HWND hc = CreateDialog(hInst, MAKEINTRESOURCE(ID[i]), hWnd, Procs[i]);
			m_child.push_back(hc);
			MoveWindow(m_child[i], 1, 39, rect.right - rect.left - 2, rect.bottom - rect.top - 40, FALSE);
			tie.pszText = const_cast<char*>(Name[i]);
			SendMessage(hWnd, TCM_INSERTITEM, i, LPARAM(&tie));
			ShowWindow(hc, SW_HIDE);
		}
		m_curWnd = 0;
	}
	void Show(const int n)
	{
		ShowWindow(m_child[m_curWnd], SW_HIDE);
		ShowWindow(m_child[m_curWnd = n], SW_SHOW);
	}
	HWND getChild(const int n){ return m_child[n]; }
private:
	std::vector<HWND> m_child;
	int m_curWnd;
};

INT_PTR CALLBACK GeneralProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK PassProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK PlantsProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK ZombiesProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK CardProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK SeedProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK FullScreenProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK GardenProc(HWND, UINT, WPARAM, LPARAM);

const int Tab_ID[Tab_Num] = { IDD_GENERAL, IDD_PASS, IDD_PLANTS, IDD_ZOMBIES, IDD_CARD, IDD_SEED, IDD_FULLSCREEN, IDD_GARDEN };
const DLGPROC Tab_Procs[Tab_Num] = { GeneralProc, PassProc, PlantsProc, ZombiesProc, CardProc, SeedProc, FullScreenProc, GardenProc };
const char* Tab_Name[Tab_Num] = { "����", "��Խ", "ֲ��", "��ʬ", "����", "����", "ȫ��", "��԰" };
// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
INT_PTR CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				LoadSkin();

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PVZ_HELPER, szWindowClass, MAX_LOADSTRING);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PVZ_HELPER));
	// ����Ϣѭ��: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	return (int)msg.wParam;
}

Tabs htabs;

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
	LoadSkin();

	hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, WndProc);
	SetWindowPos(hWnd, NULL, 500, 100, 345, 465, SWP_NOREPOSITION);
	if (!hWnd)
	{
		return FALSE;
	}

	htabs.init(GetDlgItem(hWnd, IDC_TAB1)
		,Tab_ID
		,Tab_Procs
		,Tab_Name
		,Tab_Num);
	SetDlgItemText(htabs.getChild(Tab_General), IDC_SUNNUM, "9990");
	SetDlgItemText(htabs.getChild(Tab_General), IDC_MONEYNUM, "99999");
	SetDlgItemText(htabs.getChild(Tab_Pass), IDC_B1R, "1");
	SetDlgItemText(htabs.getChild(Tab_Pass), IDC_B1C, "3");
	SetDlgItemText(htabs.getChild(Tab_Pass), IDC_B2R, "2");
	SetDlgItemText(htabs.getChild(Tab_Pass), IDC_B2C, "10");
	SetDlgItemText(htabs.getChild(Tab_Pass), IDC_W1R, "4");
	SetDlgItemText(htabs.getChild(Tab_Pass), IDC_W1C, "10");
	SetDlgItemText(htabs.getChild(Tab_Pass), IDC_W2R, "5");
	SetDlgItemText(htabs.getChild(Tab_Pass), IDC_W2C, "3");

	INIT_LIST(htabs.getChild(Tab_General), IDC_PLIST, pList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_ZLIST, zList);
	SendDlgItemMessage(hWnd, IDC_ZLIST, CB_ADDSTRING, 0, LPARAM("���ݽ�ʬ"));
	INIT_LIST(htabs.getChild(Tab_General), IDC_BLIST, bList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_NLIST, nList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_RLIST, rList);
	INIT_LIST(htabs.getChild(Tab_Pass), IDC_MLIST, mList);
	INIT_LIST(htabs.getChild(Tab_Pass), IDC_IZELIST, izeList);
	INIT_LIST(htabs.getChild(Tab_Card), IDC_CNLIST, cnList);
	INIT_LIST(htabs.getChild(Tab_Card), IDC_CIDLIST, cnList);
	INIT_LIST(htabs.getChild(Tab_Card), IDC_CPLIST, pList);
	INIT_LIST(htabs.getChild(Tab_Card), IDC_CZLIST, czList);
	INIT_LIST(htabs.getChild(Tab_Seed), IDC_SLIST, zList);
	INIT_LIST(htabs.getChild(Tab_Garden), IDC_FLOWER_LIST, fList);
	INIT_LIST(htabs.getChild(Tab_Garden), IDC_FLOWER_SIZE, fsList);
	INIT_LIST(htabs.getChild(Tab_Garden), IDC_PLACE_LIST, fpList);

	CheckDlgButton(htabs.getChild(Tab_Plants), IDC_PNORMAL, BST_CHECKED);
	CheckDlgButton(htabs.getChild(Tab_Zombies), IDC_BOOM_NORMAL, BST_CHECKED);
	CheckDlgButton(htabs.getChild(Tab_Zombies), IDC_VISIABLE_NORMAL, BST_CHECKED);
	CheckDlgButton(htabs.getChild(Tab_Zombies), IDC_ZNORMAL, BST_CHECKED);
	CheckDlgButton(htabs.getChild(Tab_Seed), IDC_NATURAL, BST_CHECKED);

	SendDlgItemMessage(htabs.getChild(Tab_Zombies), IDC_SLIDER_TIMER, TBM_SETRANGE, TRUE, MAKELONG(0, 350));
	SendDlgItemMessage(htabs.getChild(Tab_Zombies), IDC_SLIDER_GATHER, TBM_SETRANGE, TRUE, MAKELONG(0, 800));
	SendDlgItemMessage(htabs.getChild(Tab_Zombies), IDC_SLIDER_GATHER, TBM_SETPOS, TRUE, 800);

	SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL)));
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	htabs.Show(Tab_General);
	SendMessage(hWnd, WM_INIT, 0, 0);
	return TRUE;
}

void LoadSkin()
{
	static CDllFromMem dll;
	dll.LoadLibraryFromRs(hInst, "File", MAKEINTRESOURCE(IDR_SKINDLL));
	auto pLoadSkin = (void(__stdcall*)(void*, int, char*, int, int, int))dll.GetProcAddressFromRs("SkinH_AttachRes");
	HRSRC hres = FindResource(NULL, MAKEINTRESOURCE(IDR_SKIN), "File");
	size_t skinsize = SizeofResource(NULL, hres);
	LPVOID pSkinBuffer = LockResource(LoadResource(NULL, hres));
	pLoadSkin(pSkinBuffer, skinsize, "", 0, 0, 0);
}

static void InitGame(HWND hWnd)
{
	Process process;
	switch (process.OpenByName("popcapgame1.exe"))
	{
	case NOT_FOUND:
		switch (process.OpenByName("PlantsVsZombies.exe"))
		{
		case NOT_FOUND:
			MessageBox(hWnd, "�Ҳ�����Ϸ", "����", MB_OK);
			break;
		case OPEN_FAILED:
			MessageBox(hWnd, "����Ϸʧ��", "����", MB_OK);
			break;
		case SUCCESS:
			break;
		}
		break;
	case OPEN_FAILED:
		MessageBox(hWnd, "����Ϸʧ��", "����", MB_OK);
		break;
	case SUCCESS:
		break;
	}
	if (process.IsValid())
	{
		delete pvz;
		if (process.ReadMemory(4, 0x42748e) == 0xff563de8)
		{
			pvz = new PVZ_1_0(process);
		}
		else if (process.ReadMemory(4, 0x429a83) == 0xffff7489)
		{
			pvz = new PVZ_1_2_EN_1073(process);
		}
		else if (process.ReadMemory(4, 0x428902) == 0x03c109e8)
		{
			pvz = new PVZ_1_2_CN_REPAIR(process);
		}
		else if (process.ReadMemory(4, 0x434d57) == 0x5b5d5e5f)
		{
			pvz = new PVZ_1_2_CN_ENDLESS(process);
		}
		else
		{
			pvz = NULL;
			MessageBox(hWnd, "��֧�ֵİ汾", "����", MB_OK);
			return;
		}
		pvz->Patch();
		pvz->InitExtraCode();
	}
}

INT_PTR CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDCANCEL:
			DestroyWindow(hWnd);
			break;
		case IDC_RESTART:
			SendMessage(hWnd, WM_INIT, 0, 0);
			break;
		default:
			return FALSE;
		}
		break;
	case WM_NOTIFY:
		if (wParam == IDC_TAB1)
		{
			if (LPNMHDR(lParam)->code == TCN_SELCHANGE)
			{
				htabs.Show(SendDlgItemMessage(hWnd, IDC_TAB1, TCM_GETCURSEL, 0, 0));
			}
		}
		break;
	case WM_INIT:
		InitGame(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK GeneralProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (pvz == NULL && wmId != IDC_SAVE_DIR)
			return 0;
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDC_SUN:/*�޸�����*/
			pvz->SetSun(GetDlgItemInt(hWnd, IDC_SUNNUM, NULL, TRUE));
			break;
		case IDC_MONEY:/*�޸Ľ�Ǯ*/
			pvz->SetMoney(GetDlgItemInt(hWnd, IDC_MONEYNUM, NULL, TRUE));
			break;
		case IDC_NOSUN:/*��������*/
			pvz->IgnoreSun(IsDlgButtonChecked(hWnd, IDC_NOSUN));
			break;
		case IDC_COLLECT:/*�Զ��ռ�*/
			pvz->AutoPickup(IsDlgButtonChecked(hWnd, IDC_COLLECT));
			break;
		case IDC_START_CAR:/*�������ݻ�*/
			pvz->StartCar();
			break;
		case IDC_RESET_CAR:/*�ָ����ݻ�*/
			pvz->ResetCar();
			break;
		case IDC_PLANTING:/*��ֲ��*/
			if (1)
			{
				int row = GetDlgItemInt(hWnd, IDC_ROW, NULL, TRUE) - 1;
				int col = GetDlgItemInt(hWnd, IDC_COL, NULL, TRUE) - 1;
				int type = SendDlgItemMessage(hWnd, IDC_PLIST, CB_GETCURSEL, 0, 0);
				if (type == 48)
					type = 52;
				pvz->Planting(row, col, type, IsDlgButtonChecked(hWnd, IDC_COPY));
			}
			break;
		case IDC_NOPAUSE:/*ȡ����ͣ*/
			pvz->NoPause(IsDlgButtonChecked(hWnd, IDC_NOPAUSE));
			break;
		case IDC_PUT_ZOMBIE:/*�Ž�ʬ*/
			if (1)
			{
				int row = GetDlgItemInt(hWnd, IDC_ROW, NULL, TRUE) - 1;
				int col = GetDlgItemInt(hWnd, IDC_COL, NULL, TRUE) - 1;
				int type = SendDlgItemMessage(hWnd, IDC_ZLIST, CB_GETCURSEL, 0, 0);
				if (type == 33)
					type = 36;
				pvz->PutZombie(row, col, type);
			}
			break;
		case IDC_PUT_LADDER:/*������*/
			if (1)
			{
				int row = GetDlgItemInt(hWnd, IDC_ROW, NULL, TRUE) - 1;
				int col = GetDlgItemInt(hWnd, IDC_COL, NULL, TRUE) - 1;
				pvz->PutLadder(row, col);
			}
			break;
		case IDC_PUT_GRAVE:/*��Ĺ��*/
			if (1)
			{
				int row = GetDlgItemInt(hWnd, IDC_ROW, NULL, TRUE) - 1;
				int col = GetDlgItemInt(hWnd, IDC_COL, NULL, TRUE) - 1;
				pvz->PutGrave(row, col);
			}
			break;
		case IDC_AUTO_LADDER:/*���ܴ���*/
			pvz->AutoLadder();
			break;
			//case IDC_PUT_RAKE:/*�Ŷ���*/
			//{
			//					  int row = GetDlgItemInt(hWnd, IDC_ROW, NULL, TRUE) - 1;
			//					  int col = GetDlgItemInt(hWnd, IDC_COL, NULL, TRUE) - 1;
			//					  pvz->PutRake(row, col);
			//}
			//	break;
		case IDC_BLOCK:/*�����ؿ�*/
			if (1)
			{
				int row = GetDlgItemInt(hWnd, IDC_ROW, NULL, TRUE) - 1;
				int col = GetDlgItemInt(hWnd, IDC_COL, NULL, TRUE) - 1;
				int type = SendDlgItemMessage(hWnd, IDC_BLIST, CB_GETCURSEL, 0, 0) + 1;
				pvz->SetBlock(row, col, type);
			}
			break;
		case IDC_ROWTYPE:/*�����ж�*/
			if (1)
			{
				int row = SendDlgItemMessage(hWnd, IDC_NLIST, CB_GETCURSEL, 0, 0);
				int type = SendDlgItemMessage(hWnd, IDC_RLIST, CB_GETCURSEL, 0, 0);
				pvz->SetRow(row, type);
			}
			break;
		case IDC_NO_DELETE:/*��ֹɾ��*/
			pvz->NoDelete(IsDlgButtonChecked(hWnd, IDC_NO_DELETE));
			break;
		case IDC_NO_SAVE:/*��ֹ�浵*/
			pvz->NoSave(IsDlgButtonChecked(hWnd, IDC_NO_SAVE));
			break;
		case IDC_SAVE_DIR:/*�浵Ŀ¼*/
			if (1)
			{
				OSVERSIONINFO osinfo;
				osinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
				GetVersionEx(&osinfo);
				if (osinfo.dwMajorVersion >= 6)
				{
					char RootDir[20];
					GetEnvironmentVariable("windir", RootDir, 20);
					static char cmd[80];
					sprintf(cmd, "explorer %s\\..\\ProgramData\\PopCap Games\\PlantsVsZombies\\userdata", RootDir);
					WinExec(cmd, SW_SHOW);
				}
				else
					MessageBox(hWnd, "xp������!", "����", MB_OK);
			}
			break;
		case IDC_ANYWHERE:/*���ɷ���*/
			pvz->Anywhere(IsDlgButtonChecked(hWnd, IDC_ANYWHERE));
			break;
		case IDC_FAST_BELT:/*���ʹ����ӳ�*/
			pvz->FastBelt(IsDlgButtonChecked(hWnd, IDC_FAST_BELT));
			break;
		case IDC_SHOW_HIDE:/*������С��Ϸ*/
			pvz->ShowHide(IsDlgButtonChecked(hWnd, IDC_SHOW_HIDE));
			break;
		case IDC_FULL_FOG:/*ȫ��Ũ��*/
			pvz->FullFog(IsDlgButtonChecked(hWnd, IDC_FULL_FOG));
			break;
		case IDC_SEE_FOG:/*Ũ��͸��*/
			pvz->SeeFog(IsDlgButtonChecked(hWnd, IDC_SEE_FOG));
			break;
		case IDC_SEE_VASE:/*��ƿ͸��*/
			pvz->SeeVase(IsDlgButtonChecked(hWnd, IDC_SEE_VASE));
			break;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK PassProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (pvz == NULL)
			return 0;
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDC_JMP_LV:/*�����������*/
			pvz->JmpLevel(GetDlgItemInt(hWnd, IDC_LV_NUM, NULL, TRUE));
			break;
		case IDC_MIX:/*����*/
			if (1)
			{
				int lv = GetDlgItemInt(hWnd, IDC_LV2, NULL, TRUE);
				if (lv == 0)
					lv = 1;
				int mode = SendDlgItemMessage(hWnd, IDC_MLIST, CB_GETCURSEL, 0, 0);
				if (mode > 42)
					++mode;
				if (mode == 50)
					mode = 60;
				if (mode == 51)
					mode = 70;
				pvz->MixMode(mode, lv);
			}
			break;
		case IDC_UNLOCK:/*ȫģʽ����*/
			pvz->Unlock(IsDlgButtonChecked(hWnd, IDC_UNLOCK));
			break;
		case IDC_WIN:/*ֱ�ӹ���*/
			pvz->Win();
			break;
		case IDC_LOCK:/*��������*/
			if (IsDlgButtonChecked(hWnd, IDC_LOCK))
			{
				EnableWindow(GetDlgItem(hWnd, IDC_IZELIST), FALSE);
				pvz->Lock(true, SendDlgItemMessage(hWnd, IDC_IZELIST, CB_GETCURSEL, 0, 0));
			}
			else
			{
				EnableWindow(GetDlgItem(hWnd, IDC_IZELIST), TRUE);
				pvz->Lock(false);
			}
			break;
		case IDC_LITTLE:/*С��ʬ*/
			pvz->Little(IsDlgButtonChecked(hWnd, IDC_LITTLE));
			break;
		case IDC_RAIN:/*����*/
			pvz->Rain(IsDlgButtonChecked(hWnd, IDC_RAIN));
			break;
		case IDC_STORM:/*������*/
			pvz->Storm(IsDlgButtonChecked(hWnd, IDC_STORM));
			break;
		case IDC_FORCE:/*����*/
			pvz->Force(IsDlgButtonChecked(hWnd, IDC_FORCE));
			break;
		case IDC_LIKE_COL:/*������һ��*/
			pvz->LikeCol(IsDlgButtonChecked(hWnd, IDC_LIKE_COL));
			break;
		case IDC_RUN_FAST:/*��ʬ����*/
			pvz->RunFast(IsDlgButtonChecked(hWnd, IDC_RUN_FAST));
			break;
		case IDC_START_DOOR:/*����������*/
			pvz->StartDoor(IsDlgButtonChecked(hWnd, IDC_START_DOOR));
			break;
		case IDC_STABLE_DOOR:/*�̶�������*/
			pvz->StableDoor(IsDlgButtonChecked(hWnd, IDC_STABLE_DOOR));
			break;
		case IDC_SET_DOOR:/*���ɴ�����*/
			pvz->SetDoor(
				GetDlgItemInt(hWnd, IDC_B1R, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_B1C, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_B2R, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_B2C, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_W1R, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_W1C, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_W2R, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_W2C, NULL, TRUE) - 1
				);
			break;
		default:
			return FALSE;
		}
		break;
	case WM_NOTIFY:
		if (wParam == IDC_MLIST)
		{
			if (LPNMHDR(lParam)->code == TCN_SELCHANGE)
			{
				if (SendDlgItemMessage(hWnd, IDC_MLIST, CB_GETCURSEL, 0, 0) == 0)
				{
					EnableWindow(GetDlgItem(hWnd, IDC_LV2), TRUE);
				}
				else
				{
					EnableWindow(GetDlgItem(hWnd, IDC_LV2), FALSE);
				}
			}
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK PlantsProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (pvz == NULL)
			return 0;
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDC_CORN_NO_WAIT:/*��������ȴ�*/
			pvz->CornNoWait(IsDlgButtonChecked(hWnd, IDC_CORN_NO_WAIT));
			break;
		case IDC_MAGNET_NO_WAIT:/*��������ȴ�*/
			pvz->MagnetNoWait(IsDlgButtonChecked(hWnd, IDC_MAGNET_NO_WAIT));
			break;
		case IDC_POTATO_NO_WAIT:/*��������ȴ�*/
			pvz->PotatoNoWait(IsDlgButtonChecked(hWnd, IDC_POTATO_NO_WAIT));
			break;
		case IDC_MOUTH_NO_WAIT:/*���컨��ȴ�*/
			pvz->MouthNoWait(IsDlgButtonChecked(hWnd, IDC_MOUTH_NO_WAIT));
			break;
		case IDC_PSTRONG:/*�޵�*/
			pvz->PStrong();
			break;
		case IDC_PNORMAL:/*����*/
			pvz->PNormal();
			break;
		case IDC_PWEAK:/*����*/
			pvz->PWeak();
			break;
		case IDC_NO_MARK:/*�����޺�*/
			pvz->NoMark(IsDlgButtonChecked(hWnd, IDC_NO_MARK));
			break;
		case IDC_NO_SLEEP:/*Ģ���⻽��*/
			pvz->NoSleep(IsDlgButtonChecked(hWnd, IDC_NO_SLEEP));
			break;
		case IDC_STRONG_WIND:/*ǿ����Ҷ��*/
			pvz->StrongWind(IsDlgButtonChecked(hWnd, IDC_STRONG_WIND));
			break;
		case IDC_STRONG_BEAN:/*�����㶹*/
			pvz->StrongBean(IsDlgButtonChecked(hWnd, IDC_STRONG_BEAN));
			break;
		case IDC_UMBRELLA:/*����ɡ*/
			pvz->Umbrella(IsDlgButtonChecked(hWnd, IDC_UMBRELLA));
			break;
		case IDC_NO_CD:/*����ȴ*/
			pvz->NoCD(IsDlgButtonChecked(hWnd, IDC_NO_CD));
			break;
		case IDC_LOCK_SCOOP:/*��������*/
			pvz->LockScoop(IsDlgButtonChecked(hWnd, IDC_LOCK_SCOOP));
			break;
		case IDC_ANY_MOVE:/*��ʯ������*/
			pvz->AnyMove(IsDlgButtonChecked(hWnd, IDC_ANY_MOVE));
			break;
		case IDC_NO_PURPLE:/*�Ͽ�������*/
			pvz->NoPurple(IsDlgButtonChecked(hWnd, IDC_NO_PURPLE));
			break;
		case IDC_LOCK_BUTTER:/*��������*/
			CheckDlgButton(hWnd, IDC_LOCK_CORN, BST_UNCHECKED);
			pvz->LockButter(true);
			break;
		case IDC_LOCK_CORN:/*��������*/
			CheckDlgButton(hWnd, IDC_LOCK_BUTTER, BST_UNCHECKED);
			pvz->LockButter(true);
			break;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK ZombiesProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (pvz == NULL)
			return 0;
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDC_BOOM_IM:/*���̱�ը*/
			pvz->BoomIm();
			break;
		case IDC_BOOM_NORMAL:
			pvz->BoomNormal();
			break;
		case IDC_BOOM_NEVER:
			pvz->BoomNever();
			break;
		case IDC_VISIABLE_NO:/*����*/
			pvz->VisiableNo();
			break;
		case IDC_VISIABLE_NORMAL:
			pvz->VisiableNormal();
			break;
		case IDC_VISIABLE_YES:
			pvz->VisiableYes();
			break;
		case IDC_ZSTRONG:/*�޵�*/
			pvz->ZStrong();
			break;
		case IDC_ZNORMAL:
			pvz->ZNormal();
			break;
		case IDC_ZWEAK:
			pvz->ZWeak();
			break;
		case IDC_NO_SLOW:/*���ٿ���*/
			pvz->NoSlow(IsDlgButtonChecked(hWnd, IDC_NO_SLOW));
			break;
		case IDC_NO_BUTTER:/*����*/
			pvz->NoButter(IsDlgButtonChecked(hWnd, IDC_NO_BUTTER));
			break;
		case IDC_NO3Z_GROUP:/*����3����*/
			pvz->No3zGroup(IsDlgButtonChecked(hWnd, IDC_NO3Z_GROUP));
			break;
		case IDC_NO_IMP:/*����С��*/
			pvz->NoIMP(IsDlgButtonChecked(hWnd, IDC_NO_IMP));
			break;
		case IDC_NO_ICE:/*�����޺�*/
			pvz->NoICE(IsDlgButtonChecked(hWnd, IDC_NO_ICE));
			break;
		case IDC_EATABLE:/*���˿ɱ���*/
			pvz->ZEatable(IsDlgButtonChecked(hWnd, IDC_EATABLE));
			break;
		case IDC_STOP_ZTIMER:/*��ͣˢ��ʬ*/
			pvz->StopZTimer(IsDlgButtonChecked(hWnd, IDC_STOP_ZTIMER));
			break;
		case IDC_STOP_ZOMBIES:/*��ʬ��ǰ��*/
			pvz->StopZombies(IsDlgButtonChecked(hWnd, IDC_STOP_ZOMBIES));
			break;
		case IDC_STOP_BOSS:/*��BOSS*/
			pvz->StopBoss(IsDlgButtonChecked(hWnd, IDC_STOP_BOSS));
			break;
		case IDC_BALLOON_BOOM:/*�����Ա�*/
			pvz->BalloonBoom(IsDlgButtonChecked(hWnd, IDC_BALLOON_BOOM));
			break;
		case IDC_ZTIMER_SPEEDUP:/*����ˢ��ʬ*/
			if (IsDlgButtonChecked(hWnd, IDC_ZTIMER_SPEEDUP))
				pvz->ZTimerSpeed(400 - SendMessage(GetDlgItem(hWnd, IDC_SLIDER_TIMER), TBM_GETPOS, 0, 0));
			else
				pvz->ZTimerSpeed(-1);
			break;
		case IDC_GATHER_ZOMBIE:/*����*/
			pvz->GatherZombie(IsDlgButtonChecked(hWnd, IDC_GATHER_ZOMBIE),
				(float)SendMessage(GetDlgItem(hWnd, IDC_SLIDER_GATHER), TBM_GETPOS, 0, 0));
			break;
		case IDC_KILL_ALLZ:/*��ɱ��ʬ*/
			pvz->KillAllZombies();
			break;
		case IDC_CONFUSE_ALL:/*�Ȼ�ʬ*/
			pvz->ConfuseZombies();
			break;
		default:
			return FALSE;
		}
		break;
	case WM_HSCROLL:
		if (lParam == (LPARAM)GetDlgItem(hWnd, IDC_SLIDER_TIMER)
			&& IsDlgButtonChecked(hWnd, IDC_ZTIMER_SPEEDUP))
		{
			SendMessage(hWnd, WM_COMMAND, IDC_ZTIMER_SPEEDUP, 0);
		}
		else if (lParam == (LPARAM)GetDlgItem(hWnd, IDC_SLIDER_GATHER)
			&& IsDlgButtonChecked(hWnd, IDC_GATHER_ZOMBIE))
		{
			SendMessage(hWnd, WM_COMMAND, IDC_GATHER_ZOMBIE, 0);
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK CardProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (pvz == NULL)
			return 0;
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDC_CARD_NUM:/*��������*/
			pvz->SetCardNum(GetDlgItemInt(hWnd, IDC_CNLIST, NULL, TRUE));
			break;
		case IDC_CPBTN:/*�޸�Ϊֲ��*/
			if (1)
			{
				int type = SendDlgItemMessage(hWnd, IDC_CPLIST, CB_GETCURSEL, 0, 0);
				if (type == 48)
					type = 52;
				pvz->SetCard(GetDlgItemInt(hWnd, IDC_CIDLIST, NULL, TRUE) - 1, type, IsDlgButtonChecked(hWnd, IDC_CPCOPY));
			}
			break;
		case IDC_CZBTN:/*�޸�Ϊ��ʬ*/
			pvz->SetCard(GetDlgItemInt(hWnd, IDC_CIDLIST, NULL, TRUE) - 1, SendDlgItemMessage(hWnd, IDC_CZLIST, CB_GETCURSEL, 0, 0) + 60);
			break;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK SeedProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (pvz == NULL 
			&& wmId != IDC_HELP_SEED
			&& wmId != IDC_ADD_LIST
			&& wmId != IDC_DEL_SLIST
			&& wmId != IDC_CLEAR_SLIST)
			return 0;
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDC_ADD_LIST:
			if (1)
			{
				char zname[10];
				GetDlgItemText(hWnd, IDC_SLIST, zname, 10);
				if (SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_FINDSTRING, -1, LPARAM(zname)) == LB_ERR)
				{
					SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_ADDSTRING, 0, LPARAM(zname));
				}
			}
			break;
		case IDC_DEL_SLIST:
			SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_DELETESTRING,
				SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_GETCURSEL, 0, 0), 0);
			break;
		case IDC_CLEAR_SLIST:
			SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_RESETCONTENT, 0, 0);
			break;
		case IDC_HELP_SEED:
			MessageBox(hWnd,
				"1.��Ȼˢ��ֻ�޸��˳������ӣ������б����ǵ�������Ϸ����ĺ���������\n"
				"2.��ʬ����<��ȫ>�����ӿ��ƣ�Ҳ����������Ӱ��\n"
				"3.��ĳЩ�������Ȼˢ�֣��޸��������ĳ�ָ�Ԥ�Ա�֤��Ϸ������\n"
				"4.����ˢ��ƽ���������б����޸ĳ������ӣ�Ĭ�ϲ����κν�ʬ�����⴦��",
				"ˢ��˵��", MB_OK);
			break;
		case IDC_CHG_SEED:
			if (1)
			{
				char zname[10];
				int zombies[sizeof(zList) / sizeof(*zList)] = { 0 };
				int znum = SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_GETCOUNT, 0, 0);
				if (znum == 0)
					break;
				for (int i = 0; i < znum; ++i)
				{
					SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_GETTEXT, i, LPARAM(zname));
					zombies[i] = SendDlgItemMessage(hWnd, IDC_SLIST, CB_FINDSTRING, -1, LPARAM(zname));
				}
				if (IsDlgButtonChecked(hWnd, IDC_NATURAL))
				{
					pvz->NaturalSeed(zombies, znum);
				}
				else
				{
					if (znum == 2 &&
						(zombies[0] == 20 && zombies[1] == 32
						|| zombies[0] == 32 && zombies[1] == 20))
						CheckDlgButton(hWnd, IDC_RED_LIMIT, BST_UNCHECKED);
					pvz->LimitSeed(zombies, znum, IsDlgButtonChecked(hWnd, IDC_THIEF_LIMIT), IsDlgButtonChecked(hWnd, IDC_RED_LIMIT));
				}
			}
			break;
		case IDC_RESET_SEED:/*�����޸ĳ���*/
			pvz->ResetSeed();
			break;
		case IDC_ZLEFT:
			if (1)
			{
				bool zombies[33];
				pvz->SeeLeftZombies(zombies);
				char str[300];
				char temp[10];
				str[0] = '\0';
				int j = 0;
				for (int i = 0; i < 33; ++i)
				{
					if (zombies[i])
					{
						sprintf(temp, "%d.%s\n", ++j, zList[i]);
						strcat(str, temp);
					}
				}
				if (str[0] != '\0')
					MessageBox(hWnd, str, "ʣ���������", MB_OK);
			}
			break;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK FullScreenProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (pvz == NULL)
			return 0;
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDC_FSBOOM:/*�ҽ�ȫ��*/
			pvz->FSBoom(IsDlgButtonChecked(hWnd, IDC_FSBOOM));
			break;
		case IDC_FSSQUASH:/*�ѹ�ȫ��*/
			pvz->FSSquash(IsDlgButtonChecked(hWnd, IDC_FSSQUASH));
			break;
		case IDC_FSMAGNET:/*������ȫ��*/
			pvz->FSMagnet(IsDlgButtonChecked(hWnd, IDC_FSMAGNET));
			break;
		case IDC_FSSPUTTER:/*����ȫ��*/
			pvz->FSSputter(IsDlgButtonChecked(hWnd, IDC_FSSPUTTER));
			break;
		case IDC_FSMOUSE:/*���컨ȫ��*/
			pvz->FSMouth(IsDlgButtonChecked(hWnd, IDC_FSMOUSE));
			break;
		case IDC_FSPRICK:/*�ش�ȫ��*/
			pvz->FSPrick(IsDlgButtonChecked(hWnd, IDC_FSPRICK));
			break;
		case IDC_FSSPOUT:/*����ȫ��*/
			pvz->FSSpout(IsDlgButtonChecked(hWnd, IDC_FSSPOUT));
			break;
		case IDC_FSCAT:/*èʽȫ��*/
			pvz->FSCat(IsDlgButtonChecked(hWnd, IDC_FSCAT));
			break;
		case IDC_CATTOUCH:/*�����˺�*/
			pvz->CatTouch(IsDlgButtonChecked(hWnd, IDC_CATTOUCH));
			break;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK GardenProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (pvz == NULL)
			return 0;
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDC_FLOWERNPK:
			pvz->FlowerNPK(IsDlgButtonChecked(hWnd, IDC_FLOWERNPK));
			break;
		case IDC_MEDICINE:
			pvz->Medicine(IsDlgButtonChecked(hWnd, IDC_MEDICINE));
			break;
		case IDC_CHOCOLATE:
			pvz->Chocolate(IsDlgButtonChecked(hWnd, IDC_CHOCOLATE));
			break;
		case IDC_TREENPK:
			pvz->TreeNPK(IsDlgButtonChecked(hWnd, IDC_TREENPK));
			break;
		case IDC_TREE_HIGH:
			pvz->TreeHeight(GetDlgItemInt(hWnd, IDC_TREE_HEIGHT, NULL, TRUE));
			break;
		case IDC_FLOWER_NUMBER:
			pvz->FlowerNum(GetDlgItemInt(hWnd, IDC_FLOWER_NUM, NULL, TRUE));
			break;
		case IDC_CHG_FLOWER:
			pvz->ChangeFlower(GetDlgItemInt(hWnd, IDC_FLOWER_ID, NULL, TRUE),
				SendDlgItemMessage(hWnd, IDC_FLOWER_LIST, CB_GETCURSEL, 0, 0));
			break;
		case IDC_CHG_FSIZE:
			pvz->ChangeFSize(GetDlgItemInt(hWnd, IDC_FLOWER_ID, NULL, TRUE), 
				SendDlgItemMessage(hWnd, IDC_FLOWER_SIZE, CB_GETCURSEL, 0, 0));
			break;
		case IDC_F_LEFT:
			pvz->ChangeFDir(GetDlgItemInt(hWnd, IDC_FLOWER_ID, NULL, TRUE), 1);
			break;
		case IDC_F_RIGHT:
			pvz->ChangeFDir(GetDlgItemInt(hWnd, IDC_FLOWER_ID, NULL, TRUE), 0);
			break;
		case IDC_CHG_FPLACE:
			pvz->ChangeFPlace(GetDlgItemInt(hWnd, IDC_FLOWER_ID, NULL, TRUE),
				SendDlgItemMessage(hWnd, IDC_PLACE_LIST, CB_GETCURSEL, 0, 0));
			break;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
