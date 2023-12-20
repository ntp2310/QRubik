#include "openglwindow.h"

OpenGLWindow::OpenGLWindow(QWindow *parent):
    choosenCubie(nullptr), cubie(nullptr), isPressed(false),
    cameraOn(false), execute(false), pause(false), track(false), configMode(false),
    facedir(0), angle(0), coord(-1), selectedCubie(-1), currentColor(0), idx(0)
{
    setSurfaceType(QWindow::OpenGLSurface);

    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                _data[i][j][k] = i;
            }
        }
    }

    rubix = new RubixCube(_data, 3);

    m_model.rotateX(35.0);
    m_model.rotateY(-45.0);

    normX.set(1.0, 0.0, 0.0);
    normY.set(0.0, 1.0, 0.0);
    normZ.set(0.0, 0.0, 1.0);

    eye.set(0.0, 0.0, 15.0);
    target.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);

    normX = m_model * normX;
    normY = m_model * normY;
    normZ = m_model * normZ;

    m_view.lookAt(eye, target, up);

    connect(this, &OpenGLWindow::frameSwapped, this, &OpenGLWindow::updateGL);
}

OpenGLWindow::~OpenGLWindow()
{
    delete rubix;
    rubix = nullptr;

    if (choosenCubie)
    {
        delete choosenCubie;
        choosenCubie = nullptr;
    }
}

void OpenGLWindow::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE_ARB);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glClearColor(191.0f/255.0f, 200.0f/255.0f, 207.0f/255.0f, 1.0f);
    glFrontFace(GL_CCW);

    //Shading states
    glShadeModel(GL_SMOOTH);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //Depth states
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    setupLight();
}

void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_MODELVIEW);

    if (!cameraOn) render(false);

    glFlush();
}

void OpenGLWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    aspect = (GLfloat)w/(GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    m_projection.setFrustum(45.0f, aspect, 0.01f, 100.0f);
    glMultMatrixf(m_projection.get());

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWindow::setupLight()
{
    float specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float ambient[] = { 0.15f, 0.15f, 0.15f, 1.0f };
    float spotex[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float pos0[] = { 7.0f, -5.0f, 3.5f, 0.0f };
    float pos1[] = { 2.0f, 5.0f, -2.5f, 0.0f };
    float pos2[] = { 0.0f, 2.5f, 6.5f, 0.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_SUM_EXT);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, pos0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, spotex);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0f);

    //glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, spotex);
    glLightfv(GL_LIGHT1, GL_POSITION, pos1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0f);

    glEnable(GL_LIGHT2);

    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, spotex);
    glLightfv(GL_LIGHT2, GL_POSITION, pos2);
    //glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0f);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void OpenGLWindow::render(bool select)
{
    glLoadIdentity();

    glMultMatrixf(m_view.get());

    if (track && !norm.isInvalid())
    {
        m_model.rotate(angle, norm);
        randRotation.setRotate(angle, norm);

        normX = randRotation * normX;
        normY = randRotation * normY;
        normZ = randRotation * normZ;
    }

    angle = 0;

    glPushMatrix();

    glMultMatrixf(m_model.get());

    rubix->render(isPressed);

    if (!select && facedir)
    {
        glDisable(GL_LIGHTING);

        void* font = GLUT_STROKE_MONO_ROMAN;

        glLineWidth(4.0f);
        glColor3f(1.0, 1.0, 1.0);

        unsigned char front[] = "FRONT";
        glPushMatrix();
        glTranslatef(-1.25, 0, 2.5);
        glScalef(0.005, 0.005, 0.005);
        glutStrokeString(font, front);
        glPopMatrix();

        unsigned char right[] = "RIGHT";
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-1.25, 0, 2.5);
        glScalef(0.005, 0.005, 0.005);
        glutStrokeString(font, right);
        glPopMatrix();

        unsigned char back[] = "BACK";
        glPushMatrix();
        glRotatef(180, 0, 1, 0);
        glTranslatef(-1.05, 0, 2.5);
        glScalef(0.005, 0.005, 0.005);
        glutStrokeString(font, back);
        glPopMatrix();

        unsigned char left[] = "LEFT";
        glPushMatrix();
        glRotatef(-90, 0, 1, 0);
        glTranslatef(-1.05, 0, 2.5);
        glScalef(0.005, 0.005, 0.005);
        glutStrokeString(font, left);
        glPopMatrix();

        unsigned char top[] = "UP";
        glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        glTranslatef(-0.55, 0, 2.5);
        glScalef(0.005, 0.005, 0.005);
        glutStrokeString(font, top);
        glPopMatrix();

        unsigned char down[] = "DOWN";
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(-1.1, 0, 2.5);
        glScalef(0.005, 0.005, 0.005);
        glutStrokeString(font, down);
        glPopMatrix();

        glEnable(GL_LIGHTING);
    }

    glPopMatrix();
}

