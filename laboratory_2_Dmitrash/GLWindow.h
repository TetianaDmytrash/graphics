//#pragma once
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 /*
  * File:   GLWindow.h
  * Author: KnightDanila
  *
  * Created on 17 сент€бр€ 2019 г., 0:04
  */

#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "libs/GL_AL/glfw3.h"

namespace ghost_player {
    /*pattern Adaprer - wrapper*/
    class GLWindow {
    public:
        GLWindow(const std::string& title, uint32_t width, uint32_t height) {
            _handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
            glfwMakeContextCurrent(_handle);
            _width = width;
            _height = height;
            _title = title;
            glfwGetWindowPos(_handle, &_xpos, &_ypos);
            make_monitor();
        };
        GLWindow(const std::string& title, uint32_t width, uint32_t height, GLFWwindow* share) {
            _handle = glfwCreateWindow(width, height, title.data(), nullptr, share);
            glfwMakeContextCurrent(_handle);//отрисовка в конкретном окне
            _width = width;
            _height = height;
            _title = title;
            glfwGetWindowPos(_handle, &_xpos, &_ypos);
            make_monitor();
        };

        ~GLWindow() {
            //glfwDestroyWindow(handle);
            glfwSetWindowShouldClose(this->_handle, 1);
        };
        uint32_t getWidth() {
            return _width;
        }
        uint32_t getHeight() {
            return _height;
        }

        GLFWwindow* getGLFWHandle() const {
            return _handle;
        }

        void full_screen_switch() {
            if (!_full_screen) {
                _full_screen = true;
                const GLFWvidmode* mode = glfwGetVideoMode(_monitor);
                glfwSetWindowMonitor(_handle, _monitor, _xpos, _ypos, mode->width, mode->height, GLFW_DONT_CARE);
            }
            else {
                _full_screen = false;
                //const GLFWvidmode* mode = glfwGetVideoMode(_monitor);
                glfwSetWindowMonitor(_handle, nullptr, _xpos, _ypos, _width, _height, GLFW_DONT_CARE);
            }
        }
    private:
        // TODO
        GLFWwindow* _handle;

        uint32_t _width, _height; // размеры
        std::string _title; //название
        int _xpos; //позици€
        int _ypos;
        bool _full_screen = false; //полноэкранный режим

        GLFWmonitor* _monitor;//разрешение экрана

        void make_monitor() {
            _monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(_monitor);

            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        }
    };
}
#endif /* GLWINDOW_H */
