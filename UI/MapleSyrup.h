#pragma once
#include <iostream>

#include <assert.h>
#include <cctype>

#include "Logic.h"
#include "Conversion.h"
#include "CommandSuggestion.h"
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
		CommandSuggestion* cSPtr; 

		Logic* lGPtr;
		
		Conversion* cVPtr;

		UIHelp* helpPtr;

		UIShow* showPtr;

	private: System::Windows::Forms::Button^  showButton;
	private: System::Windows::Forms::Button^  helpButton;




	private: System::Windows::Forms::MonthCalendar^  calenderTop;
	private: System::Windows::Forms::Button^  backButton;
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
	private: System::Windows::Forms::Button^  editButton;
	private: System::Windows::Forms::ContextMenuStrip^  editDropDown;
	private: System::Windows::Forms::ToolStripMenuItem^  undoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  redoToolStripMenuItem;


	private: System::Windows::Forms::Timer^  timer1;













	private: System::Windows::Forms::Button^  nextButton;

	public:
		MapleSyrup(void)
		{
			InitializeComponent();
		
			//Create logic object here
			//
			//TODO: Add the constructor code here

			//Initialization
			cSPtr = new CommandSuggestion;

			lGPtr = new Logic;

			cVPtr = new Conversion;

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
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
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

	private: System::Windows::Forms::FontDialog^  fontDialog1;


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
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
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
			this->showButton = (gcnew System::Windows::Forms::Button());
			this->helpButton = (gcnew System::Windows::Forms::Button());
			this->suggestBar = (gcnew System::Windows::Forms::ListBox());
			this->fontDialog1 = (gcnew System::Windows::Forms::FontDialog());
			this->backButton = (gcnew System::Windows::Forms::Button());
			this->nextButton = (gcnew System::Windows::Forms::Button());
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
			this->editButton = (gcnew System::Windows::Forms::Button());
			this->editDropDown = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->undoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->redoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->comdIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->calenderIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->floatingIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchIcon))->BeginInit();
			this->showDropDown->SuspendLayout();
			this->helpDropDown->SuspendLayout();
			this->editDropDown->SuspendLayout();
			this->SuspendLayout();
			// 
			// commandBox
			// 
			this->commandBox->AcceptsReturn = true;
			this->commandBox->AcceptsTab = true;
			this->commandBox->AllowDrop = true;
			this->commandBox->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(11) {resources->GetString(L"commandBox.AutoCompleteCustomSource"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource1"), resources->GetString(L"commandBox.AutoCompleteCustomSource2"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource3"), resources->GetString(L"commandBox.AutoCompleteCustomSource4"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource5"), resources->GetString(L"commandBox.AutoCompleteCustomSource6"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource7"), resources->GetString(L"commandBox.AutoCompleteCustomSource8"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource9"), resources->GetString(L"commandBox.AutoCompleteCustomSource10")});
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
			this->display->AcceptsTab = true;
			this->display->AutoWordSelection = true;
			this->display->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->display->Cursor = System::Windows::Forms::Cursors::SizeAll;
			resources->ApplyResources(this->display, L"display");
			this->display->Name = L"display";
			this->display->ReadOnly = true;
			this->display->ShowSelectionMargin = true;
			this->display->TabStop = false;
			this->toolTip1->SetToolTip(this->display, resources->GetString(L"display.ToolTip"));
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
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->Cursor = System::Windows::Forms::Cursors::SizeAll;
			resources->ApplyResources(this->richTextBox1, L"richTextBox1");
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->TabStop = false;
			this->toolTip1->SetToolTip(this->richTextBox1, resources->GetString(L"richTextBox1.ToolTip"));
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
			this->toolTip1->SetToolTip(this->mainDisplayLabel, resources->GetString(L"mainDisplayLabel.ToolTip"));
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
			this->calenderIcon->MouseEnter += gcnew System::EventHandler(this, &MapleSyrup::calenderIcon_MouseEnter);
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
			// 
			// showButton
			// 
			this->showButton->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->showButton->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->showButton, L"showButton");
			this->showButton->ForeColor = System::Drawing::Color::Black;
			this->showButton->Name = L"showButton";
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
			// backButton
			// 
			resources->ApplyResources(this->backButton, L"backButton");
			this->backButton->Name = L"backButton";
			this->backButton->UseVisualStyleBackColor = true;
			this->backButton->Click += gcnew System::EventHandler(this, &MapleSyrup::backButton_Click);
			// 
			// nextButton
			// 
			resources->ApplyResources(this->nextButton, L"nextButton");
			this->nextButton->Name = L"nextButton";
			this->nextButton->UseVisualStyleBackColor = true;
			this->nextButton->Click += gcnew System::EventHandler(this, &MapleSyrup::nextButton_Click);
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
			resources->ApplyResources(this->allToolStripMenuItem, L"allToolStripMenuItem");
			this->allToolStripMenuItem->Name = L"allToolStripMenuItem";
			// 
			// archiveToolStripMenuItem
			// 
			resources->ApplyResources(this->archiveToolStripMenuItem, L"archiveToolStripMenuItem");
			this->archiveToolStripMenuItem->Name = L"archiveToolStripMenuItem";
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
			resources->ApplyResources(this->shortcutsToolStripMenuItem, L"shortcutsToolStripMenuItem");
			this->shortcutsToolStripMenuItem->Name = L"shortcutsToolStripMenuItem";
			// 
			// editButton
			// 
			this->editButton->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->editButton->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->editButton, L"editButton");
			this->editButton->ForeColor = System::Drawing::Color::Black;
			this->editButton->Name = L"editButton";
			this->editButton->UseVisualStyleBackColor = false;
			this->editButton->Click += gcnew System::EventHandler(this, &MapleSyrup::editButton_Click);
			// 
			// editDropDown
			// 
			this->editDropDown->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->editDropDown, L"editDropDown");
			this->editDropDown->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->undoToolStripMenuItem, 
				this->redoToolStripMenuItem});
			this->editDropDown->Name = L"editDropDown";
			// 
			// undoToolStripMenuItem
			// 
			resources->ApplyResources(this->undoToolStripMenuItem, L"undoToolStripMenuItem");
			this->undoToolStripMenuItem->Name = L"undoToolStripMenuItem";
			// 
			// redoToolStripMenuItem
			// 
			resources->ApplyResources(this->redoToolStripMenuItem, L"redoToolStripMenuItem");
			this->redoToolStripMenuItem->Name = L"redoToolStripMenuItem";
			// 
			// MapleSyrup
			// 
			this->AllowDrop = true;
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->Controls->Add(this->editButton);
			this->Controls->Add(this->nextButton);
			this->Controls->Add(this->backButton);
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
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->searchBox);
			this->Controls->Add(this->feedbackBox);
			this->Controls->Add(this->commandBox);
			this->Controls->Add(this->display);
			this->Controls->Add(this->calenderTop);
			this->ForeColor = System::Drawing::Color::Black;
			this->HelpButton = true;
			this->KeyPreview = true;
			this->Name = L"MapleSyrup";
			this->ShowIcon = false;
			this->Load += gcnew System::EventHandler(this, &MapleSyrup::MapleSyrup_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MapleSyrup::MapleSyrup_KeyDown);
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
			this->editDropDown->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion



