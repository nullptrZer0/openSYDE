//----------------------------------------------------------------------------------------------------------------------
/*!
   \file
   \brief       Visualization of the node boundary with its filled colors (header)

   \copyright   Copyright 2016 Sensor-Technik Wiedemann GmbH. All rights reserved.
*/
//----------------------------------------------------------------------------------------------------------------------
#ifndef C_GINODEBOUNDARY_H
#define C_GINODEBOUNDARY_H

/* -- Includes ------------------------------------------------------------------------------------------------------ */
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>

#include "stwtypes.hpp"

#include "C_GiBiSizeableItem.hpp"

/* -- Namespace ----------------------------------------------------------------------------------------------------- */
namespace stw
{
namespace opensyde_gui
{
/* -- Global Constants ---------------------------------------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------------------------------------------------- */

class C_GiNodeBoundary :
   public QGraphicsItem,
   public C_GiBiSizeableItem
{
public:
   C_GiNodeBoundary(const QString & orc_Text, const float64_t of64_Width, const float64_t of64_Height,
                    const uint32_t ou32_SubNodesCount, QGraphicsItem * const opc_Parent = NULL);
   ~C_GiNodeBoundary() override;

   QRectF boundingRect() const override;
   void paint(QPainter * const opc_Painter, const QStyleOptionGraphicsItem * const opc_Option,
              QWidget * const opc_Widget) override;
   void Redraw(void) override;
   void SetText(const QString & orc_Text);
   void SetFont(const QFont & orc_Font);
   void SetDrawBorder(const bool oq_Active);
   void SetDrawWhiteFilter(const bool oq_Active);

private:
   //Avoid call
   C_GiNodeBoundary(const C_GiNodeBoundary &);
   C_GiNodeBoundary & operator =(const C_GiNodeBoundary &) &; //lint !e1511 //we want to hide the base func.

   QString mc_Text;
   QFont mc_Font;
   QGraphicsDropShadowEffect * mpc_Shadow;

   void m_DrawBackground(QPainter * const opc_Painter) const;
   bool mq_DrawBoder;
   bool mq_DrawWhiteFilter;
   uint32_t mu32_SubNodesCount;
};

/* -- Extern Global Variables --------------------------------------------------------------------------------------- */
}
} //end of namespace

#endif
