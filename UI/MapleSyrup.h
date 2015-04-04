#pragma once
#include <iostream>
#include <assert.h>
#include <cctype>

#include "Logic.h"
#include "UICommandSuggestion.h"
#include "UIHelp.h"
#include "UIShow.h"

namespace UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Diagnostics;

	using namespace System::Web;
	using namespace System::Net::Mail;

	/// <summary>
	/// Summary for MapleSyrup
	/// </summary>
	public ref class MapleSyrup : public System::Windows::Forms::Form
	{
	private:
		UICommandSuggestion* cSPtr; 

		Logic* lGPtr;

		UIHelp* helpPtr;

		UIShow* showPtr;

	private: System::Windows::Forms::Button^  showButton;
	private: System::Windows::Forms::Button^  helpButton;
	private: System::Windows::Forms::MonthCalendar^  calenderTop;
	private: System::Windows::Forms::ContextMenuStrip^  showDropDown;
	private: System::Windows::Forms::ToolStripMenuItem^  dayToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  weekToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  monthToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  allToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  archiveToolStripMenuItem;
	private: System::Windows::Forms::ContextMenuStrip^  helpDropDown;
	private: System::Windows::Forms::ToolStripMenuItem^  introductionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  commandsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  shortcutsToolStripMenuItem;
	private: System::Windows::Forms::Button^  redoButton;
	private: System::Windows::Forms::RichTextBox^  dueDisplay;
	private: System::Windows::Forms::TextBox^  dueLabel;



	private: System::Windows::Forms::Button^  undoButton;

	public:
		MapleSyrup(void)
		{
			InitializeComponent();
		
			//Create logic object here
			//
			//TODO: Add the constructor code here

			//Initialization
			cSPtr = new UICommandSuggestion;

			lGPtr = new Logic;

			helpPtr = new UIHelp;

			showPtr = new UIShow;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MapleSyrup()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::RichTextBox^  feedbackBox;
	private: System::Windows::Forms::TextBox^  searchBox;
	private: System::Windows::Forms::RichTextBox^  display;
	private: System::Windows::Forms::RichTextBox^  floatingTasksDisplay;
	private: System::Windows::Forms::TextBox^  mainDisplayLabel;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  comdIcon;
	private: System::Windows::Forms::PictureBox^  calenderIcon;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  floatingIcon;
	private: System::Windows::Forms::PictureBox^  pictureBox8;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::PictureBox^  searchIcon;
	private: System::Windows::Forms::TextBox^  commandBox;
	private: System::Windows::Forms::ListBox^  suggestBar;
	private: System::ComponentModel::IContainer^  components;


	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MapleSyrup::typeid));
			this->commandBox = (gcnew System::Windows::Forms::TextBox());
			this->feedbackBox = (gcnew System::Windows::Forms::RichTextBox());
			this->searchBox = (gcnew System::Windows::Forms::TextBox());
			this->display = (gcnew System::Windows::Forms::RichTextBox());
			this->floatingTasksDisplay = (gcnew System::Windows::Forms::RichTextBox());
			this->mainDisplayLabel = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->comdIcon = (gcnew System::Windows::Forms::PictureBox());
			this->calenderIcon = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->floatingIcon = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->searchIcon = (gcnew System::Windows::Forms::PictureBox());
			this->calenderTop = (gcnew System::Windows::Forms::MonthCalendar());
			this->redoButton = (gcnew System::Windows::Forms::Button());
			this->undoButton = (gcnew System::Windows::Forms::Button());
			this->showButton = (gcnew System::Windows::Forms::Button());
			this->helpButton = (gcnew System::Windows::Forms::Button());
			this->suggestBar = (gcnew System::Windows::Forms::ListBox());
			this->showDropDown = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->dayToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->weekToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->monthToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->allToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->archiveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpDropDown = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->introductionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->commandsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->shortcutsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dueDisplay = (gcnew System::Windows::Forms::RichTextBox());
			this->dueLabel = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->comdIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->calenderIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->floatingIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchIcon))->BeginInit();
			this->showDropDown->SuspendLayout();
			this->helpDropDown->SuspendLayout();
			this->SuspendLayout();
			// 
			// commandBox
			// 
			this->commandBox->AcceptsReturn = true;
			this->commandBox->AcceptsTab = true;
			this->commandBox->AllowDrop = true;
			this->commandBox->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(16) {resources->GetString(L"commandBox.AutoCompleteCustomSource"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource1"), resources->GetString(L"commandBox.AutoCompleteCustomSource2"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource3"), resources->GetString(L"commandBox.AutoCompleteCustomSource4"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource5"), resources->GetString(L"commandBox.AutoCompleteCustomSource6"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource7"), resources->GetString(L"commandBox.AutoCompleteCustomSource8"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource9"), resources->GetString(L"commandBox.AutoCompleteCustomSource10"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource11"), resources->GetString(L"commandBox.AutoCompleteCustomSource12"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource13"), resources->GetString(L"commandBox.AutoCompleteCustomSource14"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource15")});
			this->commandBox->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->commandBox->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->commandBox->BackColor = System::Drawing::Color::White;
			resources->ApplyResources(this->commandBox, L"commandBox");
			this->commandBox->ForeColor = System::Drawing::SystemColors::InfoText;
			this->commandBox->Name = L"commandBox";
			this->commandBox->Tag = L"Enter";
			this->toolTip1->SetToolTip(this->commandBox, resources->GetString(L"commandBox.ToolTip"));
			this->commandBox->TextChanged += gcnew System::EventHandler(this, &MapleSyrup::commandBox_TextChanged);
			this->commandBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MapleSyrup::commandBox_KeyDown);
			// 
			// feedbackBox
			// 
			this->feedbackBox->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->feedbackBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->feedbackBox->Cursor = System::Windows::Forms::Cursors::SizeAll;
			resources->ApplyResources(this->feedbackBox, L"feedbackBox");
			this->feedbackBox->Name = L"feedbackBox";
			this->feedbackBox->ReadOnly = true;
			this->feedbackBox->TabStop = false;
			this->toolTip1->SetToolTip(this->feedbackBox, resources->GetString(L"feedbackBox.ToolTip"));
			// 
			// searchBox
			// 
			this->searchBox->AcceptsReturn = true;
			this->searchBox->AcceptsTab = true;
			this->searchBox->AllowDrop = true;
			this->searchBox->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::SuggestAppend;
			this->searchBox->BackColor = System::Drawing::Color::White;
			resources->ApplyResources(this->searchBox, L"searchBox");
			this->searchBox->ForeColor = System::Drawing::SystemColors::InfoText;
			this->searchBox->Name = L"searchBox";
			this->toolTip1->SetToolTip(this->searchBox, resources->GetString(L"searchBox.ToolTip"));
			this->searchBox->TextChanged += gcnew System::EventHandler(this, &MapleSyrup::searchBox_TextChanged);
			this->searchBox->Enter += gcnew System::EventHandler(this, &MapleSyrup::searchBox_Enter);
			this->searchBox->Leave += gcnew System::EventHandler(this, &MapleSyrup::searchBox_Leave);
			// 
			// display
			// 
			this->display->AutoWordSelection = true;
			this->display->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->display->Cursor = System::Windows::Forms::Cursors::SizeAll;
			resources->ApplyResources(this->display, L"display");
			this->display->Name = L"display";
			this->display->ReadOnly = true;
			this->display->TabStop = false;
			this->toolTip1->SetToolTip(this->display, resources->GetString(L"display.ToolTip"));
			this->display->Enter += gcnew System::EventHandler(this, &MapleSyrup::display_Enter);
			this->display->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MapleSyrup::display_KeyDown);
			// 
			// floatingTasksDisplay
			// 
			this->floatingTasksDisplay->BackColor = System::Drawing::Color::White;
			this->floatingTasksDisplay->Cursor = System::Windows::Forms::Cursors::SizeAll;
			resources->ApplyResources(this->floatingTasksDisplay, L"floatingTasksDisplay");
			this->floatingTasksDisplay->Name = L"floatingTasksDisplay";
			this->floatingTasksDisplay->ReadOnly = true;
			this->floatingTasksDisplay->ShortcutsEnabled = false;
			this->floatingTasksDisplay->TabStop = false;
			this->toolTip1->SetToolTip(this->floatingTasksDisplay, resources->GetString(L"floatingTasksDisplay.ToolTip"));
			this->floatingTasksDisplay->Enter += gcnew System::EventHandler(this, &MapleSyrup::floatingTasksDisplay_Enter);
			this->floatingTasksDisplay->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MapleSyrup::floatingTasksDisplay_KeyDown);
			// 
			// mainDisplayLabel
			// 
			this->mainDisplayLabel->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->mainDisplayLabel->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->mainDisplayLabel->Cursor = System::Windows::Forms::Cursors::SizeAll;
			resources->ApplyResources(this->mainDisplayLabel, L"mainDisplayLabel");
			this->mainDisplayLabel->ForeColor = System::Drawing::Color::Black;
			this->mainDisplayLabel->Name = L"mainDisplayLabel";
			this->mainDisplayLabel->ReadOnly = true;
			this->mainDisplayLabel->TabStop = false;
			// 
			// pictureBox2
			// 
			resources->ApplyResources(this->pictureBox2, L"pictureBox2");
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->TabStop = false;
			// 
			// comdIcon
			// 
			resources->ApplyResources(this->comdIcon, L"comdIcon");
			this->comdIcon->Name = L"comdIcon";
			this->comdIcon->TabStop = false;
			this->toolTip1->SetToolTip(this->comdIcon, resources->GetString(L"comdIcon.ToolTip"));
			// 
			// calenderIcon
			// 
			resources->ApplyResources(this->calenderIcon, L"calenderIcon");
			this->calenderIcon->Name = L"calenderIcon";
			this->calenderIcon->TabStop = false;
			this->toolTip1->SetToolTip(this->calenderIcon, resources->GetString(L"calenderIcon.ToolTip"));
			this->calenderIcon->Click += gcnew System::EventHandler(this, &MapleSyrup::calenderIcon_Click);
			// 
			// pictureBox1
			// 
			resources->ApplyResources(this->pictureBox1, L"pictureBox1");
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->TabStop = false;
			this->toolTip1->SetToolTip(this->pictureBox1, resources->GetString(L"pictureBox1.ToolTip"));
			// 
			// floatingIcon
			// 
			resources->ApplyResources(this->floatingIcon, L"floatingIcon");
			this->floatingIcon->Name = L"floatingIcon";
			this->floatingIcon->TabStop = false;
			this->toolTip1->SetToolTip(this->floatingIcon, resources->GetString(L"floatingIcon.ToolTip"));
			// 
			// pictureBox8
			// 
			resources->ApplyResources(this->pictureBox8, L"pictureBox8");
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->TabStop = false;
			this->toolTip1->SetToolTip(this->pictureBox8, resources->GetString(L"pictureBox8.ToolTip"));
			// 
			// toolTip1
			// 
			this->toolTip1->AutoPopDelay = 5000;
			this->toolTip1->InitialDelay = 1;
			this->toolTip1->ReshowDelay = 1;
			this->toolTip1->UseAnimation = false;
			this->toolTip1->UseFading = false;
			// 
			// searchIcon
			// 
			this->searchIcon->BackColor = System::Drawing::Color::White;
			resources->ApplyResources(this->searchIcon, L"searchIcon");
			this->searchIcon->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->searchIcon->Name = L"searchIcon";
			this->searchIcon->TabStop = false;
			this->toolTip1->SetToolTip(this->searchIcon, resources->GetString(L"searchIcon.ToolTip"));
			// 
			// calenderTop
			// 
			resources->ApplyResources(this->calenderTop, L"calenderTop");
			this->calenderTop->MaxSelectionCount = 9999;
			this->calenderTop->Name = L"calenderTop";
			this->calenderTop->ScrollChange = 1;
			this->toolTip1->SetToolTip(this->calenderTop, resources->GetString(L"calenderTop.ToolTip"));
			this->calenderTop->DateSelected += gcnew System::Windows::Forms::DateRangeEventHandler(this, &MapleSyrup::calenderTop_DateSelected);
			this->calenderTop->Enter += gcnew System::EventHandler(this, &MapleSyrup::calenderTop_Enter);
			this->calenderTop->Leave += gcnew System::EventHandler(this, &MapleSyrup::calenderTop_Leave);
			// 
			// redoButton
			// 
			this->redoButton->BackColor = System::Drawing::Color::White;
			resources->ApplyResources(this->redoButton, L"redoButton");
			this->redoButton->Name = L"redoButton";
			this->redoButton->TabStop = false;
			this->toolTip1->SetToolTip(this->redoButton, resources->GetString(L"redoButton.ToolTip"));
			this->redoButton->UseVisualStyleBackColor = false;
			this->redoButton->Click += gcnew System::EventHandler(this, &MapleSyrup::redoButton_Click);
			// 
			// undoButton
			// 
			this->undoButton->BackColor = System::Drawing::Color::White;
			resources->ApplyResources(this->undoButton, L"undoButton");
			this->undoButton->Name = L"undoButton";
			this->undoButton->TabStop = false;
			this->toolTip1->SetToolTip(this->undoButton, resources->GetString(L"undoButton.ToolTip"));
			this->undoButton->UseVisualStyleBackColor = false;
			this->undoButton->Click += gcnew System::EventHandler(this, &MapleSyrup::undoButton_Click);
			// 
			// showButton
			// 
			this->showButton->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->showButton->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->showButton, L"showButton");
			this->showButton->ForeColor = System::Drawing::Color::Black;
			this->showButton->Name = L"showButton";
			this->showButton->TabStop = false;
			this->showButton->UseVisualStyleBackColor = false;
			this->showButton->Click += gcnew System::EventHandler(this, &MapleSyrup::showButton_Click);
			// 
			// helpButton
			// 
			this->helpButton->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->helpButton->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->helpButton, L"helpButton");
			this->helpButton->ForeColor = System::Drawing::Color::Black;
			this->helpButton->Name = L"helpButton";
			this->helpButton->TabStop = false;
			this->helpButton->UseVisualStyleBackColor = false;
			this->helpButton->Click += gcnew System::EventHandler(this, &MapleSyrup::helpButton_Click);
			// 
			// suggestBar
			// 
			this->suggestBar->BackColor = System::Drawing::Color::White;
			this->suggestBar->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			resources->ApplyResources(this->suggestBar, L"suggestBar");
			this->suggestBar->Name = L"suggestBar";
			this->suggestBar->TabStop = false;
			// 
			// showDropDown
			// 
			this->showDropDown->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->showDropDown, L"showDropDown");
			this->showDropDown->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->dayToolStripMenuItem, 
				this->weekToolStripMenuItem, this->monthToolStripMenuItem, this->allToolStripMenuItem, this->archiveToolStripMenuItem});
			this->showDropDown->Name = L"showDropDown";
			// 
			// dayToolStripMenuItem
			// 
			this->dayToolStripMenuItem->AutoToolTip = true;
			this->dayToolStripMenuItem->Name = L"dayToolStripMenuItem";
			resources->ApplyResources(this->dayToolStripMenuItem, L"dayToolStripMenuItem");
			this->dayToolStripMenuItem->Click += gcnew System::EventHandler(this, &MapleSyrup::dayToolStripMenuItem_Click);
			// 
			// weekToolStripMenuItem
			// 
			this->weekToolStripMenuItem->AutoToolTip = true;
			this->weekToolStripMenuItem->Name = L"weekToolStripMenuItem";
			resources->ApplyResources(this->weekToolStripMenuItem, L"weekToolStripMenuItem");
			this->weekToolStripMenuItem->Click += gcnew System::EventHandler(this, &MapleSyrup::weekToolStripMenuItem_Click);
			// 
			// monthToolStripMenuItem
			// 
			this->monthToolStripMenuItem->AutoToolTip = true;
			this->monthToolStripMenuItem->Name = L"monthToolStripMenuItem";
			resources->ApplyResources(this->monthToolStripMenuItem, L"monthToolStripMenuItem");
			this->monthToolStripMenuItem->Click += gcnew System::EventHandler(this, &MapleSyrup::monthToolStripMenuItem_Click);
			// 
			// allToolStripMenuItem
			// 
			this->allToolStripMenuItem->Name = L"allToolStripMenuItem";
			resources->ApplyResources(this->allToolStripMenuItem, L"allToolStripMenuItem");
			this->allToolStripMenuItem->Click += gcnew System::EventHandler(this, &MapleSyrup::allToolStripMenuItem_Click);
			// 
			// archiveToolStripMenuItem
			// 
			this->archiveToolStripMenuItem->Name = L"archiveToolStripMenuItem";
			resources->ApplyResources(this->archiveToolStripMenuItem, L"archiveToolStripMenuItem");
			this->archiveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MapleSyrup::archiveToolStripMenuItem_Click);
			// 
			// helpDropDown
			// 
			this->helpDropDown->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->helpDropDown, L"helpDropDown");
			this->helpDropDown->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->introductionToolStripMenuItem, 
				this->commandsToolStripMenuItem, this->shortcutsToolStripMenuItem});
			this->helpDropDown->Name = L"helpDropDown";
			// 
			// introductionToolStripMenuItem
			// 
			this->introductionToolStripMenuItem->Name = L"introductionToolStripMenuItem";
			resources->ApplyResources(this->introductionToolStripMenuItem, L"introductionToolStripMenuItem");
			this->introductionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MapleSyrup::introductionToolStripMenuItem_Click);
			// 
			// commandsToolStripMenuItem
			// 
			this->commandsToolStripMenuItem->Name = L"commandsToolStripMenuItem";
			resources->ApplyResources(this->commandsToolStripMenuItem, L"commandsToolStripMenuItem");
			this->commandsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MapleSyrup::commandsToolStripMenuItem_Click);
			// 
			// shortcutsToolStripMenuItem
			// 
			this->shortcutsToolStripMenuItem->Name = L"shortcutsToolStripMenuItem";
			resources->ApplyResources(this->shortcutsToolStripMenuItem, L"shortcutsToolStripMenuItem");
			this->shortcutsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MapleSyrup::shortcutsToolStripMenuItem_Click);
			// 
			// dueDisplay
			// 
			this->dueDisplay->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->dueDisplay, L"dueDisplay");
			this->dueDisplay->Name = L"dueDisplay";
			// 
			// dueLabel
			// 
			this->dueLabel->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->dueLabel->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dueLabel->Cursor = System::Windows::Forms::Cursors::SizeAll;
			resources->ApplyResources(this->dueLabel, L"dueLabel");
			this->dueLabel->ForeColor = System::Drawing::Color::DimGray;
			this->dueLabel->Name = L"dueLabel";
			this->dueLabel->ReadOnly = true;
			this->dueLabel->TabStop = false;
			this->dueLabel->TextChanged += gcnew System::EventHandler(this, &MapleSyrup::dueLabel_TextChanged);
			// 
			// MapleSyrup
			// 
			this->AllowDrop = true;
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->Controls->Add(this->dueDisplay);
			this->Controls->Add(this->redoButton);
			this->Controls->Add(this->undoButton);
			this->Controls->Add(this->helpButton);
			this->Controls->Add(this->showButton);
			this->Controls->Add(this->floatingTasksDisplay);
			this->Controls->Add(this->pictureBox8);
			this->Controls->Add(this->floatingIcon);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->suggestBar);
			this->Controls->Add(this->searchIcon);
			this->Controls->Add(this->calenderIcon);
			this->Controls->Add(this->comdIcon);
			this->Controls->Add(this->mainDisplayLabel);
			this->Controls->Add(this->searchBox);
			this->Controls->Add(this->feedbackBox);
			this->Controls->Add(this->commandBox);
			this->Controls->Add(this->display);
			this->Controls->Add(this->calenderTop);
			this->Controls->Add(this->dueLabel);
			this->ForeColor = System::Drawing::Color::Black;
			this->HelpButton = true;
			this->KeyPreview = true;
			this->Name = L"MapleSyrup";
			this->ShowIcon = false;
			this->Load += gcnew System::EventHandler(this, &MapleSyrup::MapleSyrup_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MapleSyrup::MapleSyrup_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MapleSyrup::MapleSyrup_KeyUp);
			this->Leave += gcnew System::EventHandler(this, &MapleSyrup::MapleSyrup_Leave);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MapleSyrup::MapleSyrup_MouseClick);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->comdIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->calenderIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->floatingIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchIcon))->EndInit();
			this->showDropDown->ResumeLayout(false);
			this->helpDropDown->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

