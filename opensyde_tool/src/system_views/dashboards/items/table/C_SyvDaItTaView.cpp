//----------------------------------------------------------------------------------------------------------------------
/*!
   \file
   \brief       Table view for dashboard table widget (implementation)

   Table view for dashboard table widget

   \copyright   Copyright 2017 Sensor-Technik Wiedemann GmbH. All rights reserved.
*/
//----------------------------------------------------------------------------------------------------------------------

/* -- Includes ------------------------------------------------------------------------------------------------------ */
#include "precomp_headers.hpp"

#include <QScrollBar>
#include <QHeaderView>
#include <QMouseEvent>

#include "C_Uti.hpp"
#include "stwtypes.hpp"
#include "TglUtils.hpp"
#include "C_OgeWiUtil.hpp"
#include "C_PuiSdHandler.hpp"
#include "C_SyvDaItTaView.hpp"

/* -- Used Namespaces ----------------------------------------------------------------------------------------------- */
using namespace stw::opensyde_gui;
using namespace stw::opensyde_core;
using namespace stw::opensyde_gui_logic;

/* -- Module Global Constants --------------------------------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------------------------------------------------- */

/* -- Module Global Variables --------------------------------------------------------------------------------------- */

/* -- Module Global Function Prototypes ----------------------------------------------------------------------------- */

/* -- Implementation ------------------------------------------------------------------------------------------------ */

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Default constructor

   Set up GUI with all elements.

   \param[in,out]  opc_Data      Data storage
   \param[in,out]  opc_Parent    Optional pointer to parent