/*
* =================================================================================================================================================================== 
* Functions to load GUI & data
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
			/*
			listView1->Items->Add ("hello1");
			listView1->Items[0]->SubItems->Add ("hello1212sdfghjnbggfhfdsertyhgbgdfsertybvdfertyjnhgbfdvsefrtynhgsdfferygfsdewr4te5rhgfdewrtyjbgdfewrt5ryyhdsferthdgfdtrbyjydrduumtubyddrftg \t yrtdbytrbytrnytdnytrdyndtrnytrnyr123456");
			listView1->Items->Add ("hello11");
			listView1->Items[1]->SubItems->Add ("hello123");
			*/
}

private: void loadData(){
			 DateTime current = DateTime::Now;
			 String^ timeToLog = current.ToString("dd MMM,dddd, HH:mm:sss");
			 log ("Program starts at: " + convertTostd(timeToLog));

			 std::string loadCommand1 = showPtr->getShowFloat();
			 executeUserInput(loadCommand1);


			 std::string loadCommand2 = showPtr->getShowDay();
			 executeUserInput(loadCommand2); 
		 }


private: void clearAllLogFiles(){
			 char* fileName[4] = {"EventLog.txt" , "GUILog.txt" , "logicLog.txt" , "ParserLog.txt"};

			 for (int i=0; i<4;i++){
				std::ofstream out(fileName[i], std::ofstream::trunc);
				out.close();
			 }

		 }
