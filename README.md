# OGRE
Current version used: OGRE_1.8.1
Based Platform: Linux Ubuntu 14.04
Problem shooting:
(1) When "make" CMake build, appearing undefined reference problem like /BaseApplication.cpp.o: undefined reference to symbol '_ZN5boost6system15system_categoryEv',
http://www.ogre3d.org/forums/viewtopic.php?f=2&t=71037
add -lboost_system behind .app in link.txt
