/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of preferences dialog
///
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef BEEFTEXT_PREFERENCES_DIALOG_H
#define BEEFTEXT_PREFERENCES_DIALOG_H


#include "ui_PreferencesDialog.h"
#include "PreferencesManager.h"
#include "LatestVersionInfo.h"


//**********************************************************************************************************************
/// \brief Preferences dialog class
//**********************************************************************************************************************
class PreferencesDialog: public QDialog
{
   Q_OBJECT
public: // member functions
   explicit PreferencesDialog(QWidget* parent = nullptr); ///< Default constructor
   PreferencesDialog(PreferencesDialog const&) = delete; ///< Disabled copy-constructor
   PreferencesDialog(PreferencesDialog&&) = delete; ///< Disabled assignment copy-constructor
   ~PreferencesDialog() override = default; ///< Destructor
   PreferencesDialog& operator=(PreferencesDialog const&) = delete; ///< Disabled assignment operator
   PreferencesDialog& operator=(PreferencesDialog&&) = delete; ///< Disabled move assignment operator
   void load() const; ///< Load the preferences

private: // member functions
   void setUpdateCheckStatus(QString const& status); ///< Set the update check status label message (this is cleared after a few seconds)
   bool promptForAndRemoveAutoBackups(); ///< Ask the user if automatic backups should be deleted and if so, performs the operation
   bool checkAndReportInconsistencies(); ///< Check that the values for the dialog are consistant

private slots:
   void updateGui() const; ///< Update the GUI state
   void onCheckAutoCheckForUpdates(bool checked) const; ///< Slot for the 'Auto check for updated' checkbox.
   void onCheckAutoStart(bool checked) const; ///< Slot for the 'Auto start at login' checkbox.
   void onCheckPlaySoundOnCombo(bool checked) const; ///< Slot for the  'Play sound on combo' checkbox.
   void onCheckUseCustomSound(bool checked) const; ///< Slot for the 'Use custom sound' checkbox.
   void onChangeCustomSound() const; ///< Slot for the 'Change custom sound' button.
   void onPlaySoundButton() const; ///< Slot for the 'Play' button for custom sound.
   void onCheckEnableAppEnableDisableShortcut(bool checked) const; ///< Slot for the 'Enable app enable/disable shortcut' check box.
   void onChangeAppEnableDisableShortcut() const; ///< Slot for the button Change of the app enable/disable shortcut.
   void onResetAppEnableDisableShortcut() const; ///< Slot for the button Default of the app enable/disable shortcut.
   void onSpinDelayBetweenKeystrokesChanged(int value) const; ///< Slot for the 'Delay between keystrokes' spin value change.
   void onChangeComboListFolder(); ///< Slot for the 'Change combo list folder' action
   void onResetComboListFolder(); ///< Slot for the 'Reset combo list folder' action
   void onOpenComboListFolder() const; ///< Slot for the 'Open' button of the combo list folder.
   void onCheckAutoBackup(bool value); ///< Slot for the 'auto backup' checkbox.
   void onCheckUseCustomBackupLocation(bool value) const; ///< Slot for the 'Use custom backup location' checkbox.
   void onChangeCustomBackupLocation(); ///< Slot for the 'Change' button of the custom backup location.
   void onResetToDefaultValues(); ///< Slot for the 'Reset to default values' action
   void onRestoreBackup(); ///< Slot for the 'Restore backup' action
   void onResetWarnings(); ///< Slot for teh 'Reset warnings' action
   void onClose(); ///< Slot for the OK button
   void onUpdateIsAvailable(SpLatestVersionInfo const& latestVersionInfo); ///< Slot for the availability of an update
   void onNoUpdateIsAvailable(); ///< Slot for the lack of availability of an update
   void onUpdateCheckStarted() const; ///< Slot for the starting of an update check
   void onUpdateCheckFinished() const; ///< Slot for the finishing of an update check
   void onUpdateCheckFailed(); ///< Slot update check failure
   void onEditSensitiveApplications(); ///< Slot for the 'Edit sensitive applications' action
   void onCheckWriteDebugLogFile(bool checked) const; ///< Slot the for 'Write debug log file' checkbox
   void onCheckUseLegacyCopyPaste() const; ///< Slot for the 'Use legacy copy/paste'.
   void onCheckUseShiftInsertForPasting() const; ///< Slot for the 'Use Shift+Insert for pasting' checkbox.
   void onCheckUseCustomPowerShellVersion(bool checked); ///< Slot for the 'Use custom PowerShell version' check box.
   void onChangeCustomPowershellVersion(); ///< Slot for the 'Change' button of the custom PowerShell version.
   void onExport(); ///< Slot for the 'Export' button.
   void onImport(); ///< Slot for the 'Import' button.

private: // data members
   Ui::PreferencesDialog ui_ {}; ///< The GUI for the dialog
   PreferencesManager& prefs_; ///< The preferences manager
   QTimer updateCheckStatusTimer_; ///< The timer for clearing the update check status label
   QString previousComboListPath_; ///< The previous path of the combo list
};


#endif // #ifndef BEEFTEXT_PREFERENCES_DIALOG_H
