#ifndef BLOCK_H
#define BLOCK_H

#include "../util/types.h"
#include "../util/point.h"
#include <memory>
#include <vector>
#include <map>

inline GridItem __ = GridItem{std::nullopt};
inline GridItem I_ = GridItem{I};
inline GridItem J_ = GridItem{J};
inline GridItem O_ = GridItem{O};
inline GridItem S_ = GridItem{S};
inline GridItem Z_ = GridItem{Z};
inline GridItem T_ = GridItem{T};

inline std::map<BlockType, GridShape> blockTypeToData = {
    {I, GridShape{{I_, I_, I_, I_}}},
    {J, GridShape{
        {J_, __, __, __},
        {J_, J_, J_, J_}
    }},
    {O, GridShape{
        {O_, O_},
        {O_, O_}
    }},
    {S, GridShape{
        {__, S_, S_},
        {S_, S_, __}
    }},
    {T, GridShape{
        {T_, T_, T_},
        {__, T_, __}
    }},
    {Z, GridShape{
        {Z_, Z_, __},
        {__, Z_, Z_}
    }}
};

class Block {
  bool isHeavy_;
  GridShape shape_;
  BlockType type_;

  int height_;
  int width_;
  Point bottomLeft_;

public:
  Block(BlockType type, bool isHeavy);

  bool move(Direction d, const GridShape &g);

  void drop();

  bool rotate(RotationDirection d);

  int height() const;

  int width() const;

  Point bottomLeft() const;

  BlockType type() const;

  std::vector<std::vector<GridItem>> shape() const;
};

#endif
