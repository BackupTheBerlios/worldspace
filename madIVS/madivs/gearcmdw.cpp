//=======================================================================



//@V@:Note: This file generated by vgen V1.04 (10:25:37 22 Jun 1998).



//	gearcmdw.cpp:	Source for gearCmdWindow class



//=======================================================================







#include <v/vnotice.h>	// for vNoticeDialog



#include <v/vkeys.h>	// to map keysi



#include <v/vutil.h>



#include <v/vfilesel.h>



#include <v/vicon.h>





#include "gearcmdw.h"	// our header



#include "globales.h"



#include "plugins.h"



#include <stdio.h>

#include <stdlib.h>



#include "carga_tga.h"

#include <v/vbglcnv.h>

















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
	{"&Importar textura TGA...", M_Open_TGA, isSens, notChk, noKeyLbl, noKey, noSub},
	{"&Importar textura PCX...", M_Open_PCX, isSens, notChk, noKeyLbl, noKey, noSub},
  {"&Exportar", M_SaveAs, isSens, notChk, noKeyLbl, noKey, noSub},
	{"-", M_Line, notSens, notChk, noKeyLbl, noKey, noSub},
	{"&Salir", M_Exit, isSens, notChk, noKeyLbl, noKey, noSub},
	{NULL}
      };



//@V@:EndPulldownMenu







//@V@:BeginPulldownMenu EditMenu



    static vMenu VerMenu[] =
      {
	{"&Wireframe", M_T_Wire, isSens, notChk, noKeyLbl, noKey, noSub},
	{"&Textura", M_T_Tex, isSens, notChk, noKeyLbl, noKey, noSub},
	{"&Solido", M_T_Sol, isSens, notChk, noKeyLbl, noKey, noSub},
	{"-", M_Line, notSens, notChk, noKeyLbl, noKey, noSub},
	{"&Informaci�n", M_Info, isSens, notChk, noKeyLbl, noKey, noSub},
	{NULL}

};





static vMenu TransformacionesMenu[] =

      {
	{"Escalar", M_Escalar, isSens, notChk, noKeyLbl, noKey, noSub},
	{"Rotar", M_Rotar, isSens, notChk, noKeyLbl, noKey, noSub},
	{NULL}

      };



//@V@:EndPulldownMenu







//@V@:BeginMenu StandardMenu



    static vMenu StandardMenu[] =
      {
	{"Fichero", M_Ficheros, isSens, notChk, noKeyLbl, noKey, &FileMenu[0]},
	{"Ver", M_Ver, isSens,  notChk, noKeyLbl, noKey,&VerMenu[0]},
    	{"Transformaciones", M_Trans, isSens, notChk, noKeyLbl, noKey, &TransformacionesMenu[0]},
	{NULL}
      };



//@V@:EndMenu



//@V@:BeginCmdPane ToolBar











//vbm24

#define c24_height 16

#define c24_width 16

