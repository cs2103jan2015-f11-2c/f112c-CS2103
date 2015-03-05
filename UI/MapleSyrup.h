#pragma once
#include <iostream>

#include <msclr\marshal_cppstd.h>

#include "GuideInfor.h"
#include "Logic.h"

namespace UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MapleSyrup
	/// </summary>
	public ref class MapleSyrup : public System::Windows::Forms::Form
	{
	public:
		GuideInfor* gI;

		Logic* lG;
		MapleSyrup(void)
		{
			InitializeComponent();
		
			//Create logic object here
			//
			//TODO: Add the constructor code here

			//Initialization
			gI = new GuideInfor;

			lG = new Logic;
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

	private: System::Windows::Forms::RichTextBox^  feedbackBox;
	private: System::Windows::Forms::TextBox^  searchBox;
	private: System::Windows::Forms::RichTextBox^  display;
	private: System::Windows::Forms::RichTextBox^  floatingTasksDisplay;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::TextBox^  dateDisplay;



	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Button^  helpButton;


	private: System::Windows::Forms::PictureBox^  comdIcon;
	private: System::Windows::Forms::PictureBox^  pictureBox3;

	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::Button^  dayDisplay;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::Button^  weekDisplay;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::Button^  monthDisplay;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::Button^  allDisplay;
	private: System::Windows::Forms::Button^  archiveDisplay;

	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  floatingIcon;
	private: System::Windows::Forms::PictureBox^  pictureBox8;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::PictureBox^  searchIcon;
	private: System::Windows::Forms::Button^  undoButton;
	private: System::Windows::Forms::TextBox^  commandBox;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::ListBox^  suggestBar;

	private: System::Windows::Forms::FontDialog^  fontDialog1;
	private: System::Windows::Forms::Button^  Redo;

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
			this->dateDisplay = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->helpButton = (gcnew System::Windows::Forms::Button());
			this->comdIcon = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->dayDisplay = (gcnew System::Windows::Forms::Button());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->weekDisplay = (gcnew System::Windows::Forms::Button());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->monthDisplay = (gcnew System::Windows::Forms::Button());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->allDisplay = (gcnew System::Windows::Forms::Button());
			this->archiveDisplay = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->floatingIcon = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->searchIcon = (gcnew System::Windows::Forms::PictureBox());
			this->undoButton = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->suggestBar = (gcnew System::Windows::Forms::ListBox());
			this->fontDialog1 = (gcnew System::Windows::Forms::FontDialog());
			this->Redo = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->comdIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox7))->BeginInit();
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
			// dateDisplay
			// 
			this->dateDisplay->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->dateDisplay->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dateDisplay->Cursor = System::Windows::Forms::Cursors::SizeAll;
			resources->ApplyResources(this->dateDisplay, L"dateDisplay");
			this->dateDisplay->ForeColor = System::Drawing::Color::Black;
			this->dateDisplay->Name = L"dateDisplay";
			this->dateDisplay->ReadOnly = true;
			this->dateDisplay->TabStop = false;
			this->toolTip1->SetToolTip(this->dateDisplay, resources->GetString(L"dateDisplay.ToolTip"));
			// 
			// pictureBox2
			// 
			resources->ApplyResources(this->pictureBox2, L"pictureBox2");
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->TabStop = false;
			// 
			// helpButton
			// 
			resources->ApplyResources(this->helpButton, L"helpButton");
			this->helpButton->Name = L"helpButton";
			this->toolTip1->SetToolTip(this->helpButton, resources->GetString(L"helpButton.ToolTip"));
			this->helpButton->UseVisualStyleBackColor = true;
			this->helpButton->Click += gcnew System::EventHandler(this, &MapleSyrup::helpButton_Click);
			// 
			// comdIcon
			// 
			resources->ApplyResources(this->comdIcon, L"comdIcon");
			this->comdIcon->Name = L"comdIcon";
			this->comdIcon->TabStop = false;
			this->toolTip1->SetToolTip(this->comdIcon, resources->GetString(L"comdIcon.ToolTip"));
			// 
			// pictureBox3
			// 
			resources->ApplyResources(this->pictureBox3, L"pictureBox3");
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->TabStop = false;
			this->toolTip1->SetToolTip(this->pictureBox3, resources->GetString(L"pictureBox3.ToolTip"));
			// 
			// pictureBox4
			// 
			resources->ApplyResources(this->pictureBox4, L"pictureBox4");
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->TabStop = false;
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
			// 
			// pictureBox6
			// 
			resources->ApplyResources(this->pictureBox6, L"pictureBox6");
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->TabStop = false;
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
			// 
			// pictureBox5
			// 
			resources->ApplyResources(this->pictureBox5, L"pictureBox5");
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->TabStop = false;
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
			// 
			// pictureBox7
			// 
			resources->ApplyResources(this->pictureBox7, L"pictureBox7");
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->TabStop = false;
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
			this->undoButton->BackColor = System::Drawing::Color::White;
			resources->ApplyResources(this->undoButton, L"undoButton");
			this->undoButton->Name = L"undoButton";
			this->toolTip1->SetToolTip(this->undoButton, resources->GetString(L"undoButton.ToolTip"));
			this->undoButton->UseVisualStyleBackColor = false;
			// 
			// suggestBar
			// 
			this->suggestBar->BackColor = System::Drawing::Color::White;
			this->suggestBar->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			resources->ApplyResources(this->suggestBar, L"suggestBar");
			this->suggestBar->Name = L"suggestBar";
			this->suggestBar->TabStop = false;
			// 
			// Redo
			// 
			this->Redo->BackColor = System::Drawing::Color::White;
			resources->ApplyResources(this->Redo, L"Redo");
			this->Redo->Name = L"Redo";
			this->toolTip1->SetToolTip(this->Redo, resources->GetString(L"Redo.ToolTip"));
			this->Redo->UseVisualStyleBackColor = false;
			// 
			// MapleSyrup
			// 
			this->AllowDrop = true;
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->Controls->Add(this->Redo);
			this->Controls->Add(this->suggestBar);
			this->Controls->Add(this->undoButton);
			this->Controls->Add(this->searchIcon);
			this->Controls->Add(this->pictureBox8);
			this->Controls->Add(this->floatingIcon);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->comdIcon);
			this->Controls->Add(this->helpButton);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->dateDisplay);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->floatingTasksDisplay);
			this->Controls->Add(this->display);
			this->Controls->Add(this->searchBox);
			this->Controls->Add(this->feedbackBox);
			this->Controls->Add(this->commandBox);
			this->Controls->Add(this->weekDisplay);
			this->Controls->Add(this->monthDisplay);
			this->Controls->Add(this->allDisplay);
			this->Controls->Add(this->archiveDisplay);
			this->Controls->Add(this->pictureBox7);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->dayDisplay);
			this->ForeColor = System::Drawing::Color::Black;
			this->HelpButton = true;
			this->KeyPreview = true;
			this->Name = L"MapleSyrup";
			this->ShowIcon = false;
			this->Load += gcnew System::EventHandler(this, &MapleSyrup::MapleSyrup_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MapleSyrup::MapleSyrup_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->comdIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->floatingIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchIcon))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

