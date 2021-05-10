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
    //auto img = ci::loadImage( ci::app::loadAsset(
      //      "assets/JPEG/2C.jpg" ) );
        //loadImage(cinder::loadUrl(your_url))
    //char temp[200];
    //char* url = "https://upload.wikimedia.org/wikipedia/commons/thumb/f/f5/Playing_card_%s_%d.svg/1200px-Playing_card_%s_%d.svg.png";
    for (size_t suit = 0; suit < 4; suit++) {
        for (size_t rank = 0; rank < 13; rank++) {
            //string s;
            /*switch (suit) {
                case 0:
                    s = "club";
                    break;
                case 1:
                    s = "diamond";
                    break;
                case 2:
                    s = "heart";
                    break;
                case 3:
                    s = "spade";
                    break;
            }*/
            //if (sprintf(temp, url, s.c_str(), (rank + 1)) < 0) {
              //  perror("sprintf");
            //}  //temp becomes url
            //auto img = ci::loadImage(cinder::loadUrl(temp));
            auto img = ci::loadImage(cinder::loadUrl(urls[suit][rank]));
            mTex[suit][rank] = ci::gl::Texture2d::create(img);
        }
    }
    auto img_back = ci::loadImage(cinder::loadUrl(back_url));
    back = ci::gl::Texture2d::create(img_back);
    //auto img = ci::loadImage(cinder::loadUrl(
      //      "https://upload.wikimedia.org/wikipedia/commons/thumb/f/f5/Playing_card_club_2.svg/1200px-Playing_card_club_2.svg.png"));
    //mTex = ci::gl::Texture2d::create(img);
    //rect = ci::RectT<ci::gl::Texture2dRef>(mTex);
    //set each player's board
    for (size_t i = 0; i < 10; i++) {   //+ 1 to avoid multiplying by 0 and not moving from edge
        rect_p1[i].set((float) (kMargin + 1) * (i + 1),
                       (float) (kMargin + 1 + (float) (1 * kMargin)),
                       (float) (kMargin + 1) * ((i + 1) + 0.9f),
                       (float) (kMargin + 1) * 1 + (float) (2 * kMargin));
        rect_p2[i].set((float) (kMargin + 1) * (i + 1),
                       (float) (kMargin + 1) * 2 + (float) (2 * kMargin),
                       (float) (kMargin + 1) * ((i + 1) + 0.9f),
                       (float) (kMargin + 1) * 3 + (float) (2 * kMargin));
    }
    //set card to be played separately
    size_t i = 11;
    rect_p1[10].set((float) (kMargin + 1) * (i + 1),
                   (float) (kMargin + 1) + (float) (1 * kMargin),
                   (float) (kMargin + 1) * ((i + 1) + 0.9f),
                   (float) (kMargin + 1) * 1 + (float) (2 * kMargin));
    rect_p2[10].set((float) (kMargin + 1) * (i + 1),
                   (float) (kMargin + 1) * 2 + (float) (2 * kMargin),
                   (float) (kMargin + 1) * ((i + 1) + 0.9f),
                   (float) (kMargin + 1) * 3 + (float) (2 * kMargin));
    i = 6;  //moves discard towards middle and enlarges image
    rect_discard.set((float) (kMargin + 1) * (i + 0.5f),
                    (float) (kMargin + 1) * 9 + (float) (2 * kMargin),
                    (float) (kMargin + 1) * ((i + 1) + 1.3f),
                    (float) (kMargin + 1) * 11 + (float) (2 * kMargin));
}

void GameApp::draw() {
  ci::Color8u background_color(	212, 235, 242);  // light blue
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
            game.to_string(0),
            glm::vec2(kWindowSize / 2, kMargin * 3.3), ci::Color("blue"),
            ci::Font("Arial", 35));
    ci::gl::drawStringCentered(
            game.to_string(1),
            glm::vec2(kWindowSize / 2, kMargin * 5.4), ci::Color("blue"),
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
                    glm::vec2(kWindowSize / 2, kMargin * 9), ci::Color("blue"),
                    ci::Font("Arial", 35));
            //invalid_jack = false;
        }
    }
    //ci::gl::draw(mTex);
    //ci::gl::draw(mTex, rect);
    game.get_summary(hand_p1, 0);
    game.get_summary(hand_p2, 1);
    for (size_t i = 0; i < 11; i++) {
        std::cout<<"p1 card "<<i<<" "<<hand_p1[i]<<std::endl;
        std::cout<<"p2 card "<<i<<" "<<hand_p2[i]<<std::endl;
        if (hand_p1[i].get_face_up()) {
            size_t p1_rank = hand_p1[i].get_rank_int();
            size_t p1_suit = hand_p1[i].get_suit_int();
            ci::gl::draw(mTex[p1_suit][p1_rank - 1], rect_p1[i]);
        } else {
            ci::gl::draw(back, rect_p1[i]);
        }
        if (hand_p2[i].get_face_up()) {
            size_t p2_rank = hand_p2[i].get_rank_int();
            size_t p2_suit = hand_p2[i].get_suit_int();
            ci::gl::draw(mTex[p2_suit][p2_rank - 1], rect_p2[i]);
        } else {
            ci::gl::draw(back, rect_p2[i]);
        }
    }
    ci::gl::drawStringCentered(
            "DISCARD:",
            glm::vec2(kWindowSize / 2, kMargin * 10), ci::Color("blue"),
            ci::Font("Arial", 40));
    Card discard = game.get_last_discard();
    if (discard.get_rank_int() == 0) {
        ci::gl::draw(back, rect_discard);
    } else {
        size_t rank = discard.get_rank_int();
        size_t suit = discard.get_suit_int();
        ci::gl::draw(mTex[suit][rank - 1], rect_discard);
    }
    //ci::app::getAssetPath("assets/2C.jpg");
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
    if (game.is_rank_good(rank) && request_jack) {
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
