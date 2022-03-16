/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 /*
  * File:   GLRenderSystem.h
  * Author: KnightDanila
  *
  * Created on 17 сентября 2019 г., 7:11
  */

#ifndef GLRENDERSYSTEM_H
#define GLRENDERSYSTEM_H

namespace ghost_player {
    namespace GraphCore {

        class GLRenderSystem {
        public:

            virtual void init() {}

            virtual void render(GLFWwindow* window) {}

            /*virtual void renderTriangleArray(GLfloat vertices[], GLfloat colors[]) {}*/
            virtual void renderTriangleArray(GLfloat vertices[], GLfloat colors[], int n) {}
            virtual void renderQuadArray(GLfloat vertices[], GLfloat colors[],int n_point){}
            virtual void renderFantasyArray(GLfloat colors[]){}

            virtual void renderVBO() {}
        };

        class GLRender : public GLRenderSystem {

            void init() {
                if (!glfwInit()) {
                    fprintf(stderr, "Невозможно инициализировать GLEW\n");
                    return;
                }

                glfwWindowHint(GLFW_SAMPLES, 4);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//хотим 3.3 версию openGL
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            }

            void render(GLFWwindow* window) {
                glClearColor(0,0, 0,1);
                //glClearColor(sin(colorRGB * PI / 180), abs(cos(colorRGB * PI / 180)), abs(sin(colorRGB * PI / 180) + cos(colorRGB * PI / 180)), 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//GL_DEPTH_BUFFER_BIT - говорит о том, что фигура больше чем одна и она в трехмерном пространстве

                {
                    colorRGB <= 180 ? colorRGB += 0.1 : colorRGB = 0;
                }
                //glColor3d(0, 1, 0);
                glColor3d(sin(colorRGB * PI / 180), abs(cos(colorRGB * PI / 180)), abs(sin(colorRGB * PI / 180) + cos(colorRGB * PI / 180)));/*, 1.0f */
                glEnable(GL_DEPTH_TEST);//проверка глубины
                glMatrixMode(GL_MODELVIEW);//единичная матрица модели
                glPushMatrix();//сохраняем ее
                angle = glfwGetTime() * 50.0f; //создаем матрицу поворота и поворачиваем на угол
                //glRotatef(angle, 1.0, 1.0, 0.0);

                glGenBuffers(1, &Cube::VBO);//создание объекта в памяти видеокарты, который состоит из вершин
                glBindBuffer(GL_ARRAY_BUFFER, Cube::VBO);//говорим, что будем грузить
                glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::vertices), Cube::vertices, GL_STATIC_DRAW);// привязка данных к переменной
                glVertexPointer(3, GL_FLOAT, 0, NULL);//тип точек
                glBindBuffer(GL_ARRAY_BUFFER, Cube::VBO);
                //VAO - где-то тут посыл в память
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);
                glEnableClientState(GL_VERTEX_ARRAY);