#define c24_depth 24



  static unsigned char c24_bits[] =

  "\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1$$$nnn\244\244\244\300\300\300\211\211\211"

  "bbb\30\30\30\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\7\7\7zzz\232\232\232\232"

  "\232\232\224\224\224\255\255\255\337\337\337OOO\224\224\224NNNEEE\1\1\1\0"

  "\0\0\0\0\0\0\0\0\3\3\3\263\263\263\271\271\271\230\230\230qqq\237\237\237"

  "\207\207\207yyy\257\257\257\230\230\230DDDqqq\202\202\202\1\1\1\0\0\0\1\1"

  "\1\214\214\214ddd\330\330\330\206\206\206\231\231\231VVVWWWEEE\266\266\266"

  "\262\262\262\222\222\222sss\274\274\274...\0\0\0\40\40\40\235\235\235\236"

  "\236\236\270\270\270KKKkkklllaaaooo\270\270\270:::***xxx\352\352\352PPP\0"

  "\0\0%%%\243\243\243\253\253\253KKK\343\343\343uuu\0\0\0$$$\223\223\223\265"

  "\265\265\20\20\20\0\0\0\26\26\26\244\244\244\331\331\331uuu\332\332\332]"

  "]]^^^\220\220\220\277\277\277\234\234\234\37\37\37PPPiii\304\304\304111h"

  "hh\244\244\244NNN\\\\\\\232\232\232\217\217\217\221\221\221xxx\0\0\0\26\26"

  "\26\300\300\300WWW\17\17\17\0\0\0""888\214\214\214www***\265\265\265bbb\315"

  "\315\315\200\200\200\330\330\330\2\2\2\4\4\4\214\214\214\255\255\255HHH\0"

  "\0\0\3\3\3aaa\273\273\273TTT\2\2\2___\326\326\326FFFCCC\370\370\370\215\215"

  "\215\232\232\232\207\207\207\214\214\214\224\224\224\201\201\201iiiFFFUU"

  "U\311\311\311\206\206\206rrrXXX\215\215\215XXXddd\234\234\234\207\207\207"

  "...\234\234\234nnnooo\3\3\3\0\0\0\0\0\0yyy\334\334\334ggg\31\31\31jjj555"

  "\216\216\216YYY\231\231\231eee\273\273\273\17\17\17\26\26\26NNN\177\177\177"

  "sss\202\202\202\276\276\276^^^\263\263\263\32\32\32\0\0\0^^^\223\223\223"

  "\216\216\216qqq\334\334\334\214\214\214mmm\276\276\276\207\207\207\251\251"

  "\251III\316\316\316\306\306\306+++\0\0\0\0\0\0\0\0\0DDDccc\27\27\27\274\274"

  "\274\216\216\216GGG\220\220\220WWW\227\227\227RRR\273\273\273???\0\0\0\0"

  "\0\0\0\0\0\0\0\0\13\13\13\214\214\214\245\245\245\262\262\262\345\345\345"

  "bbb;;;\227\227\227\215\215\215\276\276\276kkk\4\4\4\0\0\0\0\0\0\0\0\0\0\0"

  "\0\0\0\0\0\0\0###\33\33\33bbb\365\365\365\275\275\275XXX^^^\7\7\7\0\0\0\0"

  "\0\0\0\0\0\0\0\0";





  static unsigned char c25_bits[] =

  "\0\0\0\0\0\0\0\0\0\0\0\0\5\0\0""4\0\0Z\0\0r\0\0x\0\0e\0\0A\0\0\12\0\0\0\0"

  "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0/\0\0p\0\0x\0\0w\0\0|\0\0\200\0\0\212"

  "\0\0\227\0\0\232\0\0G\0\0\1\0\0\0\0\0\0\0\0\0\0\0\0\0\0?\0\0u\0\0s\0\0r\0"

  "\0s\0\0u\0\0y\0\0\201\0\0\214\0\0\232\0\0\253\0\0o\0\0\1\0\0\0\0\0\0\0\0"

  "/\0\0u\0\0q\0\0o\0\0o\0\0p\0\0s\0\0u\0\0~\0\0\206\0\0\223\0\0\243\0\0\271"

  "\0\0Q\0\0\0\0\0\5\0\0p\0\0s\0\0o\0\0n\0\0l\0\0i\0\0o\0\0u\0\0}\0\0\205\0"

  "\0\221\0\0\240\0\0\261\0\0\273\0\0\17\0\0""4\0\0x\0\0r\0\0o\0\0l\0\0N\0\0"

  "@\0\0c\0\0u\0\0\177\0\0\206\0\0\221\0\0\237\0\0\260\0\0\307\0\0\\\0\0Z\0"

  "\0w\0\0s\0\0p\0\0i\0\0@\0\0""3\0\0b\0\0x\0\0\200\0\0\211\0\0\224\0\0\241"

  "\0\0\261\0\0\306\0\0\224\0\0q\0\0|\0\0u\0\0s\0\0o\0\0c\0\0b\0\0s\0\0\177"

  "\0\0\205\0\0\216\0\0\231\0\0\245\0\0\265\0\0\310\0\0\261\0\0x\0\0\200\0\0"

  "y\0\0u\0\0u\0\0u\0\0x\0\0\177\0\0\203\0\0\213\0\0\223\0\0\236\0\0\253\0\0"

  "\273\0\0\316\0\0\262\0\0e\0\0\212\0\0\201\0\0~\0\0}\0\0\177\0\0\200\0\0\205"

  "\0\0\213\0\0\222\0\0\234\0\0\246\0\0\263\0\0\301\0\0\324\0\0\233\0\0A\0\0"

  "\227\0\0\214\0\0\206\0\0\205\0\0\206\0\0\211\0\0\216\0\0\223\0\0\234\0\0"

  "\244\0\0\256\0\0\274\0\0\314\0\0\331\0\0d\0\0\12\0\0\232\0\0\232\0\0\223"

  "\0\0\221\0\0\221\0\0\224\0\0\231\0\0\236\0\0\246\0\0\256\0\0\272\0\0\307"

  "\0\0\326\0\0\316\0\0\25\0\0\0\0\0H\0\0\254\0\0\243\0\0\240\0\0\237\0\0\241"

  "\0\0\245\0\0\253\0\0\263\0\0\274\0\0\307\0\0\325\0\0\331\0\0a\0\0\0\0\0\0"

  "\0\0\1\0\0m\0\0\270\0\0\261\0\0\260\0\0\261\0\0\265\0\0\273\0\0\301\0\0\314"

  "\0\0\326\0\0\331\0\0}\0\0\2\0\0\0\0\0\0\0\0\0\0\0\1\0\0Q\0\0\274\0\0\307"

  "\0\0\306\0\0\311\0\0\316\0\0\324\0\0\331\0\0\313\0\0_\0\0\2\0\0\0\0\0\0\0"

  "\0\0\0\0\0\0\0\0\0\0\0\0\0\17\0\0Z\0\0\224\0\0\261\0\0\262\0\0\233\0\0]\0"

  "\0\22\0\0\0\0\0\0\0\0\0\0\0\0\0\0";



  static unsigned char c26_bits[] =

  "\0\0\0\0\0\0\0\0\0\0\0\0\4\10\2!B\26In5\177\205T\222\226a\200\205XNT;\15"

  "\16\12\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\0\24""2\7'\203\17$\224\23"

  "h\223]\227\270\205\237\326\236\267\333\242\312\333\244\276\315\222RYE\2\2"

  "\2\0\0\0\0\0\0\0\0\0\1\1\1OMH\267\255x\326\317{\300\341\210\273\330\306\274"

  "\335\315\270\345\312\263\342\306\277\337\265\313\336\242\317\334\245y\201"

  "m\2\3\2\0\0\0\0\0\0""06>\251\245\235\314\274\225\316\341\237\270\362\250"

  "\273\351\307\306\354\336\310\336\355\304\344\333\303\346\300\300\357\252"

  "\322\352\243\323\345\266V]Q\0\0\0\5\7\11o\212\217\231\270\232\262\320\250"

  "\246\364\254\227\355\253\233\346\274\262\363\320\303\356\342\302\363\326"

  "\310\363\312\311\370\272\322\367\260\330\361\257\311\332\274\22\23\21)9>"

  "{\261\233\226\332\237\244\353\246\241\355\244s\274\200f\244s\221\333\265"

  "\251\366\333\261\367\333\301\367\313\327\370\300\337\365\255\330\360\251"

  "\335\350\304ce[E`a\177\267\233\217\327\245\244\365\252\242\355\233f\244i"

  "R\215Z\226\322\254\250\365\324\261\365\326\300\366\301\331\365\265\340\364"

  "\252\334\351\252\344\350\302\241\240\217Tw~q\255\240\226\302\260\234\352"

  "\304\241\346\265\227\333\235\224\337\237\255\360\277\265\366\315\271\362"

  "\304\310\354\260\330\345\252\330\345\247\340\350\253\352\347\300\304\300"

  "\250X\200\206g\253\247~\265\263\221\306\303\234\334\303\242\355\265\246\350"

  "\263\303\356\274\300\342\265\302\346\254\307\337\247\316\331\243\325\333"

  "\242\341\353\250\356\354\277\305\303\250Jdmk\225\241o\233\251\205\260\267"

  "\230\303\271\240\321\253\246\325\252\273\327\243\303\326\237\313\330\246"

  "\307\322\246\316\330\246\331\336\246\345\352\262\364\360\306\254\251\225"

  "0:Cu\221\233z\210\233\203\227\226\217\251\225\220\262\233\240\270\235\263"

  "\273\227\305\302\235\314\310\244\316\311\253\324\321\253\334\334\260\354"

  "\346\277\365\360\315nma\11\11\14z\201\236\202~\242\210\211\232\216\223\220"

  "\226\234\220\242\236\225\264\246\232\311\255\243\313\267\255\313\306\266"

  "\323\317\267\343\330\276\361\347\313\343\341\307\31\31\26\0\0\0;<K\216\205"

  "\260\222\207\253\227\225\245\236\230\243\251\233\245\272\242\250\313\257"

  "\266\314\274\271\320\314\300\337\323\306\352\343\317\353\355\324jl`\0\0\0"

  "\0\0\0\1\1\2^]p\233\225\273\234\231\273\236\241\272\244\246\265\260\254\266"

  "\301\270\276\311\310\304\326\326\312\344\344\322\346\355\327\204\212}\4\4"

  "\4\0\0\0\0\0\0\0\0\0\2\2\2KIO\253\257\273\266\277\312\274\303\310\303\310"

  "\314\313\323\320\324\336\324\336\345\330\317\334\312ah^\4\4\4\0\0\0\0\0\0"

  "\0\0\0\0\0\0\0\0\0\0\0\0\17\20\20XZZ\221\226\223\256\267\260\256\273\261"

  "\232\246\233]e]\23\25\23\0\0\0\0\0\0\0\0\0\0\0\0";



   static unsigned char c27_bits[] =

  "\376\376\376\376\376\376\376\376\376\365\352\324\272\232w\366\357\346\376"

  "\376\376\326\277\201\324\300\210\376\376\376\375\373\354\355\327\213\366"

  "\355\324\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376"

  "\376\376\365\352\330a-\31\320\274\255\376\376\376\265\223u\250\206q\376\376"

  "\376\341\324\261\275\242;\367\360\333\376\376\376\376\376\376\376\376\376"

  "\371\365\357\327\303\256\372\363\346\376\376\376\272\221o\260\202]\376\376"

  "\376\322\266\235\312\256\232\376\376\376\253\203^\246\202i\376\376\376\373"

  "\367\346\367\357\277\374\371\357\360\345\327\231b<\237tN\361\342\277\366"

  "\356\342\354\336\320\344\344\342\320\316\275\320\317\276\344\344\342\356"

  "\340\320\365\354\341\346\327\300\214qM\326\304a\373\367\337\376\376\376\373"

  "\367\356\330\307\200\362\351\225\352\350\337\304\253~\316|(\332p\36\331o"

  "\35\316y%\305\252{\352\350\337\243\201e\220se\371\364\354\376\376\376\373"

  "\364\264\371\361\312\375\373\354\372\370\353\275\236h\303R\34\200\20\6i\6"

  "\2h\6\2}\16\5\277K\31\276\232d\367\362\352\372\365\352\356\336\300\337\305"

  "\242\351\330\200\211`7\216\\4\272\251\202\331q!u\11\3,\0\0\36\0\0\36\0\0"

  "*\0\0n\7\3\324f\35\271\250\177\213Z3e=2\226oT\375\373\363\361\346\333\340"

  "\321\306\305\271}\310E\26Z\1\0\34\0\0\10\0\0\10\0\0\32\0\0S\0\0\2779\23\311"

  "\267w\340\321\305\356\343\332\374\371\363\376\376\376\376\376\376\376\376"

  "\376\321\310\212\305@\25W\1\0\33\0\0\12\0\0\12\0\0\31\0\0P\0\0\2744\22\320"

  "\300\201\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376"

  "\376\376\310\306\253\327e\35k\6\2*\0\0$\0\0$\0\0)\0\0d\4\1\321Z\32\310\304"

  "\246\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376"

  "\376\366\366\366\301\224R\2639\22y\15\4y\14\4y\14\4y\15\4\2554\21\276\214"

  "M\366\366\366\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376"

  "\376\376\376\376\376\376\340\333\316\277\223X\312r\37\312r\37\312r\37\311"

  "r\37\274\217U\337\332\315\376\376\376\376\376\376\376\376\376\376\376\376"

  "\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376\345\345\345"

  "\0\0\0\0\0\0\0\0\0\0\0\0\345\345\345\376\376\376\376\376\376\376\376\376"

  "\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376"

  "\376\376\376\345\345\345\0\0\0\0\0\0\0\0\0\0\0\0\345\345\345\376\376\376"

  "\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376"

  "\376\376\376\376\376\376\376\376\376\345\345\345\0\0\0\0\0\0\0\0\0\0\0\0"

  "\345\345\345\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376"

  "\376\376\376\376\376\376\376\376\376\376\376\376\376\376\376\345\345\345"

  "\0\0\0\0\0\0\0\0\0\0\0\0\345\345\345\376\376\376\376\376\376\376\376\376"

  "\376\376\376\376\376\376";









  static vIcon icono_wire(&c24_bits[0], c24_height, c24_width,

        c24_depth);

  static vIcon icono_solid(&c25_bits[0], c24_height, c24_width,

        c24_depth);

  static vIcon icono_text(&c26_bits[0], c24_height, c24_width,

        c24_depth);

  static vIcon icono_luz(&c27_bits[0], c24_height, c24_width,

        c24_depth);





  float scale;

  static CommandObject ToolBar[] =

      {

	{C_IconButton,M_T_Wire,0,"Wireframe",&icono_wire,CA_None,isSens,NoFrame,0,0},

  {C_IconButton,M_T_Sol,0,"S�lido",&icono_solid,CA_None,isSens,NoFrame,0,0},

  {C_IconButton,M_T_Tex,0,"Textura",&icono_text,CA_None,isSens,NoFrame,0,0},

  {C_IconButton,M_T_Luces,0,"Luces",&icono_luz,CA_None,isSens,NoFrame,0,0},

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

  char msg[1024];

  vNoticeDialog note(this);





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









    strcpy(msg,RUNPATH);

    strcat(msg,"plugins");

    if (buscar_plugins(msg,plugins)!=1) {

      printf("No se encontr� ning�n plugin");

    }



    



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
//    printf("Id-->%d\n",id);
    UserDebug1(CmdEvents,"gearCmdWindow:WindowCommand(%d)\n",id)
    switch (id)



      {











	//@V@:Case M_Open



	case M_Open:



	  {



      char fich_imp[1024]="";



      vFileSelect importar(this);

      char msg[1024];

      vNoticeDialog note(this);





      int indice=0;



	  if (importar.FileSelect("Importar fichero...",fich_imp,1023,extensiones,indice)) {

      if (importar_modelo(indice,fich_imp)==1)

            modelo_cargado=1;

      

      else {

            sprintf(msg,"No se pudo importar %s",fich_imp);

            note.Notice(msg);

            modelo_cargado=0;

      }

      }

            







	    break;



	  }	//@V@:EndCase

	case M_Open_TGA:



	  {



      char fich_imp[1024]="";

      int indice=0;

      int tam_x, tam_y,j;

      char *textura_datos;

      vFileSelect importar(this);
      char msg[1024];
      char *extensiones[]={"*.tga",0};
      printf("Importar textura\n");



  	  if (importar.FileSelect("Importar textura...",fich_imp,1023,extensiones,indice))

      {





      if (textura_cargada!=1)

        glGenTextures(0, &textura);

      textura_datos = (char *) CargaTGA(fich_imp, &tam_x, &tam_y);

      if (tam_x != tam_y)

          return ;

      if (textura_datos == NULL) {

         return ;

      }





      glBindTexture(GL_TEXTURE_2D, textura);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,

                    GL_LINEAR_MIPMAP_LINEAR);

      gluBuild2DMipmaps(GL_TEXTURE_2D, 4, tam_x, tam_y, GL_RGBA,

                      GL_UNSIGNED_BYTE, textura_datos);

      free(textura_datos);

      }

      textura_cargada=1;



      if (modelo_cargado==1) {

        strcpy(msg,fich_imp);

        for (j=strlen(msg)-1;j>=0;j--)

          if ((msg[j]=='/')||(msg[j]=='\\'))

                  break;





        strcpy(model->id_textura,&msg[j+1]);

        printf("Textura activa ->%s",model->id_textura);

      }



	    break;



	  }	//@V@:EndCase

	case M_Open_PCX:



	  {



      char fich_imp[1024]="";

      int indice=0;

      int tam_x, tam_y,j;

      char *textura_datos;

      vFileSelect importar(this);

      char msg[1024];

      vNoticeDialog note(this);

      char *extensiones[]={"*.pcx;*.PCX",0};

  	  if (importar.FileSelect("Importar textura...",fich_imp,1023,extensiones,indice))

      {



      if (textura_cargada!=1)

        glGenTextures(0, &textura);

      textura_datos = (char *) CargaPCX(fich_imp, &tam_x, &tam_y);

      if (tam_x != tam_y)

          return ;

      if (textura_datos == NULL) {

         return ;

      }



      glBindTexture(GL_TEXTURE_2D, textura);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,

                    GL_LINEAR_MIPMAP_LINEAR);

      gluBuild2DMipmaps(GL_TEXTURE_2D, 4, tam_x, tam_y, GL_RGBA,

                      GL_UNSIGNED_BYTE, textura_datos);

      free(textura_datos);



      textura_cargada=1;



      }

      if (modelo_cargado==1) {

        strcpy(msg,fich_imp);

        for (j=strlen(msg)-1;j>=0;j--)

          if ((msg[j]=='/')||(msg[j]=='\\'))

                  break;





        strcpy(model->id_textura,&msg[j+1]);

        printf("Textura activa ->%s",model->id_textura);

      }



	    break;



	  }	//@V@:EndCase







	//@V@:Case M_SaveAS



	case M_SaveAs:



	  {



      char fich_imp[1024]="";

      int indice=0;



      vFileSelect importar(this);

      vNoticeDialog note(this);

      char *extensiones[]={"*.mad",0};



      if (modelo_cargado!=1)

        break;



  	  if (importar.FileSelect("Salvar MAD...",fich_imp,1023,extensiones,indice)) {

             FILE *mad_out = fopen(fich_imp, "wb");

             char magic=MAD_MAGIC;

             int j;

             fwrite(&magic,1,1,mad_out);

             fwrite(model, sizeof(modelo), 1, mad_out);

             for (j = 0; j < model->n_caras; j++)

               fwrite(&(model->triangulos[j]), sizeof(cara), 1, mad_out);

              fclose(mad_out);

             printf("Grabadas %d caras\n",j);

      }



	    break;



	  }	//@V@:EndCase







	//@V@:Case M_SaveAs







	//@V@:Case M_CloseFile



	case M_T_Wire:



	  {



      modo_dibujo=1;    //Wireframe

	    break;



	  }	//@V@:EndCase

	case M_T_Sol:



	  {



      modo_dibujo=0;    //Solido

	    break;



	  }	//@V@:EndCase



	case M_T_Tex:



	  {



      modo_dibujo=3;    //Textura

	    break;



	  }	//@V@:EndCase







	//@V@:Case M_Exit



	case M_T_Luces:



	  {



      luces*=-1;    //Wireframe

	    break;



	  }	//@V@:EndCase



	case M_Exit:



	  {







	    theApp->Exit();



	    break;





	  }	//@V@:EndCase







	//@V@:Case M_Cut



	case M_Info:



	  {



	    if (modelo_cargado==1) {

      vNoticeDialog note(this);



	    char msg[2048];



      sprintf(msg,"Caras    %d\nBytes    %d\nTextura  %s",model->n_caras,model->n_caras*sizeof(cara),model->id_textura);

      note.Notice(msg);

      }



	    break;



	  }	//@V@:EndCase







	//@V@:Case M_Copy





	case M_Escalar:



	  {



	    vNoticeDialog note(this);
	    note.Notice("No implementado");
	    break;





	  }	//@V@:EndCase







	//@V@:Case M_Paste



	case M_Rotar:



	  {



	    vNoticeDialog note(this);
	    note.Notice("No implementado");
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



