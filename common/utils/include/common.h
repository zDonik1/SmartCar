/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 27/04/2022
 *
 *************************************************************************/

#pragma once

constexpr auto FRAME_PORT = 10100;
constexpr auto MOVE_PORT = FRAME_PORT + 1;

constexpr auto ASPECT_RATIO = 4.f / 3.f;
constexpr unsigned int SCALED_IMAGE_HEIGHT = 60;
constexpr unsigned int SCALED_IMAGE_WIDTH = SCALED_IMAGE_HEIGHT * ASPECT_RATIO;
