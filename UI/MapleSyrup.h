#pragma once
#include <iostream>

#include <msclr\marshal_cppstd.h>
#include <assert.h>

#include "Logic.h"
#include "Conversion.h"
#include "CommandSuggestion.h"



namespace UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Diagnostics;

	/// <summary>
	/// Summary for MapleSyrup
	/// </summary>
	public ref class MapleSyrup : public System::Windows::Forms::Form
	{
	private:
		CommandSuggestion* cSPtr; 

		Logic* lGPtr;
		
		Conversion* cVPtr;

	private: System::Windows::Forms::Button^  showButton;
	private: System::Windows::Forms::Button^  helpButton;
	private: System::Windows::Forms::Button^  introductionDisplay;
	private: System::Windows::Forms::Button^  commandsDisplay;
	private: System::Windows::Forms::Button^  undoButton;
	private: System::Windows::Forms::Button^  redoButton;
	private: System::Windows::Forms::MonthCalendar^  calenderTop;
	private: System::Windows::Forms::Button^  backButton;
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



	private: System::Windows::Forms::Button^  dayDisplay;

	private: System::Windows::Forms::Button^  weekDisplay;

	private: System::Windows::Forms::Button^  monthDisplay;

	private: System::Windows::Forms::Button^  allDisplay;
	private: System::Windows::Forms::Button^  archiveDisplay;

	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  floatingIcon;
	private: System::Windows::Forms::PictureBox^  pictureBox8;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::PictureBox^  searchIcon;

	private: System::Windows::Forms::TextBox^  commandBox;
	private: System::Windows::Forms::Timer^  timer1;
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
			this->dayDisplay = (gcnew System::Windows::Forms::Button());
			this->weekDisplay = (gcnew System::Windows::Forms::Button());
			this->monthDisplay = (gcnew System::Windows::Forms::Button());
			this->allDisplay = (gcnew System::Windows::Forms::Button());
			this->archiveDisplay = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->floatingIcon = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->searchIcon = (gcnew System::Windows::Forms::PictureBox());
			this->undoButton = (gcnew System::Windows::Forms::Button());
			this->redoButton = (gcnew System::Windows::Forms::Button());
			this->showButton = (gcnew System::Windows::Forms::Button());
			this->helpButton = (gcnew System::Windows::Forms::Button());
			this->introductionDisplay = (gcnew System::Windows::Forms::Button());
			this->commandsDisplay = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->suggestBar = (gcnew System::Windows::Forms::ListBox());
			this->fontDialog1 = (gcnew System::Windows::Forms::FontDialog());
			this->calenderTop = (gcnew System::Windows::Forms::MonthCalendar());
			this->backButton = (gcnew System::Windows::Forms::Button());
			this->nextButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->comdIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->calenderIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->floatingIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchIcon))->BeginInit();
			this->SuspendLayout();
			// 
			// commandBox
			// 
			this->commandBox->AcceptsReturn = true;
			this->commandBox->AcceptsTab = true;
			this->commandBox->AllowDrop = true;
			this->commandBox->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(9) {resources->GetString(L"commandBox.AutoCompleteCustomSource"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource1"), resources->GetString(L"commandBox.AutoCompleteCustomSource2"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource3"), resources->GetString(L"commandBox.AutoCompleteCustomSource4"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource5"), resources->GetString(L"commandBox.AutoCompleteCustomSource6"), 
				resources->GetString(L"commandBox.AutoCompleteCustomSource7"), resources->GetString(L"commandBox.AutoCompleteCustomSource8")});
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
			// 
			// display
			// 
			this->display->AutoWordSelection = true;
			this->display->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->display->Cursor = System::Windows::Forms::Cursors::SizeAll;
			resources->ApplyResources(this->display, L"display");
			this->display->Name = L"display";
			this->display->ReadOnly = true;
			this->display->ShowSelectionMargin = true;
			this->display->TabStop = false;
			this->toolTip1->SetToolTip(this->display, resources->GetString(L"display.ToolTip"));
			this->display->Click += gcnew System::EventHandler(this, &MapleSyrup::display_Click);
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
			// dayDisplay
			// 
			this->dayDisplay->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->dayDisplay->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->dayDisplay, L"dayDisplay");
			this->dayDisplay->ForeColor = System::Drawing::Color::DimGray;
			this->dayDisplay->Name = L"dayDisplay";
			this->toolTip1->SetToolTip(this->dayDisplay, resources->GetString(L"dayDisplay.ToolTip"));
			this->dayDisplay->UseVisualStyleBackColor = false;
			this->dayDisplay->Click += gcnew System::EventHandler(this, &MapleSyrup::dayDisplay_Click);
			// 
			// weekDisplay
			// 
			this->weekDisplay->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->weekDisplay->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->weekDisplay, L"weekDisplay");
			this->weekDisplay->ForeColor = System::Drawing::Color::DimGray;
			this->weekDisplay->Name = L"weekDisplay";
			this->toolTip1->SetToolTip(this->weekDisplay, resources->GetString(L"weekDisplay.ToolTip"));
			this->weekDisplay->UseVisualStyleBackColor = false;
			this->weekDisplay->Click += gcnew System::EventHandler(this, &MapleSyrup::weekDisplay_Click);
			// 
			// monthDisplay
			// 
			this->monthDisplay->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->monthDisplay->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->monthDisplay, L"monthDisplay");
			this->monthDisplay->ForeColor = System::Drawing::Color::DimGray;
			this->monthDisplay->Name = L"monthDisplay";
			this->toolTip1->SetToolTip(this->monthDisplay, resources->GetString(L"monthDisplay.ToolTip"));
			this->monthDisplay->UseVisualStyleBackColor = false;
			this->monthDisplay->Click += gcnew System::EventHandler(this, &MapleSyrup::monthDisplay_Click);
			// 
			// allDisplay
			// 
			this->allDisplay->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->allDisplay->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->allDisplay, L"allDisplay");
			this->allDisplay->ForeColor = System::Drawing::Color::DimGray;
			this->allDisplay->Name = L"allDisplay";
			this->toolTip1->SetToolTip(this->allDisplay, resources->GetString(L"allDisplay.ToolTip"));
			this->allDisplay->UseVisualStyleBackColor = false;
			this->allDisplay->Click += gcnew System::EventHandler(this, &MapleSyrup::allDisplay_Click);
			// 
			// archiveDisplay
			// 
			this->archiveDisplay->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->archiveDisplay->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->archiveDisplay, L"archiveDisplay");
			this->archiveDisplay->ForeColor = System::Drawing::Color::DimGray;
			this->archiveDisplay->Name = L"archiveDisplay";
			this->toolTip1->SetToolTip(this->archiveDisplay, resources->GetString(L"archiveDisplay.ToolTip"));
			this->archiveDisplay->UseVisualStyleBackColor = false;
			this->archiveDisplay->Click += gcnew System::EventHandler(this, &MapleSyrup::archiveDisplay_Click);
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
			// undoButton
			// 
			this->undoButton->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->undoButton->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->undoButton, L"undoButton");
			this->undoButton->ForeColor = System::Drawing::Color::DimGray;
			this->undoButton->Name = L"undoButton";
			this->toolTip1->SetToolTip(this->undoButton, resources->GetString(L"undoButton.ToolTip"));
			this->undoButton->UseVisualStyleBackColor = false;
			this->undoButton->Click += gcnew System::EventHandler(this, &MapleSyrup::undoButton_Click);
			// 
			// redoButton
			// 
			this->redoButton->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->redoButton->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->redoButton, L"redoButton");
			this->redoButton->ForeColor = System::Drawing::Color::DimGray;
			this->redoButton->Name = L"redoButton";
			this->toolTip1->SetToolTip(this->redoButton, resources->GetString(L"redoButton.ToolTip"));
			this->redoButton->UseVisualStyleBackColor = false;
			this->redoButton->Click += gcnew System::EventHandler(this, &MapleSyrup::redoButton_Click);
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
			this->showButton->MouseEnter += gcnew System::EventHandler(this, &MapleSyrup::showButton_MouseEnter);
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
			this->helpButton->MouseEnter += gcnew System::EventHandler(this, &MapleSyrup::helpButton_MouseEnter);
			// 
			// introductionDisplay
			// 
			this->introductionDisplay->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->introductionDisplay->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->introductionDisplay, L"introductionDisplay");
			this->introductionDisplay->ForeColor = System::Drawing::Color::DimGray;
			this->introductionDisplay->Name = L"introductionDisplay";
			this->introductionDisplay->UseVisualStyleBackColor = false;
			this->introductionDisplay->Click += gcnew System::EventHandler(this, &MapleSyrup::introductionDisplay_Click);
			// 
			// commandsDisplay
			// 
			this->commandsDisplay->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->commandsDisplay->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			resources->ApplyResources(this->commandsDisplay, L"commandsDisplay");
			this->commandsDisplay->ForeColor = System::Drawing::Color::DimGray;
			this->commandsDisplay->Name = L"commandsDisplay";
			this->commandsDisplay->UseVisualStyleBackColor = false;
			this->commandsDisplay->Click += gcnew System::EventHandler(this, &MapleSyrup::commandsDisplay_Click);
			// 
			// suggestBar
			// 
			this->suggestBar->BackColor = System::Drawing::Color::White;
			this->suggestBar->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			resources->ApplyResources(this->suggestBar, L"suggestBar");
			this->suggestBar->Name = L"suggestBar";
			this->suggestBar->TabStop = false;
			// 
			// calenderTop
			// 
			resources->ApplyResources(this->calenderTop, L"calenderTop");
			this->calenderTop->Name = L"calenderTop";
			this->calenderTop->ScrollChange = 1;
			this->calenderTop->MouseLeave += gcnew System::EventHandler(this, &MapleSyrup::calenderTop_MouseLeave);
			// 
			// backButton
			// 
			resources->ApplyResources(this->backButton, L"backButton");
			this->backButton->Name = L"backButton";
			this->backButton->UseVisualStyleBackColor = true;
			// 
			// nextButton
			// 
			resources->ApplyResources(this->nextButton, L"nextButton");
			this->nextButton->Name = L"nextButton";
			this->nextButton->UseVisualStyleBackColor = true;
			// 
			// MapleSyrup
			// 
			this->AllowDrop = true;
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->Controls->Add(this->nextButton);
			this->Controls->Add(this->backButton);
			this->Controls->Add(this->redoButton);
			this->Controls->Add(this->undoButton);
			this->Controls->Add(this->commandsDisplay);
			this->Controls->Add(this->introductionDisplay);
			this->Controls->Add(this->helpButton);
			this->Controls->Add(this->showButton);
			this->Controls->Add(this->dayDisplay);
			this->Controls->Add(this->weekDisplay);
			this->Controls->Add(this->monthDisplay);
			this->Controls->Add(this->allDisplay);
			this->Controls->Add(this->archiveDisplay);
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
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

