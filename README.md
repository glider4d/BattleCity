#for windows 
 
cmake -G "Visual Studio 17 2022" -A Win32 -B "build"

#add lib glfw like subbtree

git remote add glfw https://github.com/glfw/glfw.git
git subtree add --prefix=external/glfw glfw master --squash

#for update glfw 
git subtree pull --prefix=external/glfw glfw master --squash

#for build (in build dirrectory)
cmake --build .