*/
//----------------------------------------------------------------------------------------------------------------------
C_SyvDaItTaView::C_SyvDaItTaView(C_PuiSvDbDataElementHandler * const opc_Data, QWidget * const opc_Parent) :
   C_TblViewScroll(opc_Parent),
   mc_Model(opc_Data)
{
   //Model
   this->C_SyvDaItTaView::setModel(&mc_Model);

   //Drawing delegate
   this->setItemDelegate(&mc_Delegate);

   //UI Settings
   this->setCornerButtonEnabled(false);
   this->setSortingEnabled(false);
   this->setGridStyle(Qt::NoPen);
   this->setShowGrid(false);
   this->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
   this->SetSelectionAvailable(true, false);
   this->setAlternatingRowColors(true);
   this->setDragDropMode(QAbstractItemView::DragDropMode::NoDragDrop);
   this->setDefaultDropAction(Qt::DropAction::MoveAction);
   this->setDragEnabled(false);
   this->setLineWidth(0);
   this->setFrameShadow(QAbstractItemView::Shadow::Plain);
   this->setFrameShape(QAbstractItemView::Shape::NoFrame);
   this->setEditTriggers(EditTrigger::NoEditTriggers);
   //Consider all elements for resize
   this->mpc_TableHeaderView = new C_SyvDaItTableHeaderView(Qt::Horizontal);
   this->setHorizontalHeader(this->mpc_TableHeaderView);
   this->horizontalHeader()->setStretchLastSection(false);
   this->horizontalHeader()->setFixedHeight(27);
   this->horizontalHeader()->setMinimumSectionSize(4);
   //Row Height
   this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
   this->verticalHeader()->setDefaultSectionSize(20);
   //Icon
   this->setIconSize(QSize(16, 16));

   //Hide vertical header
   this->verticalHeader()->hide();

   //Hover event
   this->setMouseTracking(true);
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Default destructor

   Clean up.
*/
//----------------------------------------------------------------------------------------------------------------------
//lint -e{1540}  no memory leak because of the parent of mpc_TableHeaderView assigned by setHorizontalHeader and the Qt
// memory management
C_SyvDaItTaView::~C_SyvDaItTaView(void)
{
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Initialize min & max values and names for data elements
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::UpdateStaticValues(void)
{
   this->mc_Model.InitMinMaxAndName();
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Get newest values
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::UpdateValue(void)
{
   this->mc_Model.UpdateValue();
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Update the error icon
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::UpdateError(void)
{
   this->mc_Model.UpdateError();
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Update of the color transparency value configured by the actual timeout state

   \param[in]  ou32_DataElementIndex   Index of shown datapool element in widget
   \param[in]  os32_Value               Value for transparency (0..255)
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::UpdateTransparency(const uint32_t ou32_DataElementIndex, const int32_t os32_Value)
{
   this->mc_Model.UpdateTransparency(ou32_DataElementIndex, os32_Value);
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Add new data element

   \param[in]  orc_DataPoolElementId   New data element ID
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::AddItem(const C_PuiSvDbNodeDataPoolListElementId & orc_DataPoolElementId)
{
   const QModelIndexList c_IndexList = this->selectedIndexes();
   const uint32_t u32_NewItem = this->mc_Model.AddItem(c_IndexList, orc_DataPoolElementId);

   // select new item
   this->selectRow(u32_NewItem);
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief  Move selected items

   \param[in]  oq_Up    Flag to switch to move one step up or down
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::MoveSelected(const bool oq_Up)
{
   const QModelIndexList c_IndexList = this->selectedIndexes();

   this->mc_Model.MoveItems(c_IndexList, oq_Up);
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Remove all selected items

   \param[in,out]  orc_RemovedDataElements   Removed data elements
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::RemoveSelectedItems(std::vector<C_PuiSvDbNodeDataPoolListElementId> & orc_RemovedDataElements)
{
   const QModelIndexList c_IndexList = this->selectedIndexes();

   this->mc_Model.RemoveItems(c_IndexList, orc_RemovedDataElements);
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Get selected item indices

   \return
   Selected item indices
*/
//----------------------------------------------------------------------------------------------------------------------
std::vector<uint32_t> C_SyvDaItTaView::GetUniqueSelectedRows(void) const
{
   std::vector<uint32_t> c_Retval;
   const QModelIndexList c_IndexList = this->selectedIndexes();
   this->mc_Model.GetUniqueRows(c_IndexList, c_Retval);
   return c_Retval;
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Get only valid selected item indices

   \return
   Only valid selected item indices
*/
//----------------------------------------------------------------------------------------------------------------------
std::vector<uint32_t> C_SyvDaItTaView::GetUniqueAndValidSelectedRows(void) const
{
   std::vector<uint32_t> c_Retval;
   const std::vector<uint32_t> c_Tmp = GetUniqueSelectedRows();
   for (uint32_t u32_It = 0UL; u32_It < c_Tmp.size(); ++u32_It)
   {
      const C_PuiSvDbNodeDataPoolListElementId * const pc_DataElementId =
         this->mc_Model.GetDataPoolElementIndex(c_Tmp[u32_It]);
      if ((pc_DataElementId != NULL) && (pc_DataElementId->GetIsValid() == true))
      {
         c_Retval.push_back(c_Tmp[u32_It]);
      }
   }
   return c_Retval;
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Restore column widths

   \param[in]  orc_ColumnWidths  Stored column widths (Restores default values if empty)
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::SetCurrentColumnWidths(const std::vector<int32_t> & orc_ColumnWidths)
{
   if (orc_ColumnWidths.size() > 0)
   {
      for (uint32_t u32_ItCol = 0; u32_ItCol < orc_ColumnWidths.size(); ++u32_ItCol)
      {
         this->setColumnWidth(static_cast<int32_t>(u32_ItCol), orc_ColumnWidths[u32_ItCol]);
      }
   }
   else
   {
      //Default
      this->setColumnWidth(C_SyvDaItTaModel::h_EnumToColumn(C_SyvDaItTaModel::eICON), 26);
      this->setColumnWidth(C_SyvDaItTaModel::h_EnumToColumn(C_SyvDaItTaModel::eNAME), 150);
      this->setColumnWidth(C_SyvDaItTaModel::h_EnumToColumn(C_SyvDaItTaModel::eVALUE), 150);
      this->setColumnWidth(C_SyvDaItTaModel::h_EnumToColumn(C_SyvDaItTaModel::eBAR), 150);
   }
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Get current column widths

   \return
   Current column widths
*/
//----------------------------------------------------------------------------------------------------------------------
std::vector<int32_t> C_SyvDaItTaView::GetCurrentColumnWidths(void) const
{
   std::vector<int32_t> c_Retval;
   c_Retval.reserve(this->model()->columnCount());
   for (int32_t s32_ItCol = 0; s32_ItCol < this->model()->columnCount(); ++s32_ItCol)
   {
      c_Retval.push_back(this->columnWidth(s32_ItCol));
   }
   return c_Retval;
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Set selection available if necessary

   \param[in]  oq_Active         Selection active flag
   \param[in]  oq_SelectFirst    Select first element
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::SetSelectionAvailable(const bool oq_Active, const bool oq_SelectFirst)
{
   if (oq_Active == true)
   {
      this->setSelectionMode(QAbstractItemView::ExtendedSelection);
      if (oq_SelectFirst)
      {
         this->setCurrentIndex(this->indexAt(QPoint(0, 0)));
      }
   }
   else
   {
      this->clearSelection();
      this->setSelectionMode(QAbstractItemView::NoSelection);
   }
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Apply style

   \param[in]  oe_Style       New style type
   \param[in]  oq_DarkMode    Flag if dark mode is active
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::SetDisplayStyle(const C_PuiSvDbWidgetBase::E_Style oe_Style, const bool oq_DarkMode)
{
   this->mc_Delegate.SetDisplayStyle(oe_Style, oq_DarkMode);
   C_OgeWiUtil::h_ApplyStylesheetPropertyToItselfAndAllChildren(this, "DarkMode", oq_DarkMode);
   this->mc_Model.SetDisplayStyle(oe_Style, oq_DarkMode);
   switch (oe_Style)
   {
   case C_PuiSvDbWidgetBase::eOPENSYDE:
      this->setGridStyle(Qt::NoPen);
      this->setShowGrid(false);
      this->setAlternatingRowColors(true);
      break;
   case C_PuiSvDbWidgetBase::eFLAT:
      this->setGridStyle(Qt::NoPen);
      this->setShowGrid(false);
      this->setAlternatingRowColors(true);
      break;
   case C_PuiSvDbWidgetBase::eSKEUOMORPH:
      this->setGridStyle(Qt::NoPen);
      this->setShowGrid(false);
      this->setAlternatingRowColors(true);
      break;
   case C_PuiSvDbWidgetBase::eOPENSYDE_2:
      this->setGridStyle(Qt::SolidLine);
      this->setShowGrid(true);
      this->setAlternatingRowColors(false);
      break;
   default:
      tgl_assert(false);
      break;
   }
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Sets the cursor handling active

   If the cursor handling is active the SplitHCursor cursor will be set when necessary by setOverrideCursor
   and restored when not

   \param[in]       oq_Active     Flag if cursor handling is active
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::SetCursorHandlingActive(const bool oq_Active)
{
   this->mpc_TableHeaderView->SetCursorHandlingActive(oq_Active);
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Hide tooltip
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::HideToolTip(void)
{
   this->m_HideToolTip();
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Overwritten key press event slot

   Here: Handle dashboard table specific key functionality

   \param[in,out]  opc_Event  Event identification and information
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::keyPressEvent(QKeyEvent * const opc_Event)
{
   // Events can get here only in content edit mode
   bool q_CallOrig = true;

   switch (opc_Event->key())
   {
   case Qt::Key_Delete:
      q_CallOrig = false;
      Q_EMIT (this->SigRemoveDataElement());
      opc_Event->accept();
      break;
   case Qt::Key_BracketRight: // Qt::Key_BracketRight matches the "Not-Num-Plus"-Key
   case Qt::Key_Plus:
      if (C_Uti::h_CheckKeyModifier(opc_Event->modifiers(), Qt::ControlModifier) == true)
      {
         q_CallOrig = false;
         Q_EMIT (this->SigAddDataElement());
         opc_Event->accept();
      }
      break;
   case Qt::Key_Up:
      if (C_Uti::h_CheckKeyModifier(opc_Event->modifiers(), Qt::ControlModifier) == true)
      {
         q_CallOrig = false;
         Q_EMIT (this->SigMoveDataElementUp());
         opc_Event->accept();
      }
      break;
   case Qt::Key_Down:
      if (C_Uti::h_CheckKeyModifier(opc_Event->modifiers(), Qt::ControlModifier) == true)
      {
         q_CallOrig = false;
         Q_EMIT (this->SigMoveDataElementDown());
         opc_Event->accept();
      }
      break;
   default:
      //Nothing to do
      break;
   }

   if (q_CallOrig == true)
   {
      C_TblViewScroll::keyPressEvent(opc_Event);
   }
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Overwritten mouse double click event slot

   Here: Handle dashboard table specific double click functionality

   \param[in,out]  opc_Event  Event identification and information
*/
//----------------------------------------------------------------------------------------------------------------------
void C_SyvDaItTaView::mouseDoubleClickEvent(QMouseEvent * const opc_Event)
{
   C_TblViewScroll::mouseDoubleClickEvent(opc_Event);

   Q_EMIT (this->SigTriggerEdit());
}