/**
 * @author A0111230J
 */

/*
* =================================================================================================================================================================== 
* Functions to load GUI & data
* GUI exited
* ===================================================================================================================================================================
*/
//Pre-condition : None
//To display the UI
//Invoked by MapleSyrup.cpp
private: System::Void MapleSyrup_Load(System::Object^  sender, System::EventArgs^  e) {
			clearAllLogFiles();
			initializeAndUndisplayAll();
			initializeShortcut();
			loadData();
}

//Pre-condition : None
//All user opened displays will be make invisible
private: void initializeAndUndisplayAll(){
			topCalenderDisplayed = false;
		}

private: void loadData(){
			 DateTime current = DateTime::Now;
			 String^ timeToLog = current.ToString("dd MMM,dddd, HH:mm:sss");
			 log ("Program starts at:", convertToStd(timeToLog));

			 std::string loadCommand1 = showPtr->getShowFloat();
			 executeUserInput(loadCommand1);

			 std::string loadCommand2 = showPtr->getShowDay();
			 executeUserInput(loadCommand2); 

			 commandBox->Select();
		 }

private: void clearAllLogFiles(){
			 char* fileName[4] = {"EventLog.txt" , "GUILog.txt", "logicLog.txt" , "ParserLog.txt"};

			 for (int i=0; i<5;i++){
				std::ofstream out(fileName[i], std::ofstream::trunc);
				out.close();
			 }

			 log ("Clear All Log Files:", "All log files cleared");
		 }

