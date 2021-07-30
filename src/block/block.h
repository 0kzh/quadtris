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
inline GridItem L_ = GridItem{L};
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
    {L, GridShape{
        {__, __, __, L_},
        {L_, L_, L_, L_}
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
  int generatedLvl_;
  Point bottomLeft_;

public:
  Block(BlockType type, bool isHeavy);

  // moves the block and returns a bool indicating if we should remove the block;
  bool move(Direction d, GridShape &g);

  void drop(GridShape &g);

  // checks if the block intersects with any of the grid blocks or the edges
  bool intersects(const Point &p, const GridShape &g);

  bool intersects(const Point &p, const GridShape &g, const GridShape &blockShape);

  void copyToGrid(GridShape &g);

  bool rotate(RotationDirection d, const GridShape &g);

  int height() const;

  int width() const;

  Point bottomLeft() const;

  BlockType type() const;

  std::vector<std::vector<GridItem>> shape() const;
};

#endif