//===================================================================================================================================================================


/*
* =================================================================================================================================================================== 
* Functions for UI shortcut
* ===================================================================================================================================================================
*/

//Pre-condition : None 
//Execute shortcuts for UI

private: bool isCtrlPressed;

private: void initializeShortcut(){
			 isCtrlPressed = false;
		 }

private: System::Void MapleSyrup_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == Keys::ControlKey){
				 isCtrlPressed = true;
			 }
			 
			 if ( isCtrlPressed && e->KeyCode == Keys::F){
				 searchBox->Select();
				 isCtrlPressed = false;
			 }

			 if ( isCtrlPressed && e->KeyCode == Keys::D){
				 if (topCalenderDisplayed == false){
					calenderTop->BringToFront();
					calenderTop->Visible = true;
					topCalenderDisplayed = true;
					calenderTop->Select();
					isCtrlPressed = false;
				 }
				 else {
					calenderTop->Visible = false;
					topCalenderDisplayed = false;
					isCtrlPressed = false;
				 }

			 }

			 if ( isCtrlPressed && e->KeyCode == Keys::A){
				 displayHelpCommands();
				 isCtrlPressed = false;
			 }

			 if ( isCtrlPressed && e->KeyCode == Keys::ShiftKey){
				 commandBox->Select();
				 isCtrlPressed = false;
			 }


		 }



//===================================================================================================================================================================



/*
* =================================================================================================================================================================== 
* Functions to change between std::String and System::String^ 
* This is to essential for communication between various classes and this UI
* ===================================================================================================================================================================
*/