private: System::Void MapleSyrup_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			//close everything
			closeCalendar();
		 }

private: System::Void MapleSyrup_Leave(System::Object^  sender, System::EventArgs^  e) {
			 DateTime current = DateTime::Now;
			 String^ timeToLog = current.ToString("dd MMM,dddd, HH:mm:sss");
			 log ("Program terminated at:", convertToStd(timeToLog));
		 }
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Functions to convert between std::String and System::String^ 
* This is to essential for communication between various classes and this UI
* ===================================================================================================================================================================
*/

//Pre-condition : None
//Convert a System::String^ type to std::string type
public: std::string convertToStd(String^ sysStr){
			char buffer[999];
			sprintf(buffer,"%s",sysStr);
			std::string stdString(buffer);
			return stdString;
		}

//Pre-condition : None
//Convert a std::string type to System::String^ type
public: String^ convertToSys(std::string stdStr){
			String^ sysString = gcnew String(stdStr.c_str());
			Console::WriteLine(sysString);
			return sysString;
		}
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Functions for UI shortcuts
* ===================================================================================================================================================================
*/
private: bool isCtrlPressed;

private: void initializeShortcut(){
			 isCtrlPressed = false;
		 }

private: System::Void MapleSyrup_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == Keys::Escape){
				display->Select();
			 }

			 //Shortcuts that uses control key
			 if (e->KeyCode == Keys::ControlKey){
				 isCtrlPressed = true;
			 }
			  
			 if ( isCtrlPressed && e->KeyCode == Keys::F){
				 searchBox->Select();
				 isCtrlPressed = false;
			 }

			 if ( isCtrlPressed && e->KeyCode == Keys::D){
				 executeCalendarShortcut();
				 isCtrlPressed = false;
			 }

			 if ( isCtrlPressed && e->KeyCode == Keys::ShiftKey){
				 commandBox->Select();
				 isCtrlPressed = false;
			 }

			 if ( isCtrlPressed && e->KeyCode == Keys::Z){
				  undoLastCommand();
			 }

			 if ( isCtrlPressed && e->KeyCode == Keys::X){
				  redoLastCommand();
			 }

		 }

