//----------------------------------------------------------------------------------------------------------------------
/*!
   \file
   \brief       Hover widget in material design

   \copyright   Copyright 2016 Sensor-Technik Wiedemann GmbH. All rights reserved.
*/
//----------------------------------------------------------------------------------------------------------------------

#ifndef C_OGEWIHOVER_H
#define C_OGEWIHOVER_H

/* -- Includes ------------------------------------------------------------------------------------------------------ */

#include <QWidget>
#include <QPoint>
#include <QTimer>

#include "stwtypes.hpp"

/* -- Namespace ----------------------------------------------------------------------------------------------------- */

namespace Ui
{
class C_OgeWiHover;
}

namespace stw
{
namespace opensyde_gui_elements
{
/* -- Global Constants ---------------------------------------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------------------------------------------------- */
class C_OgeWiHover :
   public QWidget
{
   Q_OBJECT

public:
   explicit C_OgeWiHover(QWidget & orc_Widget, const QString & orc_Title, const QString & orc_Icon,
                         const bool oq_Search, QWidget * const opc_ContainerWidget, QWidget * const opc_Parent = NULL);

   ~C_OgeWiHover() override;
   void InitStaticNames(void) const;
   bool GetMaximized(void) const;
   void SetMaximized(const bool oq_Maximized);
   int32_t GetMaximizedHeight(void) const;
   void SetMaximizedHeight(const int32_t os32_Height);
   void ApplyDarkMode(const bool oq_Active);

   //The signals keyword is necessary for Qt signal slot functionality
   //lint -save -e1736

Q_SIGNALS:
   //lint -restore
   void SigSearchChanged(const QString & orc_Text);
   void SigWiHoverMinBtnClicked(void);

private:
   Ui::C_OgeWiHover * mpc_Ui;
   QWidget * mpc_Widget;
   QWidget * mpc_ContainerWidget;
   QPoint mc_OldPosition;
   QTimer mc_TimerAnimation;
   bool mq_Maximized;
   int32_t ms32_Height;
   int32_t ms32_StepSize;
   uint32_t mu32_MouseMode;
   uint32_t mu32_ResizeMode;
   QString mc_IconPath;
   const bool mq_SearchActive;
   QSize mc_ParentWidgetSize;
   QPoint mc_ParentWidgetTopLeft;
   int32_t ms32_OffsetHorizontal;
   int32_t ms32_OffsetVertical;
   int32_t ms32_OffsetHorizontalRight;
   bool mq_DarkMode;

   void m_MoveWidget(const QMouseEvent * const opc_Event);
   void m_ResizeWidget(const QMouseEvent * const opc_Event);

   void m_AnimationTimerEvent(void);
   void m_SearchChanged(const QString & orc_Text);
   void m_UpdateParentSize(void);

   static uint32_t mh_GetResizeMode(const QPoint & orc_Pos, const QSize & orc_Size, const bool oq_Maximized);

   static void mh_AdaptMouseRangePos(QPoint & orc_Pos, const QSize & orc_Range, const QPoint & orc_TopLeft,
                                     const int32_t os32_OffsetHorizontal, const int32_t os32_OffsetVertical);
   void m_HandleBasicCursorState(const QPoint & orc_Pos);
   void m_CancelSearch(void) const;

   //Avoid call
   C_OgeWiHover(const C_OgeWiHover &);
   C_OgeWiHover & operator =(const C_OgeWiHover &) &;

protected:
   void mousePressEvent(QMouseEvent * const opc_Event) override;
   void mouseMoveEvent(QMouseEvent * const opc_Event) override;
   void mouseReleaseEvent(QMouseEvent * const opc_Event) override;
   void resizeEvent(QResizeEvent * const opc_Event) override;
};

/* -- Extern Global Variables --------------------------------------------------------------------------------------- */
}
} //end of namespace

#endif
