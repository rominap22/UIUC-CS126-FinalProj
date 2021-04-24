#include <visualizer/game_app.h>
namespace naivebayes {

namespace visualizer {

GameApp::GameApp()
    : sketchpad_(glm::vec2(kMargin, kMargin), kImageDimension,
                 kWindowSize - 2 * kMargin) {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
  selected = 0;
  is_selected = false;
  request_jack = false;
    //std::shared_ptr<ci::DataSource> img = loadAsset("assets/2C.jpg");
    auto img = ci::loadImage( ci::app::loadAsset(
            "../../assets/2C.jpg" ) );
    //std::shared_ptr<ci::gl::Texture2d> mTex = ci::gl::Texture2d::create(img);
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
    } else if (request_jack) {
        ci::gl::drawStringCentered(
                "use keyboard to enter placement of Jack (0 for 10)",
                glm::vec2(kWindowSize / 2, kMargin * 8), ci::Color("blue"),
                ci::Font("Arial", 35));
        if (invalid_jack) {
            ci::gl::drawStringCentered(
                    "invalid location of jack. You must select a face down card location (0 for 10)",
                    glm::vec2(kWindowSize / 2, kMargin * 10), ci::Color("blue"),
                    ci::Font("Arial", 35));
            //invalid_jack = false;
        }
    }
    //ci::gl::draw(mTex);
    //ci::gl::Texture texture = loadImage( loadAsset( "pictures/photo1.jpg" ) );
    //ci::gl::Texture texture = ci::loadImage("C:\\Users\\romip\\Downloads\\cards_jpeg_zip\\JPEG\\2C.jpeg");
}

void GameApp::mouseDown(ci::app::MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
  if (!game.is_over() && !request_jack) {
      game.step();
      if (game.is_jack()) {
          std::cout<<"line 60 game app: "<<game.is_jack()<<std::endl;
          request_jack = true;
          invalid_jack = false;
      }
  }
  draw();
}

void GameApp::mouseDrag(ci::app::MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
}
void GameApp::handleKeys(size_t rank) {
    std::cout<<"game app line 71: "<<game.is_rank_good(rank)<<", rank = "<<rank<<std::endl;
    if (game.is_rank_good(rank)) {
        selected = rank;
        is_selected = true;
        request_jack = false;
        game.place_jack(rank);
    } else {
        invalid_jack = true;
    }
    draw();
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
      case ci::app::KeyEvent::KEY_1:    //ace
          handleKeys(1);
          break;
      case ci::app::KeyEvent::KEY_2:
          handleKeys(2);
          break;
      case ci::app::KeyEvent::KEY_3:
          handleKeys(3);
          break;
      case ci::app::KeyEvent::KEY_4:
          handleKeys(4);
          break;
      case ci::app::KeyEvent::KEY_5:
          handleKeys(5);
          break;
      case ci::app::KeyEvent::KEY_6:
          handleKeys(6);
          break;
      case ci::app::KeyEvent::KEY_7:
          handleKeys(7);
          break;
      case ci::app::KeyEvent::KEY_8:
          handleKeys(8);
          break;
      case ci::app::KeyEvent::KEY_9:
          handleKeys(9);
          break;
      case ci::app::KeyEvent::KEY_0:
          handleKeys(10);
          break;
  }
}

}  // namespace visualizer

}  // namespace naivebayes
