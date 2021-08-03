#ifndef BLOCK_H
#define BLOCK_H

#include "../util/types.h"
#include "../util/point.h"
#include <memory>
#include <vector>
#include <map>

// inline grid items to easily map a block type to its corresponding shape
inline GridItem __ = GridItem{std::nullopt};
inline GridItem I_ = GridItem{I};
inline GridItem J_ = GridItem{J};
inline GridItem L_ = GridItem{L};
inline GridItem O_ = GridItem{O};
inline GridItem S_ = GridItem{S};
inline GridItem Z_ = GridItem{Z};
inline GridItem T_ = GridItem{T};
inline GridItem LFOUR_ = GridItem{LFOUR};

inline std::map<BlockType, GridShape> blockTypeToData = {
    {I, GridShape{{I_, I_, I_, I_}}},
    {J, GridShape{
        {J_, __, __},
        {J_, J_, J_}
    }},
    {L, GridShape{
        {__, __, L_},
        {L_, L_, L_}
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
    {LFOUR, GridShape{
        {LFOUR_}
    }},
    {Z, GridShape{
        {Z_, Z_, __},
        {__, Z_, Z_}
    }}
};

// Block class
class Block {
  bool isHeavy_;
  GridShape shape_;
  BlockType type_;
  int blockId_;

  int height_;
  int width_;
  Point bottomLeft_;

public:
  Block(BlockType type, bool isHeavy);

  // moves the block and returns a bool indicating if we should remove the block
  bool move(Direction d, GridShape &g);

  // drops the block until we've reached the bottom of a grid or intersect another block
  void drop(GridShape &g);

  // checks if the block intersects with any of the grid blocks or the edges
  bool intersects(const Point &p, const GridShape &g);

  bool intersects(const Point &p, const GridShape &g, const GridShape &blockShape);

  // puts the given GridShape onto the grid
  void copyToGrid(GridShape &g);

  // rotates the block and returns a bool indicating if we should remove the block 
  bool rotate(RotationDirection d, const GridShape &g);

  // accessor functions
  int height() const;

  int width() const;

  Point bottomLeft() const;

  BlockType type() const;

  std::vector<std::vector<GridItem>> shape() const;

  bool heavy() const;

  // setter function
  void setType(BlockType);
};

#endif
