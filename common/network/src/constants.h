/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#pragma once

#include <cstdint>

using SequenceType = uint64_t;
using RowType = uint16_t;
constexpr auto SEQUENCE_SIZE = sizeof(SequenceType);
constexpr auto ROW_SIZE = sizeof(RowType);
constexpr auto LINE_COUNT_SIZE = ROW_SIZE;
constexpr auto HEADER_SIZE = SEQUENCE_SIZE + ROW_SIZE + LINE_COUNT_SIZE;

constexpr auto MAX_DATAGRAM_SIZE = 2048; // bytes
constexpr unsigned int PIXEL_SIZE = 3; // bytes


constexpr auto lineSize(unsigned int imageWidth)
{
    return imageWidth * PIXEL_SIZE;
}

constexpr auto linesSent(unsigned int imageWidth)
{
    return (MAX_DATAGRAM_SIZE - HEADER_SIZE) / lineSize(imageWidth);
}

constexpr auto datagramSize(unsigned int imageWidth)
{
    return HEADER_SIZE + lineSize(imageWidth) * linesSent(imageWidth);
}