int OpenGLWindow::pick(int x, int y)
{
    GLint viewport[4] = {0, 0, width(), height()};

    glSelectBuffer(BUFSIZE, selectBuf);
    (void) glRenderMode(GL_SELECT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    pickMatrix((GLfloat)x, (GLfloat)(viewport[3] - y), 4.0f, 4.0f, viewport);

    glMultMatrixf(m_projection.get());

    glMatrixMode(GL_MODELVIEW);

    render(true);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glFlush();

    unsigned int hits = glRenderMode(GL_RENDER);

    if (hits != 0)
    {
        unsigned int i;
        GLuint names, *ptr, minZ, *ptrNames;

        ptr = (GLuint *) selectBuf;
        ptrNames = ptr;
        minZ = 0xffffffff;
        for (i = 0; i < hits; i++)
        {
            names = *ptr;
            ptr++;
            if (*ptr < minZ)
            {
                minZ = *ptr;
                ptrNames = ptr + 2;
            }

            ptr += names + 2;
        }

        return *ptrNames;
    }

    return 0;
}

void OpenGLWindow::mouseDrag(int cubieIdx)
{
    int face = cubieIdx % 10;

    float X = normX.angle(norm);
    float Y = normY.angle(norm);
    float Z = normZ.angle(norm);

    Moviment* moviment = nullptr;

    if (!choosenCubie) return;

    if (face == 0 || face == 1)
    {
        if ((Z > 120 || Z < 60) && (coord == -1 || coord == 2) && ((Z < Y && Z < 90) || (Z > Y && Z > 90)))
        {
            angle *= cos(Z * DEG2RAD);

            if (coord == -1)
                moviment = new Moviment(choosenCubie->position, 0, 2, angle, 1);

            rubix->setDelta(angle);
            coord = 2;
        }

        else if ((Y > 120 || Y < 60) && (coord == -1 || coord == 1) && ((Y < Z && Y < 90) || (Y > Z && Y > 90)))
        {
            angle *= cos(Y * DEG2RAD);

            if (coord == -1)
                moviment = new Moviment(choosenCubie->position, 0, 1, angle, 1);

            rubix->setDelta(angle);
            coord = 1;
        }
    }

    else if (face == 2 || face == 3)
    {
        if ((Z > 120 || Z < 60) && (coord == -1 || coord == 2) && ((Z < X && Z < 90) || (Z > X && Z > 90)))
        {
            angle *= cos(Z * DEG2RAD);

            if (coord == -1)
                moviment = new Moviment(choosenCubie->position, 0, 2, angle, 1);

            rubix->setDelta(angle);
            coord = 2;
        }

        else if ((X > 120 || X < 60) && (coord == -1 || coord == 0) && ((X < Z && X < 90) || (X > Z && X > 90)))
        {
            angle *= cos(X * DEG2RAD);

            if (coord == -1)
                moviment = new Moviment(choosenCubie->position, 0, 0, angle, 1);

            rubix->setDelta(angle);
            coord = 0;
        }
    }

    else if (face == 4 || face == 5)
    {
        if ((Y > 120 || Y < 60) && (coord == -1 || coord == 1) && ((Y < X && Y < 90) || (Y > X && Y > 90)))
        {
            angle *= cos(Y * DEG2RAD);

            if (coord == -1)
                moviment = new Moviment(choosenCubie->position, 0, 1, angle, 1);

            rubix->setDelta(angle);
            coord = 1;
        }

        else if ((X > 120 || X < 60) && (coord == -1 || coord == 0) && ((X < Y && X < 90) || (X > Y && X > 90)))
        {
            angle *= cos(X * DEG2RAD);

            if (coord == -1)
                moviment = new Moviment(choosenCubie->position, 0, 0, angle, 1);

            rubix->setDelta(angle);
            coord = 0;
        }
    }

    if (moviment)
        rubix->manipulate(moviment);
}

void OpenGLWindow::solve()
{
    idx = 0;

    solution.clear();
    path.clear();

    rubix->matchCube2Data();

    if (rubix->checkFinalState()) return;

    if (QLibrary::isLibrary("Kociemba.dll"))
    {
        QLibrary libSol("Kociemba.dll");
        libSol.load();

        if (!libSol.isLoaded())
        {
            qDebug() << libSol.errorString();
            return;
        }

        if (libSol.isLoaded())
            qDebug() << "success";

        typedef char* (*kociemba)(char*);

        auto qSolve = (kociemba)libSol.resolve("solve");

        char *config = rubix->generateConfig();
        sol = qSolve(config);

        libSol.unload();

        qDebug() << sol;

        delete[] config;

        QString s = sol;

        s = s.replace(" ", "");
        s = s.replace("F'", "f");
        s = s.replace("B'", "b");
        s = s.replace("R'", "r");
        s = s.replace("L'", "l");
        s = s.replace("U'", "u");
        s = s.replace("D'", "d");

        s = s.replace("F2", "4");
        s = s.replace("B2", "5");
        s = s.replace("R2", "1");
        s = s.replace("L2", "0");
        s = s.replace("U2", "2");
        s = s.replace("D2", "3");

        for (int i = 0; i < s.size(); i++)
        {
            if (s.at(i) == 'f') path.push_back("F'");
            else if(s.at(i) == 'b') path.push_back("B'");
            else if(s.at(i) == 'r') path.push_back("R'");
            else if(s.at(i) == 'l') path.push_back("L'");
            else if(s.at(i) == 'u') path.push_back("U'");
            else if(s.at(i) == 'd') path.push_back("D'");
            else if(s.at(i) == '4') path.push_back("F2");
            else if(s.at(i) == '5') path.push_back("B2");
            else if(s.at(i) == '1') path.push_back("R2");
            else if(s.at(i) == '0') path.push_back("L2");
            else if(s.at(i) == '2') path.push_back("U2");
            else if(s.at(i) == '3') path.push_back("D2");
            else path.push_back(s.at(i));
        }

        execute = false;
    }
}

void OpenGLWindow::inputByCamera()
{
    cameraOn = true;

    rubix->matchCube2Data();

    int stt[] = { 4, 0, 5, 1, 2, 3 };
    int idx = 0;

    int data[54];

    for (int k = 0; k < 6; k++)
    {
        int f = stt[k];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                data[idx] = rubix->_data[f][i][j];
                idx++;
            }
        }
    }

    cameraInput(data);

    idx = 0;

    for (int k = 0; k < 6; k++)
    {
        int f = stt[k];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                _data[f][i][j] = data[idx];
                idx++;
            }
        }
    }

    rubix->matchData2Cube(_data);

    cameraOn = false;
}