private: System::Void MapleSyrup_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == Keys::ControlKey){
				 isCtrlPressed = false;
			 }
		 }
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Functions to display information received from Logic.h to the various displays on UI; 
* Namely main display, main display label, floating tasks display and feedback box.
* ===================================================================================================================================================================
*/

//Pre-condition : Ensure executeUserInput() from Logic.h is executed before calling this function
//Get the error string from Logic.h when invoked by function executeUserInput(). 
//It proceed on to display this error string onto the feedbackBox of the UI.
private: void displayErrorString(){
			vector<std::string> displayErrorToFeedback = lGPtr->getFeedbackStrings();
			displayToFeedbackBox(displayErrorToFeedback);

			log ("Error string displayed:",displayErrorToFeedback.back());
		}

//Pre-condition : Ensure executeUserInput() from Logic.h is executed before calling this function 
//Get the display vectors from Logic.h when invoked by function executeUserInput(). 
//It proceed on to display these vectors to the respective displays, namely main display, floating tasks display and feedback box. 
private:void displayToAllDisplays(){
			vector<LogicUpdater::EVENT_STRING> displayToFloating = lGPtr->getFloatingStrings();
			vector<LogicUpdater::EVENT_STRING> displayToMain = lGPtr->getMainStrings();
			vector<std::string> displayToFeedback = lGPtr-> getFeedbackStrings();
			std::string displayToMainLabel = lGPtr->getMainDisplayLabel();

			displayToFeedbackBox (displayToFeedback);
			displayToFloatingDisplay (displayToFloating);
			displayToMainDisplay (displayToMain);
			displayToMainDisplayLabel(displayToMainLabel);
		}

