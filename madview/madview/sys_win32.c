//      Funci�n principal y de intercambio de buffers para el sistema windows. Este fichero s�lo se compila
//  si esta definida la metavariable _WIN32 (lcc-win32 y Visual C++). El compilador de Linux ignora este fichero

 
#ifdef _WIN32W3D
    
#include "opengl.h"					/*! Incluye las cabeceras OpenGL */
    
#include "render.h"					/*! Prototipos de las funciones que usan OpenGL en render.c */
    
#include "init_sys.h"				/*! Prototipos de las funciones de sys.c */
    
#include "estructuras.h"			/*! Estructuras varias */
    
#include "teclado.h"
    
#include "timer.h"
    


/*! Parche para Dev-C++ Bloodshed*/ 
#ifndef CDS_FULLSCREEN              
#define CDS_FULLSCREEN 4
#endif  /* 
 */
    

/*! Estas son algunas variables globales que s�lo utilizamos para abrir una ventana (o fullscreen) en Windows.
Esto no tiene que ver con ANSI C, es programaci�n en C utilizando el API de Windows. Puedes pas�rtelo por el
forro si no entiendes nada
*/ 
    
HDC hDC = NULL;

HGLRC hRC = NULL;

HWND hWnd = NULL;


int keys[256];

BOOL active = TRUE;

BOOL fullscreen = TRUE;




/*!
Intercambio de buffers. Esta funci�n llama a la funci�n de intercambio de buffers (Doublebuffering). Esta funci�n es dependiente
del sistema. En el c�digo de Linux hay una funci�n con el mismo nombre que hace lo mismo pero llamando a la funci�n de
intercambio de buffers propia de Linux

*/ 

void sys_swapbuffers(void)
{
    
SwapBuffers(hDC);

} 



/*! Jodida API de windows. Trata los mensajes que windows le pasa a la aplicaci�n.... blau. blau, blau. Esto es un tutorial
de OpenGL  y no de Windows.
*/ 
    
LRESULT CALLBACK WndProc(HWND hWnd, 
UINT uMsg, 
WPARAM wParam,
                              
LPARAM lParam) 
{
    
switch (uMsg)
        
 {
    
case WM_ACTIVATE:
        
 {
            
if (!HIWORD(wParam))
                
 {
                
active = TRUE;
                
}
            
            else
                
 {
                
active = FALSE;
                
}
            

return 0;
        
}
    

case WM_SYSCOMMAND:
        
 {
            
switch (wParam)
                
 {
            
case SC_SCREENSAVE:
            
case SC_MONITORPOWER:
                
return 0;
                
}
            
break;
        
}
    

case WM_CLOSE:
        
 {
            
PostQuitMessage(0);
            
return 0;
        
}
    

case WM_KEYDOWN:
        
 {
            
keys[wParam] = TRUE;
            
return 0;
        
}
    

case WM_KEYUP:
        
 {
            
keys[wParam] = FALSE;
            
return 0;
        
}
    
case WM_SIZE:
        
 {
            

return 0;
        
}
        
}
    


return DefWindowProc(hWnd, uMsg, wParam, lParam);

}





/*! Crea un "viewport" basandose en la configuraci�n. Seguimos con el API de Windows. Esto abrir� un DC (Device Context)
y se lo asignar� a OpenGL. Notad que a la funci�n se le pasan una serie de par�metros como tama�o y t�tulo de ventana, si
es fullscreen o no. la variable bits indica la profundidad (depth o bpp) del display

*/ 
    


