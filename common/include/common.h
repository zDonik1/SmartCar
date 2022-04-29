/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 27/04/2022
 *
 *************************************************************************/

#pragma once

#include <cstdint>

constexpr auto PORT = 10100;

constexpr auto ASPECT_RATIO = 4.f / 3.f;
constexpr int CAPTURE_HEIGHT = 972;
constexpr int CAPTURE_WIDTH = CAPTURE_HEIGHT * ASPECT_RATIO;
constexpr int SCALED_IMAGE_HEIGHT = 180;
constexpr int SCALED_IMAGE_WIDTH = SCALED_IMAGE_HEIGHT * ASPECT_RATIO;
constexpr auto PIXEL_SIZE = 3; // bytes

using SequenceType = uint64_t;
using RowType = uint16_t;
constexpr auto SEQUENCE_SIZE = sizeof(SequenceType);
constexpr auto ROW_SIZE = sizeof(RowType);
constexpr auto LINE_COUNT_SIZE = ROW_SIZE;
constexpr auto HEADER_SIZE = SEQUENCE_SIZE + ROW_SIZE + LINE_COUNT_SIZE;
constexpr auto LINE_SIZE = SCALED_IMAGE_WIDTH * PIXEL_SIZE;

constexpr auto MAX_DATAGRAM_SIZE = 8192; // NOTE: an assumption
constexpr auto LINES_SENT = (MAX_DATAGRAM_SIZE - HEADER_SIZE) / LINE_SIZE;
constexpr auto DATAGRAM_SIZE = HEADER_SIZE + LINE_SIZE * LINES_SENT;
