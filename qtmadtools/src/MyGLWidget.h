/***************************************************************************
 *   Copyright (C) 2008 by tyler   *
 *   tyler@khand   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QGLWidget>
#include <QtGui>
#include <QFileDialog>
#include "plugins.h"
#include "tga.h"



typedef struct {
    GLfloat x, y, z, u, v;
} Vertex;

typedef struct {
    Vertex vertex[3];
} Triangle;

typedef struct {

  float rad, wid;

} Profile;







class MyGLWidget:public QGLWidget {
  Q_OBJECT private:



  public:
   bool blend;
   QWidget *myParent;
   int rX,rY;
   char last_file_model[1024];
   char last_file_texture[1024];


   MyGLWidget(QWidget * parent = 0):QGLWidget(parent) {

        initializeGL();
        myParent = parent->parentWidget();
        show();
        setFocusPolicy(Qt::StrongFocus);
        setEnabled(true);
    } 



   protected slots: virtual void ImportarModelo() {

        QString filename;
	QByteArray c_filename;
	char *fich_imp,*extension;
	char msg[1024];
	int plugin_elegido=-1;

        printf("Import Model Called!!\n");
        filename = QFileDialog::getOpenFileName(this,
     tr("Open Image"), QString(last_file_model), QString(qextensiones));
        c_filename=filename.toAscii();
	//strcpy(c_filename,(char *)filename.toAscii());
	fich_imp=c_filename.data();
	printf("Return : %s\n",c_filename.data());
	//QMessageBox::information ( this, tr("Warning"),filename);

	extension = &fich_imp[strlen(fich_imp) - 3];
	if (!filename.isNull()) {
		strcpy(last_file_model,fich_imp);
		printf("Extension: %s\n", extension);
        	for (int i = 0; i < numero_plugins; i++)
            		if (strstr(plugins[i].extension, extension) == NULL)
                		continue;
            		else
                		plugin_elegido = i;
		if (plugin_elegido>-1)
			if (importar_modelo(plugin_elegido,c_filename.data())==1) {
				modelo_cargado=1;
				
			}
			else {
				sprintf(msg,"No se pudo importar %s",fich_imp);
				QMessageBox::information ( this, tr("Error"),msg);
				modelo_cargado=0;
			}
		else
			modelo_cargado=0;
	}
      
	return;

    }

   protected slots: virtual void LoadTexture() {


        QString filename;
	QByteArray c_filename;
	char *fich_imp,*extension;

        int indice=0;
        int tam_x, tam_y,j;
        char *textura_datos;
        char msg[1024];
        char extensiones[]="Ficheros TGA (*.tga)";
        filename = QFileDialog::getOpenFileName(this,tr("Open Image"), QString(last_file_texture),extensiones);
        c_filename=filename.toAscii();
	fich_imp=c_filename.data();
	printf("Importar textura: %s\n",c_filename.data());
	extension = &fich_imp[strlen(fich_imp) - 3];
	if (!filename.isNull()) {
		strcpy(last_file_texture,fich_imp);
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, tam_x, tam_y, GL_RGBA,GL_UNSIGNED_BYTE, textura_datos);
		free(textura_datos);
	
		textura_cargada=1;
		if (modelo_cargado==1) {
			strcpy(msg,fich_imp);
			for (j=strlen(msg)-1;j>=0;j--)
			if ((msg[j]=='/')||(msg[j]=='\\'))
				break;
	
			strcpy(model->id_textura,&msg[j+1]);
			printf("Textura activa ->%s",model->id_textura);
			modo_dibujo=3;
		}
		updateGL();	
	
      }
}

  protected:
    void initializeGL() {
        
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat) 1.3, 0.01f, 100.0f);
	glGetDoublev(GL_PROJECTION_MATRIX, &matriz_proyeccion_A[0][0]);
	glLoadMatrixd(&matriz_proyeccion_A[0][0]);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,zoom);
	glGetDoublev(GL_MODELVIEW_MATRIX, &matriz_modelview[0][0]);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  	glEnable(GL_ALPHA_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);    /* SMOOTH SHADING */
	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);
	glLineWidth(6);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse1);	
 	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
    }

    void resizeGL(int width, int height) {
        height = height ? height : 1;

        glViewport(0, 0, (GLint) width, (GLint) height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f,
                       100.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void paintGL() {


	int j;
	float view_x1, view_x2, view_x3, view_y1, view_y2, view_y3, view_z1,        view_z2, view_z3;
	

        QFont Fuente("Helvetica", 12);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(-1.5f, 0.0f, -6.0f);
	if (!modelo_cargado)
            renderText(50, 50, QString("No hay ningun fichero cargado"),
                       Fuente);
        else {

    		glMatrixMode(GL_PROJECTION);
		glLoadMatrixd(&matriz_proyeccion_A[0][0]);

	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
    	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);	
    	glLoadMatrixd(&matriz_modelview[0][0]);

  	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.1f,0.0f,0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.1f,0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,10.1f);
	glEnd();

	glColor3f(1.0f,1.0f,1.0f);

  	if (luces==1) {
		glEnable(GL_LIGHTING);	
	}
	if ((modo_dibujo==3)&&(textura_cargada==1))
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);
	if ((modo_dibujo==3)&&(textura_cargada==1))
		glBindTexture(GL_TEXTURE_2D, textura);
	for (j = 0; j < model->n_caras; j++) {
	        view_x1 = model->triangulos[j].vertices[0].x;
		view_y1 = model->triangulos[j].vertices[0].y;
		view_z1 = model->triangulos[j].vertices[0].z;
		view_x2 = model->triangulos[j].vertices[1].x;
		view_y2 = model->triangulos[j].vertices[1].y;
		view_z2 = model->triangulos[j].vertices[1].z;
		view_x3 = model->triangulos[j].vertices[2].x;
		view_y3 = model->triangulos[j].vertices[2].y;
		view_z3 = model->triangulos[j].vertices[2].z;
	        if (modo_dibujo==0) {
			glLineWidth(6);
		          glBegin(GL_TRIANGLES);
		}
	        else if (modo_dibujo==1){
			glLineWidth(1);
			glBegin(GL_LINE_LOOP);
		}
		else if (modo_dibujo==3) {
			glLineWidth(6);
			glBegin(GL_TRIANGLES);
        	}
	        if ((modo_dibujo==3)&&(textura_cargada==1))
			glTexCoord2f(model->triangulos[j].vertices[0].u,model->triangulos[j].vertices[0].v);
			glNormal3f(model->triangulos[j].vertices[0].Nx,model->triangulos[j].vertices[0].Ny,model->triangulos[j].vertices[0].Nz);
			glVertex3f(view_x1, view_y1, view_z1);
	        if ((modo_dibujo==3)&&(textura_cargada==1))
		          glTexCoord2f(model->triangulos[j].vertices[1].u,model->triangulos[j].vertices[1].v);
	        glNormal3f(model->triangulos[j].vertices[1].Nx,model->triangulos[j].vertices[1].Ny,

		model->triangulos[j].vertices[1].Nz);
		glVertex3f(view_x2, view_y2, view_z2);
		if ((modo_dibujo==3)&&(textura_cargada==1))
			glTexCoord2f(model->triangulos[j].vertices[2].u,model->triangulos[j].vertices[2].v);
	        glNormal3f(model->triangulos[j].vertices[2].Nx,model->triangulos[j].vertices[2].Ny,model->triangulos[j].vertices[2].Nz);
	        glVertex3f(view_x3, view_y3, view_z3);
        	glEnd();	
	}
        return;
    }
}

    void keyPressEvent(QKeyEvent * e) {

        printf("Event\n");
        switch (e->key()) {
        case Qt::Key_B:
            if (blend) {
                blend = false;
                glDisable(GL_BLEND);
                glEnable(GL_DEPTH_TEST);
            } else {
                blend = true;
                glEnable(GL_BLEND);
                glDisable(GL_DEPTH_TEST);
            }

            updateGL();
            break;

        case Qt::Key_L:
		
		luces=(luces==0)?1:0;
		printf("Light trigger pressed %d\n",luces);
                updateGL();

            break;

        case Qt::Key_Up:
		
		
		LightPosition1[1] +=  0.1f;
		
		updateGL();
            	break;

        case Qt::Key_Down:
		LightPosition1[1] -=  0.1f;
		
		updateGL();
            break;

        case Qt::Key_Left:
		LightPosition1[0] -=  0.1f;
		updateGL();
            break;

        case Qt::Key_Right:
		LightPosition1[0] +=  0.1f;
		updateGL();

            break;

        case Qt::Key_PageUp:

            break;

        case Qt::Key_PageDown:

            break;

        

	case Qt::Key_Home:
  		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glGetDoublev(GL_MODELVIEW_MATRIX, &matriz_modelview[0][0]);
		updateGL();

            break;
	case Qt::Key_End:
		modo_dibujo=(modo_dibujo>3)?0:++modo_dibujo;
		printf("Mode triggered %d\n",modo_dibujo);
  		updateGL();

            break;
	case Qt::Key_Escape:

            myParent->close();


        }
    }