//Pre-condition : vector displayToFeedback to be correctly updated
//Display feedback to feedbackBox
private: void displayToFeedbackBox(vector<std::string> displayToFeedback){
			feedbackBox->Text = "";
			for (unsigned int i = 0; i< displayToFeedback.size(); i++){
					String^ temp = convertToSys(displayToFeedback[i]);
					feedbackBox->Text += temp + "\n" ;
				}

			if (!displayToFeedback.empty()){
				log ("Feedback displayed:", displayToFeedback.back());
			}
		}

//Pre-condition : vector displayToFloating to be correctly updated
//Display list of floating tasks to floating display
private: void displayToFloatingDisplay(vector<LogicUpdater::EVENT_STRING> displayToFloating){
			floatingTasksDisplay->Text = "";

				for (unsigned int i = 0; i < displayToFloating.size(); i++){
					if (displayToFloating[i].isNew){
						String^ date = convertToSys (displayToFloating[i].dateString);
						floatingTasksDisplay->SelectionColor = Color::Green;

						std::string importanceSymbol = setImportancesymbol(displayToFloating[i].importanceLevel);
						String^ importanceSymbolString = convertToSys (importanceSymbol);

						String^  eventName= convertToSys (displayToFloating[i].eventString);

						floatingTasksDisplay->SelectionFont = gcnew Drawing::Font(floatingTasksDisplay->SelectionFont->FontFamily,floatingTasksDisplay->SelectionFont->Size, FontStyle::Bold);
						floatingTasksDisplay->SelectedText = date + importanceSymbolString + eventName + "\n";

						floatingTasksDisplay->ScrollToCaret();				
					} else {
						String^ date = convertToSys (displayToFloating[i].dateString);
						if (displayToFloating[i].isCompleted){
							floatingTasksDisplay->SelectionFont = gcnew Drawing::Font(floatingTasksDisplay->SelectionFont->FontFamily,floatingTasksDisplay->SelectionFont->Size, FontStyle::Strikeout);
						}
						floatingTasksDisplay->SelectionColor = Color::MidnightBlue;
						floatingTasksDisplay->SelectedText = date;

						std::string importanceSymbol = setImportancesymbol(displayToFloating[i].importanceLevel);
						String^ importanceSymbolString = convertToSys (importanceSymbol);
						floatingTasksDisplay->SelectionColor = Color::Red;
						if (displayToFloating[i].isCompleted){
							floatingTasksDisplay->SelectionFont = gcnew Drawing::Font(floatingTasksDisplay->SelectionFont->FontFamily,floatingTasksDisplay->SelectionFont->Size, FontStyle::Strikeout);
						}
						floatingTasksDisplay->SelectedText = importanceSymbolString;
						
						String^  eventName= convertToSys (displayToFloating[i].eventString);
						floatingTasksDisplay->SelectionColor = Color::MidnightBlue;
						if (displayToFloating[i].isCompleted){
							floatingTasksDisplay->SelectionFont = gcnew Drawing::Font(floatingTasksDisplay->SelectionFont->FontFamily,floatingTasksDisplay->SelectionFont->Size, FontStyle::Strikeout);
						}
						floatingTasksDisplay->SelectedText = eventName + "\n";
					}
				}

				log ("Floating displayed:", "Successful");
		}

//Pre-condition : vector displayToMain to be correctly updated
//Display information to main display
private: void displayToMainDisplay(vector<LogicUpdater::EVENT_STRING> displayToMain){
			display->Text = "";

			for (unsigned int i = 0; i < displayToMain.size(); i++){
				if (displayToMain[i].isMarker){
					std::string markerinStdString = displayToMain[i].eventString;
					String^ marker = convertToSys(markerinStdString);
					display->SelectionColor = Color::Gray;
					display->SelectedText =  marker + "\n";
				} else if(displayToMain[i].isNew && displayToMain[i].isClash){
					String^ date = convertToSys(displayToMain[i].dateString);
					
					std::string importanceSymbol = setImportancesymbol(displayToMain[i].importanceLevel);
					String^ importanceSymbolString = convertToSys (importanceSymbol);

					String^  eventName= convertToSys (displayToMain[i].eventString);

					display->SelectionColor = Color::Red;
					display->SelectionFont = gcnew Drawing::Font(display->SelectionFont->FontFamily,display->SelectionFont->Size, FontStyle::Bold);
					display->SelectedText = date + importanceSymbolString + eventName + "\n";

					display->ScrollToCaret();
				} else if (!displayToMain[i].isNew && displayToMain[i].isClash ){
					String^ date = convertToSys(displayToMain[i].dateString);
					
					std::string importanceSymbol = setImportancesymbol(displayToMain[i].importanceLevel);
					String^ importanceSymbolString = convertToSys (importanceSymbol);

					String^  eventName= convertToSys (displayToMain[i].eventString);

					display->SelectionColor = Color::Red;
					display->SelectedText = date + importanceSymbolString + eventName + "\n";
				} else if(displayToMain[i].isNew && !displayToMain[i].isClash){
						String^ date = convertToSys(displayToMain[i].dateString);
					
						std::string importanceSymbol = setImportancesymbol(displayToMain[i].importanceLevel);
						String^ importanceSymbolString = convertToSys (importanceSymbol);

						String^  eventName= convertToSys (displayToMain[i].eventString);

						display->SelectionColor = Color::Green;
						display->SelectionFont = gcnew Drawing::Font(display->SelectionFont->FontFamily,display->SelectionFont->Size, FontStyle::Bold);
						display->SelectedText = date + importanceSymbolString + eventName + "\n";

						int indexToBeScrolledTo = display->GetFirstCharIndexOfCurrentLine();
				} else {
						displayNormalEventToMain(displayToMain[i]);
					}
			}

			log ("Main displayed:" , "Successful");
		 }


