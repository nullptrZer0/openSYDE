//----------------------------------------------------------------------------------------------------------------------
/*!
   \file
   \brief       Widget for node edit

   \copyright   Copyright 2017 Sensor-Technik Wiedemann GmbH. All rights reserved.
*/
//----------------------------------------------------------------------------------------------------------------------

#ifndef C_SDNDENODEEDITWIDGET_H
#define C_SDNDENODEEDITWIDGET_H

/* -- Includes ------------------------------------------------------------------------------------------------------ */
#include <QWidget>

#include "stwtypes.h"

#include "C_SdNdeHalcWidget.h"
#include "C_SdNdeDpEditWidget.h"
#include "C_SdBueComIfDescriptionWidget.h"
#include "C_SdNdeNodePropertiesTabContentWidget.h"
#include "C_SdNdeCoWidget.h"

/* -- Namespace ----------------------------------------------------------------------------------------------------- */

namespace Ui
{
class C_SdNdeNodeEditWidget;
}

namespace stw_opensyde_gui
{
/* -- Global Constants ---------------------------------------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------------------------------------------------- */

class C_SdNdeNodeEditWidget :
   public QWidget
{
   Q_OBJECT

public:
   explicit C_SdNdeNodeEditWidget(const stw_types::uint32 ou32_NodeIndex, const stw_types::sintn osn_TabIndex,
                                  QWidget * const opc_Parent = NULL);
   virtual ~C_SdNdeNodeEditWidget();

   void InitStaticNames(void) const;
   bool WasChanged(void) const;
   void Save(void) const;
   void SetFlag(const stw_types::uint32 ou32_Flag) const;
   void OpenDetail(const stw_types::sint32 os32_MainIndex, const stw_types::sint32 os32_ListIndex,
                   const stw_types::sint32 os32_ElementIndex, const stw_types::sint32 os32_Flag);
   void AddFromTSP(void);
   stw_types::sintn GetTabIndex(void) const;

   static const stw_types::sintn hsn_TAB_INDEX_PROPERTIES;
   static const stw_types::sintn hsn_TAB_INDEX_DATA_POOL;
   static const stw_types::sintn hsn_TAB_INDEX_COMM;
   static const stw_types::sintn hsn_TAB_INDEX_CO_MANAGER;
   static const stw_types::sintn hsn_TAB_INDEX_HALC;

   //The signals keyword is necessary for Qt signal slot functionality
   //lint -save -e1736

Q_SIGNALS:
   //lint -restore
   void SigChanged(void);
   void SigErrorChange(void);
   void SigSwitchToDataPool(const stw_types::uint32 & oru32_BusIndex, const QString & orc_BusName);
   void SigSwitchToBus(const stw_types::uint32 & oru32_BusIndex, const QString & orc_BusName);
   void SigSwitchToBusProperties(const stw_types::uint32 & oru32_BusIndex, const QString & orc_BusName);
   void SigNameChanged(const QString & orc_Name, const QString & orc_SubItemName,
                       const bool oq_CombineItemAndSubSubName);
   void SigSave(void);
   void SigSaveAs(void);

protected:
   virtual void showEvent(QShowEvent * const opc_Event) override;
   virtual void hideEvent(QHideEvent * const opc_Event) override;

private:
   //Avoid call
   C_SdNdeNodeEditWidget(const C_SdNdeNodeEditWidget &);
   C_SdNdeNodeEditWidget & operator =(const C_SdNdeNodeEditWidget &);

   void m_LoadUserSettings(void) const;
   void m_SaveUserSettings(void) const;
   void m_DataChanged(void);
   void m_OnSwitchToBus(const stw_types::uint32 & oru32_BusIndex, const QString & orc_BusName);
   void m_OnSwitchToHalc(void);
   void m_OnSwitchToCommMessages(const stw_types::uint32 ou32_DataPoolIndex);
   void m_CurrentTabChanged(const stw_types::sintn osn_Index);
   void m_TabClicked(const stw_types::sintn osn_Index) const;
   void m_CreateTabWidgetsAlways(const stw_types::sintn osn_Index, const bool oq_AdaptCursor);
   void m_ReloadDataPools(void) const;
   void m_ReloadCommMessages(void) const;
   void m_ReloadCommDatapools(void) const;
   void m_HalcLoadedFromTSP(void) const;
   void m_CreatePropertiesTab(const bool oq_AdaptCursor);
   void m_CreateDpTab(const bool oq_AdaptCursor);
   void m_CreateCommTab(const bool oq_AdaptCursor);
   void m_CreateHalTab(const bool oq_AdaptCursor);
   void m_CreateCoManagerTab(const bool oq_AdaptCursor);
   static void mh_StartWaitingCursor(void);
   static void mh_EndWaitingCursor(void);

   Ui::C_SdNdeNodeEditWidget * mpc_Ui;
   const stw_types::uint32 mu32_NodeIndex;
   bool mq_DataChanged;
   bool mq_SkipLoadUserSettings;
   C_SdNdeNodePropertiesTabContentWidget * mpc_PropertiesWidget;
   C_SdNdeDpEditWidget * mpc_DataPoolEditWidget;
   C_SdBueComIfDescriptionWidget * mpc_ComIfDescriptionWidget;
   C_SdNdeHalcWidget * mpc_HalWidget;
   C_SdNdeCoWidget * mpc_CoManagerWidget;
};

/* -- Extern Global Variables --------------------------------------------------------------------------------------- */
} //end of namespace

#endif
