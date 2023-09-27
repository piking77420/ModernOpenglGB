%module resources

%{
	#include "../source/include/Ressources/RessourcesManager/RessourcesManager.h"
	#include "../source/include/Ressources/IResources/IResource.h"
	#include "../source/include/Ressources/Scene/Scene.h"
	#include "../source/include/Ressources/Mesh/Mesh.h"
	#include "../source/include/Ressources/Shader/Shader.h"
	#include "../source/include/Ressources/Texture/Texture.hpp"
%}



%include "../source/include/Ressources/RessourcesManager/RessourcesManager.h"
%include "../source/include/Ressources/IResources/IResource.h"
%include "../source/include/Ressources/Scene/Scene.h"
%include "../source/include/Ressources/Mesh/Mesh.h"
%include "../source/include/Ressources/Shader/Shader.h"
%include "../source/include/Ressources/Texture/Texture.hpp"