private: void displayNormalEventToMain(LogicUpdater::EVENT_STRING normalEvent){
			 if( normalEvent.isCompleted ){
				 String^ date = convertToSys (normalEvent.dateString);
				 display->SelectionColor = Color::MidnightBlue;
				 display->SelectionFont = gcnew Drawing::Font(display->SelectionFont->FontFamily,display->SelectionFont->Size, FontStyle::Strikeout);
				 display->SelectedText = date;

				 std::string importanceSymbol = setImportancesymbol(normalEvent.importanceLevel);
				 String^ importanceSymbolString = convertToSys (importanceSymbol);
				 display->SelectionColor = Color::Red;
				 display->SelectionFont = gcnew Drawing::Font(display->SelectionFont->FontFamily,display->SelectionFont->Size, FontStyle::Strikeout);
				 display->SelectedText = importanceSymbolString;
						
				 String^  eventName= convertToSys (normalEvent.eventString);
				 display->SelectionColor = Color::MidnightBlue;
				 display->SelectionFont = gcnew Drawing::Font(display->SelectionFont->FontFamily,display->SelectionFont->Size, FontStyle::Strikeout);
				 display->SelectedText = eventName + "\n";
			 } else {
				 String^ date = convertToSys (normalEvent.dateString);
				 display->SelectionColor = Color::MidnightBlue;
				 display->SelectedText = date;

				 std::string importanceSymbol = setImportancesymbol(normalEvent.importanceLevel);
				 String^ importanceSymbolString = convertToSys (importanceSymbol);
				 display->SelectionColor = Color::Red;
				 display->SelectedText = importanceSymbolString;
						
				 String^  eventName= convertToSys (normalEvent.eventString);
				 display->SelectionColor = Color::MidnightBlue;	
				 display->SelectedText = eventName + "\n";
			 }

		 }

//Pre-condition : vector displayToMain to be correctly updated
//Display the label of what is being displayed on the main display onto mainDisplayLabel
private: void displayToMainDisplayLabel (std::string displayToMainLabel){
			 String^ mainLabelDisplay = convertToSys (displayToMainLabel);
			 mainDisplayLabel->Text = mainLabelDisplay; 

			 log ("Main label displayed:", displayToMainLabel);
		}

private: std::string setImportancesymbol(int importanceLevel){
			 std::string importanceSymbol = "";

			 for (unsigned int i=0; i<importanceLevel;i++){
				 importanceSymbol += "!";
			 }

			 return importanceSymbol;
		 }
//===================================================================================================================================================================


/*
* =================================================================================================================================================================== 
* Functions to check and decide whether input command should be executed by UI or pass to logic
* It moves on to execute the command respectively
* ===================================================================================================================================================================
*/
//Pre-condition : None
//This function centralises all the calls from the various parts/event handlers from the UI 
//It first checks and matches commands that are related to developer or UI-handled. If yes, it proceeds with executing these commands
public: void executeUserInput(std::string input){
			if (checkAndExecuteDeveloperCommands(input)){
				return;
			}

			if (checkAndExecuteUIHandledCommands(input)){
				return;
			}
		
			//Pass userinput to logic when the command does not fit those handed by UI
			passCommandToLogic(input);
		}

//Pre-condition : This function can only be called by function executeUserInput() of UI
// [WARNING - Only for Developers to clear off data]
// This function takes in a std::string and check whether it is a developer command
// If yes, it will proceed on to execute the command and return true
// If no, it will return false
public: bool checkAndExecuteDeveloperCommands(std::string input){
			bool isDeveloperCommand;

			std::string inputInLowerCase = toLowerCase(input);

			if (inputInLowerCase.size() >=14 && inputInLowerCase.substr(0,14) == "mapleclearlogs"){
				clearAllLogFiles();
				Application::Exit();
				isDeveloperCommand = true;
			} else if (inputInLowerCase.size() >=10 && inputInLowerCase.substr(0,10) == "maplesyrup"){
				clearAllLogFiles();
				std::ofstream out("myStorage.txt", std::ofstream::trunc);
				out.close();
				Application::Exit();
				isDeveloperCommand = true;
			} else if (inputInLowerCase.size() >=13 && inputInLowerCase.substr(0,13) == "mapleclearall"){
				std::ofstream out("myStorage.txt", std::ofstream::trunc);
				out.close();
				Application::Exit();
				isDeveloperCommand = true;

				log ("Developer command executed:", "mapleclearall" );
			} else {
				isDeveloperCommand = false;
			}

			return isDeveloperCommand;
		}

//Pre-condition : This function can only be called by function executeUserInput() of UI
// This function takes in a std::string and check whether it is a UI-handled command
// If yes, it will proceed on to execute the command and return true
// If no, it will return false
private: bool checkAndExecuteUIHandledCommands(std::string input){
			bool isUIHandledCommand;

			std::string inputInLowerCase = toLowerCase(input);

			if (inputInLowerCase.size() ==4 &&  inputInLowerCase.substr(0,4) == "exit"){
				Application::Exit();
				isUIHandledCommand = true;

				log ("UI-handled command executed:", "exit" );
			} else if (inputInLowerCase.size() ==4 && inputInLowerCase.substr(0,4) == "help"){
				displayHelpIntroduction();
				isUIHandledCommand = true;

				log ("UI-handled command executed:", "help" );
			} else if (inputInLowerCase.size() ==8 && inputInLowerCase.substr(0,8) == "commands"){
				displayHelpCommands();
				isUIHandledCommand = true;

				log ("UI-handled command executed:", "commands" );
			} else if (inputInLowerCase.size() ==8 && inputInLowerCase.substr(0,8) == "calendar"){
				executeCalendarShortcut();
				isUIHandledCommand = true;

				log ("UI-handled command executed:", "calendar" );
			} else if (inputInLowerCase.size() ==6 && inputInLowerCase.substr(0,6) == "search"){
				searchBox->Select();
				isUIHandledCommand = true;

				log ("UI-handled command executed:", "search" );
			} else if (inputInLowerCase.size() ==4 && inputInLowerCase.substr(0,4) == "next"){
				executeNextKey();
				isUIHandledCommand = true;

				log ("UI-handled command executed:", "next" );
			} else if (inputInLowerCase.size() ==4 && inputInLowerCase.substr(0,4) =="back"){
				executeBackKey();
				isUIHandledCommand = true;

				log ("UI-handled command executed:", "back" );
			} else if (inputInLowerCase.size() ==9 && inputInLowerCase.substr(0,9) == "shortcuts"){
				displayHelpShortCuts();
				isUIHandledCommand = true;

				log ("UI-handled command executed:", "shortcuts" );
			} else{
				isUIHandledCommand = false;

			}
			
			return isUIHandledCommand;
		 }

