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

typedef struct {
    GLfloat x, y, z, u, v;
} Vertex;

typedef struct {
    Vertex vertex[3];
} Triangle;


const float piover180 = 0.0174532925f;

class MyGLWidget:public QGLWidget {
  Q_OBJECT private:



  public:
    bool blend;

  MyGLWidget(QWidget * parent = 0):QGLWidget(parent) {

        initializeGL();

        show();
        setFocusPolicy(Qt::StrongFocus);
        setEnabled(true);
  } protected:
    void initializeGL() {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClearDepth(1.0);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
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

        QFont Fuente("Helvetica", 12);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glTranslatef(-1.5f, 0.0f, -6.0f);

        glBegin(GL_TRIANGLES);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glEnd();

        glTranslatef(3.0f, 0.0f, 0.0f);

        glBegin(GL_QUADS);
        glVertex3f(-1.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glEnd();
        if (blend)
            renderText(50, 50, QString("No hay ningun fichero cargado"),
                       Fuente);
        return;
    }

    void keyPressEvent(QKeyEvent * e) {
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

        case Qt::Key_F:



            break;

        case Qt::Key_Up:

            break;

        case Qt::Key_Down:

            break;

        case Qt::Key_Left:


            break;

        case Qt::Key_Right:


            break;

        case Qt::Key_PageUp:

            break;

        case Qt::Key_PageDown:

            break;

        case Qt::Key_Escape:
            close();

        }
    }


};
