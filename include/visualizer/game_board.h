#pragma once

#include "cinder/gl/gl.h"

namespace garbage {

namespace visualizer {

/**
 * A Garbage game which will be displayed in the Cinder application and respond to
 * mouse events.
 */
class GarbageBoard {
 public:
  /**
   * Creates a Garbage board.
   *
   * @param top_left_corner     the screen coordinates of the top left corner of
   *                            the app
   * @param num_pixels_per_side the number of app pixels in one row/column
   *                            of the sketchpad
   * @param sketchpad_size      the side length of the app, measured in
   *                            screen pixels
   */
  GarbageBoard(const glm::vec2& top_left_corner, size_t num_pixels_per_side,
               double sketchpad_size);

 private:
  glm::vec2 top_left_corner_;

  size_t num_pixels_per_side_;

  /** Number of screen pixels in the width/height of one sketchpad pixel */
  double pixel_side_length_;
};

}  // namespace visualizer

}  // namespace garbage
