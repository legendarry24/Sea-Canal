#include "SeaCanal.h"

using namespace System;
using namespace System::Windows::Forms;

[MTAThreadAttribute]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	WinFormsC::SeaCanal form;
	Application::Run(%form);
}