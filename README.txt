Instructions for execution:

1)  To build type the 'make' command

2)  To run with default paramters type './rayTracer' followed 
    by either '--default' or '--yours'

3)  If you want to specify paramters then they must be entered in the
    following order after --default or --yours. 
    
    For example:
        ./rayTracer --yours <width> <height> <max depth> <field of view> <threads>

    If any paramter is not specified then default values will be used in its 
    place and for every paramter following it.
    So the following will set default values for <max depth> <field of view> and <threads>
        ./rayTracer --yours 512 512


Added Features:
-Perspective Camera
-Geometric Primitives
-Local Illumination
    The specular reflections aren't that visible in the default
    image but are much clearer in my custom one.
-Recursive Ray Tracing
-Super Sampling

Bonus:
-Transmittance Rays
    You will notice that in my custom scene the image in the smaller sphere 
    is upside down (which I think it is supposed to do) and that the shadows
    are being refracted through the cube and prism.

Sources:
Marschner, Steve, and Peter Shirley. Fundamentals of Computer Graphics. CRC Press, Taylor & Francis Group, 2016. 
https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
https://en.wikipedia.org/wiki/Phong_reflection_model

