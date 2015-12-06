#include <qt-ogre/ogre-sample.hxx>

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreViewport.h>

const Ogre::Real OgreSample::MIN_Z = 0.7f;

OgreSample::OgreSample(const std::string execPath)
   : root_(execPath + "\\plugins_d.cfg"
   , execPath + "\\ogre.cfg"
   , execPath + "\\logs.log")
   , initialized_(false)
{
   root_.addResourceLocation(execPath, "FileSystem");
   sceneManager_ = root_.createSceneManager(Ogre::ST_GENERIC);
}

void OgreSample::initialize(HWND winId, int width, int height)
{
   if (!initialized_)
   {
      renderOpenGL();
      root_.initialise(false);
      Ogre::NameValuePairList viewConfig;
      viewConfig["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)winId);

      renderWindow_ = root_.createRenderWindow("Ogre rendering window",
                                               width, height, false, &viewConfig);

      createCamera(width, height);
      viewport_ = renderWindow_->addViewport(camera_);
      viewport_->setBackgroundColour(Ogre::ColourValue(0.117f, 0.117f, 0.117f));
      createSampleScene();

      initialized_ = true;
   }
}

void OgreSample::createCamera(int width, int height)
{
   camera_ = sceneManager_->createCamera("myCamera");
   camera_->setAspectRatio(Ogre::Real(width) / Ogre::Real(height));
   camera_->setNearClipDistance(0.05f);
   camera_->setFarClipDistance(50000.f);
   resetCamera();
}

/**
 * A sample scene with a blue sphere and a white light.
 */
void OgreSample::createSampleScene()
{
   Ogre::SceneNode* sceneNode = sceneManager_->getRootSceneNode()->createChildSceneNode();
   Ogre::Entity* entity = sceneManager_->createEntity("sphere", Ogre::SceneManager::PT_SPHERE);

   Ogre::MaterialPtr blueMaterial = Ogre::MaterialManager::getSingleton()
      .create("blue"
      , Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
      );
   blueMaterial->setSelfIllumination(0.337, 0.612f, 0.839f);
   blueMaterial->setAmbient(0, 0, 0);

   entity->setMaterial(blueMaterial);
   sceneNode->attachObject(entity);
   sceneNode->setPosition(Ogre::Vector3(0.f, 0.f, -0.5f));
   sceneNode->setScale(Ogre::Vector3(0.01f, 0.01f, 0.01f));

   Ogre::Light* light = sceneManager_->createLight("Light");
   light->setPosition(-1.f, -1.f, 1.f);
   light->setDiffuseColour(0.4f, 0.4f, 0.4f);
}

/**
 * We force the render system to OpenGL for simplicity.
 */
void OgreSample::renderOpenGL()
{
   const Ogre::RenderSystemList& lRenderSystemList = root_.getAvailableRenderers();
   for (unsigned int i = 0; i < lRenderSystemList.size(); ++i)
   {
      if (lRenderSystemList.at(i)->getName().find_first_of("GL") != std::string::npos)
      {
         root_.setRenderSystem(lRenderSystemList.at(i));
         return;
      }
   }
   throw std::runtime_error("Couldn't find the OpenGL render system.");
}

/**
 * Convert the position relative to the widget into a position relative to the sphere
 * that is on a plan where z == 0.
 */
void OgreSample::moveCamera(float moveX, float moveY)
{
   Ogre::Real z = camera_->getPosition().z;
   Ogre::Real tanX = tan(camera_->getFOVy().valueRadians() / 2.) * camera_->getAspectRatio();
   Ogre::Real x = camera_->getPosition().x + moveX * 2. * tanX * z;
   Ogre::Real tanY = tan(camera_->getFOVy().valueRadians() / 2.);
   Ogre::Real y = camera_->getPosition().y - moveY * 2. * tanY * z;
   camera_->setPosition(x, y, z);
}

void OgreSample::resetCamera()
{
   camera_->setPosition(0.f, 0.f, 5.f);
   camera_->lookAt(0.f, 0.f, -2.f);
}

void OgreSample::zoom(float delta)
{
   Ogre::Vector3 movePos = camera_->getPosition() + Ogre::Vector3(0.f, 0.f, delta);
   if (movePos.z < MIN_Z)
   {
      movePos.z = MIN_Z;
   }
   camera_->setPosition(movePos);
}

void OgreSample::resize(int width, int height)
{
   if (initialized_)
   {
      renderWindow_->windowMovedOrResized();
      camera_->setAspectRatio(Ogre::Real(width) / Ogre::Real(height));
   }
}

void OgreSample::update()
{
   if (initialized_)
   {
      root_.renderOneFrame();
   }
}