//Pre-condition: Check that commmand does not belong to Develop/UI-handleded commands before passing to this function
//				 This function can only be called by function executeUserInput() of UI
//This function links UI to Logic.h by passing a command for logic.h to execute
//Thereafter, based on the Boolean variable it received from Logic.h’s executeUserInput() function, 
//it proceeds to call functions to display the relevant information to the various displays on the UI 
private: void passCommandToLogic(std::string input){
			 std::string inputInLowerCase = toLowerCase(input);

			 bool isExecuted = lGPtr->executeUserInput(inputInLowerCase);
			 log("Logic command executed & returns:", convertToStd(isExecuted.ToString()));

			 if(isExecuted){
				 displayToAllDisplays();
			 } else {
				 displayErrorString();
			 }
		 }



std::string toLowerCase(std::string word){
	for (int i=0;i<word.size();i++){
		 word[i] = tolower(word[i]);
	 }
	return word;
 }
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* commandBar
* ===================================================================================================================================================================
*/
private: System::Void commandBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode != Keys::Enter){
				return;
			 }

			 String^ temp = commandBox->Text;
			 resetCommandBar();
			 unDisplaySuggestion();
			 
			 std::string input = convertToStd(temp);
			 log("User Command:", input);

			 if (temp == ""){
				 return;
			 }

			 executeUserInput(input);
		 }

public: void resetCommandBar(){
			commandBox->Text = "";
		}
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Functions that link commandBar to CommandSuggestion.h to display the various suggestions 
* ===================================================================================================================================================================
*/
//Pre-condition : None 
//Display the information in vector suggestion onto suggestBar
private: void displaySuggestion(std::vector<std::string> suggestion){
			suggestBar->Visible = true;
			suggestBar->Items->Clear();

			for (unsigned int i = 0; i < suggestion.size();i++){
					std::string temp = suggestion[i];
					String^ toAdd = convertToSys(temp);
					
					suggestBar->Items->Add(toAdd);
				}
		}

//Pre-condition : None 
//Clear information in suggestBar and make it invisible
private: void unDisplaySuggestion(){
			suggestBar->Visible = false;
			suggestBar->Items->Clear();
		}

//This function is triggered whenever there is a textchange in the commandBox
//Use to trigger suggestBox to display the respective suggestions to user
private: System::Void commandBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 std::string temp = convertToStd(commandBox->Text);
			 std::string tempCommand = toLowerCase(temp);

			 UICommandSuggestion::ComdType tempCommandType = cSPtr->getComdType(tempCommand);

			 switch(tempCommandType){
			 case UICommandSuggestion::ADD_:{
				 std::vector<std::string> suggestionAdd = cSPtr->getSuggestionAdd();
				 displaySuggestion(suggestionAdd);
				 break;
										  }
			 case UICommandSuggestion::DELETE_:{
				 std::vector<std::string> suggestionDelete = cSPtr->getSuggestionDelete();
				 displaySuggestion(suggestionDelete);
				 break;
										  }
			 case UICommandSuggestion::EDIT_:{
				 std::vector<std::string> suggestionEdit = cSPtr->getSuggestionEdit();
				 displaySuggestion(suggestionEdit);
				 break;
										  }
			 case UICommandSuggestion::SEARCH_:{
				 std::vector<std::string> suggestionSearch = cSPtr->getSuggestionSearch();
				 displaySuggestion(suggestionSearch);
				 break;
										  }
			 case UICommandSuggestion::SHOW_:{
				 std::vector<std::string> suggestionShow = cSPtr->getSuggestionShow();
				 displaySuggestion(suggestionShow);
				 break;
										  }
			 case UICommandSuggestion::UNDISPLAY_:{
				 unDisplaySuggestion();
				 break;
										  }
			 case UICommandSuggestion::INVALID_:{
				 break;
										  }
			 }
		 }
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Functions and attributes that control show and help column
* Functions that are under the show column call UIShow.h directly to obtain the respective commands and pass them to function executeUserInput for execution
* Functions that are under the help column call the respective help functions within this class
* ===================================================================================================================================================================
*/
// To display & undisplay the Show column when clicked
private: System::Void showButton_Click(System::Object^  sender, System::EventArgs^  e) {		
			 showDropDown->Show(showButton,0,showButton->Height);		 
		 }

// Execute the respective show commands when clicked
private: System::Void dayToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 log("Called UIShow.showDay", "");
			 std::string loadCommand = showPtr->getShowDay();
			 executeUserInput(loadCommand);
		 }

private: System::Void weekToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 log("Called UIShow.showWeek", "");
			 std::string loadCommand = showPtr->getShowWeek();
			 executeUserInput(loadCommand);
		 }

private: System::Void monthToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 log("Called UIShow.showMonth", "");
			 std::string loadCommand = showPtr->getShowMonth();
			 executeUserInput(loadCommand);
		 }

private: System::Void allToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 log("Called UIShow.showAll", "");
			 std::string loadCommand = showPtr->getShowAll();
			 executeUserInput(loadCommand);
		 }

private: System::Void archiveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 log("Called UIShow.showArchive", "");
			 std::string loadCommand = showPtr->getShowArchive();
			 executeUserInput(loadCommand);
		 }


// To display & undisplay the Help column when clicked
private: System::Void helpButton_Click(System::Object^  sender, System::EventArgs^  e) {	 
			 helpDropDown->Show(helpButton,0,helpButton->Height);	 
		 }

// Execute the respective help commands when clicked
private: System::Void introductionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 displayHelpIntroduction();
		 }

private: System::Void commandsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 displayHelpCommands();
		 }

private: System::Void shortcutsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 displayHelpShortCuts();
		 }
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Functions that link UI to UIHelp.h to display help information
* ===================================================================================================================================================================
*/
private: void displayHelpIntroduction(){
			 std::string toMainDisplayLabel = "Help Introduction";
			 displayToMainDisplayLabel(toMainDisplayLabel);

			 vector<LogicUpdater::EVENT_STRING> helpIntroduction = helpPtr->getHelpIntroduction();

			 log("Called UIHelp.introduction", "");

			 displayToMainDisplay(helpIntroduction);
		 }

private: void displayHelpCommands(){
			 std::string toMainDisplayLabel = "Commands";
			 displayToMainDisplayLabel(toMainDisplayLabel);

			 vector<LogicUpdater::EVENT_STRING> helpCommands = helpPtr->getHelpCommands();

			 log("Called UIHelp.commands", "");

			 displayToMainDisplay(helpCommands);
		 }

public: void displayHelpShortCuts(){
			 std::string toMainDisplayLabel = "Shortcuts";
			 displayToMainDisplayLabel(toMainDisplayLabel);

			 vector<LogicUpdater::EVENT_STRING> helpShortcuts= helpPtr->getHelpShortcuts();

			 log("Called UIHelp.shortcuts", "");

			 displayToMainDisplay(helpShortcuts);
		}
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Calendar display functions
* ===================================================================================================================================================================
*/
private: bool topCalenderDisplayed;

