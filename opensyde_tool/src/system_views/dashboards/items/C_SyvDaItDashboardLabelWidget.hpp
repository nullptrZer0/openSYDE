//----------------------------------------------------------------------------------------------------------------------
/*!
   \file
   \brief       Widget base for dashboard label widget (header)

   See cpp file for detailed description

   \copyright   Copyright 2017 Sensor-Technik Wiedemann GmbH. All rights reserved.
*/
//----------------------------------------------------------------------------------------------------------------------
#ifndef C_SYVDADASHBOARDLABELWIDGET_H
#define C_SYVDADASHBOARDLABELWIDGET_H

/* -- Includes ------------------------------------------------------------------------------------------------------ */
#include <QWidget>
#include "C_PuiSvDbLabel.hpp"

/* -- Namespace ----------------------------------------------------------------------------------------------------- */
namespace Ui
{
class C_SyvDaItDashboardLabelWidget;
}

namespace stw
{
namespace opensyde_gui
{
/* -- Global Constants ---------------------------------------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------------------------------------------------- */
class C_SyvDaItDashboardLabelWidget :
   public QWidget
{
   Q_OBJECT

public:
   explicit C_SyvDaItDashboardLabelWidget(QWidget * const opc_Parent = NULL);
   ~C_SyvDaItDashboardLabelWidget(void) override;

   void ResetFont(void) const;
   void SetCaption(const QString & orc_Text) const;
   void SetValue(const QString & orc_Text) const;
   void SetUnit(const QString & orc_Text);

   void AdjustFontToSize(void) const;
   void SetDisplayStyle(const stw::opensyde_gui_logic::C_PuiSvDbLabel::E_Type oe_Type, const bool oq_ShowCaption,
                        const bool oq_ShowUnit);

protected:
   void resizeEvent(QResizeEvent * const opc_Event) override;
   void paintEvent(QPaintEvent * const opc_Event) override;

private:
   Ui::C_SyvDaItDashboardLabelWidget * mpc_Ui;
   QString mc_Value;
   QString mc_Unit;
   bool mq_ShowUnit;

   void m_UpdateCaptionFont(void) const;
   //Avoid call
   C_SyvDaItDashboardLabelWidget(const C_SyvDaItDashboardLabelWidget &);
   C_SyvDaItDashboardLabelWidget & operator =(const C_SyvDaItDashboardLabelWidget &) &;
};

/* -- Extern Global Variables --------------------------------------------------------------------------------------- */
}
} //end of namespace

#endif
