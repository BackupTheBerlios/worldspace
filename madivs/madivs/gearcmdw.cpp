//=======================================================================
//@V@:Note: This file generated by vgen V1.04 (10:25:37 22 Jun 1998).
//	gearcmdw.cpp:	Source for gearCmdWindow class
//=======================================================================

#include <v/vnotice.h>	// for vNoticeDialog
#include <v/vkeys.h>	// to map keysi
#include <v/vutil.h>
#include <v/vfilesel.h>

#include "gearcmdw.h"	// our header
#include "globales.h"
#include "plugins.h"


static char *filter[]={
      "*","md2",0};

plugin_info *plugins;
extern modelo *model;

//	Start defines for the main window with 100

//@V@:BeginIDs
    enum {
	m_FirstCmd = 100, // Dummy Command
	cmdAuxTimer,	// AuxTimer
	blkLast		// Last item
      };
//@V@:EndIDs

//@V@:BeginPulldownMenu FileMenu
    static vMenu FileMenu[] =
      {
	{"&Importar...", M_Open, isSens, notChk, noKeyLbl, noKey, noSub},
	{"&Exportar", M_SaveAs, isSens, notChk, noKeyLbl, noKey, noSub},
	{"&Importar textura...", M_Open_T, isSens, notChk, noKeyLbl, noKey, noSub},
	{"-", M_Line, notSens, notChk, noKeyLbl, noKey, noSub},
	{"E&xit", M_Exit, isSens, notChk, noKeyLbl, noKey, noSub},
	{NULL}
      };
//@V@:EndPulldownMenu

//@V@:BeginPulldownMenu EditMenu
    static vMenu VerMenu[] =
      {
	{"&Wireframe", M_T_Wire, isSens, notChk, noKeyLbl, noKey, noSub},
	{"&Textura", M_T_Tex, isSens, notChk, noKeyLbl, noKey, noSub},
	{NULL}
      };
//@V@:EndPulldownMenu

//@V@:BeginMenu StandardMenu
    static vMenu StandardMenu[] =
      {
	{"&Fichero", M_Ficheros, isSens, notUsed, notUsed, noKey, &FileMenu[0]},


	{"&Ver", M_Ver, isSens, notUsed, notUsed, noKey, &VerMenu[0]},
	{NULL}
      };
//@V@:EndMenu

//@V@:BeginCmdPane ToolBar
    static CommandObject ToolBar[] =
      {
	{C_Button,M_Exit,0,"Salir",NoList,CA_None,isSens,NoFrame,0,0},
	{C_Button,M_T_Wire,0,"Wireframe",NoList,CA_None,isSens,NoFrame,0,0},
	{C_Button,M_T_Tex,0,"Textura",NoList,CA_None,isSens,NoFrame,0,0},
	{C_EndOfList,0,0,0,0,CA_None,0,0,0}
      };
//@V@:EndCmdPane

//====================>>> gearAuxTimer::TimerTick <<<====================
  void gearAuxTimer::TimerTick()
  {
	cmdw->WindowCommand(cmdAuxTimer, cmdAuxTimer, C_Button); // update clock
  }

//====================>>> gearCmdWindow::gearCmdWindow <<<====================
  gearCmdWindow::gearCmdWindow(char* name, int width, int height) :
    vCmdWindow(name, width, height)
  {
    UserDebug1(Constructor,"gearCmdWindow::gearCmdWindow(%s) Constructor\n",name)

    // The Menu Bar
    gearMenu = new vMenuPane(StandardMenu);
    AddPane(gearMenu);

    // The Command Pane
    gearCmdPane = new vCommandPane(ToolBar);
    AddPane(gearCmdPane);

    // The Canvas
    gearCanvas = new gearOGLCanvasPane;
    AddPane(gearCanvas);

    _auxTimer = new gearAuxTimer(this);	// create aux timer
    _auxTimer->TimerSet(30);		// 30 ms second intervals
    // Associated dialogs

    buscar_plugins("plugins",plugins);

    
    // Show Window

    ShowWindow();
    WindowCommand(cmdAuxTimer,cmdAuxTimer,C_Button);	// update clock
  }


//====================>>> gearCmdWindow::~gearCmdWindow <<<====================
  gearCmdWindow::~gearCmdWindow()
  {

    UserDebug(Destructor,"gearCmdWindow::~gearCmdWindow() destructor\n")

    // Now put a delete for each new in the constructor.

    delete gearMenu;
    delete gearCanvas;
    delete gearCmdPane;
    _auxTimer->TimerStop();	// end it
    delete _auxTimer;	// free it
  }

//====================>>> gearCmdWindow::KeyIn <<<====================
  void gearCmdWindow::KeyIn(vKey keysym, unsigned int shift)
  {
    vBeep();
    vCmdWindow::KeyIn(keysym, shift);
  }

//====================>>> gearCmdWindow::WindowCommand <<<====================
  void gearCmdWindow::WindowCommand(ItemVal id, ItemVal val, CmdType cType)
  {
    // Default: route menu and toolbar commands here


    UserDebug1(CmdEvents,"gearCmdWindow:WindowCommand(%d)\n",id)

    switch (id)
      {


	//@V@:Case M_Open
	case M_Open:
	  {
      char fich_imp[1024]="";
      vFileSelect importar(this);
      int indice=0;
	    importar.FileSelect("Importar fichero...",fich_imp,1023,extensiones,indice);
      printf("%d->%s\n",indice,fich_imp);
      importar_modelo(indice,fich_imp);

	    break;
	  }	//@V@:EndCase

	//@V@:Case M_Save
	case M_Save:
	  {
	    vNoticeDialog note(this);
	    note.Notice("Save");
	    break;
	  }	//@V@:EndCase

	//@V@:Case M_SaveAs
	case M_SaveAs:
	  {
	    vNoticeDialog note(this);
	    note.Notice("Save As");
	    break;
	  }	//@V@:EndCase

	//@V@:Case M_CloseFile
	case M_CloseFile:
	  {
	    vNoticeDialog note(this);
	    note.Notice("Close File");
	    break;
	  }	//@V@:EndCase

	//@V@:Case M_Exit
	case M_Exit:
	  {

	    theApp->Exit();
	    break;
	  }	//@V@:EndCase

	//@V@:Case M_Cut
	case M_Cut:
	  {
	    vNoticeDialog note(this);
	    note.Notice("Cut");
	    break;
	  }	//@V@:EndCase

	//@V@:Case M_Copy
	case M_Copy:
	  {
	    vNoticeDialog note(this);
	    note.Notice("Copy");
	    break;
	  }	//@V@:EndCase

	//@V@:Case M_Paste
	case M_Paste:
	  {
	    vNoticeDialog note(this);
	    note.Notice("Paste");
	    break;
	  }	//@V@:EndCase

	//@V@:Case auxTimer
	case cmdAuxTimer:	// Event from aux timer
	  {
	    gearCanvas->TimerAnimate();
	    break;
	  }	//@V@:EndCase
	default:		// route unhandled commands up
	  {
	    vCmdWindow::WindowCommand(id, val, cType);
	    break;
	  }
      }
  }