void mouseMoveEvent   (QMouseEvent *event ) {

	
	  int x,y;
	  x=event->x();
	  y=event->y();
	  glMatrixMode(GL_MODELVIEW);
          glLoadMatrixd(&matriz_modelview[0][0]);
          glRotatef(x-rX,matriz_modelview[0][1],matriz_modelview[1][1],matriz_modelview[2][1]);
          glGetDoublev(GL_MODELVIEW_MATRIX, &matriz_modelview[0][0]);
          glLoadMatrixd(&matriz_modelview[0][0]);
          glRotatef(y-rY,matriz_modelview[0][0],matriz_modelview[1][0],matriz_modelview[2][0]);
          glGetDoublev(GL_MODELVIEW_MATRIX, &matriz_modelview[0][0]);
	  
	  rX=x;rY=y;
	  updateGL();
	
}

void mousePressEvent   (QMouseEvent *event ) {

	  rX=event->x();
	  rY=event->y();

}

void wheelEvent  (QWheelEvent *event ) {
	
	int numDegrees = event->delta() / 8;
     	int numSteps = numDegrees / 15;

     	zoom=zoom+((float)numSteps/50);
	//printf("Zoom triggered %f\n",zoom);

	matriz_modelview[3][2]=(double)zoom;
     	updateGL();
	event->accept();
        



}


};