                glDrawArrays(GL_TRIANGLES, 0, (sizeof(Cube::vertices) / sizeof(Cube::vertices[0])) / 5);//отрисовка
                glPopMatrix();
                glDisableClientState(GL_VERTEX_ARRAY);
            }

            void renderTriangleArray(GLfloat vertices[], GLfloat colors[], int n_point) {

                glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_COLOR_ARRAY);

                glVertexPointer(3, GL_FLOAT, 0, vertices);
                glColorPointer(3, GL_FLOAT, 0, colors);

                glDrawArrays(GL_QUADS, 0, n_point);

                glDisableClientState(GL_COLOR_ARRAY);
                glDisableClientState(GL_VERTEX_ARRAY);
            }

        };

        class GLRendererOld2_1 : public GLRenderSystem {

            void init() {
                if (!glfwInit()) {
                    fprintf(stderr, "Ошибка при инициализации GLFW\n");
                }
                glfwWindowHint(GLFW_SAMPLES, 4);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

            }

            void render(GLFWwindow* window) {
                glfwMakeContextCurrent(window);
                glClearColor(sin(colorRGB * PI / 180), abs(cos(colorRGB * PI / 180)), abs(sin(colorRGB * PI / 180) + cos(colorRGB * PI / 180)), 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                {
                    colorRGB <= 180 ? colorRGB += 0.1 : colorRGB = 0;
                }

                //glLoadIdentity();

                glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
                glBegin(GL_TRIANGLES);//каждый раз заново передается и отрисовывается 
                glColor3f(1.f, 0.f, 0.f);
                glVertex3f(-0.6f, -0.4f, 0.f);
                glColor3f(0.f, 1.f, 0.f);
                glVertex3f(0.6f, -0.4f, 0.f);
                glColor3f(0.f, 0.f, 1.f);
                glVertex3f(0.f, 0.6f, 0.f);
                glEnd();
            }

            void renderTriangleArray(GLfloat vertices[], GLfloat colors[], int n_point) {
                glClearColor(sin(colorRGB * PI / 180), abs(cos(colorRGB * PI / 180)), abs(sin(colorRGB * PI / 180) + cos(colorRGB * PI / 180)), 1.0f);//цвет фона
                glClear(GL_COLOR_BUFFER_BIT);//закрасить, очистить

                {
                    colorRGB <= 180 ? colorRGB += 0.1 : colorRGB = 0;
                }

                //glLoadIdentity();
                glRotatef((float)glfwGetTime() * 50.f, 0.f, 1.f, 1.f);//поворот, скорость?
                glBegin(GL_TRIANGLES);
                if (n_point % 3 == 0) {
                    for (int i = 0; i <= n_point; i += 3) {
                        glColor3f(colors[i], colors[i + 1], colors[i + 2]);
                        glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
                    }
                }
                else {
                    fprintf(stderr, "Triangle error");
                    return;

                }
                glEnd();
            }

            void renderQuadArray(GLfloat vertices[], GLfloat colors[], int n_point) {
                glClearColor(225 / 256.0f, 150 / 256.0f, 176 / 256.0f, 1);
                glClear(GL_COLOR_BUFFER_BIT);

                glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_COLOR_ARRAY);

                glVertexPointer(3, GL_FLOAT, 0, vertices);//вершины передали, тройка - формат, то есть три точки, начало от нуля
                glColorPointer(3, GL_FLOAT, 0, colors);//цвета передали
                
                glDrawArrays(GL_QUADS, 0, n_point);//количество, ф-ция отрисовки


                glDisableClientState(GL_COLOR_ARRAY);
                glDisableClientState(GL_VERTEX_ARRAY);
            }

            void renderFantasyArray(GLfloat colors[]) {
                glClearColor(sin(colorRGB * PI / 180), abs(cos(colorRGB * PI / 180)), abs(sin(colorRGB * PI / 180) + cos(colorRGB * PI / 180)), 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                glLoadIdentity();
                float bias = PI/5;//0.63;
                float angle_of_rotation = bias;//0.628319;
                
                float radius = 0.5;
                float radius_small = 0.2;
                //float x_center = array_x_move[0], y_center = array_y_move[0];
                const float step = float(PI * 2 / 5);//угол между смежными вершинами
                float angle_interior = angle_of_rotation;//больший
                float angle_external = float(angle_of_rotation + bias);//меньший
                float x_center = 0.1, y_center = 0.1;
                int j = 0;

                glRotatef((float)glfwGetTime() * 50.f, 0.f, 1.f, 1.f);
                glBegin(GL_TRIANGLE_FAN);
                glVertex2d(x_center, y_center); 
                for (int i = 1; i < 12; i++) {
                    if (i % 2 != 0) {
                        glVertex2d(x_center + radius_small * cosf(angle_interior), y_center + radius_small * sinf(angle_interior));
                        angle_interior += step;
                    }
                    else {
                        glVertex2d(x_center + radius * cosf(angle_external), y_center + radius * sinf(angle_external));
                        angle_external += step;
                    }
                    glColor3f(colors[j], colors[j + 1], colors[j + 2]);
                    j += 3;
                }
                glEnd();
            }
        };
    }
}


#endif /* GLRENDERSYSTEM_H */