private: System::Void calenderTop_EnabledChanged(System::Object^  sender, System::EventArgs^  e) {
			 calenderTop->Visible=false;
		 }

private: System::Void calenderIcon_Click(System::Object^  sender, System::EventArgs^  e) { 
			executeCalendarShortcut();
		 }

private: System::Void calenderTop_Leave(System::Object^  sender, System::EventArgs^  e) {
			executeCalendarShortcut();
		 }

private: System::Void calenderTop_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }

private: void executeCalendarShortcut(){
			 if(!topCalenderDisplayed){
				 openCalendar();
			 } else{
				 closeCalendar();
			 }
		 }

private: void openCalendar(){
			calenderTop->Visible = true;
			calenderTop->BringToFront();
			calenderTop->Select();
			topCalenderDisplayed = true;
		 }

private: void closeCalendar(){
			calenderTop->Visible = false;
			topCalenderDisplayed = false;
			calenderTop->SendToBack();
		 }

//Pre-condition : Only works when dates are chosen from the calendar
//It receives the start and end date to be displayed from calendar and pass them to UIShow.h to generate a proper command
//It moves on to pass this command to function executeUserInput for executition
private: System::Void calenderTop_DateSelected(System::Object^  sender, System::Windows::Forms::DateRangeEventArgs^  e) {	 
			 //Start date
			 String^ tempStartDate = calenderTop->SelectionStart.ToString();
			 std::string startDate = convertToStd(tempStartDate);

			 //End date
			 String^ tempEndDate = calenderTop->SelectionEnd.ToString();
			 std::string endDate = convertToStd(tempEndDate);

			 log("Calendar date(s) selected:", startDate + "to" + endDate);

			 std::string command = showPtr->generateDisplayFromCalender(startDate, endDate);
			 executeUserInput(command);
		 }
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Search function and related functions that will be used in Search Mode
* ===================================================================================================================================================================
*/

private: void noSearchInput(){
			 String^ NO_SEARCH_INPUT = "No Search Input\n";
			 display->Text = NO_SEARCH_INPUT;
			 floatingTasksDisplay->Text = NO_SEARCH_INPUT;
		 }

private: System::Void searchBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 String^ tempToBeSearched = searchBox->Text;

			 if (tempToBeSearched == ""){
				 noSearchInput();
			 }
			 
			 std::string toBeSearched = convertToStd(tempToBeSearched);
			 std::string COMMAND_SEARCH = "search";
			 std::string searchCommand = COMMAND_SEARCH + " " + toBeSearched;
			 executeUserInput(searchCommand);
			 
			 //Overwrite the maindisplaylabel with this
			 displayToMainDisplayLabel("Search Mode");
		 }

private: System::Void searchBox_Enter(System::Object^  sender, System::EventArgs^  e) {
			 log("Search Mode entered", "");
			 std::vector<tm> mainDisplayDate = lGPtr->getTempMainDisplayLabel();
			 std::string mainLabel = convertToStd(mainDisplayLabel->Text);
			 showPtr->setCurrentCommand(mainLabel,mainDisplayDate);

			 log("Called UIShow.setCurrentCommand:", mainLabel);

			 noSearchInput();
			 displayToMainDisplayLabel("Search Mode");
		 }

private: System::Void searchBox_Leave(System::Object^  sender, System::EventArgs^  e) {
			 log("Search Mode exited", "");
			 searchBox->Text = "";
			 
			 //Reload floating display before search mode
			 std::string loadCommandFloating = showPtr->getShowFloat();
			 executeUserInput(loadCommandFloating);

			 std::string currentShowCommand = showPtr->getCurrentCommand();

			 //Reload main display before search mode
			 executeUserInput(currentShowCommand); 
		 }
//===================================================================================================================================================================			 

/*
* =================================================================================================================================================================== 
* Functions that allow toggle between main display, floating display and commandBox.
* Functions that allow toggle between previous and next day of main display
* ===================================================================================================================================================================
*/
private: System::Void display_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		  if (e->KeyCode == Keys::Left){
				 executeBackKey();
				 display->SelectionStart = 0;
			 }

		  if (e->KeyCode == Keys::Right){
				executeNextKey();
				display->SelectionStart = 0;
			 }

		  if (e->KeyCode == Keys::Escape){
			    floatingTasksDisplay->Select();			
			 }
		 }

private: void executeBackKey(){
			 std::vector<tm> mainDisplayDate = lGPtr->getTempMainDisplayLabel();
			 std::string mainLabel = convertToStd(mainDisplayLabel->Text);
			 std::string newShowCommand = showPtr->displayBack(mainLabel,mainDisplayDate);
			 log("Called UIShow.displayBack:", mainLabel);
			 executeUserInput(newShowCommand);
		 }

private: void executeNextKey(){
			 std::vector<tm> mainDisplayDate = lGPtr->getTempMainDisplayLabel();
			 std::string mainLabel = convertToStd(mainDisplayLabel->Text);
			 std::string newShowCommand = showPtr->displayNext(mainLabel,mainDisplayDate);
			 log("Called UIShow.displayNext:", mainLabel);
			 executeUserInput(newShowCommand);
		 }

private: System::Void display_Enter(System::Object^  sender, System::EventArgs^  e) {
			 display->SelectionStart = 0;
		 }

private: System::Void floatingTasksDisplay_Enter(System::Object^  sender, System::EventArgs^  e) {
			floatingTasksDisplay->SelectionStart = 0;
		 }

private: System::Void floatingTasksDisplay_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == Keys::Escape){
			    commandBox->Select();
			 }
		 }
//===================================================================================================================================================================	

/*
* =================================================================================================================================================================== 
* Undo and Redo Buttons and functions
* ===================================================================================================================================================================
*/
private: System::Void undoButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 undoLastCommand();
		 }

private: void undoLastCommand(){
			executeUserInput("undo");
		 }

private: System::Void redoButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 redoLastCommand();
		 }

private: void redoLastCommand(){
			executeUserInput("redo");
		 }
//===================================================================================================================================================================	

/*
* =================================================================================================================================================================== 
* Logging function
* ===================================================================================================================================================================
*/
private: Void log(std::string label, std::string commands){
			 std::ofstream outFile("GUILog.txt",std::ios::app);

			 outFile << label + " " + commands + "\n";

			 outFile.close();
		 }
//===================================================================================================================================================================




private: System::Void dueLabel_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}