//Pre-condition : None
//To display the UI
//Invoked by MapleSyrup.cpp
private: System::Void MapleSyrup_Load(System::Object^  sender, System::EventArgs^  e) {
			initializeAndUndisplayAll();

			loadData();

			//Have a welcome message

			//Invoke a show() to logic so as to display floating tasks and today's tasks
}

private: void loadData(){
			 DateTime current = DateTime::Now;
			 String^ time = current.ToString(" dd  MMM  yyyy ,  dddd"); 
			 String^ timeToLog = current.ToString("dd MMM,dddd, HH:mm:sss");
			 log ("Program starts at: " + convertTostd(timeToLog));
			 displayToMainDisplayLabel(convertTostd(time));

			

			 std::string loadCommand = "show today";
			 executeUserInput(loadCommand);
		 }

//Pre-condition : None 
//Execute shortcuts for UI
private: System::Void MapleSyrup_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == Keys::F1){
				 commandBox->Select();
			 }

			 if (e->KeyCode == Keys::F2){
				 searchBox->Select();
			 }
		 }



/*
* =================================================================================================================================================================== 
* Functions to change between std::String and System::String^ 
* This is to essential for communication between various classes and this UI
* ===================================================================================================================================================================
*/

//Pre-condition : None
//Convert a System::String^ type to std::string type
public: std::string convertTostd(String^ sysStr){
			std::string newString = msclr::interop::marshal_as<std::string>(sysStr);
			return newString;
		}