BOOL CrearGLWindow(char *title, int width, int height, int bits,
                          int fullscreenflag) 
{
    
GLuint PixelFormat;
    
HINSTANCE hInstance;
    
WNDCLASS wc;
    
DWORD dwExStyle;
    
DWORD dwStyle;
    

PIXELFORMATDESCRIPTOR pfd;
    

        /* Vaya co�azo!! */ 
        
pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    
pfd.nVersion = 1;
    
pfd.dwFlags =
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    
pfd.iPixelType = PFD_TYPE_RGBA;
    
pfd.cColorBits = bits;
    
pfd.cRedBits = 0;
    
pfd.cRedShift = 0;
    
pfd.cGreenBits = 0;
    
pfd.cGreenShift = 0;
    
pfd.cBlueBits = 0;
    
pfd.cBlueShift = 0;
    
pfd.cAlphaBits = 0;
    
pfd.cAlphaShift = 0;
    
pfd.cAccumBits = 0;
    
pfd.cAccumRedBits = 0;
    
pfd.cAccumGreenBits = 0;
    
pfd.cAccumBlueBits = 0;
    
pfd.cAccumAlphaBits = 0;
    
pfd.cDepthBits = bits;
    
pfd.cStencilBits = 0;
    
pfd.cAuxBuffers = 0;
    
pfd.iLayerType = PFD_MAIN_PLANE;
    
pfd.bReserved = 0;
    
pfd.dwLayerMask = 0;
    
pfd.dwVisibleMask = 0;
    
pfd.dwDamageMask = 0;
    




fullscreen = fullscreenflag;
    

hInstance = GetModuleHandle(NULL);
    
wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    
wc.lpfnWndProc = (WNDPROC) WndProc;
    
wc.cbClsExtra = 0;
    
wc.cbWndExtra = 0;
    
wc.hInstance = hInstance;
    
wc.hIcon = LoadIcon(hInstance, IDI_WINLOGO);
    
wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
wc.hbrBackground = NULL;
    
wc.lpszMenuName = NULL;
    
wc.lpszClassName = "OpenGL";
    


if (!RegisterClass(&wc))
        
 {
        
MessageBox(NULL, "Error registrando la clase", "ERROR",
                    MB_OK | MB_ICONINFORMATION);
        
return FALSE;
        
}
    

if (fullscreen == TRUE)
        
 {
        
DEVMODE dmScreenSettings;
        
memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        
dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        
dmScreenSettings.dmPelsWidth = width;
        
dmScreenSettings.dmPelsHeight = height;
        
dmScreenSettings.dmBitsPerPel = bits;
        
dmScreenSettings.dmFields =
            DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
        


if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) !=
               DISP_CHANGE_SUCCESSFUL)
            
 {
            

if (MessageBox
                  (NULL,
                   "No pude cambiar a pantalla completa\nUsa modo Ventana",
                   "ErrorGL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
                
 {
                
fullscreen = FALSE;
                
}
            
            else
                
 {
                

MessageBox(NULL, "El programa se cerrara.", "ERROR",
                             MB_OK | MB_ICONSTOP);
                
return FALSE;
                
}
            
}
        
}
    

if (fullscreen == TRUE)
        
 {
        
dwExStyle = WS_EX_APPWINDOW;
        
dwStyle = WS_POPUP;
        
ShowCursor(FALSE);
        
}
    
    else
        
 {
        
dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;        //(~WS_EX_LEFTSCROLLBAR)   ;
        dwStyle = WS_POPUP | WS_CAPTION | WS_SYSMENU;
        
ShowCursor(FALSE);
        
}
    


if (!
           (hWnd =
            CreateWindowEx(dwExStyle, 
"OpenGL", 
title,
                           
dwStyle | 
WS_CLIPSIBLINGS | 
WS_CLIPCHILDREN,
                           
0, 0, 
width, height, 
NULL, 
NULL, 
hInstance,
                           
NULL)))
        
 {
        

MessageBox(NULL, "Error Creando Ventana.", "ERROR",
                     MB_OK | MB_ICONEXCLAMATION);
        
return FALSE;
        
}
    


if (!(hDC = GetDC(hWnd)))
        
 {
        

MessageBox(NULL, "Error al crear Device Context.", "ERROR",
                     MB_OK | MB_ICONEXCLAMATION);
        
return FALSE;
        
}
    

if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
        
 {
        

MessageBox(NULL, "Error obteniendo PixelFormat.", "ERROR",
                     MB_OK | MB_ICONEXCLAMATION);
        
return FALSE;
        
}
    

if (!SetPixelFormat(hDC, PixelFormat, &pfd))
        
 {
        

MessageBox(NULL, "Error asignando PixelFormat.", "ERROR",
                     MB_OK | MB_ICONEXCLAMATION);
        
return FALSE;
        
}
    

if (!(hRC = wglCreateContext(hDC)))
        
 {
        

MessageBox(NULL, "Error creando GL Rendering Context.", "ERROR",
                     MB_OK | MB_ICONEXCLAMATION);
        
return FALSE;
        
}
    

if (!wglMakeCurrent(hDC, hRC))
        
 {
        

MessageBox(NULL, "Error asignando GL Rendering Context.",
                     "ERROR", MB_OK | MB_ICONEXCLAMATION);
        
return FALSE;
        
}
    

ShowWindow(hWnd, SW_SHOW);
    
SetForegroundWindow(hWnd);
    
SetFocus(hWnd);
    


return TRUE;

}





/*!  'Mata' la ventana OpenGL, esto solucionar� muchos problemas que hemos tenido antes al 
salir de la aplicaci�n.


*/ 
    