void OpenGLWindow::mousePressEvent(QMouseEvent *event)
{
    isPressed = true;
    startPos.set(event->position().x(), height() - event->position().y() - 1, 0);

    int faceName = pick(event->position().x(), event->position().y());

    if (faceName == 1 || faceName == 0)
    {
        track = true;
    }
    else if (faceName >= 100 && faceName <= 2705)
    {
        track = false;
        selectedCubie = faceName;
        choosenCubie = rubix->findCubieById(selectedCubie / 100);

        if (configMode && choosenCubie)
        {
            choosenCubie->changeColor(selectedCubie % 10, currentColor);
            update();
        }
    }
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressed && event->buttons() & Qt::LeftButton)
    {
        endPos.set(event->position().x(), height() - event->position().y() - 1, 0);

        lastPos = windowToSphere(startPos, width(), height());
        curPos = windowToSphere(endPos, width(), height());

        if (!lastPos.isInvalid() && !curPos.isInvalid())
            angle = speedup * lastPos.angle(curPos);
        else return;

        norm = lastPos.cross(curPos);

        if (!norm.isInvalid())
            norm.normalized();
        else return;

        if (angle < -180.0f) angle += 180.0f;
        if (angle > 180.0f) angle -= 180.0f;

        float dis = endPos.distance(startPos);
        startPos = endPos;

        if (!track && dis > 0.7)
            mouseDrag(selectedCubie);

        update();
    }
}

void OpenGLWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (!track) rubix->stop();
    isPressed = false;
    track = false;
    coord = -1;
    selectedCubie = -1;
    choosenCubie = nullptr;
}

void OpenGLWindow::updateGL()
{
    if (!path.empty() && execute && !rubix->checkIdle() && !pause)
    {
        if (idx <= path.size() - 1)
        {
            Moviment *moviment = nullptr;

            if (path.at(idx) == "L")
            {
                cubie = rubix->findCubieById(5);
                moviment = new Moviment(cubie->position, false, 0, 90.0, 1, true);
            }

            else if (path.at(idx) == "L2")
            {
                cubie = rubix->findCubieById(5);
                moviment = new Moviment(cubie->position, false, 0, 180.0, 1, true);
            }

            else if (path.at(idx) == "L'")
            {
                cubie = rubix->findCubieById(5);;
                moviment = new Moviment(cubie->position, true, 0, 90.0, 1, true);
            }

            else if (path.at(idx) == "R")
            {
                cubie = rubix->findCubieById(23);;
                moviment = new Moviment(cubie->position, true, 0, 90.0, 1, true);
            }

            else if (path.at(idx) == "R2")
            {
                cubie = rubix->findCubieById(23);;
                moviment = new Moviment(cubie->position, true, 0, 180.0, 1, true);
            }

            else if (path.at(idx) == "R'")
            {
                cubie = rubix->findCubieById(23);;
                moviment = new Moviment(cubie->position, false, 0, 90.0, 1, true);
            }

            else if (path.at(idx) == "F")
            {
                cubie = rubix->findCubieById(15);;
                moviment = new Moviment(cubie->position, true, 2, 90.0, 1, true);
            }

            else if (path.at(idx) == "F2")
            {
                cubie = rubix->findCubieById(15);;
                moviment = new Moviment(cubie->position, true, 2, 180.0, 1, true);
            }

            else if (path.at(idx) == "F'")
            {
                cubie = rubix->findCubieById(15);;
                moviment = new Moviment(cubie->position, false, 2, 90.0, 1, true);
            }

            else if (path.at(idx) == "B")
            {
                cubie = rubix->findCubieById(13);;
                moviment = new Moviment(cubie->position, false, 2, 90.0, 1, true);
            }

            else if (path.at(idx) == "B2")
            {
                cubie = rubix->findCubieById(13);;
                moviment = new Moviment(cubie->position, false, 2, 180.0, 1, true);
            }

            else if (path.at(idx) == "B'")
            {
                cubie = rubix->findCubieById(13);
                moviment = new Moviment(cubie->position, true, 2, 90.0, 1, true);
            }

            else if (path.at(idx) == "U")
            {
                cubie = rubix->findCubieById(17);
                moviment = new Moviment(cubie->position, true, 1, 90.0, 1, true);
            }

            else if (path.at(idx) == "U2")
            {
                cubie = rubix->findCubieById(17);
                moviment = new Moviment(cubie->position, true, 1, 180.0, 1, true);
            }

            else if (path.at(idx) == "U'")
            {
                cubie = rubix->findCubieById(17);
                moviment = new Moviment(cubie->position, false, 1, 90.0, 1, true);
            }

            else if (path.at(idx) == "D")
            {
                cubie = rubix->findCubieById(11);
                moviment = new Moviment(cubie->position, false, 1, 90.0, 1, true);
            }

            else if (path.at(idx) == "D2")
            {
                cubie = rubix->findCubieById(11);
                moviment = new Moviment(cubie->position, false, 1, 180.0, 1, true);
            }

            else if (path.at(idx) == "D'")
            {
                cubie = rubix->findCubieById(11);
                moviment = new Moviment(cubie->position, true, 1, 90.0, 1, true);
            }

            solution.clear();

            for(int i = 0; i < path.size(); i++)
            {
                if (i == idx)
                {
                    QString red = QString("<span style='font-size:10pt; font-weight:bold; color:#ff0000;'>%1</span>").arg(path.at(idx));
                    solution.append(red);
                }
                else
                    solution.append(path.at(i));

                if (i < path.size() - 1)
                    solution.append(" ");
            }

            idx++;
            rubix->manipulate(moviment);
        }
        else
        {
            sol = nullptr;
            execute = false;
            path.clear();
        }
    }

    if (!cameraOn)
        update();
}



