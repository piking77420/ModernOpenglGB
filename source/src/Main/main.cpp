#include <Windows.h>
#include <iostream>
#include <string>
#include <LowRenderer/Cam/Camera.h>   
#include "App/App.h"
#include <Core/Debug/LogClass.h>
#include <Core/Debug/AssertClass.h>
#include <Core/Debug/Imgui/imgui.h>
#include <Core/Debug/Imgui/imgui_impl_glfw.h>
#include <Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "External/Std_Image/std_image.h"
#include "LowRenderer/FrameBuffer/FrameBuffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "External/ImguiGizmo/ImGuizmo.h"



    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
          glfwSetWindowShouldClose(window, true);
    }
  
    void EnableOpenGl()
    {
        glDepthFunc(GL_LESS);

        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
        glEnable(GL_FRONT_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CW);
    }
    void LoadCursorAppCursor(GLFWwindow* window)
    {
        
        GLFWimage image;
        image.width = 16;
        image.height = 16;
        int nbr = 0;
        image.pixels = stbi_load("Ressources/Skyrim-normal.png", &image.width, &image.height, &nbr, 0);
        GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
        glfwSetCursor(window, cursor);

    }



   

   
    int main()
    {

    #ifdef _DEBUG
    #else

            HWND hWnd = GetConsoleWindow();
            ShowWindow(hWnd, SW_HIDE);
    #endif 

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Engine", NULL, NULL);




        glfwMakeContextCurrent(window);

        gladLoadGL();
        App::framebuffer_size_callback(window, windowWidth, windowHeight);
        glfwSetFramebufferSizeCallback(window, App::framebuffer_size_callback);
        glfwSetCursorPosCallback(window, Camera::MouseCallback);
        glfwSetMouseButtonCallback(window, Camera::MouseButtonCallBack);

       

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // Imgui Init // 
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui::StyleColorsDark();
 

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        LoadCursorAppCursor(window);
        EnableOpenGl();
        App app(windowWidth, windowHeight,io);

      
   
        // Main Loop // 
        while (!glfwWindowShouldClose(window))
        {
            
            glfwPollEvents();

            if(App::GammaCorrection)
            glEnable(GL_FRAMEBUFFER_SRGB);
            
       
            processInput(window);

             //Imgui new frame // 
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGuizmo::BeginFrame();

         
            app.AppUpdate();


         
            
            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            if (App::GammaCorrection)
            glDisable(GL_FRAMEBUFFER_SRGB);

           // IMGUI RENDER // 
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);


        }   
        LOG("On Window Close", STATELOG::NONE);


        // IMGUI destroy // 
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        // delete Singeltons 
        delete Debug::Assert;


        
        glfwTerminate();

        return 0;
    }