//Pre-condition : None
//Convert a System::String^ type to std::string type
public: std::string convertTostd(String^ sysStr){
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
* Functions to display information received from Logic.h to the various displays on UI; 
* namely main display, floating tasks display and feedback box.
* ===================================================================================================================================================================
*/


//Pre-condition : Ensure executeUserInput() from Logic.h is executed before calling this function 
//Get the error string from Logic.h when invoked by function executeUserInput(). 
//It proceed on to display this error string onto the feedbackBox of the UI.
private: void displayErrorString(){
			vector<std::string> displayErrorToFeedback = lGPtr->getFeedbackStrings();

			displayToFeedbackBox(displayErrorToFeedback);
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

//Pre-condition : None
//Check whether a integer input is odd
public: bool isOdd (int num){
	if (num%2 == 0){
		return false;
	} else{
		return true;
	}
}


//Pre-condition : vector displayToFeedback to be correctly updated
//Display feedback to feedbackBox
private: void displayToFeedbackBox(vector<std::string> displayToFeedback){
			feedbackBox->Text = "";
			for (unsigned int i = 0; i< displayToFeedback.size(); i++){
					String^ temp = convertToSys(displayToFeedback[i]);
					feedbackBox->Text += temp + "\n" ;
				}

			log ("Feedback displayed");
		}

//Pre-condition : vector displayToMain to be correctly updated
//Display information to main display
private: void displayToMainDisplay( vector<LogicUpdater::EVENT_STRING> displayToMain){
			display->Text = "";

			for (unsigned int i = 0; i < displayToMain.size(); i++){
				String^ temp = convertToSys(displayToMain[i].eventString);

				if(displayToMain[i].isNew && displayToMain[i].isClash){
					display->SelectionColor = Color::Red;
					display->SelectionFont = gcnew Drawing::Font(display->SelectionFont->FontFamily,display->SelectionFont->Size, FontStyle::Italic);
					display->SelectedText = temp + "\n" ;
				} else if ( displayToMain[i].isClash ){
					display->SelectionColor = Color::Red;
					display->SelectedText = temp + "\n" ;
				} else if(displayToMain[i].isNew){
						display->SelectionColor = Color::Green;
						display->SelectedText = temp + "\n" ;
					} else{
						if(displayToMain[i].isMarker){
							display->SelectionColor = Color::Gray;
							display->SelectedText = temp + "\n" ;
						} else {
							display->SelectionColor = Color::MidnightBlue;
							display->SelectedText = temp + "\n" ;
							}
					}
			
			}

			log ("Main displayed");
		 }

//Pre-condition : vector displayToMain to be correctly updated
//Display the label of what is being displayed on the main display onto mainDisplayLabel
private: void displayToMainDisplayLabel (std::string displayToMainLabel){
			 String^ mainLabelDisplay = convertToSys (displayToMainLabel);
			 mainDisplayLabel->Text = mainLabelDisplay; 

			 log ("Main label displayed");
		}



//Pre-condition : vector displayToFloating to be correctly updated
//Display list of floating tasks to floating display
private: void displayToFloatingDisplay(vector<LogicUpdater::EVENT_STRING> displayToFloating){
			floatingTasksDisplay->Text = "";

				for (unsigned int i = 0; i < displayToFloating.size(); i++){
					String^ temp = convertToSys(displayToFloating[i].eventString);
					if (displayToFloating[i].isNew){
						floatingTasksDisplay->SelectionColor = Color::Green;
						floatingTasksDisplay->SelectedText = temp + "\n";
					} else {
						floatingTasksDisplay->SelectionColor = Color::MidnightBlue;
						floatingTasksDisplay->SelectedText = temp + "\n";
					  }
				}

				log ("Floating displayed");
		}

//===================================================================================================================================================================



/*
* =================================================================================================================================================================== 
* Functions that link UI to Logic.h
* Commands / invokes are passed from UI to Logic.h 
* Information are received from Logic.h through it's getters 
* ===================================================================================================================================================================
*/


//Pre-condition : None
//Extract the first 4 letters of an input. It is also being converted to all lowercase
public: std::string extractFirstFourLetters(std::string input){
			if (input.size() < 4){
				return input;
			}

			std::string tempOutput = input.substr(0,4);
			std::string output = cVPtr->toLowerCase(tempOutput);
			
			return output;
		}

//Pre-condition : None
//Extract the first 4 letters of an input. It is also being converted to all lowercase
public: std::string extractFirstEightLetters(std::string input){
			if (input.size() < 8){
				return input;
			}

			std::string tempOutput = input.substr(0,8);
			std::string output = cVPtr->toLowerCase(tempOutput);
			
			return output;
		}


public: void resetCommandBar(){
			commandBox->Text = "";
		}

//Pre-condition : Ensure command from user is passed into this function
//This function centralises all the calls from the various parts/event handlers from the UI to Logic.h for execution
//Thereafter, based on the Boolean variable it received from Logic.h’s executeUserInput() function, 
//It proceed on to call functions to display the relevant information to the various displays on the UI 
public: void executeUserInput(std::string input){
			//developer function
			if (input == "maplerocks"){
				clearAllLogFiles();
				Application::Exit();
				return;
			}

			if (input == "maplesyrup"){
				clearAllLogFiles();
				std::ofstream out("mytext.txt", std::ofstream::trunc);
				out.close();
				Application::Exit();
				return;
			}

			////////////////////////////////////////////////////////////////////////

			std::string firstFourLetters = extractFirstFourLetters(input);

			if (isExit(firstFourLetters)){
				Application::Exit();
				return;
			}

			if (firstFourLetters == "help"){
				displayHelpIntroduction();
				return;
			}

			std::string firstEightLetters = extractFirstEightLetters(input);
			if (firstEightLetters == "commands"){
				displayHelpCommands();
				return;
			}
			
		
  			 bool isExecuted = lGPtr->executeUserInput(input);
			 log("Logic return: " + convertTostd(isExecuted.ToString()));

			 if(isExecuted){
				 displayToAllDisplays();
			 } else {
				 displayErrorString();
			 }
		}

public: bool isExit(std::string input){
			if (input == "exit"){
				return true;
			} else {
				return false;
			}
		}

private: System::Void commandBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode != Keys::Enter){
				return;
			 }

			 String^ temp = commandBox->Text;
			 resetCommandBar();
			 unDisplaySuggestion();
			 
			 std::string input = convertTostd(temp);
			 log("User Command: " + input);

			 if (temp == ""){
				 return;
			 }

			 executeUserInput(input);
		 }


//===================================================================================================================================================================