// Programmer Code

#pragma endregion

public: std::string convertTostd(String^ sysStr){
			std::string newString = msclr::interop::marshal_as<std::string>(sysStr);
			return newString;
		}

public: String^ convertToSys(std::string stdStr){
			String^ newString = gcnew String(stdStr.c_str());
			Console::WriteLine(newString);
			return newString;
		}

public: std::string lowerCase(std::string word){
	for (int i=0;i<word.size();i++){
		 word[i] = tolower(word[i]);
	 }
	return word;
 }

private: System::Void MapleSyrup_Load(System::Object^  sender, System::EventArgs^  e) {
			DateTime current = DateTime::Now;
			dateDisplay->Text = current.ToString(" dd  MMM  yyyy ,  dddd");
}

		 
private: System::Void commandBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 // Test code
			 if (e->KeyCode == Keys::Enter){
				 String^ temp = commandBox->Text;
				 std::string input = convertTostd(temp);

				 commandBox->Text = "";
				 
				 suggestBar->Visible = false;
				 suggestBar->Items->Clear();

				 vector<Event> displayEvent = lG->executeUserInput(input);
				 String^ feedbackToUser = convertToSys( displayEvent[0].getFeedback() );
				 feedbackBox->Text = feedbackToUser;

				 /*
				 if (feedbackToUser == "exit"){
				
				 if (temp == "exit"){
					 Application::Exit();
				 }

				 if (temp == "help"){
					 System::Object^ sender;
					 EventArgs^ e;
					 helpButton_Click(sender,e);
				 }
				 */
				 
			 }
		 }

private: System::Void MapleSyrup_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == Keys::F1){
				 commandBox->Select();
			 }

			 if (e->KeyCode == Keys::F2){
				 searchBox->Select();
			 }

			 if (e->KeyCode == Keys::F3){
				 display->Select();
			 }
		 }

