﻿// ======================================================================== //
// Copyright 2009-2015 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#include "exampleViewer/widgets/imguiViewer.h"
#include "commandline/Utility.h"
#include "commandline/SceneParser/trianglemesh/TriangleMeshSceneParser.h"
#include "ospray/ospray.h"

using namespace commandline;

class RayforceSceneParser : public TriangleMeshSceneParser
{
public:
  RayforceSceneParser(ospray::cpp::Renderer renderer,
                      std::string geometryType = "rayforce") :
    TriangleMeshSceneParser(renderer, geometryType) {}
};

int main(int ac, const char **av)
{
  ospInit(&ac,av);
  ospray::imgui3D::init(&ac,av);

  ospLoadModule("rayforce");
  auto ospObjs = parseCommandLine<DefaultRendererParser,
                                  DefaultCameraParser,
                                  RayforceSceneParser,
                                  DefaultLightsParser>(ac, av);

  std::deque<ospcommon::box3f>   bbox;
  std::deque<ospray::cpp::Model> model;
  ospray::cpp::Renderer renderer;
  ospray::cpp::Camera   camera;

  std::tie(bbox, model, renderer, camera) = ospObjs;

  ospray::ImGuiViewer window(bbox, model, renderer, camera);
  window.create("ospRayforceViewer: OSPRay Rayforce Viewer");

  ospray::imgui3D::run();
}
