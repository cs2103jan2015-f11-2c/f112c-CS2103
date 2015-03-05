#include "MapleSyrup.h"
#include <string>
#include <iostream>

using namespace System; 
using namespace System::Windows::Forms;

[STAThread] 
void main(array<String^>^ args) { 
	Application::EnableVisualStyles(); 
	Application::SetCompatibleTextRenderingDefault(false);

	UI::MapleSyrup mainWindow; 
	Application::Run(%mainWindow); 
}
