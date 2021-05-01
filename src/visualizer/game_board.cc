#include <visualizer/game_board.h>

namespace garbage {

namespace visualizer {

using glm::vec2;

GarbageBoard::GarbageBoard(const vec2& top_left_corner, size_t num_pixels_per_side,
                           double sketchpad_size)
    : top_left_corner_(top_left_corner),
      num_pixels_per_side_(num_pixels_per_side),
      pixel_side_length_(sketchpad_size / num_pixels_per_side) {}

}  // namespace visualizer

}  // namespace garbage
