# Program cracking: buffer overflow && patching

My comrade wrote a tiny programm [pass](pass) that asks for password. He added 2 non-patching vulnerabilities in this programm.

![](hello_world.PNG)

I found one (read as "left second one for you to have a fun") and created appropriate string to abuse it, check [overflow_buffer_abuser](print_ascii.cpp)

Also i patched it with a pinch of art: [crack](crack.cpp)

![](readme_gif.gif)

