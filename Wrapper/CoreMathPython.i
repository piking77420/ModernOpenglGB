%module CorePythonMath

%{
	#include "../source/include/Core/Math/Vector2.h"
    #include "../source/include/Core/Math/Vector3.h"

%}


%include "std_string.i"

%include "../source/include/Core/Math/Vector2.h"
%include "../source/include/Core/Math/Vector3.h"


%extend Vector2 {

	  double &operator[](int index) {
        if (index == 0) return $self->x;
        if (index == 1) return $self->y;
        // Handle out-of-bounds or error conditions here.
        // You may want to throw an exception or return a default value.
    }

}


%extend Vector3 {
    double &operator[](int index) {
        if (index == 0) return $self->x;
        if (index == 1) return $self->y;
        if (index == 2) return $self->z;
        // Handle out-of-bounds or error conditions here.
        // You may want to throw an exception or return a default value.
    }

    %rename(toVector2) operator Vector2;
}