/*
* =================================================================================================================================================================== 
* Functions that link commandBar to CommandSuggestion.h to display the various suggestions 
* ===================================================================================================================================================================
*/

private: void displayHelpIntroduction(){
			 std::string toMainDisplayLabel = "Help Introduction";
			 displayToMainDisplayLabel(toMainDisplayLabel);

			 vector<LogicUpdater::EVENT_STRING> helpIntroduction = helpPtr->getHelpIntroduction();
			 displayToMainDisplay(helpIntroduction);
		 }


private: void displayHelpCommands(){
			 std::string toMainDisplayLabel = "Commands";
			 displayToMainDisplayLabel(toMainDisplayLabel);

			 vector<LogicUpdater::EVENT_STRING> helpCommands = helpPtr->getHelpCommands();
			 displayToMainDisplay(helpCommands);
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
			 std::string temp = convertTostd(commandBox->Text);
			 std::string tempCommand = cVPtr->toLowerCase(temp);

			 CommandSuggestion::ComdType tempCommandType = cSPtr->getComdType(tempCommand);

			 switch(tempCommandType){
			 case CommandSuggestion::ADD_:{
				 std::vector<std::string> suggestionAdd = cSPtr->getSuggestionAdd();
				 displaySuggestion(suggestionAdd);
				 break;
										  }
			 case CommandSuggestion::DELETE_:{
				 std::vector<std::string> suggestionDelete = cSPtr->getSuggestionDelete();
				 displaySuggestion(suggestionDelete);
				 break;
										  }
			 case CommandSuggestion::EDIT_:{
				 std::vector<std::string> suggestionEdit = cSPtr->getSuggestionEdit();
				 displaySuggestion(suggestionEdit);
				 break;
										  }
			 case CommandSuggestion::SEARCH_:{
				 std::vector<std::string> suggestionSearch = cSPtr->getSuggestionSearch();
				 displaySuggestion(suggestionSearch);
				 break;
										  }
			 case CommandSuggestion::SHOW_:{
				 std::vector<std::string> suggestionShow = cSPtr->getSuggestionShow();
				 displaySuggestion(suggestionShow);
				 break;
										  }
			 case CommandSuggestion::UNDISPLAY_:{
				 unDisplaySuggestion();
				 break;
										  }
			 case CommandSuggestion::INVALID_:{
				 break;
										  }
			 }
		 }


//===================================================================================================================================================================


/*
* =================================================================================================================================================================== 
* Functions and attributes that control the various displays
* ===================================================================================================================================================================
*/

//Attributes to to monitor the various displays
private: bool showDisplayed;
private: bool helpDisplayed;
private: bool topCalenderDisplayed;


//Pre-condition : None
//All user opened displays will be make invisible
private: void initializeAndUndisplayAll(){
			showDisplayed = false;
			helpDisplayed = false;
			topCalenderDisplayed = false;
		}







private: System::Void editButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 editDropDown->Show(editButton,0,editButton->Height);
		 }

// To display & undisplay the Show column when clicked
private: System::Void showButton_Click(System::Object^  sender, System::EventArgs^  e) {
			
			 showDropDown->Show(showButton,0,showButton->Height);	
			 
		 }

// To display & undisplay the Help column when mouse click
private: System::Void helpButton_Click(System::Object^  sender, System::EventArgs^  e) {	 
			 helpDropDown->Show(helpButton,0,helpButton->Height);	 
		 }


private: System::Void MapleSyrup_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			initializeAndUndisplayAll(); 
		 }

private: System::Void calenderIcon_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 if(topCalenderDisplayed == true){
				 calenderTop->Visible = false;
				 topCalenderDisplayed = false;
			 } else{
				 calenderTop->Visible = true;
				 calenderTop->BringToFront();
				 topCalenderDisplayed = true;
			 }
			 
		 }


//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Logging function
* ===================================================================================================================================================================
*/

private: Void log(std::string logString){
			 std::ofstream outFile("GUILog.txt",std::ios::app);

			 outFile << logString + "\n";

			 outFile.close();
		 }


//===================================================================================================================================================================

private: System::Void calenderIcon_MouseEnter(System::Object^  sender, System::EventArgs^  e) {			 
		 }



