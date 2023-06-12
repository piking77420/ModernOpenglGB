    #include <Windows.h>
    #include <iostream>
    #include <string>
    #include <glad/glad.h>
    #include <GLFW/glfw3.h>
    #include <LowRenderer/Cam/Camera.h>   
    #include "App/App.h"
    #include <Core/Debug/LogClass.h>
    #include <Core/Debug/AssertClass.h>
    #include <Core/Debug/Imgui/imgui.h>
    #include <Core/Debug/Imgui/imgui_impl_glfw.h>
    #include <Core/Debug/Imgui/imgui_impl_opengl3.h>
    #include <LowRenderer/Light/Light.h>
    #include "External/Std_Image/std_image.h"
    




    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
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
        image.pixels = stbi_load("assets/Textures/Cursor/Skyrim-normal.png", &image.width, &image.height, &nbr, 0);
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

        GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "BON_Engine", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);

        gladLoadGL();
        framebuffer_size_callback(window, windowWidth, windowHeight);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, Camera::MouseCallback);
        glfwSetMouseButtonCallback(window, Camera::MouseButtonCallBack);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        EnableOpenGl();
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window,true);
        ImGui_ImplOpenGL3_Init("#version 330");

        // Imgui Init // 
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

        LoadCursorAppCursor(window);


        App* app = new App(windowWidth, windowHeight,io);

      
      // Debug::Log->Print("One two three! %f %f %f %f \n", 10.232323f,23.232323f,34.24233 , 234.2442 , 444.23233);
      // Debug::Log->Print("One two three! %i %i %i \n", 1, 2, 3);
      // Debug::Assert->Assertion(false);
        
        /*
        Matrix newMatrix = Matrix(2, 3);
        newMatrix[0][0] = 2;
        newMatrix[0][1] = 0;

        newMatrix[1][0] = 0;
        newMatrix[1][1] = 1;

        newMatrix[0][2] = 3;
        newMatrix[1][2] = 2;


        std::cout << newMatrix.PivotDeGauss() << std::endl;
        */

        // Main Loop // 
        while (!glfwWindowShouldClose(window))
        {

            if(App::GammaCorrection)
            glEnable(GL_FRAMEBUFFER_SRGB);

       
            processInput(window);

             //Imgui new frame // 
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Update
            io = ImGui::GetIO();    
            app->GetInputOutPout(io);
            app->AppUpdate();

            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            if (App::GammaCorrection)
            glDisable(GL_FRAMEBUFFER_SRGB);

           // IMGUI RENDER // 
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
            glfwPollEvents();


        }   
        Debug::Log->LogInfo("On Window Close");


        // IMGUI destroy // 
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        // delete Singeltons 
        delete Debug::Log;
        delete Debug::Assert;
        delete Debug::debugLogStream;

        delete app;
        glfwTerminate();

        return 0;
    }


