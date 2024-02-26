#for windows 
 
cmake -G "Visual Studio 17 2022" -A Win32 -B "build"

#add lib glfw like subbtree

#glm
git remote add glm https://github.com/g-truc/glm.git
git subtree add --prefix=external/glm glm master --squash
#for update glm
git subtree pull --prefix=external/glm glm master --squash


git remote add glfw https://github.com/glfw/glfw.git
git subtree add --prefix=external/glfw glfw master --squash

#for update glfw 
git subtree pull --prefix=external/glfw glfw master --squash

#for build (in build dirrectory)
cmake --build .