GLvoid KillGLWindow(GLvoid) 
{
    
if (fullscreen)
        
 {
        
ChangeDisplaySettings(NULL, 0);
        
ShowCursor(TRUE);
        
}
    

if (hRC)
        
 {
        
if (!wglMakeCurrent(NULL, NULL))
            
 {
            
MessageBox(NULL, "Fallo al liberar hRC.", "Error",
                        MB_OK | MB_ICONINFORMATION);
            
}
        

if (!wglDeleteContext(hRC))   // Are We Able To Delete The RC?
        {
            
MessageBox(NULL, "Fallo al liberar hRC -2-.", "Error",
                        MB_OK | MB_ICONINFORMATION);
        
}
        
hRC = NULL;            // Set RC To NULL
        }
    

if (hDC && !ReleaseDC(hWnd, hDC)) // Are We Able To Release The DC
    {
        
MessageBox(NULL, "Fallo al liberar hDC.", "Error",
                    MB_OK | MB_ICONINFORMATION);
        
hDC = NULL;            // Set DC To NULL
    }
    

if (hWnd && !DestroyWindow(hWnd)) // Are We Able To Destroy The Window?
    {
        
MessageBox(NULL, "Fallo al liberar hWnd.", "Error",
                    MB_OK | MB_ICONINFORMATION);
        
hWnd = NULL;           // Set hWnd To NULL
    }

}




/* Otra funci�n dependiente del sistema. En Windows los mensajes de error salen en un di�logo t�pico de error.
En Linux hay otra funci�n con el mismo nombre, pero escribir� los mensajes de error por la salida est�ndar.
El par�metro es el mensaje de error
*/ 

void sys_msg(char *msg)
{
    
MessageBox(NULL, msg, "Error", MB_OK | MB_ICONEXCLAMATION);

} 




/*! Aqu� comienza todo en windows. Es el main() de C de toda la vida contaminado por el API de Windows. Lo m�s importante
es que sep�is que en lpCmdLine est� la l�nea de comandos....
*/ 

int WINAPI WinMain(HINSTANCE hInstance, 
                    HINSTANCE hPrevInstance, 
                    LPSTR lpCmdLine, 
 int nCmdShow) 
{
    
MSG msg;
    
int done = FALSE;
    



unsigned short int x_size, y_size;
    
static float tiempo_antiguo = 0;
    

        /* Inicializamos sistema (sys.c) */ 
        system_init();
    


x_size = config.SCREEN_SIZE_X;
    
y_size = config.SCREEN_SIZE_Y;
    


if (config.FULLSCREEN == 1)
        
fullscreen = TRUE;
    
    else
        
fullscreen = FALSE;
    


        /* Creamos el viewport (ventana o fullscreen) e inicializamos OpenGL. (funci�n definida arriba) */ 
        if (!CrearGLWindow("WorldSpace", x_size, y_size, 16, fullscreen))
        
 {
        
sys_msg("Fallo inesperado\n");
        
return 0;
        
}
    

        /* Hmmmm, aqui y ahora se inicializa OpenGL. Esat funci�n est� implementada en render.c */ 
        
if (init_gl() != 0)
        
 {
        
MessageBox(NULL, "Fallo de inicializacion.", "Error",
                    MB_OK | MB_ICONEXCLAMATION);
        
return FALSE;
        
}
    


        /* Este es el bucle principal. Primero trata los mensajes del API de Windows y luego llama a la funci�n
           gl_renderiza_escena, definida en render.c. �Tambi�n est� al loro por si se pulsa la tecla  ESC
         */ 
        tiempo_antiguo = get_timer();
    

while (!done) {
        
intervalo = get_timer() - tiempo_antiguo;
        
tiempo_antiguo = get_timer();
        


if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            
if (msg.message == WM_QUIT) {
                
done = TRUE;
            
}
            
            else {
                
TranslateMessage(&msg);
                
DispatchMessage(&msg);
            
}
        

}
        
        else {
            
gl_renderiza_escena();
            
if (!active || keys[VK_ESCAPE])
                
done = TRUE;
            
if (!active || keys[VK_UP])
                
tecla_pulsada(CURSOR_ARR);
            

if (!active || keys[VK_DOWN])
                
tecla_pulsada(CURSOR_ABA);
            

if (!active || keys[VK_LEFT])
                
tecla_pulsada(CURSOR_IZQ);
            

if (!active || keys[VK_RIGHT])
                
tecla_pulsada(CURSOR_DER);
        


}
    
}
    


fclose(logs);
    

        /* Liberaci�n */ 
        
KillGLWindow();
    

return (msg.wParam);


}



#endif  /* 
 */
