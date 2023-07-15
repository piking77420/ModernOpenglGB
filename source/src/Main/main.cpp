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
    #include <LowRenderer/Light/Light.h>
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



   

    // renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;
   
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
 
        float near_plane = 0.10f;
        float far_plane = 1000;
        glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);

        glm::mat4x4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));

        Matrix4X4 me =  Matrix4X4::LookAt(Vector3(-2.0f, 4.0f, -1.0f), Vector3::Zero,Vector3::Up);



        std::cout << lightView[0].x << " " << lightView[1].x << " " << lightView[2].x << " " << lightView[3].x << " ";
        std::cout << '\n';
        std::cout << lightView[0].y << " " << lightView[1].y << " " << lightView[2].y << " " << lightView[3].y << " ";
        std::cout << '\n';
        std::cout << lightView[0].z << " " << lightView[1].z << " " << lightView[2].z << " " << lightView[3].z << " ";
        std::cout << '\n';
        std::cout << lightView[0].w << " " << lightView[1].w << " " << lightView[2].w << " " << lightView[3].w << " ";
        std::cout << '\n';
        std::cout << me << std::endl;

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        LoadCursorAppCursor(window);
        EnableOpenGl();
        App* app = new App(windowWidth, windowHeight,io);
   
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

         
            app->AppUpdate();


         
            
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


        delete app;
        glfwTerminate();

        return 0;
    }