private: System::Void commandBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 std::string temp = convertTostd(commandBox->Text);
			 std::string tempCommand = lowerCase(temp);
		 
			 
			 //Add
			 if (tempCommand == gI->getCommandAdd() ){
				suggestBar->Visible = true;
				suggestBar->Items->Clear();

				for (int i=0; i<gI->getSuggestionAddArrarySize();i++){
					std::string temp = gI->getSuggestionAdd(i);
					String^ toAdd = convertToSys(temp);
					
					suggestBar->Items->Add(toAdd);
				}
			 }

			 //For undisplaying purpose 
			 if (commandBox->Text == "ad"){
				 suggestBar->Visible = false;
			 }

			 if (tempCommand == gI->getCommandDelete()){
				suggestBar->Visible = true;
				suggestBar->Items->Clear();

				for (int i=0; i<gI->getSuggestionDeleteArrarySize();i++){
					std::string temp = gI->getSuggestionDelete(i);
					String^ toAdd = convertToSys(temp);
					
					suggestBar->Items->Add(toAdd);
				}
			 }

			 //Delete
			 if (tempCommand == gI->getCommandDelete()){
				suggestBar->Visible = true;
				suggestBar->Items->Clear();

				for (int i=0; i<gI->getSuggestionDeleteArrarySize();i++){
					std::string temp = gI->getSuggestionDelete(i);
					String^ toAdd = convertToSys(temp);

					suggestBar->Items->Add(toAdd);
				}
			 }

			 //For undisplaying purpose 
			 if (commandBox->Text == "delet"){
				 suggestBar->Visible = false;
			 }

			 //Edit
			 if (tempCommand == gI->getCommandEdit()){
				suggestBar->Visible = true;
				suggestBar->Items->Clear();

				for (int i=0; i<gI->getSuggestionEditArrarySize();i++){
					std::string temp = gI->getSuggestionEdit(i);
					String^ toAdd = convertToSys(temp);

					suggestBar->Items->Add(toAdd);
				}
			 }

			 //For undisplaying purpose 
			 if (commandBox->Text == "edi"){
				 suggestBar->Visible = false;
			 }

			 //Search
			 if (tempCommand == gI->getCommandSearch()){
				suggestBar->Visible = true;
				suggestBar->Items->Clear();

				for (int i=0; i<gI->getSuggestionSearchArrarySize();i++){
					std::string temp = gI->getSuggestionSearch(i);
					String^ toAdd = convertToSys(temp);

					suggestBar->Items->Add(toAdd);
				}
			 }

			 //For undisplaying purpose 
			 if (commandBox->Text == "searc"){
				 suggestBar->Visible = false;
			 }

			 //Show
			 if (tempCommand == gI->getCommandShow()){
				suggestBar->Visible = true;
				suggestBar->Items->Clear();

				for (int i=0; i<gI->getSuggestionShowArrarySize();i++){
					std::string temp = gI->getSuggestionShow(i);
					String^ toAdd = convertToSys(temp);

					suggestBar->Items->Add(toAdd);
				}
			 }

			 //Special case for Show ( 3 lines)
			 if (tempCommand == "sho"){
				 suggestBar->Visible = false;
			 }

			 //Close bar
			 if (commandBox->Text ==""){
				suggestBar->Visible = false;
				suggestBar->Items->Clear();
			 }
			 
			 
		 }

public: System::Void helpButton_Click(System::Object^  sender, System::EventArgs^  e) {
			display->SelectionFont = gcnew Drawing::Font(display->SelectionFont->FontFamily,11,FontStyle::Bold);
			std::string helpIntro = gI->getHelpIntro();
			display->SelectedText = convertToSys(helpIntro);

			display->SelectionFont = gcnew Drawing::Font(display->SelectionFont->FontFamily,10,FontStyle::Underline);
			display->SelectionColor = Color::Blue;
			std::string helpAdd1 = gI->getCommandAdd() + ": \n";
			display->SelectedText = convertToSys(helpAdd1);

			display->SelectionFont = gcnew Drawing::Font(display->SelectionFont->FontFamily,8,FontStyle::Regular);
			display->SelectionColor = Color::Blue;
			std::string helpAdd2 = gI->getHelpAdd();
			display->SelectedText = convertToSys(helpAdd2);

			display->SelectedText = "\n";

			display->SelectionFont = gcnew Drawing::Font(display->SelectionFont->FontFamily,10,FontStyle::Underline);
			display->SelectionColor = Color::Black;
			std::string helpDel1 = gI->getCommandDelete() + ": \n";
			display->SelectedText = convertToSys(helpDel1);

			display->SelectionFont = gcnew Drawing::Font(display->SelectionFont->FontFamily,8,FontStyle::Regular);
			display->SelectionColor = Color::Black;
			std::string helpDel2 = gI->getHelpDelete();
			display->SelectedText = convertToSys(helpDel2);

		
		 }
};
}
