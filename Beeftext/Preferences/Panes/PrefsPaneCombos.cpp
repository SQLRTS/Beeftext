﻿/// \file
/// \author 
///
/// \brief Implementation of combos preferences pane.
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#include "stdafx.h"
#include "PrefsPaneCombos.h"
#include "BeeftextUtils.h"


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the pane.
//**********************************************************************************************************************
PrefsPaneCombos::PrefsPaneCombos(QWidget* parent)
   : PrefsPane(parent)
   , prefs_(PreferencesManager::instance())
{
   ui_.setupUi(this);
   fillMatchingModeCombo(*ui_.comboMatchingMode, false);
   fillCaseSensitivityCombo(*ui_.comboCaseSensitivity, false);
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void PrefsPaneCombos::load() const
{
   if (prefs_.useAutomaticSubstitution())
   {
      QSignalBlocker blocker(ui_.radioComboTriggerAuto);
      ui_.radioComboTriggerAuto->setChecked(true);
   }
   else
   {
      QSignalBlocker blocker(ui_.radioComboTriggerManual);
      ui_.radioComboTriggerManual->setChecked(true);
   }
   QSignalBlocker blocker(ui_.checkComboTriggersOnSpace);
   ui_.checkComboTriggersOnSpace->setChecked(prefs_.comboTriggersOnSpace());
   blocker = QSignalBlocker(ui_.checkKeepFinalSpaceCharacter);
   ui_.checkKeepFinalSpaceCharacter->setChecked(prefs_.keepFinalSpaceCharacter());
   SpShortcut shortcut = prefs_.comboTriggerShortcut();
   ui_.editComboTriggerShortcut->setText(shortcut ? shortcut->toString() : "");
   selectMatchingModeInCombo(*ui_.comboMatchingMode, prefs_.defaultMatchingMode(), true);
   selectCaseSensitivityInCombo(*ui_.comboCaseSensitivity, prefs_.defaultCaseSensitivity(), true);
   blocker = QSignalBlocker(ui_.checkEnablePickerWindow);
   ui_.checkEnablePickerWindow->setChecked(prefs_.comboPickerEnabled());
   shortcut = prefs_.comboPickerShortcut();
   ui_.editPickerWindowShortcut->setText(shortcut ? shortcut->toString() : "");

   this->updateGui();
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void PrefsPaneCombos::updateGui() const
{
   bool const comboTriggerAuto = ui_.radioComboTriggerAuto->isChecked();
   ui_.checkComboTriggersOnSpace->setEnabled(comboTriggerAuto);
   ui_.checkKeepFinalSpaceCharacter->setEnabled(comboTriggerAuto && ui_.checkComboTriggersOnSpace->isChecked());

   QWidgetList widgets = { ui_.editComboTriggerShortcut, ui_.buttonChangeComboTriggerShortcut, 
   ui_.buttonResetComboTriggerShortcut };
   for (QWidget* const widget: widgets)
      widget->setEnabled(ui_.radioComboTriggerManual->isChecked());

   widgets = { ui_.labelPickerWindowShortcut, ui_.editPickerWindowShortcut, ui_.buttonChangePickerWindowShortcut,
      ui_.buttonResetPickerWindowShortcut };
   for (QWidget* const widget: widgets)
      widget->setEnabled(ui_.checkEnablePickerWindow->isChecked());
}


//**********************************************************************************************************************
/// \param[in] checked Is the radio button checked
//**********************************************************************************************************************
void PrefsPaneCombos::onRadioAutomaticComboTrigger(bool checked) const
{
   prefs_.setUseAutomaticSubstitution(checked);
   this->updateGui();
}


//**********************************************************************************************************************
/// \param[in] checked Is the check box checked.
//**********************************************************************************************************************
void PrefsPaneCombos::onCheckComboTriggersOnSpace(bool checked) const
{
   prefs_.setComboTriggersOnSpace(checked);
   this->updateGui();
}


//**********************************************************************************************************************
/// \param[in] checked Is the check box checked.
//**********************************************************************************************************************
void PrefsPaneCombos::onCheckKeepFinalSpace(bool checked) const
{
   prefs_.setKeepFinalSpaceCharacter(checked);
   this->updateGui();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void PrefsPaneCombos::onChangeComboTriggerShortcut() const
{
   SpShortcut shortcut = prefs_.comboTriggerShortcut();
   if (!runShortcutDialog(shortcut))
      return;
   prefs_.setComboTriggerShortcut(shortcut);
   ui_.editComboTriggerShortcut->setText(shortcut ? shortcut->toString() : "");
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void PrefsPaneCombos::onResetComboTriggerShortcut() const
{
   SpShortcut const shortcut = PreferencesManager::defaultComboTriggerShortcut();
   prefs_.setComboTriggerShortcut(shortcut);
   ui_.editComboTriggerShortcut->setText(shortcut ? shortcut->toString() : "");
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void PrefsPaneCombos::onChangeDefaultMatchingMode() const
{
   prefs_.setDefaultMatchingMode(selectedMatchingModeInCombo(*ui_.comboMatchingMode));
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void PrefsPaneCombos::onChangeDefaultCaseSensitivity() const
{
   qDebug() << QString("%1()").arg(__FUNCTION__);
   prefs_.setDefaultCaseSensitivity(selectedCaseSensitivityInCombo(*ui_.comboCaseSensitivity));
}


//**********************************************************************************************************************
/// \param[in] checked Is the radio button checked
//**********************************************************************************************************************
void PrefsPaneCombos::onCheckEnablePickerWindow(bool checked) const
{
   prefs_.setComboPickerEnabled(checked);
   this->updateGui();
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void PrefsPaneCombos::onChangePickerWindowShortcut() const
{
   SpShortcut shortcut = prefs_.comboPickerShortcut();
   if (!runShortcutDialog(shortcut))
      return;
   prefs_.setComboPickerShortcut(shortcut);
   ui_.editPickerWindowShortcut->setText(shortcut ? shortcut->toString() : "");
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void PrefsPaneCombos::onResetPickerWindowShortcut() const
{
   SpShortcut const shortcut = PreferencesManager::defaultComboPickerShortcut();
   prefs_.setComboPickerShortcut(shortcut);
   ui_.editPickerWindowShortcut->setText(shortcut ? shortcut->toString() : "");
}


//**********************************************************************************************************************
/// \param[in] event The event
//**********************************************************************************************************************
void PrefsPaneCombos::changeEvent(QEvent* event)
{
   if (QEvent::LanguageChange == event->type())
   {
      ui_.retranslateUi(this);
      SpShortcut const shortcut = prefs_.comboTriggerShortcut();
      ui_.editComboTriggerShortcut->setText(shortcut ? shortcut->toString() : "");

      fillMatchingModeCombo(*ui_.comboMatchingMode, false);
      selectMatchingModeInCombo(*ui_.comboMatchingMode, prefs_.defaultMatchingMode(), true);

      fillCaseSensitivityCombo(*ui_.comboCaseSensitivity, false);
      selectCaseSensitivityInCombo(*ui_.comboCaseSensitivity, prefs_.defaultCaseSensitivity(), true);
   }
   PrefsPane::changeEvent(event);
}


