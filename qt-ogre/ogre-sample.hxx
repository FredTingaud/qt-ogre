#pragma once

#include <OGRE/OgreRoot.h>

namespace Ogre
{
   class SceneManager;
}
class OgreSample
{
public:
   OgreSample(const std::string execPath);
   virtual ~OgreSample() = default;

   void initialize(HWND winId, int width, int height);

   void createCamera(int width, int height);

   void createSampleScene();

   void resize(int width, int height);
   void zoom(float delta);
   void resetCamera();
   void moveCamera(float moveX, float moveY);

   void update();

private:
   void renderOpenGL();

private:
   static const Ogre::Real MIN_Z;

private:
   Ogre::Root root_;
   Ogre::SceneManager* sceneManager_;
   Ogre::RenderWindow* renderWindow_;
   Ogre::Camera* camera_;
   Ogre::Viewport* viewport_;
   bool initialized_;
};
