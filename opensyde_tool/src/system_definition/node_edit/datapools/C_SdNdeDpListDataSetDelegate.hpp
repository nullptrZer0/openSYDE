//----------------------------------------------------------------------------------------------------------------------
/*!
   \file
   \brief       Node data pool list data set drawing delegate (header)

   See cpp file for detailed description

   \copyright   Copyright 2017 Sensor-Technik Wiedemann GmbH. All rights reserved.
*/
//----------------------------------------------------------------------------------------------------------------------
#ifndef C_SDNDEDPLISTDATASETDELEGATE_H
#define C_SDNDEDPLISTDATASETDELEGATE_H

/* -- Includes ------------------------------------------------------------------------------------------------------ */

#include <QStyledItemDelegate>
#include "C_SdNdeDpListDataSetModel.hpp"

/* -- Namespace ----------------------------------------------------------------------------------------------------- */
namespace stw
{
namespace opensyde_gui_logic
{
/* -- Global Constants ---------------------------------------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------------------------------------------------- */

class C_SdNdeDpListDataSetDelegate :
   public QStyledItemDelegate
{
   Q_OBJECT

public:
   C_SdNdeDpListDataSetDelegate(QObject * const opc_Parent = NULL);

   QWidget * createEditor(QWidget * const opc_Parent, const QStyleOptionViewItem & orc_Option,
                          const QModelIndex & orc_Index) const override;
   void setEditorData(QWidget * const opc_Editor, const QModelIndex & orc_Index) const override;
   void setModelData(QWidget * const opc_Editor, QAbstractItemModel * const opc_Model,
                     const QModelIndex & orc_Index) const override;

   bool SetHoveredCol(const int32_t & ors32_Value);
   void SetModel(const C_SdNdeDpListDataSetModel * const opc_Value);

   //The signals keyword is necessary for Qt signal slot functionality
   //lint -save -e1736

Q_SIGNALS:
   //lint -restore
   void SigStore(const QModelIndex & orc_Index) const;
   void SigTedConfirmed(void) const;

private:
   const C_SdNdeDpListDataSetModel * mpc_Model;
   int32_t ms32_HoveredCol;
   QModelIndex mc_Edit;

   void m_OnNameChange(const QString & orc_Text) const;
   void m_Store(const QModelIndex & orc_Index);
};

/* -- Extern Global Variables --------------------------------------------------------------------------------------- */
}
} //end of namespace

#endif
