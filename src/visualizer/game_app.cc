#include <visualizer/game_app.h>

namespace naivebayes {

namespace visualizer {

GameApp::GameApp()
    : sketchpad_(glm::vec2(kMargin, kMargin), kImageDimension,
                 kWindowSize - 2 * kMargin) {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void GameApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);

  sketchpad_.Draw();

  ci::gl::drawStringCentered(
      "Let's Play Garbage!",
      glm::vec2(kWindowSize / 2, kMargin), ci::Color("black"),
      ci::Font("Arial", 50));

  ci::gl::drawStringCentered(
          "2-player game",
      glm::vec2(kWindowSize / 2, 2 * kMargin), ci::Color("blue"),
          ci::Font("Arial", 20));
    ci::gl::drawStringCentered(
            game.to_string(),
            glm::vec2(kWindowSize / 2, kMargin * 6), ci::Color("blue"),
            ci::Font("Arial", 35));
    if (game.is_over()) {
        ci::gl::drawStringCentered(
                game.game_summary(),
                glm::vec2(kWindowSize / 2, kMargin * 8), ci::Color("blue"),
                ci::Font("Arial", 35));
    }
}

void GameApp::mouseDown(ci::app::MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
  if (!game.is_over()) {
      game.step();
  }
  draw();
}

void GameApp::mouseDrag(ci::app::MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
}

void GameApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN:
      // ask your classifier to classify the image that's currently drawn on the
      // sketchpad and update current_prediction_
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      sketchpad_.Clear();
      break;
  }
}

}  // namespace visualizer

}  // namespace naivebayes
