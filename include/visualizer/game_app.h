#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "sketchpad.h"
#include <core/Game.h>

namespace naivebayes {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class GameApp : public ci::app::App {
 public:
  GameApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;
  void handleKeys(size_t rank);

  const double kWindowSize = 1500;  //was 875
  const double kMargin = 100;
  const size_t kImageDimension = 28;

 private:
  Sketchpad sketchpad_;
  Game game;
  int current_prediction_ = -1;
  size_t selected;
  bool is_selected;
  bool request_jack;
  bool invalid_jack;
  //std::shared_ptr<ci::gl::Texture2d> mTex;
  ci::gl::Texture2dRef mTex;
};

}  // namespace visualizer

}  // namespace naivebayes
