; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTETRISView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TETRIS.h"
LastPage=0

ClassCount=6
Class1=CTETRISApp
Class2=CTETRISDoc
Class3=CTETRISView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CGameSetting
Resource3=IDD_GAME_SETTING

[CLS:CTETRISApp]
Type=0
HeaderFile=TETRIS.h
ImplementationFile=TETRIS.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CTETRISDoc]
Type=0
HeaderFile=TETRISDoc.h
ImplementationFile=TETRISDoc.cpp
Filter=N

[CLS:CTETRISView]
Type=0
HeaderFile=TETRISView.h
ImplementationFile=TETRISView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_GAME_LEVEL5


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_ABOUT_GAMERULE




[CLS:CAboutDlg]
Type=0
HeaderFile=TETRIS.cpp
ImplementationFile=TETRIS.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_GAME_START
Command2=ID_GAME_PAUSE
Command3=ID_GAME_END
Command4=ID_GAME_SETTING
Command5=ID_GAME_EXIT
Command6=ID_GAME_LEVEL1
Command7=ID_GAME_LEVEL2
Command8=ID_GAME_LEVEL3
Command9=ID_GAME_LEVEL4
Command10=ID_GAME_LEVEL5
Command11=ID_SHOW_GRID
Command12=ID_PLAY_MUSIC
Command13=ID_ABOUT_ABOUT
Command14=ID_ABOUT_GAMERULE
CommandCount=14

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_GAME_START
Command2=ID_GAME_PAUSE
Command3=ID_GAME_END
Command4=ID_GAME_EXIT
Command5=ID_GAME_SETTING
Command6=ID_ABOUT_ABOUT
CommandCount=6

[DLG:IDD_GAME_SETTING]
Type=1
Class=CGameSetting
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO_GAMELEVEL,combobox,1344480450
Control4=65535,static,1342308352
Control5=IDC_CHECK_MUSIC,button,1342242819
Control6=IDC_CHECK_GRID,button,1342242819

[CLS:CGameSetting]
Type=0
HeaderFile=GameSetting.h
ImplementationFile=GameSetting.cpp
BaseClass=CDialog
Filter=D
LastObject=CGameSetting
VirtualFilter=dWC

