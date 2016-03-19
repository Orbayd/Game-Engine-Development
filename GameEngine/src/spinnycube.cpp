/*
 * Copyright © 2012-2013 Graham Sellers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <sb6.h>
#include <math.h>


#include <vmath.h>
// ToDo get rid of the projection, move to the camera

#include "MathEngine.h"


class singlepoint_app : public sb6::application
{
    void init()
    {
        static const char title[] = "OpenGL SuperBible - Spinny Cube";

        sb6::application::init();

        memcpy(info.title, title, sizeof(title));


    }

    virtual void startup()
    {
        static const char * vs_source[] =
        {
            "#version 410 core                                                  \n"
            "                                                                   \n"
            "in vec4 position;                                                  \n"
            "                                                                   \n"
            "out VS_OUT                                                         \n"
            "{                                                                  \n"
            "    vec4 color;                                                    \n"
            "} vs_out;                                                          \n"
            "                                                                   \n"
            "uniform mat4 mv_matrix;                                            \n"
            "uniform mat4 proj_matrix;                                          \n"
            "                                                                   \n"
            "void main(void)                                                    \n"
            "{                                                                  \n"
            "    gl_Position = proj_matrix * mv_matrix * position;              \n"
            "    vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);      \n"
            "}                                                                  \n"
        };

        static const char * fs_source[] =
        {
            "#version 410 core                                                  \n"
            "                                                                   \n"
            "out vec4 color;                                                    \n"
            "                                                                   \n"
            "in VS_OUT                                                          \n"
            "{                                                                  \n"
            "    vec4 color;                                                    \n"
            "} fs_in;                                                           \n"
            "                                                                   \n"
            "void main(void)                                                    \n"
            "{                                                                  \n"
            "    color = fs_in.color;                                           \n"
            "}                                                                  \n"
        };

        program = glCreateProgram();
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, fs_source, NULL);
        glCompileShader(fs);

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, vs_source, NULL);
        glCompileShader(vs);

        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);

        mv_location = glGetUniformLocation(program, "mv_matrix");
        proj_location = glGetUniformLocation(program, "proj_matrix");

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        static const GLfloat vertex_positions[] =
        {
            -0.25f,  0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f,  0.25f,

            -0.25f,  0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
             0.25f,  0.25f,  0.25f,

             0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f, -0.25f
        };

        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(vertex_positions),
                     vertex_positions,
                     GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }

    virtual void render(double currentTime)
    {
        static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
        static const GLfloat one = 1.0f;

        glViewport(0, 0, info.windowWidth, info.windowHeight);
        glClearBufferfv(GL_COLOR, 0, green);
        glClearBufferfv(GL_DEPTH, 0, &one);

        glUseProgram(program);

        glUniformMatrix4fv(proj_location, 1, GL_FALSE, (float *)&projMatrix);
	
        float f = (float)currentTime * 0.3f;


		Matrix World;
		Matrix TransA( TRANS, 0.0f, 0.0f, -4.0f) ;
		Matrix TransB( TRANS, sinf(2.1f * f) * 0.5f, cosf(1.7f * f) * 0.5f, sinf(1.3f * f) * cosf(1.5f * f) * 2.0f );
		Matrix RotY( ROT_Y, ((float)currentTime * 45.0f) * MATH_PI_180 );
		Matrix RotX( ROT_X, ((float)currentTime * 81.0f) * MATH_PI_180 );
		
		World = RotX * RotY * TransB * TransA;
		glUniformMatrix4fv(mv_location, 1, GL_FALSE, (float *)&World);

        glDrawArrays(GL_TRIANGLES, 0, 36);

    }

    virtual void shutdown()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(program);
        glDeleteBuffers(1, &buffer);
    }

    void onResize(int w, int h)
    {
        sb6::application::onResize(w, h);

        aspect = (float)w / (float)h;

		vmath::mat4 proj_matrix =(vmath::perspective(50.0f, aspect, 0.1f, 1000.0f));
        projMatrix = (Matrix &) proj_matrix;
    }

private:
    GLuint          program;
    GLuint          vao;
    GLuint          buffer;
    GLint           mv_location;
    GLint           proj_location;

    float           aspect;
	Matrix			projMatrix;
};

DECLARE_MAIN(singlepoint_app)
