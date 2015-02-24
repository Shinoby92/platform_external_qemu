/*
* Copyright (C) 2011 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#ifndef EGL_DISPLAY_H
#define EGL_DISPLAY_H

#include <list>
#include <map>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include "emugl/common/mutex.h"
#include "emugl/common/smart_ptr.h"

#include "EglConfig.h"
#include "EglContext.h"
#include "EglSurface.h"
#include "EglWindowSurface.h"




typedef  std::map< unsigned int, ContextPtr>     ContextsHndlMap;
typedef  std::map< unsigned int, SurfacePtr>     SurfacesHndlMap;

class EglDisplay {
public:
    // Create new EglDisplay instance from a given native display |dpy|,
    // with matching internal display |idpy|. If |isDefault| is true,
    // this will be considered the default diplay.
    EglDisplay(EGLNativeDisplayType dpy,
               EGLNativeInternalDisplayType idpy,
               bool isDefault = true);

    // Return the native display handle for this EglDisplay.
    EGLNativeDisplayType getNativeDisplay() const { return m_dpy; }

    // Return the native internal display handle for this EglDisplay.
    EGLNativeInternalDisplayType nativeType() const { return m_idpy; }

    // Return the number of known configurations for this EglDisplay.
    int nConfigs() const { return m_configs.size(); }

    // Write up to |config_size| EGLConfig values into the |configs| array.
    // Return the number if values written.
    int getConfigs(EGLConfig* configs,int config_size) const;

    // Select all display configurations that match at least the values
    // in |dummy|. If |configs| is NULL, this returns the number of all
    // matching configs. Otherwise, this writes into |configs| up to
    // |config_size| matching EGLConfig values, and returns their number.
    int chooseConfigs(const EglConfig& dummy,
                      EGLConfig* configs,
                      int config_size) const;

    // Return the EglConfig value that matches a given EGLConfig |conf|.
    EglConfig* getConfig(EGLConfig conf) const;

    // Return the EglConfig value that matches a given EGLConfig with
    // EGL_CONFIG_ID value |id|.
    EglConfig* getConfig(EGLint id) const;

    EGLSurface addSurface(SurfacePtr s );
    SurfacePtr getSurface(EGLSurface surface) const;
    bool removeSurface(EGLSurface s);
    bool removeSurface(SurfacePtr s);

    EGLContext addContext(ContextPtr ctx );
    ContextPtr getContext(EGLContext ctx) const;
    bool removeContext(EGLContext ctx);
    bool removeContext(ContextPtr ctx);
    ObjectNameManager* getManager(GLESVersion ver) const { return m_manager[ver];}

    ~EglDisplay();
    void initialize(int renderableType);
    void terminate();
    bool isInitialize();

    ImagePtr getImage(EGLImageKHR img) const;
    EGLImageKHR addImageKHR(ImagePtr);
    bool destroyImageKHR(EGLImageKHR img);
    EGLNativeContextType getGlobalSharedContext() const;

private:
   int doChooseConfigs(const EglConfig& dummy,EGLConfig* configs,int config_size) const;
   void addMissingConfigs(void);
   void initConfigurations(int renderableType);

   EGLNativeDisplayType           m_dpy;
   EGLNativeInternalDisplayType   m_idpy;
   bool                           m_initialized;
   bool                           m_configInitialized;
   bool                           m_isDefault;
   ConfigsList                    m_configs;
   ContextsHndlMap                m_contexts;
   SurfacesHndlMap                m_surfaces;
   GlobalNameSpace                m_globalNameSpace;
   ObjectNameManager              *m_manager[MAX_GLES_VERSION];
   mutable emugl::Mutex                   m_lock;
   ImagesHndlMap                  m_eglImages;
   unsigned int                   m_nextEglImageId;
   mutable EGLNativeContextType           m_globalSharedContext;
};

#endif