/*
* =================================================================================================================================================================== 
* Show button functions
* ===================================================================================================================================================================
*/

private: System::Void dayToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 std::string loadCommand = showPtr->getShowDay();
			 executeUserInput(loadCommand);
		 }

private: System::Void weekToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 std::string loadCommand = showPtr->getShowWeek();
			 executeUserInput(loadCommand);
		 }

private: System::Void monthToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 std::string loadCommand = showPtr->getShowMonth();
			 executeUserInput(loadCommand);
		 }
//===================================================================================================================================================================


/*
* =================================================================================================================================================================== 
* Help button functions
* ===================================================================================================================================================================
*/

private: System::Void introductionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 displayHelpIntroduction();
		 }

private: System::Void commandsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 displayHelpCommands();
		 }


//===================================================================================================================================================================


/*
* =================================================================================================================================================================== 
* Calender + front and back display buttons
* ===================================================================================================================================================================
*/
private: System::Void calenderTop_DateSelected(System::Object^  sender, System::Windows::Forms::DateRangeEventArgs^  e) {	 
			 //Start
			 String^ tempStartDate = calenderTop->SelectionStart.ToString();
			 std::string startDate = convertTostd(tempStartDate);

			 //end
			 String^ tempEndDate = calenderTop->SelectionEnd.ToString();
			 std::string endDate = convertTostd(tempEndDate);

			 std::string command = showPtr->generateDisplayFromCalender(startDate, endDate);

			 executeUserInput(command);
		 }

private: System::Void calenderTop_EnabledChanged(System::Object^  sender, System::EventArgs^  e) {
			 calenderTop->Visible=false;
		 }

private: System::Void backButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 std::vector<tm> mainDisplayDate = lGPtr->getTempMainDisplayLabel();
			 std::string mainLabel = convertTostd(mainDisplayLabel->Text);
			 std::string newShowCommand = showPtr->displayBack(mainLabel,mainDisplayDate);

			 
			 executeUserInput(newShowCommand);
		 }
private: System::Void nextButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 std::vector<tm> mainDisplayDate = lGPtr->getTempMainDisplayLabel();
			 std::string mainLabel = convertTostd(mainDisplayLabel->Text);
			 std::string newShowCommand = showPtr->displayNext(mainLabel,mainDisplayDate);

			 
			 executeUserInput(newShowCommand);
		 }

//===================================================================================================================================================================


/*
* =================================================================================================================================================================== 
* My own test function
* ===================================================================================================================================================================
*/

private: System::Void emailToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 std::string emails[4] = { "kangter@gmail.com","joshua.chejy@gmail.com","owj_88@hotmail.com" };

			 
			 for (int i=0 ;i<1;i++){
			

			 MailMessage^ mail = gcnew MailMessage("maplesyrupcs@gmail.com","joshua.chejy@gmail.com", "Test", "This email is sent via MapleSyrup Program");

			 SmtpClient^ client = gcnew SmtpClient ("smtp.gmail.com");
			 
			 client->Port = 587;

			 client->Credentials = gcnew System::Net::NetworkCredential("maplesyrupcs@gmail.com","wjgljcyk");

			 client->EnableSsl = true;

			 client->Send(mail);

			 }

		 }

//===================================================================================================================================================================


/*
* =================================================================================================================================================================== 
* Search function and related functions that will be used in Search Mode
* ===================================================================================================================================================================
*/

private: System::Void searchBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 String^ tempToBeSearched = searchBox->Text;
			 std::string toBeSearched = convertTostd(tempToBeSearched);

			 std::string COMMAND_SEARCH = "search";

			 std::string searchCommand = COMMAND_SEARCH + " " + toBeSearched;

			 executeUserInput(searchCommand);
			 
			 //Overwrite the maindisplaylabel with this
			 displayToMainDisplayLabel("Search Mode");

		 }


private: System::Void searchBox_Enter(System::Object^  sender, System::EventArgs^  e) {			 
			 displayToMainDisplayLabel("Search Mode");
		 }

private: System::Void searchBox_Leave(System::Object^  sender, System::EventArgs^  e) {
			 searchBox->Text = "";
			 displayToMainDisplayLabel("Search Mode exited");

			 
		 }
//===================================================================================================================================================================			 

};
}