#ifndef VIRTUALBLOCK_H
#define VIRTUALBLOCK_H

/*!
 * \brief The IBlock class
 *
 *  Any visible thing on the canvas, and not the wire, are block. the term
 * "block" describes the minimal visible unit on the canvas.
 *
 * Although the class name is "IBlock", this class is actually an Abstract base
 * class cause it contain some concrete implementation. One can't instantialte
 * this class since it contain pure virtual function.
 *
 * A typical block has an rectangle profile.
 */
#include <QPainter>
#include <QPoint>
class IBlock {
 public:
  /*!
   * \brief The position struct
   * this struct were used to describe where the block are and how big it will
   * be.
   * releative to the canvas.
   */
  struct position {
    /*!
     * Since a block must be drawn in a canva,  all the coordinates are
     * releative to the canvas.
     */
    QPointF leftTopPoint;
    /*!
     * the width of the block *profile*. this  attribute and the height will
     * decide how big the block is .
     *
     * notice that the visible area of a block may smaller than the size
     * defined by this attribute.
     * \sa IBlock::position::height
     */

    int width;
    /*!
     * \sa IBlock::position::width
     */
    int height;
  };
  /*!
   * All block  had  three status. When the metainfo is loaded from  Under
   'floating' status, the block
   * will fllow the user's mouse pointer.
   * Under 'fixed" status, the block will be rendered normally on the canvas.
   * \dotfile   blockFSMGraph.dot
   *
   */
  enum BlockStatus { loaded, floating, fixed };
  /*!
   * draw itself
   */
  virtual void paintSelf(QPainter* paint) = 0;

  // protected:
  position mPosition;
};

#endif  // VIRTUALBLOCK_H
