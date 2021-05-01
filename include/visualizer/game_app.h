#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_board.h"
#include <core/Game.h>

namespace garbage {

namespace visualizer {

class GameApp : public ci::app::App {
 public:
  GameApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;
  void handleKeys(size_t rank);

  const double kWindowSize = 1500;  //was 875
  const double kMargin = 100;
  const size_t kImageDimension = 28;

 private:
  GarbageBoard garbage_board;
  Game game;
  int current_prediction_ = -1;
  size_t selected;
  bool is_selected;
  bool request_jack;
  bool invalid_jack;
  std::shared_ptr<ci::gl::Texture2d> mTex[4][13];
  std::shared_ptr<ci::gl::Texture2d> back;    //reverse (face down) side of card
  ci::Rectf rect_p1[11];
  ci::Rectf rect_p2[11];
  ci::Rectf rect_discard;
  Card hand_p1[11];
  Card hand_p2[11];
  //URL of reverse (face down) side of card
  char* back_url = "https://upload.wikimedia.org/wikipedia/commons/thumb/d/d4/Card_back_01.svg/1200px-Card_back_01.svg.png";
   //Ace, 2-10, J, Q, K of clubs, diamonds, hearts, spades
  char* urls[4][13] = {
          {"https://upload.wikimedia.org/wikipedia/commons/thumb/6/61/Ace_of_clubs.svg/1024px-Ace_of_clubs.svg.png",
           "https://upload.wikimedia.org/wikipedia/commons/thumb/4/42/2_of_clubs.svg/1024px-2_of_clubs.svg.png",
           "https://upload.wikimedia.org/wikipedia/commons/thumb/4/4d/3_of_clubs.svg/1024px-3_of_clubs.svg.png",
           "https://upload.wikimedia.org/wikipedia/commons/thumb/e/e5/4_of_clubs.svg/1024px-4_of_clubs.svg.png",
           "https://upload.wikimedia.org/wikipedia/commons/thumb/7/72/5_of_clubs.svg/1024px-5_of_clubs.svg.png",
           "https://upload.wikimedia.org/wikipedia/commons/thumb/4/49/6_of_clubs.svg/1024px-6_of_clubs.svg.png",
           "https://upload.wikimedia.org/wikipedia/commons/thumb/d/db/7_of_clubs.svg/1024px-7_of_clubs.svg.png",
           "https://upload.wikimedia.org/wikipedia/commons/thumb/5/54/8_of_clubs.svg/1024px-8_of_clubs.svg.png",
           "https://upload.wikimedia.org/wikipedia/commons/thumb/6/67/9_of_clubs.svg/1024px-9_of_clubs.svg.png",
           "https://upload.wikimedia.org/wikipedia/commons/thumb/c/c9/10_of_clubs.svg/1024px-10_of_clubs.svg.png",
           "https://upload.wikimedia.org/wikipedia/commons/thumb/7/7b/Jack_of_clubs2.svg/1024px-Jack_of_clubs2.svg.png",
           "https://upload.wikimedia.org/wikipedia/commons/thumb/d/d2/Queen_of_clubs2.svg/1024px-Queen_of_clubs2.svg.png",
           "https://upload.wikimedia.org/wikipedia/commons/thumb/d/d3/King_of_clubs2.svg/1024px-King_of_clubs2.svg.png",
          }, {
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/e/e6/Ace_of_diamonds.svg/1024px-Ace_of_diamonds.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/8/8d/2_of_diamonds.svg/1024px-2_of_diamonds.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/5/50/3_of_diamonds.svg/1024px-3_of_diamonds.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/b/b8/4_of_diamonds.svg/1024px-4_of_diamonds.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/6/6b/5_of_diamonds.svg/1024px-5_of_diamonds.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/3/34/6_of_diamonds.svg/1024px-6_of_diamonds.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/8/83/7_of_diamonds.svg/1024px-7_of_diamonds.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/5/5a/8_of_diamonds.svg/1024px-8_of_diamonds.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/f/f2/9_of_diamonds.svg/1024px-9_of_diamonds.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/f/f3/10_of_diamonds.svg/1024px-10_of_diamonds.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/8/80/Jack_of_diamonds2.svg/1024px-Jack_of_diamonds2.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/d/d9/Queen_of_diamonds2.svg/1024px-Queen_of_diamonds2.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/c/c6/King_of_diamonds2.svg/1024px-King_of_diamonds2.svg.png",
          }, {
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/0/07/Ace_of_hearts.svg/1024px-Ace_of_hearts.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/3/39/2_of_hearts.svg/1024px-2_of_hearts.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/5/5d/3_of_hearts.svg/1024px-3_of_hearts.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/4_of_hearts.svg/1024px-4_of_hearts.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/a/a1/5_of_hearts.svg/1024px-5_of_hearts.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/7/7e/6_of_hearts.svg/1024px-6_of_hearts.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/4/4a/7_of_hearts.svg/1024px-7_of_hearts.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/6/6b/8_of_hearts.svg/1024px-8_of_hearts.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/9/9d/9_of_hearts.svg/1024px-9_of_hearts.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/a/ad/10_of_hearts.svg/1024px-10_of_hearts.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/3/34/Jack_of_hearts2.svg/1024px-Jack_of_hearts2.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/f/f6/Queen_of_hearts2.svg/1024px-Queen_of_hearts2.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/0/06/King_of_hearts2.svg/1024px-King_of_hearts2.svg.png",
          },
          {
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/5/5a/Ace_of_spades.svg/1024px-Ace_of_spades.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/a/a4/2_of_spades.svg/1024px-2_of_spades.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/e/eb/3_of_spades.svg/1024px-3_of_spades.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/a/a4/4_of_spades.svg/1024px-4_of_spades.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/8/8a/5_of_spades.svg/1024px-5_of_spades.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/4/4e/6_of_spades.svg/1024px-6_of_spades.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/f/f7/7_of_spades.svg/1024px-7_of_spades.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/4/40/8_of_spades.svg/1024px-8_of_spades.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/6/63/9_of_spades.svg/1024px-9_of_spades.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/6/68/10_of_spades.svg/1024px-10_of_spades.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/a/a9/Jack_of_spades2.svg/1024px-Jack_of_spades2.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/d/d2/Queen_of_spades2.svg/1024px-Queen_of_spades2.svg.png",
                  "https://upload.wikimedia.org/wikipedia/commons/thumb/2/22/King_of_spades2.svg/1024px-King_of_spades2.svg.png"
          }
  };
};

}  // namespace visualizer

}  // namespace garbage