//Pre-condition : None
//Convert a std::string type to System::String^ type
public: String^ convertToSys(std::string stdStr){
			String^ newString = gcnew String(stdStr.c_str());
			Console::WriteLine(newString);
			return newString;
		}

//===================================================================================================================================================================



/*
* =================================================================================================================================================================== 
* Functions to display information received from Logic.h to the various displays on UI; 
* namely main display, floating tasks display and feedback box.
* ===================================================================================================================================================================
*/


//Pre-condition : Ensure executeUserInput() from Logic.h is executed before calling this function 
//Get the display vectors from Logic.h when invoked by function executeUserInput(). 
//It proceed on to display these vectors to the respective displays, namely main display, floating tasks display and feedback box. 
//Upon successful display to these displays, it will return true to caller. 
private:void displayToAllDisplays(){
			vector<Display::EVENT_STRING> displayToFloating = lGPtr->getFloatingStrings();
			vector<Display::EVENT_STRING> displayToMain = lGPtr->getMainStrings();
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
			for (int i=0; i< displayToFeedback.size(); i++){
					String^ temp = convertToSys(displayToFeedback[i]);
					feedbackBox->Text += temp + "\n" ;
				}

			log ("Feedback displayed");
		}

//Pre-condition : vector displayToMain to be correctly updated
//Display information to main display
private: void displayToMainDisplay( vector<Display::EVENT_STRING> displayToMain){
			display->Text = "";

			for (int i=0; i< displayToMain.size(); i++){
				String^ temp = convertToSys(displayToMain[i].eventString);

				if(displayToMain[i].isNew && displayToMain[i].isClash){
					display->SelectionColor = Color::Red;
					display->SelectionFont = gcnew Drawing::Font(display->SelectionFont->FontFamily,14, FontStyle::Bold);
					display->SelectedText = temp + "\n" ;
				} else if ( displayToMain[i].isClash ){
					display->SelectionColor = Color::Red;
					display->SelectedText = temp + "\n" ;
				} else if(displayToMain[i].isNew){
						display->SelectionColor = Color::Green;
						display->SelectedText = temp + "\n" ;
					} else{
						if(isOdd(i)){
							display->SelectionColor = Color::Blue;
							display->SelectedText = temp + "\n" ;
						} else {
							display->SelectionColor = Color::LightSlateGray;
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
private: void displayToFloatingDisplay(vector<Display::EVENT_STRING> displayToFloating){
			floatingTasksDisplay->Text = "";

				for (int i=0; i< displayToFloating.size(); i++){
					String^ temp = convertToSys(displayToFloating[i].eventString);
					if (displayToFloating[i].isNew){
						floatingTasksDisplay->SelectionColor = Color::Green;
						floatingTasksDisplay->SelectedText = temp + "\n";
					} else if(isOdd(i)){
						floatingTasksDisplay->SelectionColor = Color::Blue;
						floatingTasksDisplay->SelectedText = temp + "\n";
					} else {
						floatingTasksDisplay->SelectionColor = Color::LightSlateGray;
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
			std::string tempOutput = input.substr(0,4);
			std::string output = cVPtr->toLowerCase(tempOutput);
			
			return output;
		}

//Pre-condition : Ensure executeUserInput() from Logic.h is executed before calling this function 
//Get the error string from Logic.h when invoked by function executeUserInput(). 
//It proceed on to display this error string onto the main display of the UI.
//Upon successful display, it will return true to caller. 
private: void displayErrorString(){
			vector<std::string> tempErrorString = lGPtr->getErrorString();

			for (int i=0; i < tempErrorString.size(); i++){
			String^ errorString = convertToSys(tempErrorString[i]);
			display->Text += errorString + "\n";
			}
		}

public: void resetCommandBar(){
			commandBox->Text = "";
		}

//Pre-condition : Ensure command from user is passed into this function
//This function centralises all the calls from the various parts/event handlers from the UI to Logic.h for execution
//Thereafter, based on the Boolean variable it received from Logic.h’s executeUserInput() function, 
//It proceed on to call functions to display the relevant information to the various displays on the UI 
public: void executeUserInput(std::string input){
  			 bool isExecuted = lGPtr->executeUserInput(input);
			 log("Logic return: " + convertTostd(isExecuted.ToString()));

			 if(isExecuted){
				 displayToAllDisplays();
			 } else {
				 displayErrorString();
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

			 std::string firstfourletters = extractFirstFourLetters(convertTostd (temp));

			if (firstfourletters == "exit"){
				Application::Exit();
				return;
			}
			
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

//Pre-condition : None 
//Display the information in vector suggestion onto suggestBar
private: void displaySuggestion(std::vector<std::string> suggestion){
			suggestBar->Visible = true;
			suggestBar->Items->Clear();

			for (int i=0; i< suggestion.size();i++){
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

			unDisplayShow();
			unDisplayHelp();
		}

//Pre-condition : None 
//To display the components of column show
private: void displayShow (){
		dayDisplay->Visible = true;
		weekDisplay->Visible = true;
		monthDisplay->Visible = true;
		allDisplay->Visible = true;
		archiveDisplay->Visible = true;
		showDisplayed = true;

		dayDisplay->BringToFront();
		weekDisplay->BringToFront();
		monthDisplay->BringToFront();
		allDisplay->BringToFront();
		archiveDisplay->BringToFront();
		showButton->BringToFront();
		}

//Pre-condition : None 
//To un-display the components of column show
private: void unDisplayShow (){
		dayDisplay->Visible = false;
		weekDisplay->Visible = false;
		monthDisplay->Visible = false;
		allDisplay->Visible = false;
		archiveDisplay->Visible = false;
		showDisplayed = false;
		}


// To display the Show column when mouse enter
private: System::Void showButton_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 if (helpDisplayed == true){
				 unDisplayHelp();			 
			 }

			 if (showDisplayed == false){
				 displayShow();
			 }
		 }


// To display & undisplay the Show column when clicked
private: System::Void showButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (helpDisplayed == true){
				 unDisplayHelp();			 
			 }

			 if (showDisplayed == false){
				 displayShow();
			 } else {
				 unDisplayShow();		 
			 }
		 }

//Pre-condition : None 
// To display the components of column Help
private: void displayHelp (){
		introductionDisplay->Visible = true;
		commandsDisplay->Visible = true;
		undoButton->Visible = true;
		redoButton->Visible = true;
		helpDisplayed = true;

		introductionDisplay->BringToFront();
		commandsDisplay->BringToFront();
		undoButton->BringToFront();
		redoButton->BringToFront();
		helpButton->BringToFront();
		}

//Pre-condition : None 
// To display the components of column Help
private: void unDisplayHelp (){
		introductionDisplay->Visible = false;
		commandsDisplay->Visible = false;
		undoButton->Visible = false;
		redoButton->Visible = false;
		helpDisplayed = false;
		}

// To display Help column when mouse enter
private: System::Void helpButton_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 if(showDisplayed == true){
				 unDisplayShow();
			 }
			 if (helpDisplayed == false){
				 displayHelp();
			 }

		 }

// To display & undisplay the Help column when mouse click
private: System::Void helpButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(showDisplayed == true){
				 unDisplayShow();
			 }
			 if (helpDisplayed == false){
				 displayHelp();
			 } else{
				 unDisplayHelp();
			 }
		 }


private: System::Void MapleSyrup_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			initializeAndUndisplayAll(); 
		 }



// Display Calender
private: System::Void calenderTop_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			if(topCalenderDisplayed == true){
				 calenderTop->Visible = false;
				 topCalenderDisplayed = false;
			 }
			 
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

private: System::Void dayDisplay_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void weekDisplay_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void monthDisplay_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void allDisplay_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void archiveDisplay_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void introductionDisplay_Click(System::Object^  sender, System::EventArgs^  e) {
			SetCurrentDirectoryA("D:\\NUS\\CS2103\\Team\\V0.0");
			Process::Start("[f11-2c][V0.0].pdf");

		 }
private: System::Void commandsDisplay_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void undoButton_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void redoButton_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void display_Click(System::Object^  sender, System::EventArgs^  e) {
		 }

};
}
