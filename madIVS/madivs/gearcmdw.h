//	gearcmdw.h:	Header for gearcmdw class

//=======================================================================



#ifndef gearCMDW_H

#define gearCMDW_H



#include <v/vcmdwin.h>	// So we can use vCmdWindow

#include <v/vmenu.h>	// For the menu pane

#include <v/vutil.h>	// For V Utilities

#include <v/vcmdpane.h> // command pane

#include <v/vtimer.h>	// Timer



#include "globales.h"

#include "plugins.h"



#ifdef vDEBUG

#include <v/vdebug.h>

#endif



#include "gearcnv.h"	// gearOGLCanvasPane





const ItemVal M_Open_TGA =    40000;
const ItemVal M_Open_PCX =    40007;
const ItemVal M_T_Wire =    40001;
const ItemVal M_T_NULL =    99999;
const ItemVal M_T_Tex =     40002;
const ItemVal M_T_Sol =     40003;
const ItemVal M_Ficheros =  40004;
const ItemVal M_Ver =       40005;
const ItemVal M_T_Luces =     40006;
const ItemVal M_Info =     40008;
const ItemVal M_Rotar =     40100;
const ItemVal M_Escalar =     40101;



    class gearCmdWindow;



    class gearAuxTimer : public vTimer

      {

      public:		//---------------------------------------- public

	gearAuxTimer(gearCmdWindow* cw) { cmdw = cw; }

	~gearAuxTimer() {}

	virtual void TimerTick();

      private:		//--------------------------------------- private

	gearCmdWindow* cmdw;

      };



    class gearCmdWindow : public vCmdWindow

      {

	friend int AppMain(int, char**);	// allow AppMain access



      public:		//---------------------------------------- public

	gearCmdWindow(char*, int, int);

	virtual ~gearCmdWindow();

	virtual void WindowCommand(ItemVal id, ItemVal val, CmdType cType);

	virtual void KeyIn(vKey keysym, unsigned int shift);

	gearAuxTimer* GetgearAuxTimer() {return _auxTimer;}// Aux Timer



      protected:	//--------------------------------------- protected



      private:		//--------------------------------------- private



	// Standard elements

	vMenuPane* gearMenu;		// For the menu bar

	gearOGLCanvasPane* gearCanvas;		// For the canvas

	vCommandPane* gearCmdPane;	// for the command pane

	gearAuxTimer* _auxTimer;	// Aux Timer



	// Dialogs associated with CmdWindow





      };






#endif

