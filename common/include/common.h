/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 27/04/2022
 *
 *************************************************************************/

#pragma once

constexpr auto PORT = 10100;

constexpr auto ASPECT_RATIO = 4.f / 3.f;
constexpr int CAPTURE_HEIGHT = 972;
constexpr int CAPTURE_WIDTH = CAPTURE_HEIGHT * ASPECT_RATIO;
constexpr auto PIXEL_SIZE = 3; // bytes
constexpr auto IMAGE_SIZE = CAPTURE_HEIGHT * CAPTURE_WIDTH * PIXEL_SIZE;
